#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

	/*for (int padding = IMAGE_HEIGHT/4; padding < IMAGE_HEIGHT/2; padding += 4)
	{
		DrawTriangle(vect2d(padding, IMAGE_HEIGHT - padding),
					 vect2d(IMAGE_WIDTH / 2, padding),
					 vect2d(IMAGE_WIDTH - padding, IMAGE_HEIGHT - padding),
					 color(255, 0, 0, 255),
					 color(0, 255, 0, 255),
					 color(0, 0, 255, 255));
	}*/

	vect2d v1 = vect2d(32, 480); // Leftmost vertex
	vect2d v2 = vect2d(256, 64); // Center-top vertex
	vect2d v3 = vect2d(512 - 32, 320); // Rightmost vertex

	// v1 v3 v2
	DrawFilledTriangle(v1, v2, v3,
			   color(255, 0, 0, 255),
			   color(0, 255, 0, 255),
			   color(0, 0, 255, 255));

	/*for (int i = 0; i < IMAGE_HEIGHT; ++i)
	{
		DrawLine(vect2d(0, i),
				 vect2d(IMAGE_WIDTH, i),
				 color( (float)i * 255/512, 255 - (float)i * 255/512, 100 + i/512, 255 ),
				 color( 0, (float)i * 255/512, 255 - (float)i * 255/512, 255));
	}*/

	/*DrawLine(vect2d(IMAGE_WIDTH / 3, IMAGE_HEIGHT * 2/3), vect2d(IMAGE_WIDTH * 2/3, IMAGE_HEIGHT / 3),
			color(255, 0, 0, 255), color(110, 110, 255, 255));*/
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

