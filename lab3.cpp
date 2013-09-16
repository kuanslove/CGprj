////////////////////////////////////////////////////////
//
// CS4611 Lab3, 11/2011.
//
////////////////////////////////////////////////////////

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else*/
#include <GL/glut.h>
//#endif

////////////////////////////////////////////////////////
// struct definition
////////////////////////////////////////////////////////

//image type - contains height, width, and data
struct Image {
  unsigned long sizeX;
  unsigned long sizeY;
  char *data;
};
typedef struct Image Image;

////////////////////////////////////////////////////////
// global constant and variable definition
////////////////////////////////////////////////////////
float theta=0;
int delta=0;


const int screenWidth = 600;
const int screenHeight = 600;

//these consts are defined for scaling the scene
const int screenPace = 60;
const double scalePace = 0.2; //the incresement of scale value
const double scaleLow = 0.1; //the minimum scale value
const double scaleHigh = 3.0; //the maximum scale value

//these consts are defined for the objects of the scene
//consts for floor object
const double floorWidth = 4.0;
const double floorHeight = 0.05;

//consts for dustbin object
const double dustbinWidth = 0.3;
const double dustbinHeight = 0.5;

//consts for table object
const double tableTopWidth = 2.0;
const double tableTopHeight = 0.1;
const double tableLegWidth = 0.1;
const double tableLegHeight = 1.0;
const double distTable = tableTopWidth / 2.0 - tableLegWidth / 2.0;

//consts for chair object
const double chairTopWidth = 0.5;
const double chairTopHeight = 0.05;
const double chairLegWidth = 0.05;
const double chairLegHeight = 0.5;
const double distchair = chairTopWidth / 2.0 - chairLegWidth / 2.0;
const double chairBackWidth = 0.05;
const double chairBackHeight = 0.5;
//const double distChair2 = chairTopWidth / 2.0 - chairBackWidth / 2.0;
const double chairArmLowerWidth = 0.05;
const double chairArmLowerHeight = 0.2;
//const double distChair3 = chairTopWidth / 2.0 - chairArmLowerWidth / 2.0;
const double chairArmUpperWidth = 0.05;
const double chairArmUpperHeight = 0.4;

//consts for teapot object
const double teapotSize = 0.2;

//consts for teacup object
const double teacupWidth = 0.05;
const double teacupHeight = 0.1;

//consts for lamp object
const double lampBaseWidth = 0.15;
const double lampBaseHeight = 0.25;
const double lampArmWidth = 0.05;
const double lampArmHeight = 0.5;
const double lampTopBase = 0.3;
const double lampTopHeight = 0.1;

//const for the material properties
GLfloat floor_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat floor_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat floor_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat floor_shininess[] = {5.0f};

GLfloat dustbin_ambient[] = {0.1f, 0.18725f, 0.1745f, 0.5f};
GLfloat dustbin_diffuse[] = {0.396f,  0.74151f, 0.69102f, 0.5f};
GLfloat dustbin_specular[] = {0.297254f, 0.30829f, 0.306678f, 0.5f};
GLfloat dustbin_shininess[] = {2.0f};

GLfloat furniture_ambient[] = {0.2125f, 0.1275f, 0.054f, 1.0f};
GLfloat furniture_diffuse[] = {0.714f, 0.4284f, 0.18144f, 1.0f};
GLfloat furniture_specular[] = {0.393548f, 0.271906f, 0.166721f, 1.0f};
GLfloat furniture_shininess[] = {3.0f};

GLfloat teapot_ambient[] = {0.33f, 0.22f, 0.03f, 1.0f};
GLfloat teapot_diffuse[] = {0.78f, 0.57f, 0.11f, 1.0f};
GLfloat teapot_specular[] = {0.99f, 0.91f, 0.81f, 1.0f};
GLfloat teapot_shininess[] = {27.8f};

