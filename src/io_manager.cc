/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of IOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/io_manager.h"
#include <png.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <iostream>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/ui_ctrl.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
IOManager::IOManager(void) :
    file_browser_(nullptr),
    load_canvas_btn_(nullptr),
    load_stamp_btn_(nullptr),
    save_canvas_btn_(nullptr),
    current_file_label_(nullptr),
    file_name_box_(nullptr),
    save_file_label_(nullptr),
    file_name_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void IOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  file_browser_ = new GLUI_FileBrowser(image_panel,
                                      "Choose Image",
                                      false,
                                      UICtrl::UI_FILE_BROWSER,
                                      s_gluicallback);

  file_browser_->set_h(400);

  file_name_box_ = new GLUI_EditText(image_panel ,
                                    "Image:",
                                    file_name_,
                                    UICtrl::UI_FILE_NAME,
                                    s_gluicallback);
  file_name_box_->set_w(200);

  new GLUI_Separator(image_panel);

  current_file_label_ = new GLUI_StaticText(image_panel,
                                           "Will load image: none");
  load_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Load Canvas",
                                    UICtrl::UI_LOAD_CANVAS_BUTTON,
                                    s_gluicallback);
  load_stamp_btn_ = new GLUI_Button(image_panel,
                                   "Load Stamp",
                                   UICtrl::UI_LOAD_STAMP_BUTTON,
                                   s_gluicallback);

  new GLUI_Separator(image_panel);

  save_file_label_ = new GLUI_StaticText(image_panel,
                                        "Will save image: none");

  save_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Save Canvas",
                                    UICtrl::UI_SAVE_CANVAS_BUTTON,
                                    s_gluicallback);

  load_canvas_toggle(false);
  load_stamp_toggle(false);
  save_canvas_toggle(false);
}


bool IOManager::is_valid_image_file(const std::string & name) {
  FILE *f;
  bool is_valid = false;
  if (is_valid_image_file_name(name)) {
    if ((f = fopen(name.c_str(), "r"))) {
      is_valid = true;
      fclose(f);
    }
  }
  return is_valid;
}

