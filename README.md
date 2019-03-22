# nosuspend A little command-line tool for systems using systemd.

`nosuspend` allows users to avoid suspend or shutdown even on privileged level
(e.g. root) when a running user process shouldn't be interrupted.

To accomplish this, `nosuspend` sets the systemd-inhibit flag with UID 0/root in
order to block computer suspend while another command-line operation is running.

## warning

This program could install a PolKit rule allowing active users to run
`systemd-inhibit` with the UID 0/root flag and without a password.  The default
setting requires a password.

## dependencies

nosuspend needs the commandline tool `screen` to be installed

## installation

1. clone the repo
2. `cd nosuspend`

Multiple options for the next step:

3A. most secure build: `make secure` (or just `make`, which does the same by
    default)

This will build with a policy file which requires you to enter root passphrase
to use nosupend.

3B. operate without passphrase (less strictly secure): `make relaxed`

This will build with a policy file which allows nosuspend to run without asking
for a root passphrase.

4. run `sudo make install` to install nosuspend to the system

## uninstall

To uninstall nosuspend, cd to the nosuspend directory and run:

`sudo make uninstall`

## how to use

To use nosuspend, simply run before another command as in:
`nosuspend appname -parameter for appname`

Full bash completion is supported for easy command substitution.

Note: when a suspend signal is sent while nosuspend is functioning, a dialog may
appear saying something like "Authentication is required for suspending the
system while an application asked to inhibit it." That dialog may ask for a root
passphrase. Entering the passphrase and clicking "OK" should allow the suspend
to go ahead, overriding nosuspend. Ignoring, closing, or canceling the dialog
will let nosuspend continue in blocking suspension.