GLfloat lamp_ambient[] = {0.1f, 0.1f, 0.5f, 1.0f};
GLfloat lamp_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lamp_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lamp_shininess[] = {50.0f};

//const for the light source
//light one: white
GLfloat light_ambient0[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat light_diffuse0[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_specular0[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_position0[] = {2.0f, 4.0f, 2.0f, 1.0f};

//light two: cyan - pointing to the right wall
GLfloat light_ambient1[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat light_diffuse1[] = {0.1f, 1.0f, 1.0f, 1.0f};
GLfloat light_specular1[] = {0.1f, 1.0f, 1.0f, 1.0f};
GLfloat light_position1[] = {-2.0f, 4.0f, 2.0f, 1.0f};

//light three: magenta - pointing to the left wall
GLfloat light_ambient2[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat light_diffuse2[] = {1.0f, 0.1f, 1.0f, 1.0f};
GLfloat light_specular2[] = {1.0f, 0.1f, 1.0f, 1.0f};
GLfloat light_position2[] = {2.0f, 4.0f, -2.0f, 1.0f};

//light four: yellow
GLfloat light_ambient3[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat light_diffuse3[] = {1.0f, 1.0f, 0.1f, 1.0f};
GLfloat light_specular3[] = {1.0f, 1.0f, 0.1f, 1.0f};
GLfloat light_position3[] = {-2.0f, 4.0f, -2.0f, 1.0f};

//light five: white (spot light)
GLfloat light_ambient4[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat light_diffuse4[] = {1.0f, 1.1f, 1.1f, 1.0f};
GLfloat light_specular4[] = {1.0f, 1.1f, 1.1f, 1.0f};
GLfloat light_position4[] = {-1.0f, 3.0f, -1.0f, 1.0f};
GLfloat light_direction4[] = {0.0f, -1.0f, 0.0f, 1.0f};

//fog color
GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};

GLfloat fogDensity = 0.35f;
GLfloat fogStart = 3.0f;
GLfloat fogEnd = 10.0f;

enum {OFF, ON};

//initial setting for lights: lighting, light1, light2, light3, light4 and light5
int light_setting[] = {ON, ON, OFF, OFF, OFF, OFF};
int ls_bak[] = {ON, ON, OFF, OFF, OFF, OFF};

int fogSetting = OFF; //fog setting
int textureSetting = ON; //texture setting
GLenum shadeModel = GL_SMOOTH; //shadeModel setting
int shadeModelSetting=ON;
//the cylinder object
GLUquadricObj* qobj;

const double pi = 3.1415926;

//camera position
const double originalCameraX = 5.0;
const double originalCameraY = 5.0;
const double originalCameraZ = 5.0;
double cameraX = 5.0;
double cameraY = 5.0;
double cameraZ = 5.0;

//center of interest
const double originalCoiX = 0.0;
const double originalCoiY = 0.0;
const double originalCoiZ = 0.0;
double coiX = 0.0;
double coiY = 0.0;
double coiZ = 0.0;

//yaw and pitch
const double displacement = 10.0;
double yawDegree = 0.25 * pi;
double pitchDegree = -0.8041 * pi;
double cosYaw = 0.0, sinYaw = 0.0, cosPitch = 0.0, sinPitch = 0.0;
bool mouse_yaw_picth = false;


//current and previous positions of the mouse, used in scaling and rotating the scene
int currentX = 0;
int currentY = 0;
int previousX = 0;
int previousY = 0;

const GLint texImage1Name = 2001;
const GLint texImage2Name = 2002;
const GLint texCheckerBoardName = 2003;

int menu;

////////////////////////////////////////////////////////
// function definition and implementation
////////////////////////////////////////////////////////

void myMenu(int);

static unsigned int getint(FILE *fp)
{
  int c, c1, c2, c3;
  // get 4 bytes
  c = getc(fp); c1 = getc(fp); c2 = getc(fp); c3 = getc(fp);
  return ((unsigned int) c) + (((unsigned int) c1) << 8) + (((unsigned int) c2) << 16) + (((unsigned int) c3) << 24);
}
static unsigned int getshort(FILE *fp)
{
  int c, c1;
  //get 2 bytes
  c = getc(fp); c1 = getc(fp);
  return ((unsigned int) c) + (((unsigned int) c1) << 8);
}
int loadImageFromFile(char *filename, Image *image)
{
  FILE *file;

  unsigned long size; //size of the image in bytes
  unsigned long i; //standard counter
  unsigned short int planes;//number of planes in image (must be 1)
  unsigned short int bpp; //number of bits per pixel (must be 24)
  char temp; //temporary color storage for bgr-rgb conversion

  //make sure the file is there.
  if ((file = fopen(filename, "rb"))==NULL) {
    printf("File Not Found : %s\n", filename);
    return 0;
  }

  //read the head of the image file
  fseek(file, 18, SEEK_CUR);
  //seek through the bmp header, up to the width/height
  // read the width and height
  image->sizeX = getint (file); //printf("Width of %s: %lu\n", filename, image->sizeX);
  image->sizeY = getint (file);
  //printf("Height of %s: %lu\n", filename, image->sizeY);
  size = image->sizeX * image->sizeY * 3;
  // calculate the size (assuming 24 bits or 3 bytes per pixel)
  planes = getshort(file);
  // read the planes
  if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, planes);
    return 0;
  }

  bpp = getshort(file);
  // read the bpp
  if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    return 0;
  }

  fseek(file, 24, SEEK_CUR);
  // seek past the rest of the bitmap header
  // read the data of the image file
  image->data = (char *)malloc(size);
  if (image->data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    return 0;
  }

  if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s\n", filename);
    return 0;
  }

  for (i = 0;i < size;i+= 3) { // reverse all of the colors(bgr -> rgb)
    temp = image->data[i];
    image->data[i] = image->data[i + 2];
    image->data[i + 2] = temp;
  }
  return 1;
}
void getTexture(char *imageFileName, Image *image, GLint texImageName)
{
  image = (Image *) malloc(sizeof(Image));
  // allocate space for texture
  if (image == NULL) {
    printf("Error allocating space for image");
    exit(0);
  }

  if (!loadImageFromFile(imageFileName, image)) exit(1);
  glBindTexture(GL_TEXTURE_2D, texImageName);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // scale linearly when image bigger than texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // scale linearly when image smalled than texture
  glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
}
void drawTable(){
	//draw the four table legs
	glPushMatrix();
    glTranslated(distTable, tableLegHeight / 2.0, -distTable); //front left leg
    glScaled(tableLegWidth, tableLegHeight, tableLegWidth);
    glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
    glTranslated(distTable, tableLegHeight / 2.0, distTable); //front right leg
    glScaled(tableLegWidth, tableLegHeight, tableLegWidth);
    glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
    glTranslated(-distTable, tableLegHeight / 2.0, -distTable); //back left leg
    glScaled(tableLegWidth, tableLegHeight, tableLegWidth);
    glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
    glTranslated(-distTable, tableLegHeight / 2.0, distTable); //back right leg
    glScaled(tableLegWidth, tableLegHeight, tableLegWidth);
    glutSolidCube(1.0);
	glPopMatrix();

	glTranslated(0.0, tableLegHeight, 0.0);

	//draw the table top
	glPushMatrix();
    glTranslated(0.0, tableTopHeight / 2.0, 0.0);
    glScaled(tableTopWidth, tableTopHeight, tableTopWidth);
    glutSolidCube(1.0);
	glPopMatrix();
}
void chair(){
    //glColor3f(0.5,0.8,0.3);
    glPushMatrix();
    glTranslatef(distchair,chairLegHeight/2.0,distchair);
    glScalef(chairLegWidth,chairLegHeight,chairLegWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-distchair,chairLegHeight/2.0,distchair);
    glScalef(chairLegWidth,chairLegHeight,chairLegWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(distchair,chairLegHeight/2.0,-distchair);
    glScalef(chairLegWidth,chairLegHeight,chairLegWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-distchair,chairLegHeight/2.0,-distchair);
    glScalef(chairLegWidth,chairLegHeight,chairLegWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,chairLegHeight+chairTopHeight/2.0,0);
    glScalef(chairTopWidth,chairTopHeight,chairTopWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(distchair,chairLegHeight+chairTopHeight+chairBackHeight/2.0,0);
    glScalef(chairBackWidth,chairBackHeight,chairBackHeight);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,chairLegHeight+chairTopHeight+chairArmLowerHeight/2.0,distchair);
    glScalef(chairArmLowerWidth,chairArmLowerHeight,chairArmLowerWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,chairLegHeight+chairTopHeight+chairArmLowerHeight/2.0,-distchair);
    glScalef(chairArmLowerWidth,chairArmLowerHeight,chairArmLowerWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,chairLegHeight+chairTopHeight+chairArmLowerHeight+chairArmUpperWidth/2.0,distchair);
    glScalef(chairArmUpperHeight,chairArmUpperWidth,chairArmUpperWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,chairLegHeight+chairTopHeight+chairArmLowerHeight+chairArmUpperWidth/2.0,-distchair);
    glScalef(chairArmUpperHeight,chairArmUpperWidth,chairArmUpperWidth);
    glutSolidCube(1.0);
    glPopMatrix();
}
void dustbin(){
    //glColor3f(0,0.4,0.5);
    glPushMatrix();
    glTranslatef(0,dustbinHeight/2.0,0);
    glScalef(dustbinWidth,dustbinHeight,dustbinWidth);
    glutSolidCube(1.0);
    glPopMatrix();
}
void lamp(){
    //glColor3f(0,0,1);
    glPushMatrix();
    glRotatef(-90,1,0,0);

        glPushMatrix();
        //glTranslatef(0, 0, lampBaseHeight/2.0);
        gluCylinder(qobj,lampBaseWidth,lampBaseWidth,lampBaseHeight,8,8);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, lampBaseHeight);
        //+lampArmHeight/2.0); Cylinder and Cone start at 0 level rather than -1/2*height
        gluCylinder(qobj,lampArmWidth,lampArmWidth,lampArmHeight,8,8);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, lampBaseHeight+lampArmHeight);
        //+lampTopHeight/2.0);
        glutSolidCone(lampTopBase,lampTopHeight,8,8);
        glPopMatrix();

    glPopMatrix();
}
void tpot(){
    //glColor3f(1,0,0);
    glutSolidTeapot(teapotSize);
}
void tcup(){
        //glColor3f(1,0,0);
        glPushMatrix();
        //glTranslatef(0, 0, lampBaseHeight/2.0);
        glRotatef(-90,1,0,0);
        gluCylinder(qobj,teacupWidth,teacupWidth,teacupHeight,8,8);
        glPopMatrix();
}
void myDisplay(void){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0 * screenWidth / screenHeight, 0.1, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, coiX, coiY, coiZ, 0.0, 1.0, 0.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  //set the light source properties
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

  glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position1);


  //set the remaining light sources	- write your code here
  glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
  glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
  glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

  glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient3);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse3);
  glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular3);
  glLightfv(GL_LIGHT3, GL_POSITION, light_position3);

  glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient4);
  glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse4);
  glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular4);
  glLightfv(GL_LIGHT4, GL_POSITION, light_position4);
  //turn on or off the fog - write your code here
