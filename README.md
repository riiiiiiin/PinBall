# PinBall

### 文件结构
+ 头文件放在Headers下  
+ 源文件放在Sources下  
+ ui文件放在Forms下  
+ 资源文件放在Resources下  

### 自定义类
+ "MButton"是暂停页面上按钮的基类。实现按钮大体绘制。  
 "MPushButton"是暂停页面上的单次点击按钮。只具备鼠标悬浮效果和点击事件。  
 "MCheckButton"是暂停页面上的0/1按钮。额外绘制一个图标表现0/1。  
 如何继承MButton：构造函数传入参数:(int)高度,(QString)按钮名称,(QString)左侧Label显示文字,(QWidget*)parent  
 MButton没有实现点击或其他触发信号，需要自己实现

+ "MConfirmation"是确认窗口。模态。实现橙色横幅，title和两个按钮。  
  title和按钮是protected对象，需要自行指定文字和geometry。按钮已绑定到对应信号。默认esc拒绝，enter接受。
  如何继承MConfirmation：只需指定title和按钮的文字和geometry。可以自己override部分槽。
  
+ 以上两个类具体包括哪些信号和槽，烦请诸君自行查阅源码。我实在是没精力写这个了。
