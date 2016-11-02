#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

 /*   gcc -o nosuspend nosuspend.c        */
 /*   chown -v root:root ./nosuspend    */
 /*   chmod -v 4755 ./nosuspend         */

int main(int argc,char* argv[]){
    if(argc<2) return 0;
    if(fork() == 0){
        int status;
        char uname[100];
        getlogin_r(uname,100);
        char cmd[5000];
        const char* cmd1 = "systemd-inhibit --why='User application run' su ";
        const char* cmd2 = " -c '";
        strcat(cmd, cmd1);
        strcat(cmd,uname);
        strcat(cmd, cmd2);
        for (int i = 1; i < argc; ++i)
        {
            strcat(cmd, argv[i]);
            strcat(cmd, " ");
        }
        strcat(cmd, " '");
        setuid(0);
        status = system(cmd);
        exit(0);
    }
    return 0;
}
