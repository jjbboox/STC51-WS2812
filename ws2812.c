#include <reg51.h>
#include <intrins.h>
#include "ws2812.h"

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

// RESETÐÅºÅ
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
