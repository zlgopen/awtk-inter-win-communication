# 直接修改主窗口中的温度

## 实现方法

在设置窗口 "OK" 按钮的事件处理函数中，通过窗口管理器找到主窗口，然后找到名为 temperature 的控件，并更新它的值。

```c
static ret_t temperature_adjust_on_ok(void* ctx, event_t* e) {
  int value = widget_get_value(widget_lookup(WIDGET(ctx), "temperature", TRUE));
  widget_t* main_win = widget_lookup(window_manager(), "main", FALSE);

  widget_set_value(widget_lookup(main_win, "temperature", TRUE), value);
  window_close(WIDGET(ctx));

  return RET_OK;
}
```

## 优点

* 实现简单。
* 窗口之间耦合紧密，代码难以维护，老板不敢轻易换人。

> 建议不要使用。
