# 3DEditor
计算机图形学课程项目

3D地图编辑器使用说明

默认情况进入第三人称预览，显示已经存入的建筑

右键菜单。

第一人称预览：不支持空中飞行，将受到重力下降到地面。

Map made mode地图编辑模式，wsad上下左右选择方格，按z切换地形，不同纹理依次代表山地、草地、树林、河流

Map made mode->generate map按照你的设计在世界中生成相应地形

Full screen全屏

Not full screen 退出全屏

3d model making mode 建筑制作模式

Work mode下按F生成第一个块，此时按c和v可以改变块的大小

Wsadqe生成当前块上下左右前后的块，zx可以选择纹理

Select mode下可以选择当前块，还是按wsadqe

View mode下自由查已经做好的模型

Save model into the world下可以把当前模型放入世界中，使用yhgjtu表示上下左右前后移动，还可以通过bn进行旋转。

Confirm to save将把当前的模型数据保存到things,txt文件中，下次打开的时候还会存在

一、项目功能介绍

（1）地形绘制模式

在一个二维地图上标定想要的地形，可供选择的地形有：

山地：通过随机生成山的制高点然后向下生成土堆。

河流：使用水的纹理方块

草原：使用草的纹理方块

树林：使用泥地纹理方块，然后在指定区域绘制10颗树，每棵树分为树干部分和树叶部分，分别使用不同的纹理方块。

（2）建筑制作模式

可以比较自由的绘制方块建筑，选择事先载入的纹理，基本的增加、删除、选择、放大缩小功能都具备。

（3）第三人称预览

可以将制作好的二维地图生成到实际世界（使用了天空盒）中进行预览，也可以将制作好的建筑放入世界中合适位置（支持平移、旋转）保存（数据将存放在专门的txt文件中保存）

（4）第一人称预览

模拟了简单的重力，人会持续下降直至地平线高度。

二、代码结构说明

Texture.h头文件中定义了使用的各种纹理，可以随时添加新的纹理图案。

Tga.h头文件负责读取.tga格式的纹理图片

Skybox.h头文件负责绘制天空盒

Parameter.h头文件保存了其他文件中需要的各种变量

Lib.h头文件涵盖了需要使用的各种库函数头文件

Readfile.h头文件是读取保存数据用的txt文件

Draw.h绘制面、方块、纹理，以及山、树等的写好的函数。

Main.h是主函数部分，包含了菜单，键盘鼠标控制

Things.txt存放自定义建筑模型的数据。
