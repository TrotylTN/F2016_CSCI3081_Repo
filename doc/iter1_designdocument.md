# Design Justifications for BrushWork
#### Group Name:
Group A1

#### Members:
- Tiannan Zhou
- Zhangjun Xu
- Yu Xian Ang

#### Instructions
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.


## 1  Design Question One
> This iteration of the project is all about tools. Naturally, a key design decision is how these tools are represented. Each tool has several characteristics, including the shape of the tool, its size, and the way it blends with the canvas when the tool is applied. Some tools share characteristics with other tools, such as how the pen and calligraphy pen tools blend with the canvas in the same manner.
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
In our final software design, we decided to use an abstract base class and subclasses as the tools. The main idea of this design is the tools have the same attributes, which are color, size and mask, only their values are different. For example, spray can has larger coverage but pen is smaller. Figure 1 is a UML diagram illustrates our design for the tools.

###### Figure 1: UML diagram
![UML Diagram][UMLDiagram]

To implement this design in C++, we first implement the abstract base class called Tool, which is shown in Figure 2.

<Figure 2: Tool header code>

Notice in Figure 2, the Tool class included all the attributes and functions a tool needs. Also notice that draw_mask and set_color is virtual because some subclasses have different way to implement it. The value of attributes, which are mask_, mask_len_, mask_radius_ and color_, is deferred to the constructors in respective subclasses of Tool. Besides, instead of putting the drawing function in BrushWorkApp, we put our drawing function inside Tool class because not all tools have the same algorithm. We put a pointer referred to BrushWorkApp.display_buffer_ as an argument for drawing function in order to let the function have the permission to modify the canvas. With all the tools we have, there are 2 different algorithms for draw_mask shown in Figure 3 and Figure 4.

<Figure 3: draw_mask function in tool.cc>

<Figure 4: draw_mask function in highlighter.cc>

The difference between these 2 algorithms is in algorithm in Figure 4, used in highlighter class, the result color is decided by the luminance of the existing color on the canvas while in Figure 3, the result color is purely getting the percentage of the color of the tool and the current color on the canvas.

To complete the design, BrushWorkApp must have access to the tools. In Figure 5, BrushWorkApp keep all tools in an array called toolbox_. Then in Figure 6, BrushWorkApp uses set_color of the current tool and repetitively call draw_color of the current tool to fill in the gaps between previous position and current position on the canvas.

<Figure 5: toolbox_ part in brushwork_app.h>

<Figure 6: mouseDragged() and mouseLeftDown() and destructor in brushwork_app.cc>

Finally, it is worth noting that all the tools is deleted before exiting the program and it is BrushWorkApp responsible, can find in Figure 6. To use the BrushWorkApp in application code, the developer only need to know to call set_color(...) and draw_mask(...) to perform operations, they does not need to know the implementations. These member functions do everything needed to draw on the canvas.

### 1.2 Design Justification
(Intro)
The intuition of the design above is to create a reliable, easily maintainable and easily extensible class design for BrushWorkApp.

(Intuition for the first design)

<Figure 7: The big Tool class containing all tools mask>

(Describe how bad the big Tool class is. How hard to maintain, add new class, etc.)

(Describe new alternative if any)

(Conclusion)

## 2  Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
To design the eraser tool, we set set_color  function as a virtual function in the virtual base Tool class. Then we override set_color function in Eraser class and set color_ to background color. Therefore, when user switch tools between eraser and other tools, the color set does not conflict.

<Figure : set_color function in Tool class>

<Figure : set_color function  in Eraser class>

### 2.2 Design Justification
The reason we design our Eraser class this way because it is much easier to maintain. Since we set the color of the eraser to the background color, whenever the background color changes, the color of the eraser will update automatically.

## 3  Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

1. To add a new pencil tool to BrushWork, first of all, you have to change the toolbox’s size in Brushwork.h.
    ```C++
    #include/Brushwork_app.h
    class BrushWorkApp : public BaseGfxApp {
     public:
    	...
     private :
               …
    	Tool* toolbox[7];  /** instead of 6**/
               …
    };
    ```

2. Declare a new instance for Pencil and stored in the toolbox[6].

    "src/Brushwork_app.cc"
    ```C++
    …
    void BrushWorkApp::InitGlui(void) {
    …
    toolbox[0] = new Pen();
    toolbox[1] = new Eraser();
    toolbox[2] = new SprayCan();
    toolbox[3] = new CalligraphyPen();
    toolbox[4] = new Highlighter();
    toolbox[5] = new Crayon();
    toolbox[6] = new Pencil();
    ...
    }
    ```
    etc

3. Finally, Pencil class is needed to implement into pencil.h and pencil.cc as follow. The Pencil class is very similar to the Pen class.

    "include/pencil.h"
    ```C++
    #ifndef INCLUDE_PENCIL_H_
    #define INCLUDE_PENCIL_H_
    #include "include/tool.h"
    namespace image_tools {
    class Pencil : public Tool{
        public:
            Pencil(void);
    };
    } //namespace image_tools
    #endif //INCLUDE_PENCIL_H_
    ```

    "src/pencil.cc"
    ```C++
    #include "include/pen.h"

    namespace image_tools {

    Pencil::Pencil(void) {
      // initialize pencil’s mask_, mask_radius_ and mask_len_
    };
    }
    ```
