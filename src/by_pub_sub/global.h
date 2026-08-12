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
#ifndef GLOBAL_H
#define GLOBAL_H

#include "tkc/types_def.h"
#include "tkc/object_evt_router.h"

BEGIN_C_DECLS

/**
 * @class global_t
 * @annotation ["fake"]
 * 全局。
 */

/**
 * @method global_init
 * 全局初始化。
 * @annotation ["static", "private"]
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t global_init(void);

/**
 * @method global_evt_router
 * 全局事件路由器。
 * @annotation ["static", "private"]
 *
 * @return {tk_object_t*} 返回运动控制事件路由器对象。
 */
tk_object_t* global_evt_router(void);

/**
 * @method global_deinit
 * 全局反初始化。
 * @annotation ["static", "private"]
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t global_deinit(void);

END_C_DECLS

#endif /*GLOBAL_H*/
