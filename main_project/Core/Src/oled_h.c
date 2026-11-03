#include "oled_h.h"
#include "i2c.h"




uint8_t font5x7[11][5] = {
    {0x3E,0x51,0x49,0x45,0x3E}, // 0
    {0x00,0x42,0x7F,0x40,0x00}, // 1
    {0x42,0x61,0x51,0x49,0x46}, // 2
    {0x21,0x41,0x45,0x4B,0x31}, // 3
    {0x18,0x14,0x12,0x7F,0x10}, // 4
    {0x27,0x45,0x45,0x45,0x39}, // 5
    {0x3C,0x4A,0x49,0x49,0x30}, // 6
    {0x01,0x71,0x09,0x05,0x03}, // 7
    {0x36,0x49,0x49,0x49,0x36}, // 8
    {0x06,0x49,0x49,0x29,0x1E},  // 9
    {0x00, 0x60, 0x60, 0x00, 0x00} // .
};

uint8_t empty = 0x00;



HAL_StatusTypeDef oled_send_command(uint8_t command){
	uint8_t data[2] = {0x00, command};
	return HAL_I2C_Master_Transmit(&hi2c1, OLEDAddr << 1, data, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef oled_send_data(uint8_t *data, uint16_t len)
{
    uint8_t send_data[len + 1];

    send_data[0] = 0x40;

    for (uint16_t i = 0; i < len; i++)
    {
        send_data[i + 1] = data[i];
    }

    return HAL_I2C_Master_Transmit(
        &hi2c1,
        OLEDAddr << 1,
        send_data,
        len + 1,
        HAL_MAX_DELAY
    );
}

void oled_setup(void){

	HAL_Delay(100);

	oled_send_command(0xAE);		//先关闭屏幕

	oled_send_command(0x8D);
	oled_send_command(0x14);		//启用内部电荷泵，必须要写

	oled_send_command(0x20);		//设置显存寻址模式
	oled_send_command(0x00);			//水平寻址模式，横着刷新完1page，自动跳到下一page
										//0x01:垂直寻址模式，竖着
										//0x02:水平，但刷完当前page就不动了

	oled_send_command(0x21);		//列范围
	oled_send_command(0x00);			//从第0列
	oled_send_command(0x7F);			//到127列

	oled_send_command(0x22);		//page范围
	oled_send_command(0x00);			//第0page
	oled_send_command(0x07);			//第7page

	oled_send_command(0xAF);		//开启屏幕

	oled_fill();		//全都亮起来先
}

void oled_draw(uint8_t x, uint8_t y){		//填充某个像素
	uint8_t page = y / 8;
	uint8_t yInPage = y % 8;
	uint8_t pixel = 1U << yInPage;

	oled_send_command(0x21);		//设置列范围
	oled_send_command(x);
	oled_send_command(x);

	oled_send_command(0x22);		//设置页范围
	oled_send_command(page);
	oled_send_command(page);

	oled_send_data(&pixel, sizeof(pixel));
}

void oled_fill(void){				//点亮全屏
	oled_send_command(0x21);		//列范围
	oled_send_command(0x00);			//从第0列
	oled_send_command(0x7F);			//到127列

	oled_send_command(0x22);		//page范围
	oled_send_command(0x00);			//第0page
	oled_send_command(0x07);

	uint8_t data[128] = {0};

	for (int i = 0; i < 128; ++i)
	{
	    data[i] = 0xff;
	}
	for (int page = 0; page < 8; page++)
	{
	    oled_send_data(data, sizeof(data));
	}
}
void oled_erase_all(void){			//熄灭全屏

	oled_send_command(0x21);		//列范围
	oled_send_command(0x00);			//从第0列
	oled_send_command(0x7F);			//到127列

	oled_send_command(0x22);		//page范围
	oled_send_command(0x00);			//第0page
	oled_send_command(0x07);

	uint8_t data[128] = {0};

	for (int page = 0; page < 8; page++)
	{
	    oled_send_data(data, sizeof(data));
	}

}


void oled_display_char(uint8_t *numbers){

	oled_erase_all();

	oled_send_command(0x21);		//列范围
	oled_send_command(0x01);			//从第1列，字符留一列
	oled_send_command(0x7F);			//到127列

	oled_send_command(0x22);		//page范围
	oled_send_command(0x00);			//第0page
	oled_send_command(0x07);


	for(int j = 0; j < 3; ++j){
		for(int i = 0; i < 10; ++i){
			if (numbers[j] == i) {
				oled_send_data(font5x7[i], sizeof(font5x7[i]));					//写字符
				oled_send_data(&empty, sizeof(empty));							//空出一列

				if(j==1){
					oled_send_data(font5x7[10], sizeof(font5x7[10]));			//写个小数点
					oled_send_data(&empty, sizeof(empty));						//空出一列
				}
				break;
			}
		}
	}
}
