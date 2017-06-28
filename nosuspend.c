#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <spawn.h>

 /*   gcc -o nosuspend nosuspend.c        */
 /*   chown -v root:root ./nosuspend    */
 /*   chmod -v 4755 ./nosuspend         */

extern char **environ;

void show_help(char* arg) {
    fprintf(stderr, 
    "nosuspend blocks computer suspend while another "
    "command-line operation is running\n"
    "Usage: %s  executable arg arg2 . . \n", arg);
}

void run_cmd(char *cmd)
{
    pid_t pid;
    char *arg[] = {"sh", "-c", cmd, NULL};
    int status;
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, arg, environ);
    if (status == 0) {
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
        }
    } else {
        fprintf(stderr,"posix_spawn: %s\n", strerror(status));
    }
}

void create_cmd_line(char* cmd, int argc,char* argv[], int sc) {
    char uname[100] = "\0";
    if (getlogin_r(uname,100)) {
        fprintf(stderr, "Fail to get user name, exit here\n");
        exit(1);
        }
    
    const char* cmd1 = "pkexec /bin/systemd-inhibit --why='User application run' su ";
    const char* cmd2 = " -c '";
    strcat(cmd, cmd1);
    strcat(cmd,uname);
    strcat(cmd, cmd2);
    if (sc) strcat(cmd, "screen ");
    for (int i = 1; i < argc; ++i) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }
    strcat(cmd, " '");
    //fprintf(stderr," cmd = %s", cmd);
}

char* check_for_gui_libs(char *p, char* argv[]) {
    char cmdp[100] = "\0";
    strcat(cmdp,"which ");
    strcat(cmdp,argv[1]);
    strcat(cmdp,"|xargs ldd | grep -E 'libgtk*|libqt*|*fltk*'");
    FILE *fp = popen(cmdp, "r");
    if (!fp) {
        return 0;
    }
    char fpf[1024] = "\0";
    if( fgets (fpf, sizeof(fpf), fp)!=NULL ) {
        p = fgets(fpf, sizeof(fpf), fp);  
    }
    pclose(fp);
    return p;
}

int check_user_input(int argc,char* argv[]){
   // fprintf(stderr," argc = %i", argc);
    if (strlen(argv[1]) > 45) {
        fprintf(stderr, "first arg is to long my friend \n");
        return 1;
    }
    
    int bz = 0;
    int bzgo = 0;
    const char nogo[] = "&;|$><`\\!";
    char *ret = NULL;
    for (int i = 0; i < argc; ++i) {
       // fprintf(stderr," argv = %s", argv[i]);
        bz += strlen(argv[i]);
        bzgo +=strspn(argv[i],". ABCDEFGHIJKLMNOPQRSTUVWXYZÄÜÖabcdefghijklmnopqrstuvwxyzäüöß0123456789_/'-?*~:%");
        ret = strpbrk(argv[i],nogo);
        if (bz>4000) {
            fprintf(stderr, "arg list is to long my friend \n");
            return 1;
        }
        if (ret) {
            fprintf(stderr, "arg (& ; | $ > < ` \\ ! ) is not allowed \n");
            return 1;
        }
        if (bz != bzgo) {
            fprintf(stderr, "arg contain not allowed chars \n");
            return 1;
        }
    }
    return 0;
}

int main(int argc,char* argv[]){

    if ((strcmp(argv[1], "-h") == 0) ||(strcmp(argv[1], "--help")== 0)) {
        show_help(argv[0]);
        return 0;
    } else if(argc<2) {
        show_help(argv[0]);
        return 0;
    }
    
    if (system("which screen 2>&1 >/dev/null")!=0) {
        fprintf(stderr, "couldn't find 'screen', please install it to use nosuspend\n");
        exit(1);
    }

    if (check_user_input(argc, argv)) exit(1);

    char cmd[5000] = "\0";

    char *p = "";
    p = check_for_gui_libs(p, argv);

    if (*p == 0) {
        create_cmd_line(cmd, argc, argv, 1);
        run_cmd(cmd);
        sleep(1);
    } else {
        create_cmd_line(cmd, argc, argv, 0);
        run_cmd(cmd);
        exit(0);
    }
    return 0;
}
