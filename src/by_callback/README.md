# 通过回调函数让主窗口自己修改温度

## 实现方法

* 调用者将回调函数传递给设置窗口。

```c
ret_t temperature_adjust_open(temperature_adjust_on_result_t on_result, void* ctx, int init_value) {
  widget_t* win = window_open("temperature_adjust");

  widget_set_prop_pointer(win, STR_ON_RESULT, on_result);
  widget_set_prop_pointer(win, STR_ON_RESULT_CTX, ctx);

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
static ret_t temperature_return_result(widget_t* win, bool_t success) {
  int value = widget_get_value(widget_lookup(win, "temperature", TRUE));
  temperature_adjust_on_result_t on_result = (temperature_adjust_on_result_t)widget_get_prop_pointer(win, STR_ON_RESULT);
  void* on_result_ctx = widget_get_prop_pointer(win, STR_ON_RESULT_CTX);

  return on_result(on_result_ctx, success, value);
}

static ret_t temperature_adjust_on_ok(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);

  temperature_return_result(win, TRUE);
  window_close(win);

  return RET_OK;
}
```

## 优点

 * 窗口之间耦合松散，方便代码维护。

> 建议使用。