#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h> // sqrt, pow

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

// For easier handling of function arguments
class color
{
	public:
		int r, g, b, a;

		color(int r, int g, int b, int a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
};

class vect2d
{
	public:
		int x, y;

		vect2d(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
};

// Self-explanatory
void PutPixel(vect2d v, color c)
{
	FBptr[4*v.x + (4*v.y*IMAGE_WIDTH) + 0] = c.r;
	FBptr[4*v.x + (4*v.y*IMAGE_WIDTH) + 1] = c.g;
	FBptr[4*v.x + (4*v.y*IMAGE_WIDTH) + 2] = c.b;
	FBptr[4*v.x + (4*v.y*IMAGE_WIDTH) + 3] = c.a;
}

// Bresenham algorithm generalized to all 8 octants: the input coordinates
// are shifted into the first octant, thrown into the algorithm and then
// moved back to their original octant before being drawn on-screen.
//
// d = delta; i = input; f = final; r = error margin
void DrawLine(vect2d v1, vect2d v2, color c1, color c2)
{
	int oct;
	int dix = v2.x - v1.x;
	int diy = v2.y - v1.y;
	int x1, x2, y1, y2, xf, yf;

	// Color interpolation
	int d = sqrt(pow((dix),2) + pow((diy),2));

	color c(0, 0, 0, 0);
	float rv = (c2.r - c1.r) / (float)d;
	float gv = (c2.g - c1.g) / (float)d;
	float bv = (c2.b - c1.b) / (float)d;
	float av = (c2.a - c1.a) / (float)d;

	// Determine which octant the line belongs to, save
	// it for later and move it into the first octant
	if (dix >= 0)
	{
		if (diy >= 0)
		{
			if (dix >= diy)
			{
				oct = 0;
				x1 = v1.x;
				x2 = v2.x;
				y1 = v1.y;
				y2 = v2.y;
			}
			else
			{
				oct = 1;
				x1 = v1.y;
				x2 = v2.y;
				y1 = v1.x;
				y2 = v2.x;
			}
		}
		else
		{
			if (dix >= -diy)
			{
				oct = 7;
				x1 = v1.x;
				x2 = v2.x;
				y1 = -v1.y;
				y2 = -v2.y;
			}
			else
			{
				oct = 6;
				x1 = -v1.y;
				x2 = -v2.y;
				y1 = v1.x;
				y2 = v2.x;
			}
		}
	}
	else
	{
		if (diy >= 0)
		{
			if (-dix >= diy)
			{
				oct = 3;
				x1 = -v1.x;
				x2 = -v2.x;
				y1 = v1.y;
				y2 = v2.y;
			}
			else
			{
				oct = 2;
				x1 = v1.y;
				x2 = v2.y;
				y1 = -v1.x;
				y2 = -v2.x;
			}
		}
		else
		{
			if (-dix >= -diy)
			{
				oct = 4;
				x1 = -v1.x;
				x2 = -v2.x;
				y1 = -v1.y;
				y2 = -v2.y;
			}
			else
			{
				oct = 5;
				x1 = -v1.y;
				x2 = -v2.y;
				y1 = -v1.x;
				y2 = -v2.x;
			}
		}
	}

	// Bresenham's algorithm starts here
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dr = dy / dx;
	float r = 0;

	int y =  y1;

	for (int x = x1; x < x2; ++x)
	{
		// Shift coordinates back into original octant
		switch (oct)
		{
			case 0: 
				xf = x;
				yf = y;
				break;
			case 1: 
				xf = y;
				yf = x;
				break;
			case 6: 
				xf = y;
				yf = -x;
				break;
			case 3: 
				xf = -x;
				yf = y;
				break;
			case 4: 
				xf = -x;
				yf = -y;
				break;
			case 5: 
				xf = -y;
				yf = -x;
				break;
			case 2: 
				xf = -y;
				yf = x;
				break;
			case 7: 
				xf = x;
				yf = -y;
				break;
		}

		// Color interpolation
		c.r = c1.r + rv*(x2 - x);
		c.g = c1.g + gv*(x2 - x);
		c.b = c1.b + bv*(x2 - x);
		c.a = c1.a + av*(x2 - x);

		PutPixel(vect2d(xf, yf), c);
		r += dr;

		if (r >= 0.5)
		{
			++y;
			--r;
		}
	}
}

// Draws the outline of a triangle
void DrawTriangle(vect2d v1, vect2d v2, vect2d v3, color c1, color c2, color c3)
{
	DrawLine(v1, v2, c1, c2);
	DrawLine(v2, v3, c3, c1);
	DrawLine(v3, v1, c2, c3);
}

#endif // _MYGL_H_

