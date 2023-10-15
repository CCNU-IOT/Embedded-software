#include "oled.h"

#define OLED_I2C_ADDRESS 0x78 // 实际7位I2C地址 0x3c 左移一位得到0x78
#define OLED_CMD_SINGLE 0x80 // 用于表示发送单个命令
#define OLED_CMD_STREAM 0x00 // 用于表示发送数据流

I2C_HandleTypeDef hi2c;

static void OLED_WriteByte(uint8_t data, uint8_t cmd) { // 向OLED写入一个字节
    uint8_t buffer[2];                                  // 存放要发送数据的缓冲区
    buffer[0] = cmd;
    buffer[1] = data;
    HAL_I2C_Master_Transmit(&hi2c, OLED_I2C_ADDRESS, buffer, 2, HAL_MAX_DELAY);
}

void OLED_Init() 
{
    IIC_Init();

    OLED_WriteByte(0xAE, OLED_CMD_SINGLE);  // 关闭显示
    OLED_WriteByte(0xD5, OLED_CMD_SINGLE);  // 设置时钟分频因子
    OLED_WriteByte(0x80, OLED_CMD_SINGLE);  // 分频因子
    OLED_WriteByte(0xA8, OLED_CMD_SINGLE);  // 设置多极电压比例
    OLED_WriteByte(0x3F, OLED_CMD_SINGLE);  // 1/64 偏压
    OLED_WriteByte(0xD3, OLED_CMD_SINGLE);  // 设置显示偏移
    OLED_WriteByte(0x00, OLED_CMD_SINGLE);
    OLED_WriteByte(0x40, OLED_CMD_SINGLE);  // 设置起始行
    OLED_WriteByte(0x8D, OLED_CMD_SINGLE);  // 启用电荷泵
    OLED_WriteByte(0x14, OLED_CMD_SINGLE);
    OLED_WriteByte(0x20, OLED_CMD_SINGLE);  // 设置内存地址模式
    OLED_WriteByte(0x00, OLED_CMD_SINGLE);  // 水平地址模式
    OLED_WriteByte(0xA1, OLED_CMD_SINGLE);  // 段重定位
    OLED_WriteByte(0xC8, OLED_CMD_SINGLE);  // 垂直方向重定位
    OLED_WriteByte(0xDA, OLED_CMD_SINGLE);  // COM硬件配置
    OLED_WriteByte(0x12, OLED_CMD_SINGLE);
    OLED_WriteByte(0x81, OLED_CMD_SINGLE);  // 对比度控制
    OLED_WriteByte(0xCF, OLED_CMD_SINGLE);  // 设置对比度
    OLED_WriteByte(0xD9, OLED_CMD_SINGLE);  // 预充电周期
    OLED_WriteByte(0xF1, OLED_CMD_SINGLE);
    OLED_WriteByte(0xDB, OLED_CMD_SINGLE);  // 设置 VCOMH 电压倍率
    OLED_WriteByte(0x40, OLED_CMD_SINGLE);
    OLED_WriteByte(0xA4, OLED_CMD_SINGLE);  // 全局显示开启
    OLED_WriteByte(0xA6, OLED_CMD_SINGLE);  // 设置显示方式：正常显示
    OLED_WriteByte(0xAF, OLED_CMD_SINGLE);  // 打开显示
}

void OLED_DisplayOn(void) 
{
    OLED_WriteByte(0xAF, OLED_CMD_SINGLE);
}

void OLED_DisplayOff(void) 
{
    OLED_WriteByte(0xAE, OLED_CMD_SINGLE);
}

void OLED_DisplayChar(uint8_t x, uint8_t y, char ch) // 在坐标(x, y)处显示ASCII字符
{
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) //所给坐标超过显示范围
    {
        return; 
    }

    uint16_t offset = x + (y / 8) * OLED_WIDTH; // 字符在缓冲区中的偏移

    // 显示字符
    OLED_WriteByte(0x00, OLED_CMD_SINGLE); // 命令：写入数据
    OLED_WriteByte(offset % OLED_WIDTH, OLED_CMD_SINGLE); // 列地址
    OLED_WriteByte(0xB0 + (y / 8), OLED_CMD_SINGLE); // 页地址
    OLED_WriteByte((1 << (y % 8)), OLED_CMD_SINGLE); // 位地址
    OLED_WriteByte(ch, OLED_CMD_STREAM); // 字符数据
}
