# 通过发布/订阅让窗口之间通信

本示例中，一个全局的 object_evt_router 充当消息总线，窗口之间通过命名主题（topic）进行通信。发布者与订阅者完全解耦，不需要知道对方的存在。

## 实现方法

* 定义主题（topic.h）。两个主题分别代表"请求修改"和"温度变化"两个方向。

```c
#define TOPIC_TEMPERATURE_MODIFY_REQ "temperature_modify_req"
#define TOPIC_TEMPERATURE_CHANGED    "temperature_changed"
```

其中 TOPIC_TEMPERATURE_MODIFY_REQ 用于主窗口→设置窗口，请求修改温度；TOPIC_TEMPERATURE_CHANGED 用于设置窗口→主窗口，通知温度变化。

* 创建全局事件路由器（global.c）。路由器是所有窗口通信的中介。

```c
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
```

在 application_init 中调用 global_init()，在 application_exit 中调用 global_deinit()（见 main.c）。

* 主窗口：订阅"温度变化"，并在点击 "modify" 时发布"修改请求"。

```c
ret_t main_window_init(void) {
  widget_t* win = window_open("main");
  widget_child_on(win, "quit", EVT_CLICK, main_window_on_quit, win);
  widget_child_on(win, "modify", EVT_CLICK, main_window_on_modify, win);

  widget_t* temperature = widget_lookup(win, "temperature", TRUE);
  object_evt_router_subscribe(global_evt_router(), TOPIC_TEMPERATURE_CHANGED,
                              main_window_on_temperature_changed,
                              &(object_evt_router_subscribe_opt_t){
                                  .callback_ctx = temperature,
                              });

  return RET_OK;
}
```

点击"modify"按钮时，发布 EVT_VALUE_CHANGED 事件，把当前温度放在 old_value 中（请求方向，携带的是编辑起点）。

```c
static ret_t main_window_on_modify(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  widget_t* temperature = widget_lookup(win, "temperature", TRUE);
  value_change_event_t vce;
  value_change_event_init(&vce, EVT_VALUE_CHANGED, NULL);
  value_set_float(&vce.old_value, widget_get_value(temperature));
  object_evt_router_publish(global_evt_router(), TOPIC_TEMPERATURE_MODIFY_REQ, &vce.e);
  return RET_OK;
}
```

订阅的回调从 new_value 中取出温度变化结果，更新主窗口的 temperature 控件。

```c
static ret_t main_window_on_temperature_changed(tk_object_t* subscriber, event_t* e, void* ctx) {
  widget_t* temperature = WIDGET(ctx);
  value_change_event_t* evt = value_change_event_cast(e);
  return_value_if_fail(evt != NULL, RET_BAD_PARAMS);

  return widget_set_value(temperature, value_float(&evt->new_value));
}
```

* 设置窗口：订阅"修改请求"，并在点击 "OK" 时发布"温度变化"。设置窗口不常驻，需要时再打开。

```c
ret_t temperature_adjust_init(void) {
  object_evt_router_subscribe(global_evt_router(), TOPIC_TEMPERATURE_MODIFY_REQ,
                              temperature_adjust_on_open, NULL);
  return RET_OK;
}
```

收到"修改请求"后，从 old_value 中取出初始温度并打开设置窗口。

```c
static ret_t temperature_adjust_on_open(tk_object_t* subscriber, event_t* e, void* ctx) {
  value_change_event_t* evt = value_change_event_cast(e);
  return_value_if_fail(evt != NULL, RET_BAD_PARAMS);

  return temperature_adjust_open(value_float(&evt->old_value));
}
```

点击"OK"按钮时，把编辑结果放在 new_value 中发布（结果方向），然后关闭窗口。

```c
inline static ret_t temperature_return_result(widget_t* win, bool_t success) {
  if (success) {
    value_change_event_t vce;
    float_t value = widget_get_value(widget_lookup(win, "temperature", TRUE));
    value_change_event_init(&vce, EVT_VALUE_CHANGED, NULL);
    value_set_float(&vce.new_value, value);
    object_evt_router_publish(global_evt_router(), TOPIC_TEMPERATURE_CHANGED, &vce.e);
    return RET_OK;
  }
  return RET_OK;
}
```

* 数据流向（一次完整的"请求—修改—返回"往返）。

```
① 请求修改   TOPIC_TEMPERATURE_MODIFY_REQ   (主窗口 → 设置窗口)

   [主窗口] ──publish──► [事件路由器] ──► [设置窗口]
   → old_value = 当前温度；设置窗口以此为初始值打开

② 通知结果   TOPIC_TEMPERATURE_CHANGED   (设置窗口 → 主窗口)

   [设置窗口] ──publish──► [事件路由器] ──► [主窗口]
   → new_value = 编辑结果；主窗口据此更新 temperature 控件
```

> 发布者不需要注册：调用 object_evt_router_publish 时指定主题即可，路由器也不会保存发布者的引用。

## 优点

* 发布者与订阅者完全解耦，互不感知对方的存在，方便代码维护。
* 通过主题约定通信，新增订阅者（例如另一个窗口监听温度变化）不需要修改任何现有代码。
* 基于标准的 object_evt_router，任何 tk_object 都可以作为发布者或订阅者，不限于窗口。
* 路由器自带优先级（priority）和事件过滤（evt_filter）；主题为空字符串时表示订阅所有主题，可以用来做全局事件日志；订阅回调返回非 RET_OK 可以中断后续分发；发布支持嵌套，且分发过程中退订会延迟到分发结束之后再清理，所以在回调里退订是安全的。

> 建议使用。
