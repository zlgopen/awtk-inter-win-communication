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

#include "temperature_adjust.h"

static ret_t main_window_on_result(void* ctx, bool_t success, int value) {
  widget_set_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), value);
  return RET_OK;
}

static ret_t main_window_on_modify(void* ctx, event_t* e) {
  int value = widget_get_value(widget_lookup(WIDGET(ctx), "temperature", TRUE));

  temperature_adjust_open(main_window_on_result, ctx, value);

  return RET_OK;
}

static ret_t main_window_on_quit(void* ctx, event_t* e) {
  tk_quit();

  return RET_OK;
}

ret_t main_window_open(void) {
  widget_t* win = window_open("main");

  widget_child_on(win, "modify", EVT_CLICK, main_window_on_modify, win);
  widget_child_on(win, "quit", EVT_CLICK, main_window_on_quit, win);

  return RET_OK;
}
