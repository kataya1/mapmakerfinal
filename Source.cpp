
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <glut.h> 


using namespace std;
int cx = 0, cy = 0, cz = 0;
int cn;

void changeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

struct viktor
{
	float x, y, z;
};

void getnormal(int x1, int y1, int z1, int  x2, int y2, int z2, int x3, int y3, int z3)
{
	//point a, b, c;

	// calculate the vectors A and B
	// note that v[3] is defined with counterclockwise winding in mind
	// a
	struct viktor a;
	a.x = x3 - x2;
	a.y = y3 - y2;
	a.z = z3 - z2;
	// b
	struct viktor b;
	b.x = x1 - x2;
	b.y = y1 - y2;
	b.z = z1 - z2;
	/* c
	c.x = p1.x - p4.x;
	c.y = p1.y - p4.y;
	c.z = p1.z - p4.z; */
	struct viktor normal;
	// calculate the cross product and place the resulting vector
	// into the address specified by vertex_t *normal
	normal.x = ((a.y * b.z) - (a.z * b.y));
	normal.y = ((a.z * b.x) - (a.x * b.z));
	normal.z = ((a.x * b.y) - (a.y * b.x));

	// normalize
	float len = (float)(sqrt((double)((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z))));

	// avoid division by 0
	if (len == 0.0f)
		len = 1.0f;

	// reduce to unit size
	normal.x /= len;
	normal.y /= len;
	normal.z /= len;

	glNormal3f(normal.x, normal.y, normal.z);
}

struct Quads
{
	int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	float r, g, b;
	int state;
	int total;
}; Quads Q[100];


void addQuad()
{

	Q[0].state++;
	if (Q[0].state > 4) { Q[0].state = 1; }
	int st = Q[0].state;

	if (st == 1) { Q[0].total++;cn = Q[0].total; }
	if (st == 1) { Q[cn].x1 = cx;	Q[cn].y1 = cy;	Q[cn].z1 = cz; }
	if (st == 1 || st == 2) { Q[cn].x2 = cx;	Q[cn].y2 = cy;	Q[cn].z2 = cz; }
	if (st == 1 || st == 2 || st == 3) { Q[cn].x3 = cx;	Q[cn].y3 = cy;	Q[cn].z3 = cz; }
	if (st == 1 || st == 2 || st == 3 || st == 4) { Q[cn].x4 = cx;	Q[cn].y4 = cy;	Q[cn].z4 = cz; }

}
void drawQuads()
{
	GLfloat	black[] = { 0.0,0.0,0.0,1.0 };
	GLfloat blue[] = { 0.0,0.0,1,1.0 };
	GLfloat	white[] = { 1.0,1.0,1.0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	int i;
	for (i = 1;i < Q[0].total + 1;i++)
	{

		//glNormal3f(0, 1, 0);
		glPushMatrix();
		getnormal(Q[i].x1, Q[i].y1, Q[i].z1, Q[i].x2, Q[i].y2, Q[i].z2, Q[i].x3, Q[i].y3, Q[i].z3);
		glPopMatrix();
		glBegin(GL_QUADS);
		glColor3f(Q[i].r, Q[i].g, Q[i].b);

		glVertex3f(Q[i].x1, Q[i].y1, Q[i].z1);
		glVertex3f(Q[i].x2, Q[i].y2, Q[i].z2);
		glVertex3f(Q[i].x3, Q[i].y3, Q[i].z3);
		glVertex3f(Q[i].x4, Q[i].y4, Q[i].z4);
		glEnd();
	}

}

void drawGrid()
{
	int i;
	for (i = 0;i < 40;i++)
	{
		glPushMatrix();
		if (i < 20) { glTranslatef(0, 0, i); }
		if (i >= 20) { glTranslatef(i - 20, 0, 0); glRotatef(-90, 0, 1, 0); }
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glLineWidth(1);
		glVertex3f(0, -0.1, 0);
		glVertex3f(19, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
}

void thecube()
{
	//glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.4);
	//glPopMatrix();
}
void myinit()
{
	glPushMatrix();
	glOrtho(-1, 20, -1, 20, -1, 20);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light0_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat light0_diffuse[] = { 0.8,0.8,0.8,1.0 };
	GLfloat light0_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light0_position[] = { 10,10,10,1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, light0_ambient);


	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glPopMatrix();
}

void drawBitmapText(char *string, float x, float y)
{
	char *c;
	glColor3f(1.0, 0, 0);
	glRasterPos2f(x, y);
	glOrtho(-1, 1, -1, 1, -1, 1);
	for (c = string; *c != ' '; c++)
	{

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(-13, 0, -45);
	glRotatef(40, 1, 1, 0);

	drawGrid();

	drawQuads();
	thecube();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	float f = 0.05;
	if (key == 'w') { cz -= 1; }if (key == 's') { cz += 1; }
	if (key == 'a') { cx -= 1; }if (key == 'd') { cx += 1; }
	if (key == 'q') { cy += 1; }if (key == 'z') { cy -= 1; }
	if (key == 32) { addQuad(); }if (key == 27) { exit(0); }
	if (key == 'r') { Q[cn].r = 1;Q[cn].g = 0;Q[cn].b = 0; }
	if (key == 'g') { Q[cn].r = 0;Q[cn].g = 1;Q[cn].b = 0; }
	if (key == 'b') { Q[cn].r = 0;Q[cn].g = 0;Q[cn].b = 1; }
	if (key == 'y') { Q[cn].r = 1;Q[cn].g = 1;Q[cn].b = 0; }
	glutPostRedisplay();
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	myinit();
	gluPerspective(35, 1.0f, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2, 0.2, 0.2, 1);

}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("testing");
	glutKeyboardFunc(keyboard);
	init();
	glutReshapeFunc(changeViewport);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}