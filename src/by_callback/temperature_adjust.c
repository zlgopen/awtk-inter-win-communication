/**
 * File:   temperature_adjust.c
 * Author: AWTK Develop Team
 * Brief:  temperature_adjust
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
#define STR_ON_RESULT "on_result"
#define STR_ON_RESULT_CTX "on_result_ctx"

static ret_t temperature_adjust_on_inc(void* ctx, event_t* e) {
  widget_add_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), 1);

  return RET_OK;
}

static ret_t temperature_adjust_on_dec(void* ctx, event_t* e) {
  widget_add_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), -1);

  return RET_OK;
}

static ret_t temperature_return_result(widget_t* win, bool_t success) {
  int value = widget_get_value(widget_lookup(win, "temperature", TRUE));
  temperature_adjust_on_result_t on_result =
      (temperature_adjust_on_result_t)widget_get_prop_pointer(win, STR_ON_RESULT);
  void* on_result_ctx = widget_get_prop_pointer(win, STR_ON_RESULT_CTX);

  return on_result(on_result_ctx, success, value);
}

static ret_t temperature_adjust_on_ok(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);

  temperature_return_result(win, TRUE);
  window_close(win);

  return RET_OK;
}

static ret_t temperature_adjust_on_cancel(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);

  temperature_return_result(win, FALSE);
  window_close(win);

  return RET_OK;
}

ret_t temperature_adjust_open(temperature_adjust_on_result_t on_result, void* ctx, int init_value) {
  widget_t* win = window_open("temperature_adjust");

  widget_set_prop_pointer(win, STR_ON_RESULT, on_result);
  widget_set_prop_pointer(win, STR_ON_RESULT_CTX, ctx);

  widget_child_on(win, "inc", EVT_CLICK, temperature_adjust_on_inc, win);
  widget_child_on(win, "dec", EVT_CLICK, temperature_adjust_on_dec, win);
  widget_child_on(win, "ok", EVT_CLICK, temperature_adjust_on_ok, win);
  widget_child_on(win, "cancel", EVT_CLICK, temperature_adjust_on_cancel, win);
  widget_set_value(widget_lookup(win, "temperature", TRUE), init_value);

  return RET_OK;
}
