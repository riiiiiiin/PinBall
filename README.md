- [代码结构](#代码结构)  
      - [/](#/)  
        - [/FrameWork -程序中枢](#framework--程序中枢)  
        - [/Game -可游玩的游戏部分](#game--可游玩的游戏部分)  
        - [/MapEditor -地图编辑器](#mapeditor--地图编辑器)  
        - [/UI\_Base -自创(?)UI设计](#ui_base--自创ui设计)  
- [已知bug](#已知bug)  
- [TODO](#todo)  
        - [这部分容易完成](#这部分容易完成)   
        - [这可能是远期计划了吧...大概率不会去做了](#这可能是远期计划了吧大概率不会去做了)  

# 代码结构
#### /
      mainwindow.h
      mainwindow.cpp
      main.cpp
      程序入口
##### /FrameWork -程序中枢
      /Resources/FrameWork_pics
      /Resources/Music&SE

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

      /Headers/themepack.h
      /Sources/themepack.cpp
      游戏风格包的实现类,用于预加载游戏部分可更换的图片
      具体更换方式...请期待后续文档说明

      /Headers/encodedmap.h
      原本设计为在地图编辑器和游戏地图间传送自定义地图的一个抽象
      原本还计划将其作为存储地图设置使用的抽象
      遗憾的是,由于后端队员抽象能力奇差,目前这一抽象也被用在后端地图构建部分

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
      我承认,后面这三层包装并不是太好.一部分是后端提供的抽象太抽象（?）,另一部分就是交接的问题

##### /MapEditor -地图编辑器
      /Resources
      'Legacy'地图编辑器风格的图片素材

      /Headers/madaptablelabel.h
      /Sources/madaptablelabel.cpp
      毫无卵用地包装了一遍QLabel
      很难理解我是在什么精神状态下写的这个东西

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
      原本计划实现键盘交互,但是现在只实现了鼠标交互

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



# 已知bug
##### 开发基本完成后会把未修复bug放在issue里面的🥺

+ flipper的初始位置似乎不在下垂位置，而是在顶部
   - 不是单独的问题，而是圆弧穿模的表现之一
   - [x] 定位问题
   - [x] 解决问题
+ kidney的下圆弧似乎表现出比预期更大的碰撞箱
   - 问题表现:从下部击中kidney内侧面时,在接触内侧面前就反弹;从上部贴kidney内侧面向下时，似乎击中什么东西而异常反弹
   - [x] 定位问题
   - 问题所在:当前版本中，默认的kidney将所有弧都构造成了整圆😅
   - [x] 解决问题
   - 顶部圆弧确实表现异常：不确定是定位异常还是碰撞函数异常,恢复为整圆规避问题
+ 左上角圆弧内的BonusPoint似乎没法被触发？
   - 笑死跑太慢了触发不到😅
   - [x] 定位问题
   - [x] 解决问题
+ 左上角的圆弧的上端和下端的碰撞箱似乎比地图贴图略短
   - [x] 定位问题
   - [x] 解决问题
   - 笑死了居然是黑边画太大了
+ 活版依然存在碰撞问题
   - 活版尖端圆弧表现依然恐怖
      - [ ] 定位问题
      - [ ] 解决问题
      - 怎么队友直接删了这个啊
   - 移动中的活版,在特定时候会表现为法向速度衰减过大,猜测为参数不合适
      - [ ] 定位问题
      - [ ] 解决问题
+ 在第二次及以后，newgame框表现异常：不管使用esc还是enter都会导致程序退出（非崩溃）
   - 猜测：来自QDialog
   - [ ] 定位问题  
   - [ ] 解决问题

# TODO
##### 这部分容易完成
+ [x] 确认地图编辑器的g运行状况  
      - 已修复，正常运作
+ [x] 在游戏和地图编辑器应用不同的bgm  
      - 当前设计:从头开始播放
+ [x] 给地图加上祖传外发光  
      - 效果一般 在地图编辑器中试安装了一个
+ [x] 给主窗口加一个Icon
+ [x] 整理文件系统
+ [x] **非编译式**的主题设置功能!
+ [x] 新主题的奖励点实在太丑
+ [x] 新主题的flipper太暗了
      - 考虑加亮+ps画一个外发光
+ [x] 给地图ps一个外发光
+ [ ] 碰撞音效接口
      - 大概向上传信号吧...
+ [ ] ball的替代贴图接口
+ [ ] 游戏入口改为开场视频
      - 视频播放结束后再调用resume开始游戏
      - 注意效率

##### 这可能是远期计划了吧...大概率不会去做了
+ [ ] 实现更好的键盘交互
+ [ ] 将静音和音量滑块组合在一起
+ [ ] 地图编辑器的文件读写
+ [ ] 其他config的文件读写
