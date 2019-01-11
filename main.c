#include <reg51.h>
#include <intrins.h>
#include "ws2812.h"

#define DOUT		(P33)

// WS2812灯带颗粒数
#define	PIXEL_CNT		(16)

Pixel color = {0, 31, 255, 127, 255};
int g_step = -1, r_step = -1, b_step = 1;

// 各颗粒值的初始值
Pixel idata pixels[PIXEL_CNT] = {
	{1, 31, 255, 127, 255},
	{2, 31, 255, 127, 127},
	{3, 31, 255, 127, 31},
	{4, 31, 255, 127, 7},
	{5, 31, 255, 127, 1},
	{6, 31, 255, 127, 0},
	{7, 31, 255, 127, 0},
	{8, 31, 255, 127, 0},
	{9, 31, 255, 127, 0},
	{10, 31, 255, 127, 0},
	{11, 31, 255, 127, 0},
	{12, 31, 255, 127, 0},
	{13, 31, 255, 127, 0},
	{14, 31, 255, 127, 0},
	{15, 31, 255, 127, 0},
	{0, 31, 255, 127, 0},
};

// 通用计数器
unsigned long cnt = 0;

// 指定毫秒数Delay
void delay_ms(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;

	do {
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do {
			while (--j);
		} while (--i);
	} while (--x);
}

// 主函数
void main() {
	// 初始化段
	
	// 循环处理段
	while(1) {
		// 等待50ms
		delay_ms(50);
		if(DKEY) {
			// 流水灯效果，颜色渐变
			cnt %= 0x300;
			
			g_step = color.green == 0?1:(color.green == 0xff?-1:g_step);
			color.green += (cnt / 0x100) != 1?0:g_step;
	
			r_step = color.red == 0?1:(color.red == 0xff?-1:r_step);
			color.red += (cnt / 0x100) != 0?0:r_step;
			
			b_step = color.blue == 0?1:(color.blue == 0xff?-1:b_step);
			color.blue += (cnt / 0x100) != 2?0:b_step;
			
			set_pixels_color(pixels, PIXEL_CNT, color);
			send_pixels(pixels, cnt % PIXEL_CNT, PIXEL_CNT);
			cnt++;
		}
		else {
			// 全部LED显示相同的颜色和亮度
			Pixel p_white = {0, 255, 255, 255, 255};
			send_pixels(&p_white, 0, PIXEL_CNT);
		}
	}	
}
