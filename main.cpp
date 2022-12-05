#include <GL/gl.h>
#include <GL/glut.h>
#include<iostream>

GLfloat angle = 0.1;
GLfloat density = 0.1; //set the density to 0.1 which is not that thick
GLfloat fogColor[4] = {0.5,0.5,0.5,1.0}; //set the fog color to grey
GLdouble eyeView[3] = {0.0, 0.0, 5.0};

// defining a shape in this case it's a solid cube
void cube(void) {
	//rotating the shape by an angle of 0.1 degree along the vector (0.05, 0, 0) (x axis)
	glRotatef(angle, 0.05,0.0,0.0);

	//rotating the shape by an angle of 0.1 degree along the vector (0, 0.05, 0) (y axis)
	glRotatef(angle, 0.0,0.05,0.0);
	
	//rotating the shape by an angle of 0.1 degree along the vector (0, 0, 0.05) (z axis)
	glRotatef(angle, 0.0,0.0,0.05);

	//define the color of the shape to red
	glColor3f(1.0,0.0,0.0);

	//defining the shape as solid cube
	glutSolidCube(2);
}

void init(void) {
	glEnable (GL_DEPTH_TEST); //enable the depth testing
	glEnable (GL_FOG); //enable the fog

	glFogi (GL_FOG_MODE, GL_EXP); //set the fog mode to GL_EXP
	// glFogi (GL_FOG_MODE, GL_OP_EXP_BASE_2_EXT); //set the fog mode to GL_OP_EXP_BASE_2_EXT
	// glFogi (GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2
	// glFogi (GL_FOG_MODE, GL_LINEAR); //set the fog mode to GL_LINEAR
	
	glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
	glFogf (GL_FOG_DENSITY, density); //set the density to the value above
	glHint (GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
}


void keyUp(unsigned char a,int x,int y){
	printf("%c iudfn\n",a);
}

void keyUpSpl(int a,int x,int y){
	// on pressing left and right arrow key you can change the eyeView matrix along the x axis
	if(a==GLUT_KEY_LEFT){
		eyeView[0]-=0.1;
	}
	if(a==GLUT_KEY_RIGHT){
		eyeView[0]+=0.1;
	}
}



void display(void) {
	//setting up the background color to black
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//starting from origin before applying matrix operations (semantically equivalent to defining a 4x4 identity matrix)
	glLoadIdentity();

	//creating a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an up vector
	gluLookAt (eyeView[0],eyeView[1],eyeView[2],0.0,0.0,0.0,0.0,1.0,0.0);

	//calling the cube function which defines a cube on the screen
	cube();

	// swapping buffer
	glutSwapBuffers();
	
	//incrementing the angle by which it'll rotate
	angle+=0.75;
}

void reshape(int w,int h) {
	// to make the screen responsive
	// in other word the program will run the same way in all size of screen
	glViewport (0,0,(GLsizei)w, (GLsizei)h);
	
	//starting from origin before applying matrix operations
	glLoadIdentity ();

	//matrix operations to the projection matrix stack.
	glMatrixMode (GL_PROJECTION);

	//specifying a viewing frustum into the world coordinate system
	gluPerspective (60, (GLfloat)w / (GLfloat)h,1.0,100.0);
	
	//matrix operations to the modelview matrix stack. 
	glMatrixMode (GL_MODELVIEW);
}

int main(int argc,char **argv) {
	// initialize the GLUT library
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (500, 500); // defining up window size
	glutInitWindowPosition (100, 100); // positioning the window on screen
	glutCreateWindow ("Real Time Fog Animation"); // title of the window
	init (); // initializing the environment, for this case setting up foggy environment
	glutDisplayFunc (display); // rendering the display using the display function
	glutIdleFunc (display); // catching any kind of activities on the window
	glutReshapeFunc (reshape); // making the window responsive according the the display size and aspect ratio
	// glutKeyboardFunc(keyUp);
	glutSpecialFunc(keyUpSpl); // defining the functionalities of special keys on the keyboard
	glutMainLoop(); // calling callback function over and over
	return 0;
}

// reference : https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMatrixMode.xml