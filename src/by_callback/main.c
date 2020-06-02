/**
 * File:   main.c
 * Author: AWTK Develop Team
 * Brief:  application entry
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

#include "awtk.h"
#include "main_window.h"

ret_t application_init() {
  main_window_open();

  return RET_OK;
}

ret_t application_exit() {
  return RET_OK;
}

#include "awtk_main.inc"
