# nosuspend
A little command-line tool for systems using systemd.

nosuspend sets the systemd-inhibit flag with UID 0/root in order to block
computer suspend while another command-line operation is running.

## warning

This program use setuid() and system(), 
I try to keep it as save as possible, 
but it may still be used for command injection vulnerability.
So, be warned before you clone and use it. 

## dependencies

nosuspend needs the commandline tool `screen` to be installed

## installation

just clone the repo, `cd nosuspend`, then `sudo make install`

## how to use

To use nosuspend, simply run before another command as in:
`nosuspend appname -parameter for appname`

Note: when a suspend signal is sent while nosuspend is functioning, a dialog may
appear saying something like "Authentication is required for suspending the
system while an application asked to inhibit it." That dialog may ask for a root
passphrase. Entering the passphrase and clicking "OK" should allow the suspend
to go ahead, overriding nosuspend. Ignoring, closing, or canceling the dialog
will let nosuspend continue in blocking suspension.
