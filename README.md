### 已知bug
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
   - 顶部圆弧确实表现异常：不确定是定位异常还是碰撞函数异常
+ 左上角的圆弧的上端和下端的碰撞箱似乎比地图贴图略短
   - [ ] 定位问题
   - [ ] 解决问题
+ 活版依然存在碰撞问题
   - 静止时活版尖端有奇妙的碰撞箱空缺,不清楚是否为有意为之,如果是有意为之,表现未免过于僵硬
      - [ ] 定位问题
      - [ ] 解决问题 
   - 活版尖端圆弧表现依然恐怖
      - [ ] 定位问题
      - [ ] 解决问题
   - 移动中的活版,在特定时候会表现为法向速度衰减过大,猜测为参数不合适
      - [ ] 定位问题
      - [ ] 解决问题
+ 在第二次及以后，newgame框表现异常：不管使用esc还是enter都会导致程序退出（非崩溃）
   - 问题来源依然未知：其他同类确认框未出现此问题
   - [ ] 定位问题
   - [ ] 解决问题

### TODO
##### 以下分先后
+ [x] 确认地图编辑器的g运行状况  
      - 已修复，正常运作
+ [x] 在游戏和地图编辑器应用不同的bgm  
      - 当前设计:从头开始播放
+ [x] 给地图加上祖传外发光  
      - 效果一般 考虑使用Photoshop自己绘制一个
+ [ ] 修改小球，鼓和奖励点的贴图  
      - 小球如果修改贴图,是否要配套设计旋转动画?
+ [ ] 碰撞光效和音效  
      - 目前无方案：目前地图元素的抽象方式不允许这么做
+ [ ] 将程序入口改为开场视频  
      - 呃呃了 zqx怎么连源码都没传上来  
+ [ ] 在地图背景上加入更多装饰
+ [ ] 优化轨道，四边形的贴图
+ [ ] 优化腰子，活版的贴图
+ [ ] 整理文件系统（杀了我吧）

### 未跟进部分
+ [ ] 地图背景似乎传了新版
+ [ ] 记得左上角放一个黑点
