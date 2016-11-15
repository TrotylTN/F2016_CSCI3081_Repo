/*******************************************************************************
 * Name            : state_manager.cc
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Implementation of StateManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Sun Oct 2 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/state_manager.h"
#include <iostream>
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
StateManager::StateManager(void) :
    undo_btn_(nullptr),
    redo_btn_(nullptr),
    cached_buffer_({}),
    size_limit_(20),
    state_ptr_(-1) {
      cached_buffer_.clear();
    }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void StateManager::InitGlui(const GLUI *const glui,
                            void (*s_gluicallback)(int)) {
  undo_btn_ = new GLUI_Button(const_cast<GLUI*>(glui), "Undo", UICtrl::UI_UNDO,
                              s_gluicallback);
  undo_toggle(false);

  redo_btn_  = new GLUI_Button(const_cast<GLUI*>(glui), "Redo", UICtrl::UI_REDO,
                               s_gluicallback);
  redo_toggle(false);
}

void StateManager::UndoOperation(PixelBuffer* &display_buffer) {
  state_ptr_--;
  std::cout << "Undoing... state_ptr: " << state_ptr_ << std::endl;
  display_buffer = this->cached_buffer_[state_ptr_];
  if (state_ptr_ < this->cached_buffer_.size() - 1)
    redo_toggle(true);
  else
    redo_toggle(false);
  if (state_ptr_ > 0)
    undo_toggle(true);
  else
    undo_toggle(false);
}

void StateManager::RedoOperation(PixelBuffer* &display_buffer) {
  state_ptr_++;
  std::cout << "Redoing... state_ptr: " << state_ptr_ << std::endl;
  display_buffer = this->cached_buffer_[state_ptr_];
  if (state_ptr_ < this->cached_buffer_.size() - 1)
    redo_toggle(true);
  else
    redo_toggle(false);
  if (state_ptr_ > 0)
    undo_toggle(true);
  else
    undo_toggle(false);
}

void StateManager::InsertNewBuffer(PixelBuffer* new_buffer) {
  for (int i = this->cached_buffer_.size() - 1; i > state_ptr_; i--) {
    delete this->cached_buffer_[i];
    this->cached_buffer_.erase(this->cached_buffer_.begin() + i);
  }
  this->cached_buffer_.push_back(new_buffer);
  state_ptr_++;
  std::cout << "Current state_ptr: " << state_ptr_ << std::endl;
  if (state_ptr_ < this->cached_buffer_.size() - 1)
    redo_toggle(true);
  else
    redo_toggle(false);
  if (state_ptr_ > 0)
    undo_toggle(true);
  else
    undo_toggle(false);
}

}  /* namespace image_tools */
