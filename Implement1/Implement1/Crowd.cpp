#include "Crowd.h"
#include <math.h>




Crowd::Crowd()
{
	srand(time(NULL));
    pi = acos(-1);
	totalCount = 0;
	prevent = 0;
	Clock = false;
}
void Crowd::setCount(int num)
{
	if(num >400)
		totalCount = 400;
	else
		totalCount = num;
}
void Crowd::init_crowd(int w,int h,int radius,float rectH,float gapHeight)
{
	people = (person*)operator new(totalCount*sizeof(person));
	obstaclesH = rectH;
    screenH = h;
    screenW = w;
	gapH = gapHeight;
	const int nrolls = totalCount;  // number of experiments


	std::default_random_engine generator;
	std::normal_distribution < float > distribution(1.34 * trate, 0.26 * trate);

	//int p[10] = {};

	for (int i = 0; i<nrolls; ++i) {
		float number = distribution(generator);
		people[i].V0 = (mytype)1.34 * trate;
	
	}





	
		

		
	

	




	float x=0.0, y = 0.0;

	for (int i=0;i<totalCount;i++)
	{

		people[i].f = Vector3(0,0,0);
		people[i].velocity = Vector3(0,0,0);
		
		//people[i].V0 = 5 * trate;
		//people[i].Vmax = 1.3 * people[i].V0;
		people[i].Vmax =  people[i].V0;

		//people[i].position = Vector3( mytype(((double)rand()*(w) / RAND_MAX - w/2)), mytype(((double)rand()*(h) / RAND_MAX - h / 2)),0);
		//people[i].position = Vector3( mytype(rand()%w-w/2), i*0.001 ,0);
        //people[i].position = Vector3( mytype(rand()%w-w/2), 0 ,0);
		
		people[i].radius = (mytype)radius;
		switch (i%2)
		{
		case 0:
			people[i].position = Vector3( -30*((i/2)/5)-300,((i/2)%5) *35-50, 0);
			people[i].direction = tright;
			//people[i].target = Vector3(- people[i].radius, 0, 0);
			people[i].target = Vector3(w/2,0,0);
			break;
		case 1:
			people[i].direction = tleft;
			people[i].position = Vector3(30 * ((i/2) / 5) +300, ((i/2) % 5) * 35 - 50,0);
			//people[i].target = Vector3(people[i].radius, 0, 0);
			people[i].target = Vector3(-w/2,0,0);
			break;
		
		default:
			people[i].direction = tright;
			people[i].target = Vector3(w/2,0,0);
			//people[i].target = Vector3(w/2,people[i].position[1],0);
			//people[i].target = Vector3(-people[i].radius, 0, 0);
			cout<<"some people never direction"<<endl;
			break;
		}
		
	}

}


void Crowd::updateTarget(int i)
{
	

	if (people[i].desireDir.length() < 5) {
		if (people[i].direction == tright)
		{
			//cout<<"hello"<<endl;
			//people[i].target += Vector3(1, 0, 0) * trate * 1;
			//people[i].desireDir = people[i].target - people[i].position;

			people[i].position[0] = -people[i].target[0];
			people[i].desireDir = people[i].target - people[i].position;

		}
		else if (people[i].direction == tleft)
		{
			//people[i].target -= Vector3(1, 0, 0) * trate * 1;
			//people[i].desireDir = people[i].target - people[i].position;

			people[i].position[0] = -people[i].target[0];
			people[i].desireDir = people[i].target - people[i].position;



		}

	}


}

