#include <reg51.h>
#include <intrins.h>

// 使用的IO口，无需初始化
sbit	DOUT = P3^3;
sbit	DKEY = P3^2;

#define	DELAY_LONG	{_nop_();_nop_();_nop_();}
#define DELAY_SHORT	{_nop_();_nop_();}

#define SEND_1	{DOUT=1;DELAY_LONG;DOUT=0;DELAY_SHORT;}
#define SEND_0	{DOUT=1;DELAY_SHORT;DOUT=0;DELAY_LONG;}
#define SEND_BIT(x) {if(x) {SEND_1;} else {SEND_0;}}

// WS2812灯带颗粒数
#define	PIXEL_CNT		(16)

// RGB颗粒结构
typedef struct {
	unsigned int	next_pixel;		// 下一颗粒的index
	unsigned char green;				// 绿色值
	unsigned char red;					// 红色值
	unsigned char blue;					// 蓝色值
	unsigned char brightness;		// 亮度值
} Pixel;

void reset();
void send_p(Pixel _p);				// 发送1个颗粒的值
void send_pixels(Pixel *_p_list, unsigned int _start, unsigned int _cnt);		// 发送所有颗粒的值
void set_pixels_color(Pixel *pixels, unsigned int _cnt, Pixel _color);

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
		do
		{
			while (--j);
		} while (--i);
	} while (--x);
}

// 主函数
void main() {
	// 初始化段
#ifdef	ALL_WHITE

#endif
	
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

void Delay50us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 1;
	j = 134;
	do
	{
		while (--j);
	} while (--i);
}

// RESET信号
void reset() {
	DOUT = 0;
	Delay50us();
}

void send_p(Pixel _p) {
	unsigned char p_v;
	p_v = (_p.green * _p.brightness) >> 8;
	SEND_BIT(p_v & 0x80);
	SEND_BIT(p_v & 0x40);
	SEND_BIT(p_v & 0x20);
	SEND_BIT(p_v & 0x10);
	SEND_BIT(p_v & 0x08);
	SEND_BIT(p_v & 0x04);
	SEND_BIT(p_v & 0x02);
	SEND_BIT(p_v & 0x01);
	p_v = (_p.red * _p.brightness) >> 8;
	SEND_BIT(p_v & 0x80);
	SEND_BIT(p_v & 0x40);
	SEND_BIT(p_v & 0x20);
	SEND_BIT(p_v & 0x10);
	SEND_BIT(p_v & 0x08);
	SEND_BIT(p_v & 0x04);
	SEND_BIT(p_v & 0x02);
	SEND_BIT(p_v & 0x01);
	p_v = (_p.blue * _p.brightness) >> 8;
	SEND_BIT(p_v & 0x80);
	SEND_BIT(p_v & 0x40);
	SEND_BIT(p_v & 0x20);
	SEND_BIT(p_v & 0x10);
	SEND_BIT(p_v & 0x08);
	SEND_BIT(p_v & 0x04);
	SEND_BIT(p_v & 0x02);
	SEND_BIT(p_v & 0x01);
}

void send_pixels(Pixel *_p_list, unsigned int _start, unsigned int _cnt) {
	Pixel *_p = &_p_list[_start % _cnt];
	reset();
	while(_cnt--) {
		send_p(*_p);
		_p = &_p_list[_p->next_pixel];
	}
	reset();
}

void set_pixels_color(Pixel *pixels, unsigned int _cnt, Pixel _color) {
	int i;
	for(i = 0; i < _cnt; i++) {
		pixels[i].green = _color.green;
		pixels[i].red = _color.red;
		pixels[i].blue = _color.blue;
	}
}
