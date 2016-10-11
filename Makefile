CMP = g++ -I. -c -std=c++11
CMPLIB = g++ -I./ext/glui/include -I. -c -std=c++11

LINKOBJ += obj/main.o
LINKOBJ += obj/base_gfx_app.o
LINKOBJ += obj/brushwork_app.o
LINKOBJ += obj/color_data.o
LINKOBJ += obj/pixel_buffer.o
LINKOBJ += obj/tool.o
LINKOBJ += obj/pen.o
LINKOBJ += obj/eraser.o
LINKOBJ += obj/spray_can.o
LINKOBJ += obj/calligraphy_pen.o
LINKOBJ += obj/highlighter.o
LINKOBJ += obj/crayon.o

bin/BrushWork: $(LINKOBJ) | bin
	cd ext/glui && make
	g++ -L./ext/glui/lib -o bin/BrushWork $(LINKOBJ) -std=c++11 -lglut -lGL -lGLU -lglui

obj/main.o: obj/brushwork_app.o obj/color_data.o src/main.cc | obj
	$(CMPLIB) -o obj/main.o src/main.cc

obj/base_gfx_app.o: src/base_gfx_app.cc | obj
	$(CMPLIB) -o obj/base_gfx_app.o src/base_gfx_app.cc

obj/brushwork_app.o: obj/pen.o obj/eraser.o obj/spray_can.o obj/calligraphy_pen.o obj/highlighter.o obj/crayon.o obj/color_data.o obj/pixel_buffer.o obj/base_gfx_app.o src/brushwork_app.cc | obj
	$(CMPLIB) -o obj/brushwork_app.o src/brushwork_app.cc

obj/color_data.o: src/color_data.cc | obj
	$(CMP) -o obj/color_data.o src/color_data.cc

obj/pixel_buffer.o: obj/color_data.o src/pixel_buffer.cc | obj
	$(CMP) -o obj/pixel_buffer.o src/pixel_buffer.cc

obj/tool.o: obj/pixel_buffer.o obj/color_data.o src/tool.cc | obj
	$(CMP) -o obj/tool.o src/tool.cc

obj/pen.o: obj/tool.o src/pen.cc | obj
	$(CMP) -o obj/pen.o src/pen.cc

obj/eraser.o: obj/tool.o src/eraser.cc | obj
	$(CMP) -o obj/eraser.o src/eraser.cc

obj/spray_can.o: obj/tool.o src/spray_can.cc | obj
	$(CMP) -o obj/spray_can.o src/spray_can.cc

obj/calligraphy_pen.o: obj/tool.o src/calligraphy_pen.cc | obj
	$(CMP) -o obj/calligraphy_pen.o src/calligraphy_pen.cc

obj/highlighter.o: obj/tool.o src/highlighter.cc | obj
	$(CMP) -o obj/highlighter.o src/highlighter.cc

obj/crayon.o: obj/tool.o src/crayon.cc | obj
	$(CMP) -o obj/crayon.o src/crayon.cc

bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	rm -rf ./bin ./obj
	cd ext/glui && make clean
