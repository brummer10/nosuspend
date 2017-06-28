# nosuspend
A little command-line tool for systems using systemd.

nosuspend sets the systemd-inhibit flag with UID 0/root in order to block
computer suspend while another command-line operation is running.

## warning

This program could install a PolKit rule which allow active users to run 
`systemd-inhibit` with the UID 0/root flag without password.
The default setting is with password.

## why

To allow users to avoid suspend or shutdown even on privileged level (e.g. root) 
when a running user process shouldn't be interrupted.
In addition nosuspend provide bash completion for easily comand substitution.

## dependencies

nosuspend needs the commandline tool `screen` to be installed

## installation

just clone the repo, `cd nosuspend`, 

you could build in to different fashions, 

`make secure` or `make`

will build with a policy file which requiers you to enter root passphrase
to use nosupend.
This is the default.

`make relaxed`

will build with a policy file witch allow the use without root passphrase

then `sudo make install`

## how to use

To use nosuspend, simply run before another command as in:
`nosuspend appname -parameter for appname`

Note: when a suspend signal is sent while nosuspend is functioning, a dialog may
appear saying something like "Authentication is required for suspending the
system while an application asked to inhibit it." That dialog may ask for a root
passphrase. Entering the passphrase and clicking "OK" should allow the suspend
to go ahead, overriding nosuspend. Ignoring, closing, or canceling the dialog
will let nosuspend continue in blocking suspension.
