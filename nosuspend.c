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

int main(int argc,char* argv[]){

    if ((strcmp(argv[1], "-h") == 0) ||(strcmp(argv[1], "--help")== 0)) {
        show_help(argv[0]);
        return 0;
    } else if(argc<2) {
        show_help(argv[0]);
        return 0;
    }

    int status;
    char uname[100];
    getlogin_r(uname,100);
    char cmd[5000];
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
    
    if(strstr(argv[1], "jack") != NULL) {
        setuid(0);
        status = system(cmd);
        sleep(1);
        //execlp("/bin/sh","/bin/sh","-c",cmd,NULL);

    } else if(fork() == 0) {
        setuid(0);
        status = system(cmd);
        //execlp("/bin/sh","/bin/sh","-c",cmd,NULL);
        exit(0);
    }
    return 0;
}