void Crowd::updatef()
{
	float deltaT = 10.0 ;
	//float deltaT = 1300.0;
	float relaxationT = 0.5 ;
	for(int i =0;i<totalCount;i++)
	{
		
		people[i].f = Vector3(0,0,0);
		people[i].desireDir = people[i].target - people[i].position;
		//cout<<"----------: "<<i<<"  target"<<people[i].target<<endl;
		//cout<<"position"<<people[i].position<<endl;
		updateTarget(i);
		//cout<<"-----------------------target: "<<people[i].target<<endl;
		//cout<<"-----------------------position: "<<people[i].position<<endl;
		//cout<<"-----------------------desireDir: "<<people[i].desireDir<<endl;
		//cout<<"-----------------------desireDirlen: "<<people[i].desireDir.length()<<endl;
		people[i].desireDir = people[i].desireDir.normalize();
		//cout<<"1----------------------desireDir: "<<people[i].desireDir * people[i].V0<<endl;
		//cout<<"2----------------------desireDir: "<<people[i].velocity<<endl;
		people[i].f += (people[i].desireDir * people[i].V0 - people[i].velocity ) / relaxationT ;

	}
	//////////


	float Vf = 2.1  * trate * trate;
	float sigma = 0.3 * trate;
	
	float viewAngle = 100;
	

	for(int i =0;i<totalCount;i++)
	{
		//cout<<"f: "<<people[i].f<<endl;
		people[i].totalkeepDis = Vector3(0,0,0);
		for (int j = 0; j <totalCount ; j++)
		{
			float c = 0;
			if(i != j)
			{
				Vector3 keepDis = Vector3(0,0,0);
				
				
				
				
				Vector3 a = people[i].position;
				Vector3 b = people[j].position;
				Vector3 bmove = people[j].V0 * people[j].desireDir * deltaT * deltaTime;//// ////
				float bstep = people[j].V0 * deltaT * deltaTime;
				Vector3 rab = a - b ;
				if (rab.length() == 0)
					cout << "hit" << endl;
				//cout <<i<< "rab: " << rab << endl;
				
				//cout<<"a: "<<a<<endl;
				//cout<<"b: "<<b<<endl;
				//cout<<"rab: "<<rab<<endl;
				//cout<<i<<" bmove: "<<bmove<<endl;
				//cout<<"rab-bmove: "<<(rab - bmove)<<endl;
				float expfv = expf(-1 * max(float(0),sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep)) / (2 * sigma));
				//cout<<"expfv: "<<expfv<<endl;

				//if(expfv<0.0001)
				//	expfv = 0;
				keepDis = -Vf * expfv
								*	-1 * (1 / (2 * sigma)) * 0.5 * (1 / (max(float(0),sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep   ))+ prevent))
									* 2 * (rab.length() +  (rab - bmove).length()) * ((rab / (rab.length()+prevent)) + ((rab - bmove) /  ((rab - bmove).length()+prevent)));
				//cout << "director: "<<((rab / (rab.length() + prevent)) + ((rab - bmove) / ((rab - bmove).length() + prevent))) << endl;
				/*
				cout<<"expf: "<<-1 * sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep) / (2 * sigma)<<endl;
				cout<<"first: "<<-Vf * expf(-1 * sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep) / (2 * sigma))<<endl;
				cout<<"second: "<<-1 * (1 / (2 * sigma)) * 0.5 * (1 / sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep + prevent ) )<<endl;
				cout<<"multi: "<<-Vf * expf(-1 * sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep) / (2 * sigma))
								*	-1 * (1 / (2 * sigma)) * 0.5 * (1 / sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep + prevent ) )<<endl;				
				cout<<"third: "<<2 * (rab.length() +  (rab - bmove).length()) * ((rab / (rab.length()+prevent)) + ((rab - bmove) /  ((rab - bmove).length()+prevent)))<<endl;		
				
				
				
				cout<<"rab.length(): "<<rab.length() <<endl;
				cout<<"(rab - bmove).length(): "<< (rab - bmove).length() <<endl;
				cout<<"bstep: "<< bstep <<endl;
				cout<<"rab: "<<rab<<endl;
				cout<<"bmove: "<<bmove<<endl;
				
				cout<<"x: "<<(rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep<<endl;
				cout<<"sqrtf(x): "<<sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep  )<<endl;
				
				cout<<"squrtf(x)+prevent: "<<sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep  )+ prevent<<endl;
				cout<<"1/ (squrtf(x)+prevent): "<<(1 / sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep  )+ prevent )<<endl;
				cout<<"(): "<<-1 * sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep) / (2 * sigma)<<endl;
				cout<<"expfv: "<<expfv<<endl;
				cout<<(rab.length() +  (rab - bmove).length()) * ((rab / (rab.length()+prevent)) + ((rab - bmove) /  ((rab - bmove).length()+prevent)))<<endl;

				cout<<"keepDis: "<<keepDis<<endl;
				*/
				/*
				cout<<expf(-2829.65)<<endl;
				cout<<"* "<<rab.length()+prevent<<endl;
				cout<<"** "<<  (rab - bmove).length()+prevent<<endl;
				cout<<"-** "<< (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep + prevent <<endl;
				cout<<"*** "<<sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep + prevent) <<endl;
				cout<<"**** "<<-1 * sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep) / (2 * sigma)<<endl;
				cout<<"***** "<<expf(-1 * sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep) / (2 * sigma))<<endl;
				*/
				
				//if(keepDis.length()>0.1)
				//cout << i << " " << a << endl;
				//cout << j << " " << b << endl;
				//cout<<i<<j<<"keepDis: "<<keepDis<<endl;
                  
				/*
				if(isinf((1.0 / (rab.length()+prevent))))
				{
					cout<<"1: "<<endl;
				}else{
				cout<<"//"<<endl;
				cout<<(1.0 / (rab.length()+prevent))<<endl;
				}
				
				if(isinf(    (1.0) /  ((rab - bmove).length()+prevent)   ))
				{
					cout<<"2: "<<endl;
				}else{
				cout<<"///"<<endl;
				cout<<  (1.0) /  ((rab - bmove).length()+prevent) <<endl;
				}
				
				if(isinf(  1.0 / sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep + prevent )    ))
				{
					cout<<"3: "<<endl;
				}else{
					cout<<"////"<<endl;
					cout<<1.0 / sqrtf( (rab.length() +  (rab - bmove).length()) * (rab.length() +  (rab - bmove).length()) -  bstep * bstep + prevent ) <<endl;
				}
				*/
				
				//cout<<i<<" : "<<j<< keepDis <<endl;
				if((people[i].desireDir).dot(-keepDis) >= (-keepDis).length() * cosf(pi * viewAngle / 180.0 ))
					c = 1;
				else
					c = 0.5;
				//cout << "c: "<<c << endl;
				
				people[i].totalkeepDis += c * keepDis;
				//people[i].f += c * keepDis;




			}

		}

		//if(people[i].totalkeepDis.length() >50 )
		//cout <<i <<"   people[i].totalkeepDis: "<<(people[i].totalkeepDis) << endl;
		/////限制totalKeepDis大小
		/*float rate;
		if((people[i].totalkeepDis).length() <= keepDis_Max * r)
			rate = 1 ;
		else
			rate = keepDis_Max / (people[i].totalkeepDis).length();

		people[i].totalkeepDis *= rate; */
		
		   
		   
		people[i].f += people[i].totalkeepDis;
		//cout << "total F: "<<people[i].f<< endl;
		
	}
	
	//with obstacles top
	mytype Uf = 10 * trate * trate*0.3;
	mytype R = 0.2 * trate;
	for (int i = 0; i < totalCount; i++)
	{
		float c1 = 0;
		Vector3 a = people[i].position;
		Vector3 b1 = a;
		b1[1] = screenH/2;
		Vector3 keepDis;
		Vector3 raB1 = a - b1 ;
		keepDis = -Uf * expf(- raB1.length() / R) *  ( -1 / R) * raB1 / (raB1.length() + prevent);

		if ((people[i].desireDir).dot(-keepDis) >= (-keepDis).length() * cosf(pi * viewAngle / 180.0))
			c1 = 1;
		else
			c1 = 0.5;

		people[i].f += c1 * keepDis;


	}

	

	//with obstacles down
	for (int i = 0; i < totalCount; i++)
	{
		float c2 = 0;
		Vector3 a = people[i].position;
		Vector3 b2 = a;
		b2[1] = - screenH / 2;
		Vector3 keepDis;
		Vector3 raB2 = a - b2;
		keepDis = -Uf * expf(-raB2.length() / R)* -(1 / R) * raB2 / (raB2.length() + prevent);

		if ((people[i].desireDir).dot(-keepDis) >= (-keepDis).length() * cosf(pi * viewAngle / 180.0))
			c2 = 1;
		else
			c2 = 0.5;

		people[i].f += c2 * keepDis;

	}

	if (Clock) {
		for (int i = 0; i < totalCount; i++)
		{
			float c3 = 0;
			Vector3 a = people[i].position;
			Vector3 b3 = a;
			if (a[1] > gapH / 2) {

				b3[0] = 0;

			}
			else {
				b3[0] = 0;
				b3[1] = gapH / 2;


			}


			Vector3 keepDis;
			Vector3 raB2 = a - b3;
			keepDis = -Uf * expf(-raB2.length() / R)* -(1 / R) * raB2 / (raB2.length() + prevent);

			if ((people[i].desireDir).dot(-keepDis) >= (-keepDis).length() * cosf(pi * viewAngle / 180.0))
				c3 = 1;
			else
				c3 = 0.5;

			people[i].f += c3 * keepDis;

		}


		for (int i = 0; i < totalCount; i++)
		{
			float c4 = 0;
			Vector3 a = people[i].position;
			Vector3 b4 = a;
			if (a[1] < -gapH / 2) {

				b4[0] = 0;

			}
			else {
				b4[0] = 0;
				b4[1] = -gapH / 2;


			}


			Vector3 keepDis;
			Vector3 raB2 = a - b4;
			keepDis = -Uf * expf(-raB2.length() / R)* -(1 / R) * raB2 / (raB2.length() + prevent);

			if ((people[i].desireDir).dot(-keepDis) >= (-keepDis).length() * cosf(pi * viewAngle / 180.0))
				c4 = 1;
			else
				c4 = 0.5;

			people[i].f += c4 * keepDis;

		}


	}












	//fluctuations
	for (int i = 0; i < totalCount; i++)
	{
		Vector3 fluctuation = Vector3(people[i].f[1], -people[i].f[0], 0);
		fluctuation.normalize();

		//cout <<"f: "<< fluctuation << endl;
		//cout << "fluctuation: " << fluctuation * ((double)rand()*(100) / RAND_MAX - 50.0) << endl;
		people[i].f += fluctuation *trate* ((double)rand()*(2) / RAND_MAX - 1.0) ;
		//cout <<"random: "<< ((double)rand()*(2) / RAND_MAX - 1.0) << endl;

		//people[i].f += fluctuation * trate * (rand() % 3 - 1);
		

		//cout << fluctuation * trate * (rand() % 3 - 1) << endl; 

	}
}

