/**
 * File:   temperature_adjust.c
 * Author: AWTK Develop Team
 * Brief:  temperature_adjust
 *
 * Copyright (c) 2026 - 2026  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2026-08-11 Shen ZhaoKun <shenzhaokun@zlg.cn> created
 *
 */

#include "awtk.h"
#include "base/object_widget.h"
#include "global.h"
#include "topic.h"
#include "temperature_adjust.h"

static ret_t temperature_adjust_on_inc(void* ctx, event_t* e) {
  widget_add_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), 1);

  return RET_OK;
}

static ret_t temperature_adjust_on_dec(void* ctx, event_t* e) {
  widget_add_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), -1);

  return RET_OK;
}

inline static ret_t temperature_return_result(widget_t* win, bool_t success) {
  if (success) {
    value_change_event_t vce;
    float_t value = widget_get_value(widget_lookup(win, "temperature", TRUE));
    value_change_event_init(&vce, EVT_VALUE_CHANGED, NULL);
    value_set_float(&vce.new_value, value);
    widget_dispatch(win, &vce.e);
    return RET_OK;
  }
  return RET_OK;
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

static ret_t temperature_adjust_on_destroy(void* ctx, event_t* e) {
  tk_object_t* obj_win = TK_OBJECT(ctx);
  object_evt_router_unregister(global_evt_router(), TOPIC_TEMPERATURE_CHANGED, obj_win);
  tk_object_unref(obj_win);
  return RET_OK;
}

static ret_t temperature_adjust_open(float_t init_value) {
  widget_t* win = window_open("temperature_adjust");
  tk_object_t* obj_win = object_widget_create(win);

  widget_child_on(win, "inc", EVT_CLICK, temperature_adjust_on_inc, win);
  widget_child_on(win, "dec", EVT_CLICK, temperature_adjust_on_dec, win);
  widget_child_on(win, "ok", EVT_CLICK, temperature_adjust_on_ok, win);
  widget_child_on(win, "cancel", EVT_CLICK, temperature_adjust_on_cancel, win);
  widget_set_value(widget_lookup(win, "temperature", TRUE), init_value);

  widget_on(win, EVT_DESTROY, temperature_adjust_on_destroy, obj_win);

  object_evt_router_register(global_evt_router(), TOPIC_TEMPERATURE_CHANGED, obj_win,
                             EVT_VALUE_CHANGED,
                             &(object_evt_router_register_opt_t){
                                 .publisher_lifecycle = TK_OBJECT_LIFE_HOLD,
                             });

  return RET_OK;
}

static ret_t temperature_adjust_on_open(tk_object_t* subscriber, event_t* e, void* ctx) {
  value_change_event_t* evt = value_change_event_cast(e);
  return_value_if_fail(evt != NULL, RET_BAD_PARAMS);

  return temperature_adjust_open(value_float(&evt->old_value));
}

ret_t temperature_adjust_init(void) {
  object_evt_router_subscribe(global_evt_router(), TOPIC_TEMPERATURE_MODIFY_REQ,
                              temperature_adjust_on_open, NULL);
  return RET_OK;
}
