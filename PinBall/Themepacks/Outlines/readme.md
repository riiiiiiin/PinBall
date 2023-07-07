### OUTLINES
本文件夹**不是**能正常使用的主题包,而是用来提供主题包制作的指导和帮助的包
+ theme.json中的字典中,留空了所有值.制作材质包需要填写其中**每个值**,任何一个值的缺失,都会导致主题包无效,在程序输出中,将有对应输出
+ "Theme_Title"的值需要填写一个字符串,表示材质包的标题(在地图编辑器中展示)
+ 其他各项的值为字符串,为对应图片在主题包文件夹中的名称(如cover.png)
+ 本文件夹提供的各.psd文件,是方便制作材质包而提供的碰撞箱外观
#### 以下为各key的名称,图片用途以及在本文件夹中提供的碰撞箱图片的对照表  

| key | 图片用途 | 碰撞箱 | 
| ---- | ---- | ---- |
| "Cover" | 地图编辑器中展示的主题封面 |推荐比例5:2|  
|"BG_Map_Editor" | 地图编辑器中展示的地图以及静态元素| bg_mapeditor.psd|
|"BG_Game" | 游戏中的地图以及静态元素| bg_map.psd|
| "lFlipper"| 游戏中的左侧活版| left_flipper.psd|
|"rFlipper"|游戏中的右侧活版|right_flipper.psd|
|"Ball"|游戏中的球|ball.psd|
|"Ball_alter"|游戏中,得分后一段事件球的替代图像|ball.psd|
|"lKidney_game"|游戏中的左三角形弹力鼓 | left_kidney.psd|
|"lKidney_home"|地图编辑器右半区待拖动的左三角形弹力鼓|推荐比例1:1|
|"lKidney_placed"|地图编辑器中已放置的左三角形弹力鼓|left_kidney.psd|
|"lKidney_valid"|地图编辑器中正在拖动的左三角形弹力鼓,允许放置|left_kidney.psd|
|"lKidney_invalid"|地图编辑器中正在拖动的左三角形弹力鼓,不允许放置|left_kidney.psd|
|"rKidney_game"|游戏中的右三角形弹力鼓 | right_kidney.psd|
|"rKidney_home"|地图编辑器右半区待拖动的右三角形弹力鼓|推荐比例1:1|
|"rKidney_placed"|地图编辑器中已放置的右三角形弹力鼓|right_kidney.psd|
|"rKidney_valid"|地图编辑器中正在拖动的右三角形弹力鼓,允许放置|right_kidney.psd|
|"rKidney_invalid"|地图编辑器中正在拖动的右三角形弹力鼓,不允许放置|right_kidney.psd|
|"Drum_game"|游戏中的弹力鼓|drum.psd|
|"Drum_home"|地图编辑器右半区待拖动的弹力鼓|推荐比例1:1|
|"Drum_placed"|地图编辑器中已放置的弹力鼓|drum.psd|
|"Drum_valid"|地图编辑器中正在拖动的弹力鼓,允许放置|drum.psd|
|"Drum_invalid"|地图编辑器中正在拖动的弹力鼓,不允许放置|drum.psd|
|"Bonus_Point_game"|游戏中的奖励点|bonus_point.psd|
|"Bonus_Point_home"|地图编辑器右半区待拖动的奖励点|推荐比例1:1|
|"Bonus_Point_placed"|地图编辑器中已放置的奖励点|bonus_point.psd|
|"Bonus_Point_valid"|地图编辑器中正在拖动的奖励点,允许放置|bonus_point.psd|
|"Bonus_Point_invalid"|地图编辑器中正在拖动的奖励点,不允许放置|bonus_point.psd|
#### 注意事项
- 图片在加载过程中会被重新成倍率拉伸,因此,上述图片的制作中,比例需要保持不变,而图片大小可以自己设定
- 事实上,即使未按照上述推荐碰撞箱进行设计,这样的材质不会影响到程序正常运作,只会导致视觉上的穿模而已
- 当然,对于json字典而言,上述字段的顺序并不重要,只需要保证每个字段都存在,并且提供了正确且能够被打开的文件名