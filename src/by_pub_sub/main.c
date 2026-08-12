/**
 * File:   main.c
 * Author: AWTK Develop Team
 * Brief:  application entry
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

#include "global.h"
#include "main_window.h"
#include "temperature_adjust.h"

ret_t application_init() {
  global_init();
  main_window_init();
  temperature_adjust_init();
  return RET_OK;
}

ret_t application_exit() {
  global_deinit();
  return RET_OK;
}

#include "awtk_main.inc"
