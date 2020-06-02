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

#include "temperature.h"
#include "temperature_adjust.h"

static ret_t temperature_adjust_on_inc(void* ctx, event_t* e) {
  widget_add_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), 1);

  return RET_OK;
}

static ret_t temperature_adjust_on_dec(void* ctx, event_t* e) {
  widget_add_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), -1);

  return RET_OK;
}

static ret_t temperature_adjust_on_ok(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  int value = widget_get_value(widget_lookup(win, "temperature", TRUE));

  temperature_set_value(temperature(), value);

  window_close(WIDGET(ctx));

  return RET_OK;
}

static ret_t temperature_adjust_on_cancel(void* ctx, event_t* e) {
  window_close(WIDGET(ctx));

  return RET_OK;
}

ret_t temperature_adjust_open(void) {
  widget_t* win = window_open("temperature_adjust");

  widget_child_on(win, "inc", EVT_CLICK, temperature_adjust_on_inc, win);
  widget_child_on(win, "dec", EVT_CLICK, temperature_adjust_on_dec, win);
  widget_child_on(win, "ok", EVT_CLICK, temperature_adjust_on_ok, win);
  widget_child_on(win, "cancel", EVT_CLICK, temperature_adjust_on_cancel, win);
  widget_set_value(widget_lookup(win, "temperature", TRUE), temperature()->value);

  return RET_OK;
}