if(fogSetting){
    glEnable(GL_FOG);
}
else {
    glDisable(GL_FOG);

}





  glColor3d(0.0, 0.0, 0.0);

/////////////////////////////////////////floor////////////////////////////////////////
  glMaterialfv(GL_FRONT, GL_AMBIENT, floor_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, floor_shininess);

glRotatef(theta,0,1,0);
  //draw the bottom floor
  glPushMatrix();
  glTranslatef(0,floorHeight/2.0,0);
  glScaled(floorWidth, floorHeight, floorWidth);

  glutSolidCube(1.0);
  glPopMatrix();

  //draw the left wall
  glPushMatrix();
  glTranslated(-floorWidth / 2.0, floorWidth / 2.0, 0.0);
  glRotated(90.0, 0.0, 0.0, 1.0);
  glScaled(floorWidth, floorHeight, floorWidth);
  glutSolidCube(1.0);
  glPopMatrix();

  //draw the right wall
  glPushMatrix();
  glTranslated(0.0, floorWidth / 2.0, -floorWidth / 2.0);
  glRotated(90.0, 1.0, 0.0, 0.0);
  glScaled(floorWidth, floorHeight, floorWidth);
  glutSolidCube(1.0);
  glPopMatrix();

  if (textureSetting == ON) glEnable(GL_TEXTURE_2D);

  //map an image texture on the left wall
  glBindTexture(GL_TEXTURE_2D, texImage1Name);
  glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3d(-floorWidth / 2.0 + floorHeight, 1.5, floorWidth / 2.0 - 1.25);
    glTexCoord2f(1.0, 0.0); glVertex3d(-floorWidth / 2.0 + floorHeight, 1.5, -floorWidth / 2.0 + 1.25);
    glTexCoord2f(1.0, 1.0); glVertex3d(-floorWidth / 2.0 + floorHeight, floorWidth - 0.5, -floorWidth / 2.0 + 1.25);
    glTexCoord2f(0.0, 1.0); glVertex3d(-floorWidth / 2.0 + floorHeight, floorWidth - 0.5, floorWidth / 2.0 - 1.25);
  glEnd();

  //map another image texture on the right wall - write your code here
  glBindTexture(GL_TEXTURE_2D, texImage2Name);
  glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3d(-floorWidth / 2.0 + 0.5, 1.5, -floorWidth / 2.0 + floorHeight);
    glTexCoord2f(1.0, 0.0); glVertex3d( floorWidth / 2.0 - 0.5, 1.5, -floorWidth / 2.0 + floorHeight);
    glTexCoord2f(1.0, 1.0); glVertex3d( floorWidth / 2.0 - 0.5, floorWidth - 0.5,-floorWidth / 2.0 + floorHeight);
    glTexCoord2f(0.0, 1.0); glVertex3d(-floorWidth / 2.0 + 0.5, floorWidth - 0.5,-floorWidth / 2.0 + floorHeight);
  glEnd();
  //map the checkerboard texture on the bottom floor - write your code here






  glBindTexture(GL_TEXTURE_2D, texCheckerBoardName);
  glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3d(-floorWidth / 2.0 , floorHeight+0.001, floorWidth / 2.0 );
    glTexCoord2f(1.0, 0.0); glVertex3d( floorWidth / 2.0 , floorHeight+0.001, floorWidth / 2.0 );
    glTexCoord2f(1.0, 1.0); glVertex3d( floorWidth / 2.0 , floorHeight+0.001, -floorWidth / 2.0 );
    glTexCoord2f(0.0, 1.0); glVertex3d(-floorWidth / 2.0 , floorHeight+0.001, -floorWidth / 2.0 );
  glEnd();






  if (textureSetting == ON) glDisable(GL_TEXTURE_2D);
