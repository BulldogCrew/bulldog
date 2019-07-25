
Debian
====================
This directory contains files used to package bulldogd/bulldog-qt
for Debian-based Linux systems. If you compile bulldogd/bulldog-qt yourself, there are some useful files here.

## bulldog: URI support ##


bulldog-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bulldog-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bulldogqt binary to `/usr/bin`
and the `../../share/pixmaps/bulldog128.png` to `/usr/share/pixmaps`

bulldog-qt.protocol (KDE)

