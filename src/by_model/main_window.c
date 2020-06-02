/**
 * File:   main_window.c
 * Author: AWTK Develop Team
 * Brief:  main_window
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2020-06-02 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "temperature.h"
#include "temperature_adjust.h"

static ret_t main_window_on_value_changed(void* ctx, event_t* e) {
  widget_set_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), temperature()->value);

  return RET_OK;
}

static ret_t main_window_on_modify(void* ctx, event_t* e) {
  temperature_adjust_open();

  return RET_OK;
}

static ret_t main_window_on_quit(void* ctx, event_t* e) {
  emitter_off_by_ctx(EMITTER(temperature()), ctx);
  tk_quit();

  return RET_OK;
}

ret_t main_window_open(void) {
  widget_t* win = window_open("main");

  widget_child_on(win, "modify", EVT_CLICK, main_window_on_modify, win);
  widget_child_on(win, "quit", EVT_CLICK, main_window_on_quit, win);
  widget_set_value(widget_lookup(win, "temperature", TRUE), temperature()->value);
  emitter_on(EMITTER(temperature()), EVT_VALUE_CHANGED, main_window_on_value_changed, win);

  return RET_OK;
}
