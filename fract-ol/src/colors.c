#include "colors.h"

static void	init_purple(int *p)
{
	p[0] = 0xE6E6FA;
	p[1] = 0xD8BFD8;
	p[2] = 0xDDA0DD;
	p[3] = 0xEE82EE;
	p[4] = 0xDA70D6;
	p[5] = 0xFF00FF;
	p[6] = 0xFF00FF;
	p[7] = 0xBA55D3;
	p[8] = 0x9370DB;
	p[9] = 0x663399;
	p[10] = 0x8A2BE2;
	p[11] = 0x9400D3;
	p[12] = 0x9932CC;
	p[13] = 0x8B008B;
	p[14] = 0x800080;
	p[15] = 0x6A5ACD;
	p[16] = 0x7B68EE;
	p[17] = 0x483D8B;
	p[18] = 0x4B0082;
}

static void	init_green(int *p)
{
	p[0] = 0xADFF2F;
	p[1] = 0x7FFF00;
	p[2] = 0x7CFC00;
	p[3] = 0x00FF00;
	p[4] = 0x32CD32;
	p[5] = 0x98FB98;
	p[6] = 0x90EE90;
	p[7] = 0x00FA9A;
	p[8] = 0x00FF7F;
	p[9] = 0x3CB371;
	p[10] = 0x228B22;
	p[11] = 0x008000;
	p[12] = 0x006400;
	p[13] = 0x9ACD32;
	p[14] = 0x6B8E23;
	p[15] = 0x808000;
	p[16] = 0x556B2F;
	p[17] = 0x66CDAA;
	p[18] = 0x8FBC8B;
	p[19] = 0x20B2AA;
	p[20] = 0x008B8B;
	p[21] = 0x008080;
}

static void	init_brown(int *p)
{
	p[0] = 0xFFF8DC;
	p[1] = 0xFFEBCD;
	p[2] = 0xFFE4C4;
	p[3] = 0xF5DEB3;
	p[4] = 0xFFDEAD;
	p[5] = 0xD2B48C;
	p[6] = 0xDEB887;
	p[7] = 0xF4A460;
	p[8] = 0xDAA520;
	p[9] = 0xCD853F;
	p[10] = 0xB8860B;
	p[11] = 0xD2691E;
	p[12] = 0xA0522D;
	p[13] = 0x8B4513;
	p[14] = 0xA52A2A;
	p[15] = 0x800000;
}

void	init_palette(int *p, int color)
{
	if (color == BROWN)
		init_brown(p);
	else if (color == PURPLE)
		init_purple(p);
	else
		init_green(p);
}
