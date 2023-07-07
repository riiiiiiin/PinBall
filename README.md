- [代码结构](#代码结构)  
      - [/](#/)  
        - [/FrameWork -程序中枢](#framework--程序中枢)  
        - [/Game -可游玩的游戏部分](#game--可游玩的游戏部分)  
        - [/MapEditor -地图编辑器](#mapeditor--地图编辑器)  
        - [/UI\_Base -自创(?)UI设计](#ui_base--自创ui设计)  
        - [/Themepacks -地图材质包](#themepacks--地图材质包)

# 代码结构
#### /
      main.cpp
      程序入口
##### /FrameWork -程序中枢
      /Resources/FrameWork_pics
      /Resources/Music_SE
      /Resources/Videos
      /Resources/Slogans
      在程序中所使用的部分资源

      /Headers/confirmations.h
      /Sources/confirmations.cpp
      程序使用的确认框

      /Headers/gamewidgetmanager.h
      /Sources/gamewidgetmanager.cpp
      处理游戏和地图编辑器间切换使用的框架,声音播放中枢

      /Headers/pausemenu.h
      /Sources/pausemenu.cpp
      游戏过程中的暂停菜单

      /Headers/settingsmenu.h
      /Sources/settingsmenu.cpp
      地图编辑器的拓展设置菜单

      /Headers/skippablevideowidget.h
      /Sources/skippablevideowidget.cpp
      可点击跳过的视频播放类  
      用来装载开场动画  

      /Headers/themepack.h
      /Sources/themepack.cpp
      游戏材质包(风格包)的实现类,用于预加载游戏部分可更换的图片
      具体更换方式请参见Themepacks部分

      /Headers/mainwindow.h
      /Sources/mainwindow.cpp
      游戏载体窗口

      /Headers/encodedmap.h
      在地图编辑器和游戏地图间传送自定义地图的一个抽象

##### /Game -可游玩的游戏部分
      /Resources
      'Legacy'地图风格的图片素材

      /Headers/object.h
      /Sources/object.cpp
      游戏底层抽象,实现碰撞箱

      /Headers/map.h
      /Sources/map.cpp
      游戏过程的抽象,实现游戏地图及图形化

      /Headers/gamewindow.h
      /Sources/gamewindow.cpp
      游戏的对外接口,处理游戏的开始结束等

      /Headers/gamemap.h
      /Sources/gamemap.cpp
      处理游戏的外围事件,包括应用前端ui,与中枢交互

##### /MapEditor -地图编辑器
      /Resources
      'Legacy'地图编辑器风格的图片素材

      /Headers/madaptablelabel.h
      /Sources/madaptablelabel.cpp
      自动适应图片大小的label

      /Headers/mdraggable.h
      /Sources/mdraggable.cpp
      "可拖动"标签的基类
      
      /Headers/mdraggableshadow.h
      /Sources/mdraggableshadow.cpp
      "可拖动"标签的"影子",继承自QGraphicsItem用于处理重叠检测

      /Headers/mdraggables.h
      /Sources/mdraggables.cpp
      游戏实际使用的"可拖动"标签派生类

      /Headers/mdragcontainer.h
      /Sources/mdragcontainer.cpp
      容纳和处理"可拖动"标签的容器,地图编辑器的主要逻辑

      /Headers/mapeditor.h
      /Sources/mapeditor.cpp
      地图编辑器的图形化部分,处理与中枢的交互

##### /UI_Base -自创(?)UI设计
      /Resources
      自己绘制的CheckButton图标

      /Headers/mbutton.h
      /Sources/mbutton.cpp
      按钮基类

      /Headers/mpushbutton.h
      /Sources/mpushbutton.cpp
      实现了点击功能的按钮

      /Headers/mcheckbutton.h
      /Sources/mcheckbutton.cpp
      实现了是/否单选功能的按钮

      /Headers/mslider.h
      /Sources/mslider.cpp
      实现了滑动条的按钮

      /Headers/mconfirmation.h
      /Sources/mconfirmation.cpp
      实现了是/否选项的dialog式弹出框,支持少量键盘操作

      /Headers/mtab.h
      /Sources/mtab.cpp
      菜单的基类

##### /Themepacks -地图材质包
      请将这个文件夹放置在编译出的可执行文件所在的目录下来安装材质包
      /Bustling_Downtown
      小组制作的拓展材质包
      /The_Old_Ones
      小组制作的拓展材质包之二
      /Outlines
      材质包制作的模板
      /Outlines/readme.md
      材质包制作的指引
