#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

 /*   gcc -o nosuspend nosuspend.c        */
 /*   chown -v root:root ./nosuspend    */
 /*   chmod -v 4755 ./nosuspend         */

void show_help(char* arg) {
    fprintf(stderr, 
    "nosuspend blocks computer suspend while another "
    "command-line operation is running\n"
    "Usage: %s  executable arg arg2 . . \n", arg);
}

void create_cmd_line(char* cmd, int argc,char* argv[]) {
    char uname[100];
    getlogin_r(uname,100);
    const char* cmd1 = "systemd-inhibit --why='User application run' su ";
    const char* cmd2 = " -c '";
    strcat(cmd, cmd1);
    strcat(cmd,uname);
    strcat(cmd, cmd2);
    for (int i = 1; i < argc; ++i) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }
    strcat(cmd, " '");
}

void create_cmd_line_with_screen(char* cmd, int argc,char* argv[]) {
    char uname[100];
    getlogin_r(uname,100);
    const char* cmd1 = "systemd-inhibit --why='User application run' su ";
    const char* cmd2 = " -c '";
    strcat(cmd, cmd1);
    strcat(cmd,uname);
    strcat(cmd, cmd2);
    strcat(cmd, "screen ");
    for (int i = 1; i < argc; ++i) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }
    strcat(cmd, " '");
}

char* check_for_gui_libs(char *p, char* argv[]) {
    char cmdp[100];
    strcat(cmdp,"which ");
    strcat(cmdp,argv[1]);
    strcat(cmdp,"|xargs ldd | grep -E 'libgtk*|libqt*|*fltk*'");
    FILE *fp = popen(cmdp, "r");
    if (!fp) {
        return 0;
    }
    char fpf[1024];
    if( fgets (fpf, sizeof(fpf), fp)!=NULL ) {
        p = fgets(fpf, sizeof(fpf), fp);  
    }
    pclose(fp);
    return p;
}

int main(int argc,char* argv[]){

    if ((strcmp(argv[1], "-h") == 0) ||(strcmp(argv[1], "--help")== 0)) {
        show_help(argv[0]);
        return 0;
    } else if(argc<2) {
        show_help(argv[0]);
        return 0;
    }

    char cmd[5000];

    char *p = "";
    p = check_for_gui_libs(p, argv);

    if (*p == 0) {
        create_cmd_line_with_screen(cmd, argc, argv);
        setuid(0);
        system(cmd);
        //execlp("/bin/sh","/bin/sh","-c",cmd,NULL);
        sleep(1);
    } else if(fork() == 0) {
        create_cmd_line(cmd, argc, argv);
        setuid(0);
        system(cmd);
        //execlp("/bin/sh","/bin/sh","-c",cmd,NULL);
        exit(0);
    }
    return 0;
}
