/*
 * Elizabeth Qiu
 * Scene in 3D
 * built on ex8.c
 * draw house code based off
 * https://github.com/dmurtari/csci4229/blob/master/hw3/hw3.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#//define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th=0;         //  Azimuth of view angle
int ph=-5;         //  Elevation of view angle
double zh=0;      //  Rotation of teapot
int axes=0;       //  Display axes
int mode=0;       //  What to display
int FPS=60;


//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))
#define PI 3.1416

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   glColor4f(1,1,1,1);
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}



void drawCylinder(double x, double y, double z, double scaleX, double scaleY, double scaleZ, double rotate) {
	double radius = 0.3;
	double height = 0.2;

	glPushMatrix();

	glTranslated(x,y,z);
	glScaled(scaleX, scaleY, scaleZ);
	glRotated(rotate,0,0,1);

	/* Side of cylinder */
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_QUAD_STRIP);
		for(double i = 0.0; i <= 2.1*PI; i+=.05){
			glVertex3d(radius * cos(i), height, radius * sin(i));
			glVertex3d(radius * cos(i), -height, radius * sin(i));
		}
	glEnd();

    /* Top and Bottom of Cylinder */
    glColor3f(0.498039,0.137255,1.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, height, 0.0);

	for(double i = 0.0; i < 2*PI*radius*4; i+=.1) {
		glVertex3d(radius * cos(i), height, radius * sin(i));
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, -height, 0.0);

	for(double i = 0.0; i < 2*PI*radius*4; i+=.1) {
		glVertex3d(radius * cos(i), -height, radius * sin(i));
	}
	glEnd();

	glPopMatrix();
}

static void drawRoof(double x, double y, double z, double dx, double dy, double dz,double th){

  const double rooftop = 2;
  const double roofoff = 1.5;
  const double roofwid = 1.25;
  const double roofbot = .75;
  glPushMatrix();

  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);
  // Roof
  glBegin(GL_TRIANGLES);
  // Front
  glColor3ub(30,30,30);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  // Back
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  glEnd();
  // Sides of Roof
  glBegin(GL_QUADS);
  // Right side
  glColor3ub(50,50,50);
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  // Left Side
  glColor3ub(90,90,90);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  // Bottom
  glColor3ub(153,51,0);
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glEnd();

  // Draw the chimney
  glBegin(GL_QUADS);
  // Left
  glColor3ub(60,0,0);
  glVertex3f(+.5,+1,+.25);
  glVertex3f(+.5,+1,-.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+.5,+2,+.25);
  // Right
  glColor3ub(60,0,0);
  glVertex3f(+1,+1,+.25);
  glVertex3f(+1,+1,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+2,+.25);
  // Back
  glColor3ub(100,0,0);
  glVertex3f(+.5,+1,-.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+1,-.25);
  // Front
  glColor3ub(100,0,0);
  glVertex3f(+.5,+1,+.25);
  glVertex3f(+.5,+2,+.25);
  glVertex3f(+1,+2,+.25);
  glVertex3f(+1,+1,+.25);
  // Top
  glColor3ub(10,10,10);
  glVertex3f(+.5,+2,+.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+2,+.25);
  glEnd();
  glPopMatrix();
}