//////////////////////////////////////////floor////////////////////////////////////////

  glTranslated(0.0, floorHeight, 0.0);


	//set up furniture (table, chairs) material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, furniture_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, furniture_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, furniture_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, furniture_shininess);

	//draw the two chairs - write your code here
    glPushMatrix();
    glTranslatef(-floorWidth / 4.0, 0, floorWidth / 4.0);
    glRotatef(-90,0,1,0);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(floorWidth / 4.0, 0, -floorWidth / 4.0);
    chair();
    glPopMatrix();

	//shift to the quad on the floor which the table will be placed
	glPushMatrix();
	glTranslated(-1.0, 0.0, -1.0);

	//draw the table
	drawTable();

	//raise to the table top: all the remaining objects are above the table
	glTranslated(0.0, tableTopHeight, 0.0);

	//set up teapot/teacup material properties - write your code here
	glMaterialfv(GL_FRONT, GL_AMBIENT, teapot_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, teapot_shininess);
	//draw the teapot - write your code here
	glPushMatrix();
	glTranslatef(0,0.15,0);
	glRotatef(45,0,1,0);
    tpot();
    glPopMatrix();
	//draw the teacup - write your code here
    glPushMatrix();
    glTranslatef(0, 0, tableTopWidth / 4.0);
    tcup();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(tableTopWidth / 4.0, 0, 0);
    tcup();
    glPopMatrix();
	//set up lamp material properties - write your code here
	glMaterialfv(GL_FRONT, GL_AMBIENT, lamp_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lamp_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lamp_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, lamp_shininess);
	//draw the lamp - write your code here
    glPushMatrix();
    glTranslatef(-tableTopWidth / 4.0, 0, -tableTopWidth / 4.0);
    lamp();
    glPopMatrix();

	glPopMatrix();
	//set up dustbin material properties - write your code here
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMaterialfv(GL_FRONT, GL_AMBIENT, dustbin_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dustbin_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, dustbin_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, dustbin_shininess);
	//draw the dustbin - write your code here
  glPushMatrix();
  glTranslated(floorWidth / 4.0, dustbinHeight/2.0, floorWidth / 4.0);
  glScaled(dustbinWidth, dustbinHeight, dustbinWidth);
  glutSolidCube(1.0);
  glPopMatrix();
