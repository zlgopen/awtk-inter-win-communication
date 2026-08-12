/**
 * File:   topic.h
 * Author: AWTK Develop Team
 * Brief:  主题。
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
#ifndef TOPIC_H
#define TOPIC_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

/**
 * @enum topic_t
 * @annotation ["string"]
 * @prefix TOPIC_
 * 主题。
 */

/**
 * @const TOPIC_TEMPERATURE_CHANGED
 * 温度变化。
 */
#define TOPIC_TEMPERATURE_CHANGED "temperature_changed"

/**
 * @const TOPIC_TEMPERATURE_MODIFY_REQ
 * 温度修改请求。
 */
#define TOPIC_TEMPERATURE_MODIFY_REQ "temperature_modify_req"

END_C_DECLS

#endif /*TOPIC_H*/
