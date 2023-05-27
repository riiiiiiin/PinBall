# MapEditor_Prototype

### 文件结构
+ 头文件放在Headers下  
+ 源文件放在Sources下  
+ ui文件放在Forms下  
+ 资源文件放在Resources下 

### 自定义类
+ MDraggable 是能够拖拽的标签。  
 因为马上就要改了所以我不高兴再写好readme  
 要改的地方：如何确定拖拽的地图元素的类别？初步想法是enum+多态  
+ MDragContainer 是能拖拽的这些个东西的容器  
 要改的地方：添加对多种地图元素的支持，如何将放置的地图元素转换成地图？  
 更长期目标：能否实现它的文件读写？
