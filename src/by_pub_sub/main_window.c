/**
 * File:   main_window.c
 * Author: AWTK Develop Team
 * Brief:  main_window
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
#include "main_window.h"

static ret_t main_window_on_quit(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

static ret_t main_window_on_modify(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  widget_t* temperature = widget_lookup(win, "temperature", TRUE);
  value_change_event_t vce;
  value_change_event_init(&vce, EVT_VALUE_CHANGED, NULL);
  value_set_float(&vce.old_value, widget_get_value(temperature));
  widget_dispatch(win, &vce.e);
  return RET_OK;
}

static ret_t main_window_on_temperature_changed(tk_object_t* subscriber, event_t* e, void* ctx) {
  widget_t* temperature = WIDGET(ctx);
  value_change_event_t* evt = value_change_event_cast(e);
  return_value_if_fail(evt != NULL, RET_BAD_PARAMS);

  return widget_set_value(temperature, value_float(&evt->new_value));
}

ret_t main_window_init(void) {
  widget_t* win = window_open("main");
  tk_object_t* obj_win = object_widget_create(win);
  widget_child_on(win, "quit", EVT_CLICK, main_window_on_quit, win);
  widget_child_on(win, "modify", EVT_CLICK, main_window_on_modify, win);

  object_evt_router_register(global_evt_router(), TOPIC_TEMPERATURE_MODIFY_REQ, obj_win,
                             EVT_VALUE_CHANGED,
                             &(object_evt_router_register_opt_t){
                                 .publisher_lifecycle = TK_OBJECT_LIFE_OWN,
                             });

  widget_t* temperature = widget_lookup(win, "temperature", TRUE);
  object_evt_router_subscribe(global_evt_router(), TOPIC_TEMPERATURE_CHANGED,
                              main_window_on_temperature_changed,
                              &(object_evt_router_subscribe_opt_t){
                                  .callback_ctx = temperature,
                              });

  return RET_OK;
}
