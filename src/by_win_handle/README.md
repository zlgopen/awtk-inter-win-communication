# 通过窗口句柄修改主窗口的温度

## 实现方法


* 调用者将窗口句柄传递给设置窗口。

```c
ret_t temperature_adjust_open(widget_t* caller, int init_value) {
  widget_t* win = window_open("temperature_adjust");

  widget_set_prop_pointer(win, STR_CALLER, caller);
  widget_child_on(win, "inc", EVT_CLICK, temperature_adjust_on_inc, win);
  widget_child_on(win, "dec", EVT_CLICK, temperature_adjust_on_dec, win);
  widget_child_on(win, "ok", EVT_CLICK, temperature_adjust_on_ok, win);
  widget_child_on(win, "cancel", EVT_CLICK, temperature_adjust_on_cancel, win);
  widget_set_value(widget_lookup(win, "temperature", TRUE), init_value);

  return RET_OK;
}
```

* 在设置窗口 "OK" 按钮的事件处理函数中，通过窗口句柄找到名为 temperature 的控件，并更新它的值。

```c
static ret_t temperature_adjust_on_ok(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  int value = widget_get_value(widget_lookup(win, "temperature", TRUE));
  widget_t* main_win = (widget_t*)widget_get_prop_pointer(win, STR_CALLER);

  widget_set_value(widget_lookup(main_win, "temperature", TRUE), value);
  window_close(WIDGET(ctx));

  return RET_OK;
}
```

## 优点

* 实现简单。
* 窗口之间耦合紧密，代码难以维护，老板不敢轻易换人。

> 建议不要使用。