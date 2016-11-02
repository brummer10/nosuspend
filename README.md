# nosuspend
A little command-line tool to avoid computer suspend as long a app is running
It requires systemd running.

Usage is simply: nosuspend appname -parameter for appname

nosuspend set the systemd-inhibit flag with UID 0/root.
