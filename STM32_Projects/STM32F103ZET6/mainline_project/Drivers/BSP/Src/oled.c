#include "oled.h"

#define OLED_I2C_ADDRESS 0x78
#define OLED_CMD_SINGLE 0x80
#define OLED_CMD_STREAM 0x00

I2C_HandleTypeDef hi2c;

static void OLED_WriteByte(uint8_t data, uint8_t cmd) { // ��OLEDд��һ���ֽ�
    uint8_t buffer[2];                                  // ���Ҫ�������ݵĻ�����
    buffer[0] = cmd;
    buffer[1] = data;
    HAL_I2C_Master_Transmit(&hi2c, OLED_I2C_ADDRESS, buffer, 2, HAL_MAX_DELAY);
}

void OLED_Init() 
{
    IIC_Init();

    OLED_WriteByte(0xAE, OLED_CMD_SINGLE);  // �ر���ʾ
    OLED_WriteByte(0xD5, OLED_CMD_SINGLE);  // ����ʱ�ӷ�Ƶ����
    OLED_WriteByte(0x80, OLED_CMD_SINGLE);  // ��Ƶ����
    OLED_WriteByte(0xA8, OLED_CMD_SINGLE);  // ���ö༫��ѹ����
    OLED_WriteByte(0x3F, OLED_CMD_SINGLE);  // 1/64 ƫѹ
    OLED_WriteByte(0xD3, OLED_CMD_SINGLE);  // ������ʾƫ��
    OLED_WriteByte(0x00, OLED_CMD_SINGLE);
    OLED_WriteByte(0x40, OLED_CMD_SINGLE);  // ������ʼ��
    OLED_WriteByte(0x8D, OLED_CMD_SINGLE);  // ���õ�ɱ�
    OLED_WriteByte(0x14, OLED_CMD_SINGLE);
    OLED_WriteByte(0x20, OLED_CMD_SINGLE);  // �����ڴ��ַģʽ
    OLED_WriteByte(0x00, OLED_CMD_SINGLE);  // ˮƽ��ַģʽ
    OLED_WriteByte(0xA1, OLED_CMD_SINGLE);  // ���ض�λ
    OLED_WriteByte(0xC8, OLED_CMD_SINGLE);  // ��ֱ�����ض�λ
    OLED_WriteByte(0xDA, OLED_CMD_SINGLE);  // COMӲ������
    OLED_WriteByte(0x12, OLED_CMD_SINGLE);
    OLED_WriteByte(0x81, OLED_CMD_SINGLE);  // �Աȶȿ���
    OLED_WriteByte(0xCF, OLED_CMD_SINGLE);  // ���öԱȶ�
    OLED_WriteByte(0xD9, OLED_CMD_SINGLE);  // Ԥ�������
    OLED_WriteByte(0xF1, OLED_CMD_SINGLE);
    OLED_WriteByte(0xDB, OLED_CMD_SINGLE);  // ���� VCOMH ��ѹ����
    OLED_WriteByte(0x40, OLED_CMD_SINGLE);
    OLED_WriteByte(0xA4, OLED_CMD_SINGLE);  // ȫ����ʾ����
    OLED_WriteByte(0xA6, OLED_CMD_SINGLE);  // ������ʾ��ʽ��������ʾ
    OLED_WriteByte(0xAF, OLED_CMD_SINGLE);  // ����ʾ
}

void OLED_DisplayOn(void) 
{
    OLED_WriteByte(0xAF, OLED_CMD_SINGLE);
}

void OLED_DisplayOff(void) 
{
    OLED_WriteByte(0xAE, OLED_CMD_SINGLE);
}

void OLED_DisplayChar(uint8_t x, uint8_t y, char ch) 
{// ������(x, y)����ʾASCII�ַ�
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) {
        return; 
    }

    // �����ַ��ڻ������е�ƫ��
    uint16_t offset = x + (y / 8) * OLED_WIDTH;

    // ��ʾ�ַ�
    OLED_WriteByte(0x00, OLED_CMD_SINGLE); // ���д������
    OLED_WriteByte(offset % OLED_WIDTH, OLED_CMD_SINGLE); // �е�ַ
    OLED_WriteByte(0xB0 + (y / 8), OLED_CMD_SINGLE); // ҳ��ַ
    OLED_WriteByte((1 << (y % 8)), OLED_CMD_SINGLE); // λ��ַ
    OLED_WriteByte(ch, OLED_CMD_STREAM); // �ַ�����
}