glDisable(GL_BLEND);
  glutSwapBuffers();
}
void myMouse(int button, int state, int x, int y){
  int dtX, dtY;
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      previousX = x;
      previousY = screenHeight - y;
    }
    else if (state == GLUT_UP) {
      currentX = x;
      currentY = screenHeight - y;
      dtX = currentX - previousX;
      dtY = currentY - previousY;
      yawDegree = yawDegree - (dtX * pi) / (displacement * 180.0);
      pitchDegree = pitchDegree + (dtY * pi) / (displacement * 180.0);
      sinYaw = sin(yawDegree);
      cosYaw = cos(yawDegree);
      sinPitch = sin(pitchDegree);
      cosPitch = cos(pitchDegree);
      coiX = cameraX + cosPitch * cosYaw;
      coiY = cameraY + sinPitch;
      coiZ = cameraZ + cosPitch * sinYaw;
	  if (!mouse_yaw_picth) mouse_yaw_picth = true;
      myDisplay();
    }
  }
}
void set_Lights_and_ShadeModel(void){
  light_setting[0] == OFF ? glDisable(GL_LIGHTING) : glEnable(GL_LIGHTING);
  light_setting[1] == OFF ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
  light_setting[2] == OFF ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
  light_setting[3] == OFF ? glDisable(GL_LIGHT2) : glEnable(GL_LIGHT2);
  light_setting[4] == OFF ? glDisable(GL_LIGHT3) : glEnable(GL_LIGHT3);
  light_setting[5] == OFF ? glDisable(GL_LIGHT4) : glEnable(GL_LIGHT4);
  //set properties for other light sources - write your code here
  shadeModel=(shadeModelSetting==OFF)?GL_FLAT:GL_SMOOTH;
  glShadeModel(shadeModel);
}
void createMenu(void){
  menu = glutCreateMenu(myMenu);
    light_setting[0] == OFF ? glutAddMenuEntry("Turn Lighting On [a]", 'a') : glutAddMenuEntry("Turn Lighting Off [a]", 'a');
    light_setting[1] == OFF ? glutAddMenuEntry("Turn White Light On [b]", 'b') : glutAddMenuEntry("Turn White Light Off [b]", 'b');

  //create menu items for other light sources - write your code here
    light_setting[2] == OFF ? glutAddMenuEntry("Turn Cyan Light On [c]", 'c') : glutAddMenuEntry("Turn White Light Off [c]", 'c');
    light_setting[3] == OFF ? glutAddMenuEntry("Turn Magenta Light On [d]", 'd') : glutAddMenuEntry("Turn White Light Off [d]", 'd');
    light_setting[4] == OFF ? glutAddMenuEntry("Turn Yellow Light On [b]", 'e') : glutAddMenuEntry("Turn White Light Off [e]", 'e');
    light_setting[5] == OFF ? glutAddMenuEntry("Turn Spot Light On [f]", 'f') : glutAddMenuEntry("Turn White Light Off [f]", 'f');
  glutAddMenuEntry("--------------------", 0);
    textureSetting == OFF ? glutAddMenuEntry("Set Texture On [g]", 'g') : glutAddMenuEntry("Set Texture Off [g]", 'g');
    fogSetting== OFF ? glutAddMenuEntry("Set Fog On [g]", 'h') : glutAddMenuEntry("Set Fog Off [h]", 'h');
    shadeModelSetting== OFF ? glutAddMenuEntry("Set Smooth Shading [i]", 'i') : glutAddMenuEntry("Set Flat Shading [i]", 'i');

  //create menu items for fog and shade model - write your code here

  glutAddMenuEntry("--------------------", 0);
  glutAddMenuEntry("Zoom in [j]", 'j');
  glutAddMenuEntry("Zoom out [k]", 'k');
  glutAddMenuEntry("Reset [l]", 'l');
  glutAddMenuEntry("--------------------", 0);
  glutAddMenuEntry("Quit", 27);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void myKeyboard(unsigned char key, int x, int y){
	int k=0;
  switch (key) {
    case 'a': //lighting
      light_setting[0] = light_setting[0] == OFF ? ON : OFF;
      break;
    case 'b': //light0
      light_setting[1] = light_setting[1] == OFF ? ON : OFF;
      break;

	//handle other lights ON/OFF settings - write your code here
    case 'c': //light Cyan
      light_setting[2] = (light_setting[2] == OFF) ? ON : OFF;
      break;
    case 'd': //light Magenta
      light_setting[3] = (light_setting[3] == OFF) ? ON : OFF;
      break;
    case 'e': //light Yellow
      light_setting[4] = (light_setting[4] == OFF) ? ON : OFF;
      break;
    case 'f': //light Spot
      light_setting[5] = (light_setting[5] == OFF) ? ON : OFF;
      break;
    case 'g': //texture
      textureSetting = (textureSetting == OFF) ? ON : OFF;
      break;

	//handle fog ON/OFF setting - write your code here
    case 'h': //texture
      fogSetting = (fogSetting == OFF) ? ON : OFF;
      break;
	//handle shading FLAT/SMOOTH setting - write your code here
    case 'i': //texture
      shadeModelSetting = (shadeModelSetting == OFF) ? ON : OFF;
      break;

    case 'j': //zoomin
      cameraX = (cameraX - 0.5 > 1.0) ?  cameraX - 0.5 : cameraX;
      cameraY = (cameraY - 0.5 > 1.0) ?  cameraY - 0.5 : cameraY;
      cameraZ = (cameraZ - 0.5 > 1.0) ?  cameraZ - 0.5 : cameraZ;
	  if (mouse_yaw_picth) {
		  coiX = cameraX + cosPitch * cosYaw;
		  coiY = cameraY + sinPitch;
		  coiZ = cameraZ + cosPitch * sinYaw;
	  }
      break;
    case 'k': //zoomout
      cameraX = (cameraX + 0.5 < 8) ?  cameraX + 0.5 : cameraX;
      cameraY = (cameraY + 0.5 < 8) ?  cameraY + 0.5 : cameraY;
      cameraZ = (cameraZ + 0.5 < 8) ?  cameraZ + 0.5 : cameraZ;
	  if (mouse_yaw_picth) {
		  coiX = cameraX + cosPitch * cosYaw;
		  coiY = cameraY + sinPitch;
		  coiZ = cameraZ + cosPitch * sinYaw;
	  }
      break;
    case 'l': //reset
      cameraX = originalCameraX;
      cameraY = originalCameraY;
      cameraZ = originalCameraZ;
      coiX = originalCoiX;
      coiY = originalCoiY;
      coiZ = originalCoiZ;
      for(k=0;k<6;k++){light_setting[k] = ls_bak[k];}
      shadeModelSetting=ON;
      fogSetting =OFF;
      textureSetting =ON;
      break;

    case 'r': //rotate control
        delta=!delta;
        break;

    case 27: //escape key, exit the program
      exit(0);
    default:
      break;
    }
  glutDestroyMenu(menu);
  createMenu();
  set_Lights_and_ShadeModel();
  myDisplay();
}
void myMenu(int value){
  myKeyboard((unsigned char)value, 0, 0);
}
void myInit(void){
  //create the cylinder object and set the style
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj, GLenum(GLU_FILL));

  createMenu(); //create pop-up menu and add menu entries

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  Image *image1, *image2;
char c,chkcolor;;
int chkbdsize;
Image *chkbdFloor;
Image ckflr;
chkbdFloor=&ckflr;


chkbdFloor->sizeX=8;
chkbdFloor->sizeY=8;
  chkbdsize = chkbdFloor->sizeX * chkbdFloor->sizeY * 3;
  chkbdFloor->data = (char *)malloc(chkbdsize);
for(c=0;c<64;c++){

    if((c/8)%2==0){
    chkcolor=255-255*(c%2);
        chkbdFloor->data[3*c]=chkcolor;
        chkbdFloor->data[3*c+1]=chkcolor;
        chkbdFloor->data[3*c+2]=chkcolor;
    }
    else{
        chkcolor=0+255*(c%2);
        chkbdFloor->data[3*c]=chkcolor;
        chkbdFloor->data[3*c+1]=chkcolor;
        chkbdFloor->data[3*c+2]=chkcolor;
    }


}


  //create one image texture
  getTexture("road.bmp", image1, texImage1Name);

  //create another image texture - write your code here
  getTexture("upper-peninsula.bmp", image2, texImage2Name);
  //create the checkerboard texture	- write your code here
glBindTexture(GL_TEXTURE_2D, texCheckerBoardName);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // scale linearly when image bigger than texture
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // scale linearly when image smalled than texture
glTexImage2D(GL_TEXTURE_2D, 0, 3, chkbdFloor->sizeX, chkbdFloor->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, chkbdFloor->data);
  //initialize fog properties - write your code here
    glFogi(GL_FOG_MODE,GL_EXP);
    glFogfv(GL_FOG_COLOR,fogColor);
    glFogf(GL_FOG_DENSITY,fogDensity);
    glFogf(GL_FOG_START,fogStart);
    glFogf(GL_FOG_END,fogEnd);

  set_Lights_and_ShadeModel();
}


void rot(){
    theta+=delta*0.04;
    glutPostRedisplay();

}
////////////////////////////////////////////////////////
// main function
////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
  glutInit(&argc, argv); //initialize the toolkit
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //set display mode
  glutInitWindowSize(screenWidth, screenHeight); //set window size
  glutInitWindowPosition(150, 150); //set window position on screen
  glutCreateWindow("CS4611 Lab3 Base Code"); //open the screen window

  //register the callback function
  glutDisplayFunc(myDisplay);
  glutMouseFunc(myMouse);
  glutKeyboardFunc(myKeyboard);
  glutIdleFunc(rot);

  myInit();

  glutMainLoop(); //go into a perpetual loop
}
