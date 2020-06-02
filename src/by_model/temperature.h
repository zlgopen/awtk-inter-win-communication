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

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "awtk.h"

BEGIN_C_DECLS

typedef struct _temperature_t {
  emitter_t emitter;
  int value;
} temperature_t;

/*singleton*/
temperature_t* temperature();

ret_t temperature_init(int init_value);
ret_t temperature_deinit(void);

ret_t temperature_set_value(temperature_t* t, int value);

END_C_DECLS

#endif /*TEMPERATURE_H*/
