
Debian
====================
This directory contains files used to package solarid/solari-qt
for Debian-based Linux systems. If you compile solarid/solari-qt yourself, there are some useful files here.

## solari: URI support ##


solari-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install solari-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your solari-qt binary to `/usr/bin`
and the `../../share/pixmaps/solari128.png` to `/usr/share/pixmaps`

solari-qt.protocol (KDE)

