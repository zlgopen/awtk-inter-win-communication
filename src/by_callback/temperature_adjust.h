/**
 * File:   temperature_adjust.h
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

#ifndef TEMPERATURE_ADJUST_H
#define TEMPERATURE_ADJUST_H

#include "awtk.h"

BEGIN_C_DECLS

typedef ret_t (*temperature_adjust_on_result_t)(void* ctx, bool_t success, int value);

ret_t temperature_adjust_open(temperature_adjust_on_result_t on_result, void* ctx, int init_value);

END_C_DECLS

#endif /*TEMPERATURE_ADJUST_H*/
