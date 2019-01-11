#ifndef _WS_2812_H_
#define _WS_2812_H_

// ʹ�õ�IO�ڣ������ʼ��
#ifndef DOUT
#define DOUT	(P3_3)
#endif

#define	DELAY_LONG	{_nop_();_nop_();_nop_();}
#define DELAY_SHORT	{_nop_();_nop_();}

#define SEND_1	{DOUT=1;DELAY_LONG;DOUT=0;DELAY_SHORT;}
#define SEND_0	{DOUT=1;DELAY_SHORT;DOUT=0;DELAY_LONG;}
#define SEND_BIT(x) {if(x) {SEND_1;} else {SEND_0;}}

// RGB�����ṹ
typedef struct {
	unsigned int	next_pixel;		// ��һ������index
	unsigned char green;				// ��ɫֵ
	unsigned char red;					// ��ɫֵ
	unsigned char blue;					// ��ɫֵ
	unsigned char brightness;		// ����ֵ
} Pixel;

void reset();
void send_p(Pixel _p);				// ����1��������ֵ
void send_pixels(Pixel *_p_list, unsigned int _start, unsigned int _cnt);		// �������п�����ֵ
void set_pixels_color(Pixel *pixels, unsigned int _cnt, Pixel _color);

#endif	// _WS_2812_H_
