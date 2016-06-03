/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <android/log.h>
#include <android_native_app_glue.h>

#include "JNIHelper.h"
#include "JUIWindow.h"

#include "JUIButton.h"
#include "JUITextView.h"
#include "JUIDialog.h"


// Class name of helper function
#define HELPER_CLASS_NAME "com/ndkgui/helper/NDKHelper"
// Class name of JUIhelper function
#define JUIHELPER_CLASS_NAME "com/ndkgui/helper/JUIHelper"
// Share object name of helper function library
#define HELPER_CLASS_SONAME "ndkgui"



enum BUTTON_INDEX {
    BUTTON_ADVERTISE = 0,
    BUTTON_DISCOVER,
    BUTTON_PLAY_GAME,
    BUTTON_STOP,
    UI_BUTTON_COUNT
};
ndkGui::JUIButton *ui_buttons_[UI_BUTTON_COUNT];
ndkGui::JUITextView *status_text_;



/*
 * Initialize game management UI,
 * invoking jui_helper functions to create java UIs
 */
void InitUI(struct android_app* app_) {

  const int32_t LEFT_MARGIN = 20;

  // The window initialization
  ndkGui::JUIWindow::Init(app_->activity, JUIHELPER_CLASS_NAME);

  // Using jui_helper, a support library, to create and bind game management UIs
  int32_t win_width = ANativeWindow_getWidth(app_->window);
  int32_t win_height = ANativeWindow_getHeight(app_->window);

  if (win_height <= 0 || win_width <= 0) {
    LOGE("Failed to get native window size");
    return;
  }
  if (win_height > win_width) {
    int32_t tmp = win_width;
    win_width = win_height;
    win_height = tmp;
  }

  int32_t button_raw_width = win_width / 4;  // we have 4 buttons
  int32_t button_height = win_height / 4;
  int cur_idx = 0;

  // Create 4 buttons to control nearby sign-in
  // The sequence is dictated by enum BUTTON_INDEX,
  // it MUST match the button titles array defined here
  const char *titles[UI_BUTTON_COUNT] = {"Advertise", "Discover", "Play Game",
                                         "Stop"};

  for (cur_idx = 0; cur_idx < UI_BUTTON_COUNT; cur_idx++) {
    ndkGui::JUIButton *button = new ndkGui::JUIButton(titles[cur_idx]);
    button->AddRule(ndkGui::LAYOUT_PARAMETER_CENTER_VERTICAL,
                    ndkGui::LAYOUT_PARAMETER_TRUE);
    button->AddRule(ndkGui::LAYOUT_PARAMETER_ALIGN_PARENT_LEFT,
                    ndkGui::LAYOUT_PARAMETER_TRUE);
    button->SetAttribute("MinimumWidth", button_raw_width - LEFT_MARGIN);
    button->SetAttribute("MinimumHeight", button_height);
    button->SetMargins(LEFT_MARGIN + cur_idx * button_raw_width, 0, 0, 0);
    ndkGui::JUIWindow::GetInstance()->AddView(button);
    ui_buttons_[cur_idx] = button;
  }

  status_text_ = new ndkGui::JUITextView("Nearby Connection is Idle");
  status_text_->AddRule(ndkGui::LAYOUT_PARAMETER_ALIGN_PARENT_BOTTOM,
                        ndkGui::LAYOUT_PARAMETER_TRUE);
  status_text_->AddRule(ndkGui::LAYOUT_PARAMETER_CENTER_IN_PARENT,
                        ndkGui::LAYOUT_PARAMETER_TRUE);
  status_text_->SetAttribute("TextSize", ndkGui::ATTRIBUTE_UNIT_SP, 17.f);
  ndkGui::JUIWindow::GetInstance()->AddView(status_text_);

  return;
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {

    // Make sure glue isn't stripped.
    app_dummy();

    //ndkGui::JNIHelper::Init(state->activity, HELPER_CLASS_NAME,HELPER_CLASS_SONAME);
    InitUI(state);

}
//END_INCLUDE(all)
