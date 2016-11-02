# nosuspend
A little command-line tool for systems using systemd.

nosuspend blocks computer suspend while another command-line operation is running.

To use, simply run before another command as in: nosuspend appname -parameter for appname

nosuspend sets the systemd-inhibit flag with UID 0/root.