Crowd::mytype Crowd::getdegree(int i)
{
	mytype length = people[i].totalkeepDis.length();
	//cout <<"- - - - - " <<length << endl;
	//cout << length << endl;
	if (length*10000 < 1000)
	{
		
		return -1;
	}
	else {
		mytype cos = people[i].totalkeepDis[0] / length;
		
		//cout << people[i].totalkeepDis << endl;
		//cout << cos << endl;
		//cout << acosf(cos) << endl;
		
		mytype degree = acosf(cos) * 180 / pi;
		//cout << degree << endl;
		if (people[i].totalkeepDis[1] < 0)
			degree = -degree + 360;
		return degree;
	}
	
	


}
void Crowd::ToggleClick()
{
	Clock = !Clock;


}
void Crowd::updatev()
{
	for(int i =0;i<totalCount;i++)
	{
		people[i].velocity += people[i].f * deltaTime;

        //cout<<people[i].velocity<<endl;
		float rate ;
		
		if((people[i].velocity).length() <= people[i].Vmax)
			rate = 1 ;
		else
			rate = people[i].Vmax / (people[i].velocity).length();

		people[i].velocity *= rate; 
		
	}


}

void Crowd::updatepos()
{
	for(int i =0;i<totalCount;i++)
	{
		people[i].position += people[i].velocity * deltaTime;
        //people[i].target[1] = people[i].position[1];


	}

}
void Crowd::collisionHandlewithObstacles()
{
    for(int i =0;i<totalCount;i++)
	{
       
	    if(screenH/2 - people[i].position[1] < people[i].radius){
            mytype a_y = people[i].position[1];
            mytype difference = people[i].radius - (screenH/2 - a_y) ;
            people[i].position[1] -= difference;
        }
        
        if(people[i].position[1] + screenH/2 < people[i].radius){
            mytype a_y = people[i].position[1];
            mytype difference = people[i].radius - (screenH/2 + a_y) ;
            people[i].position[1] += difference;
        }
        
            //handle(i,j,people[i].radius,people[j].radius,0.5,0.5);


	}


}
void Crowd::handle(int A,int B,mytype radiusA,mytype radiusB,mytype weightA,mytype weightB)
{
    Vector3 posA = people[A].position;
    Vector3 posB = people[B].position;
    Vector3 vec = posA - posB;
    
    mytype vecLen = vec.length()+prevent;
    mytype desiredDis = radiusA + radiusB;
    /*
    cout<<"posA: "<<  setprecision(5)<<posA<<endl;
    cout<<"posB: "<<  setprecision(5)<<posB<<endl;
    cout<<"vec: "<<vec<<endl;
    cout<<"vec.length(): "<<vec.length()<<endl;
    cout<<"prevent: "<<prevent<<endl;
    cout<<"vecLen: "<<vecLen<<endl;
    cout<<"vec/vecLen: "<<vec/vecLen<<endl;
    */
    if(vecLen<desiredDis)
    {
        //cout<<"in ----------------------------------------"<<vecLen<<endl;
        people[A].position = posA + (desiredDis-vecLen)*(vec/vecLen) * weightA;
        //people[A].position[2] = 0;
        people[B].position = posB - (desiredDis-vecLen)*(vec/vecLen) * weightB;
        //people[B].position[2] = 0;
    }


}
void Crowd::collisionHandlewithOthers()
{
	for(int i =0;i<totalCount;i++)
	{
		for(int j =0;j<totalCount;j++)
		{
		
            handle(i,j,people[i].radius,people[j].radius,0.5,0.5);
		}


	}



} 
void Crowd::CollissionDetest()
{

	for(int i =0;i<10;i++)
	{
		collisionHandlewithObstacles();
		collisionHandlewithOthers();
	}
	
}
void Crowd::update()
{
    //CollissionDetest();
	updatef();
	updatev();
	updatepos();
	
}
Crowd::~Crowd()
{
}
