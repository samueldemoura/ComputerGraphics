#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <iostream>
#include <math.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

// Self-explanatory
void PutPixel(int x, int y, color c)
{
	FBptr[4*x + (4*y*IMAGE_WIDTH) + 0] = c.r;
	FBptr[4*x + (4*y*IMAGE_WIDTH) + 1] = c.g;
	FBptr[4*x + (4*y*IMAGE_WIDTH) + 2] = c.b;
	FBptr[4*x + (4*y*IMAGE_WIDTH) + 3] = c.a;
}

// Bresenham algorithm generalized to all 8 octants: the input coordinates
// are shifted into the first octant, thrown into the algorithm and then
// moved back to their original octant before being drawn on-screen.
//
// d = delta; i = input; f = final; r = error margin
void DrawLine(int xi1, int yi1, int xi2, int yi2, color c1, color c2)
{
	int oct;
	int dix = xi2 - xi1;
	int diy = yi2 - yi1;
	int x1, x2, y1, y2, xf, yf;

	// Color interpolation
	int d = sqrt(pow((xi1 - xi2),2) + pow((yi1 - yi2),2));

	color c(0, 0, 0, 0);
	float rv = (c2.r - c1.r) / (float)d;
	float gv = (c2.g - c1.g) / (float)d;
	float bv = (c2.b - c1.b) / (float)d;
	float av = (c2.a - c1.a) / (float)d;

	// Determine which octant the line belongs to
	if (dix >= 0)
	{
		if (diy >= 0)
		{
			if (dix >= diy)
			{
				oct = 0;
			}
			else
			{
				oct = 1;
			}
		}
		else
		{
			if (dix >= -diy)
			{
				oct = 7;
			}
			else
			{
				oct = 6;
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
			}
			else
			{
				oct = 2;
			}
		}
		else
		{
			if (-dix >= -diy)
			{
				oct = 4;
			}
			else
			{
				oct = 5;
			}
		}
	}

	// Move it into the first octant
	switch (oct)
	{
		case 0: 
			x1 = xi1;
			x2 = xi2;
			y1 = yi1;
			y2 = yi2;
			break;
		case 1: 
			x1 = yi1;
			x2 = yi2;
			y1 = xi1;
			y2 = xi2;
			break;
		case 2: 
			x1 = yi1;
			x2 = yi2;
			y1 = -xi1;
			y2 = -xi2;
			break;
		case 3: 
			x1 = -xi1;
			x2 = -xi2;
			y1 = yi1;
			y2 = yi2;
			break;
		case 4: 
			x1 = -xi1;
			x2 = -xi2;
			y1 = -yi1;
			y2 = -yi2;
			break;
		case 5: 
			x1 = -yi1;
			x2 = -yi2;
			y1 = -xi1;
			y2 = -xi2;
			break;
		case 6: 
			x1 = -yi1;
			x2 = -yi2;
			y1 = xi1;
			y2 = xi2;
			break;
		case 7: 
			x1 = xi1;
			x2 = xi2;
			y1 = -yi1;
			y2 = -yi2;
			break;
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

		PutPixel(xf, yf, c);
		r += dr;

		if (r >= 0.5)
		{
			++y;
			--r;
		}
	}
}

// Draws the outline of a triangle
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, color c1, color c2, color c3)
{
	DrawLine(x1, y1, x2, y2, c1, c2);
	DrawLine(x2, y2, x3, y3, c3, c1);
	DrawLine(x3, y3, x1, y1, c2, c3);
}

#endif // _MYGL_H_

