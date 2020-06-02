/**
 * File:   temperature.h
 * Author: AWTK Develop Team
 * Brief:  temperature model
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

static temperature_t* s_temperature;

temperature_t* temperature() {
  return s_temperature;
}

ret_t temperature_init(int init_value) {
  return_value_if_fail(s_temperature == NULL, RET_BAD_PARAMS);

  s_temperature = TKMEM_ZALLOC(temperature_t);
  return_value_if_fail(s_temperature != NULL, RET_OOM);

  emitter_init(EMITTER(s_temperature));
  temperature_set_value(s_temperature, init_value);

  return RET_OK;
}

ret_t temperature_deinit(void) {
  return_value_if_fail(s_temperature != NULL, RET_OOM);
  emitter_deinit(EMITTER(s_temperature));
  TKMEM_FREE(s_temperature);
  s_temperature = NULL;

  return RET_OK;
}

ret_t temperature_set_value(temperature_t* t, int value) {
  return_value_if_fail(t != NULL, RET_BAD_PARAMS);

  t->value = value;

  return emitter_dispatch_simple_event(EMITTER(t), EVT_VALUE_CHANGED);
}
