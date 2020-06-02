# 通过 model 通知主窗口修改主温度

## 实现方法

* 实现 model

```c
typedef struct _temperature_t {
  emitter_t emitter;
  int value;
}temperature_t
```

模型一般继承 emitter_t 类，使其具有变化通知的功能。详情请参考 temperature.h/.c

* 主窗口关注 model 变化事件

```c
static ret_t main_window_on_value_changed(void* ctx, event_t* e) {
  widget_set_value(widget_lookup(WIDGET(ctx), "temperature", TRUE), temperature()->value);

  return RET_OK;
}

...

emitter_on(EMITTER(temperature()), EVT_VALUE_CHANGED, main_window_on_value_changed, win);

```

* 在设置窗口 "OK" 按钮的事件处理函数中，直接修改模型的值。

```c
static ret_t temperature_adjust_on_ok(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  int value = widget_get_value(widget_lookup(win, "temperature", TRUE));

  temperature_set_value(temperature(), value);

  window_close(WIDGET(ctx));

  return RET_OK;
}
```

## 优点

* 窗口之间耦合松散，方便代码维护。

* 可以把业务逻辑从界面剥离出来。

> 建议使用。

## 其它事项

* 如果有多个温度对象，可以把 model 对象传递给设置窗口。

* 如果后台线程要修改 model，一定要用 idle_queue 进行串行 AUI 线程修改。

* 如果希望彻底分离用户界面，建议使用 [AWTK-MVVM](https://github.com/zlgopen/awtk-mvvm)