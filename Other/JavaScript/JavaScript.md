# vscode写Js Canvas无代码提示

解决方法：

+ 如果是2d上下文，则在获取上下文的前一句加上`/** @type {CanvasRenderingContext2D} */`
+ 如果是3d上下文，则加上`/** @type {WebGLRenderingContext} */`

```js
let drawing = document.querySelector("#canvas")
/** @type {CanvasRenderingContext2D} */
let context = drawing.getContext("2d") 
```

搞定！
