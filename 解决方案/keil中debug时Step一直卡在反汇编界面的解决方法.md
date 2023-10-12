## keil中debug时Step一直卡在反汇编界面的解决方法

### 一、卡在反汇编界面的表现：
工具栏红框内圆叉为红色，后四个按钮为灰色（如下图1）。点击Step（F11）时反复执行Disassembly内的几条语句（下图2中黄色箭头所指），

![image-20231006214804598](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202310062151926.png)
图1⬆

![image-20231006213332094](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202310062145741.png)
图2⬆

### 二、解决方法：

![image-20231006213836941](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202310062145742.png)

如上图所标

1. 全局编译（Rebuild）
2. 点击2处下载（或按下F8）
3. 点击3处开始debug（或Ctrl+F5）

![image-20231006212735425](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202310062145740.png)

点击debug后若工具栏显示如图则无问题。