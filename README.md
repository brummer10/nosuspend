# nosuspend
A little command-line tool for systems using systemd.

nosuspend sets the systemd-inhibit flag with UID 0/root in order to block
computer suspend while another command-line operation is running.

## dependencys

nosuspend needs the commanline tool screen to be installed

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
