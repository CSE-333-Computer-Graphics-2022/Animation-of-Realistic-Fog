#include <GL/gl.h>

#include <GL/glut.h>
#include<iostream>
using namespace::std;

GLfloat angle = 0.1;
GLfloat density = 0.1; //set the density to 0.3 which is acctually quite thick
GLfloat fogColor[4] = {0.5,0.5,0.5,1.0}; //set the fog color to grey
GLdouble eyeView[3] = {0.0, 0.0, 5.0};

void cube(void) {
	glRotatef(angle, 0.1,0.0,0.0);
	glRotatef(angle, 0.0,0.1,0.0);
	glRotatef(angle, 0.0,0.0,0.1);
	glColor3f(1.0,0.0,0.0);
	glutSolidCube(2);
}

void init(void) {
	glEnable (GL_DEPTH_TEST); //enable the depth testing
	glEnable (GL_FOG); //enable the fog
	glFogi (GL_FOG_MODE, GL_OP_EXP_BASE_2_EXT); //set the fog mode to GL_EXP2
	glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
	glFogf (GL_FOG_DENSITY, density); //set the density to the value above
	glHint (GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
}


void keyUp(unsigned char a,int x,int y){
	printf("%c iudfn\n",a);
}

void keyUpSpl(int a,int x,int y){
	if(a==GLUT_KEY_LEFT){
		eyeView[0]--;
	}
	if(a==GLUT_KEY_RIGHT){
		eyeView[0]++;
	}
}



void display(void) {
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt (eyeView[0],eyeView[1],eyeView[2],0.0,0.0,0.0,0.0,1.0,0.0);
	cube();
	glutSwapBuffers();
	angle++;
}

void reshape(int w,int h) {
	glViewport (0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h,1.0,100.0);
	glMatrixMode (GL_MODELVIEW);
}

int main(int argc,char **argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("A basic OpenGL Window");
	init ();
	glutDisplayFunc (display);
	glutIdleFunc (display);
	glutReshapeFunc (reshape);
	// glutKeyboardFunc(keyUp);
	glutSpecialFunc(keyUpSpl);
	glutMainLoop();
	return 0;
}
