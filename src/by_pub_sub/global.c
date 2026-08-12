/**
 * File:   global.h
 * Author: AWTK Develop Team
 * Brief:  全局。
 *
 * Copyright (c) Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

#include "global.h"

static tk_object_t* s_evt_router = NULL;

inline static ret_t global_evt_router_init(void) {
  if (s_evt_router != NULL) {
    return RET_SKIP;
  }
  s_evt_router = object_evt_router_create();
  return_value_if_fail(s_evt_router != NULL, RET_OOM);

  tk_object_set_name(s_evt_router, "@GLOBAL_EVT_ROUTER");

  return RET_OK;
}

inline static ret_t global_evt_router_deinit(void) {
  ret_t ret = RET_OK;
  if (s_evt_router == NULL) {
    return RET_SKIP;
  }
  ret = tk_object_unref(s_evt_router);
  s_evt_router = NULL;
  return ret;
}

tk_object_t* global_evt_router(void) {
  return s_evt_router;
}

ret_t global_init(void) {
  return global_evt_router_init();
}

ret_t global_deinit(void) {
  return global_evt_router_deinit();
}
