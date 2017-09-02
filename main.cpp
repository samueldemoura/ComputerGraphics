#include "main.h"
#include <math.h>

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

	for (int padding = IMAGE_HEIGHT/4; padding < IMAGE_HEIGHT/2; padding += 4)
	{
		DrawTriangle(padding, IMAGE_HEIGHT - padding,
					IMAGE_WIDTH / 2, padding,
					IMAGE_WIDTH - padding, IMAGE_HEIGHT - padding,
					color(255, 0, 0, 255),
					color(0, 255, 0, 255),
					color(0, 0, 255, 255));
	}
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

