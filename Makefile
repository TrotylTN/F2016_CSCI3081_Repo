CMP = g++ -I. -c -std=c++11
CMPLIB = g++ -I./ext/glui/include -I. -c -std=c++11

bin/BrushWork: obj/main.o obj/base_gfx_app.o obj/brushwork_app.o obj/color_data.o obj/pixel_buffer.o | bin
	cd ext/glui && make
	g++ -L./ext/glui/lib -o bin/BrushWork obj/main.o obj/base_gfx_app.o obj/brushwork_app.o obj/color_data.o obj/pixel_buffer.o obj/tool.o -std=c++11 -lglut -lGL -lGLU -lglui

obj/main.o: obj/brushwork_app.o obj/color_data.o src/main.cc | obj
	$(CMPLIB) -o obj/main.o src/main.cc

obj/base_gfx_app.o: src/base_gfx_app.cc | obj
	$(CMPLIB) -o obj/base_gfx_app.o src/base_gfx_app.cc

obj/brushwork_app.o: obj/tool.o obj/color_data.o obj/pixel_buffer.o obj/base_gfx_app.o src/brushwork_app.cc | obj
	$(CMPLIB) -o obj/brushwork_app.o src/brushwork_app.cc

obj/color_data.o: src/color_data.cc | obj
	$(CMP) -o obj/color_data.o src/color_data.cc

obj/pixel_buffer.o: obj/color_data.o src/pixel_buffer.cc | obj
	$(CMP) -o obj/pixel_buffer.o src/pixel_buffer.cc

obj/tool.o: src/tool.cc | obj
	$(CMPLIB) -o obj/tool.o src/tool.cc

bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	rm -rf ./bin ./obj
	cd ext/glui && make clean