static void drawHouse(double x, double y, double z, double dx, double dy, double dz,double th){

  const double rooftop = 2;
  const double roofoff = 1.5;
  const double roofwid = 1.25;
  const double roofbot = .75;
  glPushMatrix();

  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);

  // Body of house
  glBegin(GL_QUADS);
  //Back
  glColor3f(0.419608,0.137255,0.556863);
  glVertex3f(-1,-1, 1);
  glVertex3f(+1,-1, 1);
  glVertex3f(+1,+1, 1);
  glVertex3f(-1,+1, 1);
  // Front
  glColor3f(0.419608,0.137255,0.556863);
  glVertex3f(+1,-1,-1);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,+1,-1);
  glVertex3f(+1,+1,-1);
  //  Right
  glColor3f(0.498039,0.137255,1.0);
  glVertex3f(+1,-1,+1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,+1,-1);
  glVertex3f(+1,+1,+1);
  //  Left
  glColor3f(0.498039,0.137255,1.0);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,-1,+1);
  glVertex3f(-1,+1,+1);
  glVertex3f(-1,+1,-1);
  //  Top
  glColor3f(0.498039,0.137255,1.0);
  glVertex3f(-1,+1,+1);
  glVertex3f(+1,+1,+1);
  glVertex3f(+1,+1,-1);
  glVertex3f(-1,+1,-1);
  //  Bottom
  glColor3f(0.419608,0.137255,0.7);
  glVertex3f(-1,-1,-1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,-1,+1);
  glVertex3f(-1,-1,+1);
  glEnd();

  // Roof
  glBegin(GL_TRIANGLES);
  // Front
  glColor3ub(30,30,30);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  // Back
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  glEnd();
  // Sides of Roof
  glBegin(GL_QUADS);
  // Right side
  glColor3ub(50,50,50);
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  // Left Side
  glColor3ub(90,90,90);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(0,+rooftop,+roofwid);
  glVertex3f(0,+rooftop,-roofwid);
  // Bottom
  glColor3ub(153,51,0);
  glVertex3f(+roofoff,+roofbot,-roofwid);
  glVertex3f(+roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,+roofwid);
  glVertex3f(-roofoff,+roofbot,-roofwid);
  glEnd();

  // Draw the chimney
  glBegin(GL_QUADS);
  // Left
  glColor3ub(60,0,0);
  glVertex3f(+.5,+1,+.25);
  glVertex3f(+.5,+1,-.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+.5,+2,+.25);
  // Right
  glColor3ub(60,0,0);
  glVertex3f(+1,+1,+.25);
  glVertex3f(+1,+1,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+2,+.25);
  // Back
  glColor3ub(100,0,0);
  glVertex3f(+.5,+1,-.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+1,-.25);
  // Front
  glColor3ub(100,0,0);
  glVertex3f(+.5,+1,+.25);
  glVertex3f(+.5,+2,+.25);
  glVertex3f(+1,+2,+.25);
  glVertex3f(+1,+1,+.25);
  // Top
  glColor3ub(10,10,10);
  glVertex3f(+.5,+2,+.25);
  glVertex3f(+.5,+2,-.25);
  glVertex3f(+1,+2,-.25);
  glVertex3f(+1,+2,+.25);
  glEnd();


  // Draw a Door
  glBegin(GL_QUADS);
  glColor3ub(100,50,0);
  // Front
  glVertex3f(+.2,-1,-1.1);
  glVertex3f(-.2,-1,-1.1);
  glVertex3f(-.2,0,-1.1);
  glVertex3f(+.2,0,-1.1);
  // Top
  glVertex3f(+.2,0,-1.1);
  glVertex3f(+.2,0,-1.0);
  glVertex3f(-.2,0,-1.0);
  glVertex3f(-.2,0,-1.1);
  // Right
  glVertex3f(+.2,0,-1.1);
  glVertex3f(+.2,-1,-1.1);
  glVertex3f(+.2,-1,-1.0);
  glVertex3f(+.2,0,-1.0);
  // Left
  glVertex3f(-.2,0,-1.1);
  glVertex3f(-.2,-1,-1.1);
  glVertex3f(-.2,-1,-1.0);
  glVertex3f(-.2,0,-1.0);
  glEnd();

  glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   glOrtho(-3, 3, -3, 3, -10, 10);
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   drawHouse(-3,0,2 , 1,1,1 , 0);
   drawHouse(6.5,0,1 , 1.5,1,1 , 30);
   drawHouse(-6.5,0,1 , 1.5,1,1 , -30);
   drawCylinder(0,0,2.5, 4, 7, 4, 0);
   drawRoof(0,0.60,2.5,1,1,1,0);
   drawCylinder(3,0,2,4,5,4,0);
   drawRoof(3,0.20,2,1,1,1,0);

   drawCylinder(0,5,-2, 4, 5, 4, 0);
   drawCylinder(5,5,-2, 4, 9, 3, 20);
   drawCylinder(-5,5,-2, 4, 9, 3, -20);

   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,25);
   //  Print the text string
   Print("Angle=%d,%d",th,ph);
   //  Render the scene
   glFlush();
   //  Make the rendered scene visible
   glutSwapBuffers();
}


/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0'){
      th = 0;
      ph = 5;
   }
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   const double dim=2.5;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Elizabeth Qiu- HW3");
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
