#include "oled.h"

#define OLED_I2C_ADDRESS 0x78 // 实际7位I2C地址0x3c 左移一位得到0x78
#define OLED_CMD 0x00 // 0000 0000 发送命令
#define OLED_DATA 0x80 // 1100 0000 发送数据

I2C_HandleTypeDef hi2c;

static void OLED_WriteByte(uint8_t cmd , uint8_t data) { // 向OLED写入一个字节
    uint8_t buffer[2]; // 存放要发送数据的缓冲区
    buffer[0] = cmd;
    buffer[1] = data;
    HAL_I2C_Master_Transmit(&hi2c, OLED_I2C_ADDRESS, buffer, 2, HAL_MAX_DELAY);
}

void OLED_Init() 
{
    I2C_Init();

    OLED_WriteByte(OLED_CMD, 0xAE);  // 关闭显示
    OLED_WriteByte(OLED_CMD, 0xD5);  // 设置时钟分频因子
    OLED_WriteByte(OLED_CMD, 0x80);  // 分频因子
    OLED_WriteByte(OLED_CMD, 0xA8);  // 设置多极电压比例
    OLED_WriteByte(OLED_CMD, 0x3F);  // 1/64 偏压
    OLED_WriteByte(OLED_CMD, 0xD3);  // 设置显示偏移
    OLED_WriteByte(OLED_CMD, 0x00);
    OLED_WriteByte(OLED_CMD, 0x40);  // 设置起始行
    OLED_WriteByte(OLED_CMD, 0x8D);  // 启用电荷泵
    OLED_WriteByte(OLED_CMD, 0x14);
    OLED_WriteByte(OLED_CMD, 0x20);  // 设置内存地址模式
    OLED_WriteByte(OLED_CMD, 0x00);  // 水平地址模式
    OLED_WriteByte(OLED_CMD, 0xA1);  // 段重定位
    OLED_WriteByte(OLED_CMD, 0xC8);  // 垂直方向重定位
    OLED_WriteByte(OLED_CMD, 0xDA);  // COM硬件配置
    OLED_WriteByte(OLED_CMD, 0x12);
    OLED_WriteByte(OLED_CMD, 0x81);  // 对比度控制
    OLED_WriteByte(OLED_CMD, 0xCF);  // 设置对比度
    OLED_WriteByte(OLED_CMD, 0xD9);  // 预充电周期
    OLED_WriteByte(OLED_CMD, 0xF1);
    OLED_WriteByte(OLED_CMD, 0xDB);  // 设置 VCOMH 电压倍率
    OLED_WriteByte(OLED_CMD, 0x40);
    OLED_WriteByte(OLED_CMD, 0xA4);  // 全局显示开启
    OLED_WriteByte(OLED_CMD, 0xA6);  // 设置显示方式：正常显示
    OLED_WriteByte(OLED_CMD, 0xAF);  // 打开显示
    OLED_WriteByte(OLED_CMD, 0xAE);  // 关闭显示
}

void OLED_DisplayOff(void) // 清屏
{
    OLED_WriteByte(OLED_CMD, 0xAE);
}

void OLED_DisplayPixel(uint8_t x, uint8_t y) // 点亮坐标(x, y)处像素
{
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) //所给坐标超过显示范围
        return; 

    uint16_t offset = x + (y / 8) * OLED_WIDTH; // 坐标在缓冲区中的偏移

    // 点亮像素
    OLED_WriteByte(OLED_CMD, 0x00); // 命令：写入数据
    OLED_WriteByte(OLED_CMD, offset % OLED_WIDTH); // 列地址
    OLED_WriteByte(OLED_CMD, 0xB0 + (y / 8)); // 页地址
    OLED_WriteByte(OLED_CMD, (1 << (y % 8))); // 位地址
    OLED_WriteByte(OLED_CMD, 0xAF); // 点亮当前像素
}

void OLED_DisplayString(uint8_t x, uint8_t y, char *str) // 在坐标(x, y)处显示字符串
{
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) //所给坐标超过显示范围
        return; 

    uint16_t offset = x + (y / 8) * OLED_WIDTH; // 坐标在缓冲区中的偏移

    // 点亮像素
    OLED_WriteByte(OLED_CMD, 0x00); // 命令：写入数据
    OLED_WriteByte(OLED_CMD, offset % OLED_WIDTH); // 列地址
    OLED_WriteByte(OLED_CMD, 0xB0 + (y / 8)); // 页地址
    OLED_WriteByte(OLED_CMD, (1 << (y % 8))); // 位地址

    uint8_t data[OLED_WIDTH];
    for (int i = 0; str[i] != '\0'; i++) 
    {
        char character = str[i];
        for (int j = 0; j < 16; j++) 
            data[i * 16 + j] = font8x16[character * 16 + j]; // 8*16字模数组
        HAL_I2C_Master_Transmit(&hi2c, OLED_DATA, &data[offset], strlen(str) * 8, HAL_MAX_DELAY);
    }
}
