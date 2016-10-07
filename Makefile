bin/BrushWork: obj/main.o obj/base_gfx_app.o obj/brushwork_app.o obj/color_data.o obj/pixel_buffer.o
	gcc -o bin/BrushWork obj/main.o obj/base_gfx_app.o obj/brushwork_app.o obj/color_data.o obj/pixel_buffer.o

obj/main.o: obj/brushwork_app.o obj/color_data.o src/main.cc
	gcc -o obj/main.o src/main.cc

obj/base_gfx_app.o:
