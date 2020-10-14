all: apps

libs/ilclient/libilclient.a:
	$(MAKE) -C libs/ilclient

libs/vgfont/libvgfont.a:
	$(MAKE) -C libs/vgfont

libs/revision/librevision.a:
	$(MAKE) -C libs/revision

apps: libs/ilclient/libilclient.a libs/vgfont/libvgfont.a libs/revision/librevision.a
	$(MAKE) -C hello_world
	$(MAKE) -C hello_triangle
	$(MAKE) -C hello_triangle2
	$(MAKE) -C hello_video
	$(MAKE) -C hello_audio
	$(MAKE) -C hello_font
	$(MAKE) -C hello_dispmanx
	$(MAKE) -C hello_tiger
	$(MAKE) -C hello_encode
	$(MAKE) -C hello_jpeg
	$(MAKE) -C hello_videocube
	$(MAKE) -C hello_teapot
	$(MAKE) -C hello_fft
	$(MAKE) -C hello_mmal_encode

clean:
	$(MAKE) -C libs/ilclient clean
	$(MAKE) -C libs/vgfont clean
	$(MAKE) -C libs/revision clean
	$(MAKE) -C hello_world clean
	$(MAKE) -C hello_triangle clean
	$(MAKE) -C hello_triangle2 clean
	$(MAKE) -C hello_video clean
	$(MAKE) -C hello_audio clean
	$(MAKE) -C hello_font clean
	$(MAKE) -C hello_dispmanx clean
	$(MAKE) -C hello_tiger clean
	$(MAKE) -C hello_encode clean
	$(MAKE) -C hello_jpeg clean
	$(MAKE) -C hello_videocube clean
	$(MAKE) -C hello_teapot clean
	$(MAKE) -C hello_fft clean
	$(MAKE) -C hello_mmal_encode clean

