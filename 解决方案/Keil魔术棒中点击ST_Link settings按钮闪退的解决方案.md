## Keil魔术棒中点击ST_Link Settings按钮闪退的解决方案

![image-20231005212736323](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202310052153402.png)

如图，点击 Options for target（魔法棒）>> Debug >> Settings 出现闪退。

解决办法：使用旧版STLinkUSBDriver.dll替换现有STLinkUSBDriver.dll

旧版STLinkUSBDriver.dll见仓库同目录下文件夹。或：[下载链接](https://documentation-service.arm.com/static/6391bb322b0dd145f803165d?token=)

注：STLinkUSBDriver.dll可能在D:\Keil_v5\ARM\STLink目录