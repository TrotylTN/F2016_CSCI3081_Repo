bin/BrushWork: obj/main.o obj/base_gfx_app.o obj/brushwork_app.o obj/color_data.o obj/pixel_buffer.o | bin
	cd ext/glui && make
	g++ -L./ext/glui/lib -o bin/BrushWork obj/main.o obj/base_gfx_app.o obj/brushwork_app.o obj/color_data.o obj/pixel_buffer.o -std=c++11 -lglut -lGL -lGLU -lglui

obj/main.o: obj/brushwork_app.o obj/color_data.o src/main.cc | obj
	g++ -I./ext/glui/include -I. -c -o obj/main.o src/main.cc -std=c++11

obj/base_gfx_app.o: src/base_gfx_app.cc | obj
	g++ -I./ext/glui/include -I. -c -o obj/base_gfx_app.o src/base_gfx_app.cc -std=c++11

obj/brushwork_app.o: obj/color_data.o obj/pixel_buffer.o obj/base_gfx_app.o src/brushwork_app.cc | obj
	g++ -I./ext/glui/include -I. -c -o obj/brushwork_app.o src/brushwork_app.cc -std=c++11

obj/color_data.o: src/color_data.cc | obj
	g++ -I. -c -o obj/color_data.o src/color_data.cc -std=c++11

obj/pixel_buffer.o: obj/color_data.o src/pixel_buffer.cc | obj
	g++ -I. -c -o obj/pixel_buffer.o src/pixel_buffer.cc -std=c++11

bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	rm -rf ./bin ./obj
	cd ext/glui && make clean
