#ifndef _WS_2812_H_
#define _WS_2812_H_

// 使用的IO口，无需初始化
#ifndef DOUT
#define DOUT	(P3_3)
#endif

#define	DELAY_LONG	{_nop_();_nop_();_nop_();}
#define DELAY_SHORT	{_nop_();_nop_();}

#define SEND_1	{DOUT=1;DELAY_LONG;DOUT=0;DELAY_SHORT;}
#define SEND_0	{DOUT=1;DELAY_SHORT;DOUT=0;DELAY_LONG;}
#define SEND_BIT(x) {if(x) {SEND_1;} else {SEND_0;}}

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

#endif	// _WS_2812_H_
