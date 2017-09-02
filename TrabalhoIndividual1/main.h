#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include "definitions.h"
#include "mygl.h"

// RENDER TIME CALC
//int oldTimeSinceStart;

GLuint tex;

void (*DrawFunc)(void);

//*****************************************************************************
void display(void)
{
	DrawFunc();

	// Copia o framebuffer para a textura.
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, FBptr);

	glEnable(GL_TEXTURE_2D);

	// Desenha o quadrilátero com a textura mapeada
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);	
		glVertex3f( 1.0f, 1.0f, 0.0f);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

	// RENDER TIME CALC
	/*int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;

    std::cout << "FPS: " << 1000/(deltaTime) << std::endl;*/
}

//*****************************************************************************
void exitprog(void)
{
	// Libera a memória referente ao framebuffer.
	if (!FBptr)
		delete [] FBptr;

	std::clog << "Exiting...\n";
}

//*****************************************************************************
void InitOpenGL(int *argc, char **argv)
{
	glutInit(argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("My OpenGL");

	// Ajusta a projeção ortográfica.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// RENDER TIME CALC
	//oldTimeSinceStart = 0;
}

//*****************************************************************************
void InitCallBacks(void)
{
	atexit( exitprog );
	glutDisplayFunc(display);
}

//*****************************************************************************
void InitDataStructures(void)
{
	// Aloca o framebuffer e inicializa suas posições com 0.
	FBptr = new unsigned char[IMAGE_WIDTH * IMAGE_HEIGHT * 5];
	
	for (unsigned int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT ; i++)
	{
		FBptr[i*4]   = 0;
		FBptr[i*4+1] = 0;
		FBptr[i*4+2] = 0;
		FBptr[i*4+3] = 255;
	}

	// Cria uma textura 2D, RGBA (8 bits por componente).
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

