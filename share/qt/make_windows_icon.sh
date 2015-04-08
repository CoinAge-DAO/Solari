#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/solari.png
ICON_DST=../../src/qt/res/icons/solari.ico
convert ${ICON_SRC} -resize 16x16 solari-16.png
convert ${ICON_SRC} -resize 32x32 solari-32.png
convert ${ICON_SRC} -resize 48x48 solari-48.png
convert solari-16.png solari-32.png solari-48.png ${ICON_DST}