void IOManager::set_image_file(const std::string & file_name) {
  // If a directory was selected
  // instead of a file, use the
  // latest file typed or selected.
  std::string image_file = file_name;
  if (!is_valid_image_file_name(image_file)) {
    image_file = file_name_;
  }

  // TOGGLE SAVE FEATURE
  // If no file is selected or typed,
  // don't allow file to be saved. If
  // there is a file name, then allow
  // file to be saved to that name.

  if (!is_valid_image_file_name(image_file)) {
    save_file_label_->set_text("Will save image: none");
    save_canvas_toggle(false);
  } else {
    save_file_label_->set_text((std::string("Will save image: ") +
                                image_file).c_str());
    save_canvas_toggle(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened,
  // then disable stamp and canvas loading.
  if (is_valid_image_file(image_file)) {
    load_stamp_toggle(true);
    load_canvas_toggle(true);

    current_file_label_->set_text((std::string("Will load: ") +
                                   image_file).c_str());
    file_name_box_->set_text(image_file);
  } else {
    load_stamp_toggle(false);
    load_canvas_toggle(false);
    current_file_label_->set_text("Will load: none");
  }
}

PixelBuffer *IOManager::LoadImageToCanvas() {
  std::cout << "Load Canvas has been clicked for file " <<
      file_name_ << std::endl;
  if (has_suffix(file_name_, ".png")) {
    return LoadPNG();
  } else if (has_suffix(file_name_, ".jpg") ||
             has_suffix(file_name_, ".jpeg")) {
    return LoadJPEG();
  }
  return nullptr;
}

PixelBuffer *IOManager::LoadImageToStamp(void) {
  std::cout << "Load Stamp has been clicked for file " <<
      file_name_ << std::endl;
  /* load image */
  PixelBuffer* temp_buffer = NULL;
  if (has_suffix(file_name_, ".png")) {
    if ((temp_buffer = LoadPNG()) == NULL) {
      return temp_buffer;
    }
  } else if (has_suffix(file_name_, ".jpg") ||
             has_suffix(file_name_, ".jpeg")) {
    if ((temp_buffer = LoadJPEG()) == NULL) {
      return temp_buffer;
    }
  }

  /* Resize the image to stamp's size */
  int stamp_limit = 80;
  int buffer_height = temp_buffer->height();
  int buffer_width = temp_buffer->width();
  double scale;
  if (buffer_height > buffer_width) {
    scale = static_cast<double>(stamp_limit) / buffer_height;
    temp_buffer = Resample(temp_buffer, stamp_limit, buffer_width * scale);
  } else {
    scale = static_cast<double>(stamp_limit) / buffer_width;
    temp_buffer = Resample(temp_buffer, buffer_height * scale, stamp_limit);
  }

  return temp_buffer;
}

void IOManager::SaveCanvasToFile(PixelBuffer *display_buffer) {
  std::cout << "Save Canvas been clicked for file " <<
      file_name_ << std::endl;
  if (has_suffix(file_name_, ".png") && display_buffer != NULL) {
    SavePNG(display_buffer);
  } else if ((has_suffix(file_name_, ".jpg") || has_suffix(file_name_, ".jpeg"))
             && display_buffer != NULL) {
    SaveJPEG(display_buffer);
  } else {
    exit(1);
  }
  return;
}

void IOManager::SavePNG(PixelBuffer *display_buffer) {
  png_image image;
  png_bytep buffer;
  ColorData color;

  memset(&image, 0, (sizeof image));

  /* Set image attributes */
  image.opaque  = NULL;
  image.version = PNG_IMAGE_VERSION;
  image.width   = display_buffer->width();
  image.height  = display_buffer->height();
  image.format  = PNG_FORMAT_RGBA;

  /* allocate buffer memory */
  buffer = reinterpret_cast<png_byte*>(malloc(PNG_IMAGE_SIZE(image)));

  /* set rgba values of every pixels into buffer */
  int y = 0;
  int x = 0;

  while (y < display_buffer->height()) {
    while (x < display_buffer->width()) {
      color = display_buffer->get_pixel(x, display_buffer->height()-y-1);
      buffer[y * 4 * image.width + x * 4 + 0] =
            static_cast<png_byte>(static_cast<unsigned int>(color.red()*255));
      buffer[y * 4 * image.width + x * 4 + 1] =
            static_cast<png_byte>(static_cast<unsigned int>(color.green()*255));
      buffer[y * 4 * image.width + x * 4 + 2] =
            static_cast<png_byte>(static_cast<unsigned int>(color.blue()*255));
      buffer[y * 4 * image.width + x * 4 + 3] =
            static_cast<png_byte>(static_cast<unsigned int>(color.alpha()*255));
      x++;
    }
    x = 0;
    y++;
  }

  /* write buffer to png file */
  if (png_image_write_to_file(&image, file_name().c_str(), 0/*convert_to_8bit*/,
              buffer, 0/*row_stride*/, NULL/*colormap*/) != 0) {
               /* The image has been written successfully. */
               std::cout << "Save Canvas been clicked for file " <<
                   file_name_ << std::endl;
           } else {
             fprintf(stderr, "Save png file error.\n");
           }
  return;
}

void IOManager::SaveJPEG(PixelBuffer *display_buffer) {
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  FILE * outfile;
  JSAMPROW row_pointer[1];
  JSAMPLE *buffer;
  int row_stride;
  ColorData color;

  /* set error */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  if ((outfile = fopen(file_name().c_str(), "wb")) == NULL) {
    fprintf(stderr, "can not open %s \n", file_name().c_str());
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  /* set jpeg file attributes */
  cinfo.image_width  = display_buffer->width();
  cinfo.image_height = display_buffer->height();
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&cinfo);

  jpeg_set_quality(&cinfo, 100, TRUE);
  jpeg_start_compress(&cinfo, TRUE);

  /* initialize line-writer */
  row_stride = display_buffer->width()*3;

  /* allocate buffer memory */
  buffer = reinterpret_cast<JSAMPLE *>
           (malloc(row_stride * display_buffer->height()));

  /* write in rgb value of every pixel into buffer */
  int x = 0;
  int y = 0;

  while (y < display_buffer->height()) {
    while (x < display_buffer->width()) {
      color = display_buffer->get_pixel(x, display_buffer->height() - y -1);
      buffer[y * 3 * display_buffer->width() + x * 3 + 0] =
                                      static_cast<JSAMPLE>((color.red()*255));
      buffer[y * 3 * display_buffer->width() + x * 3 + 1] =
                                      static_cast<JSAMPLE>((color.green()*255));
      buffer[y * 3 * display_buffer->width() + x * 3 + 2] =
                                      static_cast<JSAMPLE>((color.blue()*255));
      x++;
    }
    x = 0;
    y++;
  }
  /* writing buffer into jpeg file */
  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = & buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
}

PixelBuffer *IOManager::LoadPNG(void) {
  PixelBuffer* temp_buffer = NULL;
  png_image image;
  memset(&image, 0, (sizeof image));
  image.version = PNG_IMAGE_VERSION;

  /* read all files attributes */
  if (png_image_begin_read_from_file(&image, file_name_.c_str()) != 0) {
    temp_buffer = new PixelBuffer(image.width,
                                  image.height,
                                  ColorData(0, 0, 0, 0));

    png_bytep buffer;
    image.format = PNG_FORMAT_RGBA;

    /* malloc buffer memory */
    buffer = reinterpret_cast<png_byte*>(malloc(PNG_IMAGE_SIZE(image)));

    /* read whole image to temporary pixel buffer */
    if (temp_buffer != NULL &&
        png_image_finish_read(&image, NULL, buffer, 0, NULL) != 0) {
      const float BASE_COLOR = 255.0;

      if (image.format == PNG_FORMAT_RGBA) {
        for (int y = 0; y < static_cast<int>(image.height); y++) {
          for (int x = 0; x < static_cast<int>(image.width); x ++) {
            float r = static_cast<float>(buffer[(y * image.width + x) * 4]);
            float g = static_cast<float>(buffer[(y * image.width + x) * 4 + 1]);
            float b = static_cast<float>(buffer[(y * image.width + x) * 4 + 2]);
            float a = static_cast<float>(buffer[(y * image.width + x) * 4 + 3]);
            temp_buffer->set_pixel(x, image.height - y - 1,
                                   ColorData(r / BASE_COLOR,
                                             g / BASE_COLOR,
                                             b / BASE_COLOR,
                                             a / BASE_COLOR));
          }
        }
      }

      delete(buffer);
      return temp_buffer;
    } else {
      delete(buffer);
      delete(temp_buffer);
      return NULL;
    }

    fprintf(stderr, "pngtopixel_buffer: error: %s\n", image.message);
    return NULL;
  }

  fprintf(stderr,
        "pngtopixel_buffer: usage: pngtopixel_buffer input-file output-file\n");
  return NULL;
}

PixelBuffer *IOManager::LoadJPEG(void) {
  float r, g, b;
  const float BASE_COLOR = 255.0;
  int width, height;
  PixelBuffer *temp_buffer = NULL;

  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE * fp;
  JSAMPARRAY buffer;
  int row_stride;

  if ((fp = fopen(file_name_.c_str(), "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", file_name_.c_str());
    return NULL;
  }

  cinfo.err = jpeg_std_error(&jerr);

  /* decompress jpeg file */
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, fp);

  (void) jpeg_read_header(&cinfo, TRUE);
  (void) jpeg_start_decompress(&cinfo);

  width = cinfo.output_width;
  height = cinfo.output_height;

  temp_buffer = new PixelBuffer(width, height, ColorData(0.0, 0.0, 0.0, 0.0));

  /* set line reader */
  row_stride = cinfo.output_width * cinfo.output_components;
  /* allocate buffer memory */
  buffer = (*cinfo.mem->alloc_sarray)
           (reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE, row_stride, 1);

  /* read whole image to temporary pixel buffer */
  while (cinfo.output_scanline < cinfo.output_height) {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    for (int x = 0; x < width; x++) {
      r = buffer[0][cinfo.output_components * x];
      if (cinfo.output_components > 2) {
        g = buffer[0][cinfo.output_components * x + 1];
        b = buffer[0][cinfo.output_components * x + 2];
      } else {
        g = r;
        b = r;
      }

      temp_buffer->set_pixel(x, height - cinfo.output_scanline,
                             ColorData(r / BASE_COLOR,
                                       g / BASE_COLOR,
                                       b / BASE_COLOR));
    }
  }

  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(fp);
  return temp_buffer;
}

PixelBuffer *IOManager::Resample(PixelBuffer *display_buffer,
                                 int new_height, int new_width) {
  /* Initialize variables */
  int old_height = display_buffer->height();
  int old_width = display_buffer->width();
  double h_scale = static_cast<double>(new_height) / old_height;
  double w_scale = static_cast<double>(new_width) / old_width;
  PixelBuffer *stamp_buffer =
    new PixelBuffer(new_width, new_height, display_buffer->background_color());

  /* Nearest Neighbor algorithm */
  for (int y = 0; y < new_height; y++) {
    int nearest_match_y = y / h_scale;
    for (int x = 0; x < new_width; x++) {
      int nearest_match_x = x / w_scale;
      ColorData temp_color = display_buffer->get_pixel(nearest_match_x,
                                                       nearest_match_y);
      stamp_buffer->set_pixel(x, y, temp_color);
    }
  }

  return stamp_buffer;
}

}  /* namespace image_tools */
