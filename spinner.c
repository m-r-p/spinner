
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

static int gSizeX = 640;
static int gSizeY = 480;


void init()
{
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glShadeModel(GL_SMOOTH);
}


static float alpha = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draw a grey rectangle in 2D mode
    // size is 440 x 280
    glBegin(GL_QUADS);
    glColor3f(.5,.5,.5);
    glVertex2s(100, 100);
    glVertex2s(gSizeX-100, 100);
    glVertex2s(gSizeX-100, gSizeY-100);
    glVertex2s(100, gSizeY-100);
    glEnd();

    // push the 2D projection matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    // set up a 3D projection
    glLoadIdentity();

    // front clipping plane at 200.0
    // use coordinates 1/2 of actual screen size
    // so that objects twice as far away map to screen
    glFrustum( -gSizeX/4., gSizeX/4.,
    	       -gSizeY/4., gSizeY/4.,
	       200, 1000 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_SMOOTH);

    glTranslatef(0, 0, -400);
    glScalef( 220, 140, 140 );
    glRotatef(-alpha, 1, 0, 0);

    glBegin(GL_QUADS);
    glColor3f(0, 0, 1); glVertex3f(-1, -1,  0);
    glColor3f(0, 1, 1); glVertex3f(-1,  1,  0);
    glColor3f(1, 1, 1); glVertex3f( 1,  1,  0);
    glColor3f(1, 0, 1); glVertex3f( 1, -1,  0);
    glEnd();

    alpha = alpha + 1.0;

    // restore the 2D projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glutSwapBuffers();
}


void reshape(int w, int h)
{
    // standard HotPlayer context
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( 0, w, 0, h );

    // clear expensive GL modes
    glDisable( GL_ALPHA_TEST );
    glDisable( GL_BLEND );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_FOG );
    glDisable( GL_LIGHTING );
    glDisable( GL_LOGIC_OP );
    glDisable( GL_STENCIL_TEST );
    glDisable( GL_DITHER );

    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
    glRasterPos2s( 0, 0 );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(gSizeX, gSizeY);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hello!");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);

    init();

    glutMainLoop();

    return 0;
}

