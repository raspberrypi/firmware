#!/usr/bin/sh
tar -cf firmware.bin			\
	*.elf				\
	*.dat				\
	*.dtb				\
	*.img				\
	COPYING.*			\
	LICENCE.*			\
	overlays/*.dtb			\
	overlays/README
gcab --create rpi-firmware-`date +"%Y%m%d"`.cab	\
	firmware.bin			\
	LICENCE.*			\
	firmware.inf			\
	firmware.metainfo.xml
