#include <iostream> 
using namespace std; 
#include <iomanip>
#include "glut.h"
#include "Vectors.h"
#include<ctime>
#include<cstdlib>
#include<random>
#include <string>

#define tright 0
#define tleft 1
#define tup 2
#define tdown 3
#define deltaTime 0.03
#define trate 20
#define keepDis_Max 50 
class Crowd
{
	typedef float mytype;
	struct person
	{
		int direction;
		Vector3 target;

		mytype V0;
		mytype Vmax;
		mytype radius;
		Vector3 f;
		Vector3 velocity;
		Vector3 position;
		Vector3 desireDir;
		Vector3 totalkeepDis;
	};

public:
	mytype pi;
	mytype prevent;
	mytype obstaclesH,gapH;
	bool Clock;
	mytype screenH, screenW;
	int totalCount;
	person* people;
	Crowd();
	~Crowd();
	void setCount(int);
	void init_crowd(int, int, int, float,float);
	void update();
	void ToggleClick();
	mytype getdegree(int);
private:
	void updatef();
	void updatev();
	void updatepos();
	void updateTarget(int);
	void handle(int, int, mytype, mytype, mytype, mytype);
	void CollissionDetest();
	void collisionHandlewithOthers();
	void collisionHandlewithObstacles();
};