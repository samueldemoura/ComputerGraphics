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
		float r, g, b, a;

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
// d = delta; i = input; r = error margin
void DrawLine(vect2d v1, vect2d v2, color c1, color c2)
{
	int oct;
	int dix = v2.x - v1.x;
	int diy = v2.y - v1.y;
	int x1, x2, y1, y2;

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

	// Color interpolation
	color c = c1;
	float rv = (c2.r - c1.r) / dx;
	float gv = (c2.g - c1.g) / dx;
	float bv = (c2.b - c1.b) / dx;
	float av = (c2.a - c1.a) / dx;

	for (int x = x1; x < x2; ++x)
	{
		// Interpolate colors
		c.r += rv;
		c.g += gv;
		c.b += bv;
		c.a += av;

		// Shift coordinates back into original octant
		switch (oct)
		{
			case 0: 
				PutPixel(vect2d(x, y), c);
				break;
			case 1: 
				PutPixel(vect2d(y, x), c);
				break;
			case 6: 
				PutPixel(vect2d(y, -x), c);
				break;
			case 3: 
				PutPixel(vect2d(-x, y), c);
				break;
			case 4: 
				PutPixel(vect2d(-x, -y), c);
				break;
			case 5: 
				PutPixel(vect2d(-y, -x), c);
				break;
			case 2: 
				PutPixel(vect2d(-y, x), c);
				break;
			case 7: 
				PutPixel(vect2d(x, -y), c);
				break;
		}

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
	DrawLine(v2, v3, c2, c3);
	DrawLine(v3, v1, c3, c1); 
}

#endif // _MYGL_H_

