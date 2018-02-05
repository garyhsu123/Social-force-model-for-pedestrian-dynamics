#include "Crowd.h"
#include "glut.h"
#include <iostream> 
#include "glui.h"
#define deltaTimes 1

double times = 0.0;
using namespace std; 
#include "Vectors.h"
int screenW = 1000,screenH = 200;

int pNumber = 100;

int radius = 4.5;
float rectH = 10;
int viewEdge = 30;
Crowd task;
//
float gapH = radius * 5;
bool Colck = false;
void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);

	


	glLoadIdentity();
	gluLookAt(0,0,10,0,0,0,0,1,0);
	task.update();

   //wall
    glColor3f(1,1,1);
    
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,screenH/2 + rectH/2 ,0);
    glScalef(1000,rectH,20);   
    glutSolidCube(1);
    glPopMatrix();
	
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,- screenH/2 - rectH/2,0);
    glScalef(1000,rectH,20);   
    glutSolidCube(1);
    glPopMatrix();
    

	if (Colck) {
		glPushMatrix();

		glBegin(GL_LINES);
		glVertex2f(0, gapH / 2);
		glVertex2f(0, screenH / 2.0);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(0, -gapH / 2);
		glVertex2f(0, -screenH / 2.0);
		glEnd();

		glPopMatrix();
	}
   //glBegin(GL_POLYGON);
   //    glVertex3f(0.0, 0.0, 0.0);
   //    glVertex3f(250, 0.0, 0.0);
   //    glVertex3f(250, 250, 0.0);
   //    glVertex3f(0.0, 250, 0.0);
   //glEnd();

    //cout<<"hi"<<endl;
	for(int i =0;i<pNumber;i++)
	{
		/////////////////// set Color
		if(task.people[i].direction ==tright)
			glColor3f(1,0,0);
		else if (task.people[i].direction == tleft)
			glColor3f(0,1,0);
		///////////////////
		



			glPushMatrix();
			
			glLoadIdentity();

			
			glTranslatef(task.people[i].position[0],task.people[i].position[1],task.people[i].position[2]);
			glutSolidSphere(radius,50,50);

			

			
			float degree = task.getdegree(i);
			//cout << " degree  "<<degree << endl;
			if (degree >= 0) {
				glPushMatrix();
				glColor3f(1, 1, 1);

				glRotatef(degree, 0, 0, 1);
				glRotatef(90, 0, 1, 0);
				//glutWireCone(2, 10, 10, 10);
				glPopMatrix();
			}
			





		glPopMatrix();

			
			

		
		
	}
	
	
    glFlush();
}

void Init()
{
	glClearColor(0,0,0,1);
	
	task.setCount(pNumber); // 設置人數
	task.init_crowd(screenW,screenH,radius,rectH, gapH); //初始化Crowd

}
void reshape (int width, int height) {  
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  

	glOrtho(-width/2,width/2,-height/2-viewEdge,height/2+viewEdge,0.0001,50);
	
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
	
}  

//callback funtion as a timer, no need to modify it
void Tick(int id){
	double d = deltaTimes / 1000.0;
	times += d;
    //cout<<times<<endl;
    //glutPostRedisplay();
	

	glutTimerFunc(deltaTimes, Tick, 0); // 1000ms for time step size

}
void idle(){
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'z':
		task.ToggleClick();
		Colck = !Colck;
		break;
	default:
		cout << "Please press 'z' to switch" << endl;
		break;
	}
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(screenW, screenH);
    glutInitWindowPosition(20, 80);
    glutCreateWindow("Hello world :D");
	Init();
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutTimerFunc(deltaTimes, Tick, 0);
    glutDisplayFunc(displayMe);
	
    glutMainLoop();
    return 0;
}
