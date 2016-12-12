/*******************************************************************************
 * Name            : fp_io_manager.h
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Header for FPIOManager class
 * Copyright       : Group A01. All rights reserved.
 * Creation Date   : Sat Dec 3 9:41:00 2016
 * Original Author : Yu Xian Ang
 *
 ******************************************************************************/

#ifndef SRC_APP_FLASHPHOTO_SRC_INCLUDE_FP_IO_MANAGER_H_
#define SRC_APP_FLASHPHOTO_SRC_INCLUDE_FP_IO_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/io_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for I/O operations in FlashPhoto. This includes
 * initializing GLUI control elements related to image loading/saving, as well
 * as handling the load/save operations themselves. The load operation includes
 * validating the image type and filesystem permissions before the load will
 * proceed. It also handles loading an image from a file to the stamp.
 */
class FPIOManager : public IOManager {
 public:
    FPIOManager();
    ~FPIOManager() {}

    /**
     * @brief Initialize GLUI control elements for IO management
     *
     * @param glui GLUI handle
     * @param s_gluicallback Callback to install
     */
    GLUI_Panel* InitGlui(const GLUI *const glui,
                  void (*s_gluicallback)(int));

 private:
    /* Copy/move assignment/construction disallowed */
    FPIOManager(const FPIOManager &rhs) = delete;
    FPIOManager& operator=(const FPIOManager &rhs) = delete;
};

} /* namespace image_tools */

#endif /* SRC_APP_FLASHPHOTO_SRC_INCLUDE_FP_IO_MANAGER_H_ */
