// vclip_test.cpp : Defines the entry point for the console application.
//


#include <vector>
#include <iostream>
#include <math.h>

#include "VECTOR.h"
#include "GEOMETRY.h"
#include "VCLIP.h"

Vector3 X(1,0,0);
Vector3 Y(0,1,0);
Vector3 Z(0,0,1);

class PART {
public:
	Vector3 x;
	Quaternion q;

	RECTANGULAR_PARALLELEPIPED<PART>* rp;

	PART()
	{
		rp = new RECTANGULAR_PARALLELEPIPED<PART>(0,0,0,0,0,0,1,1,1,1);
		//rp->parent = this;
	}
};

int main(int argc, char* argv[]) {

	VCLIP<PART> vclip;

	PART* p1 = NULL;
	PART* p2 = NULL;
	p1 = new PART;
	p2 = new PART;
	
	p1->x.col[0] = -0.48f;
	p1->x.col[1] = 0.0f;
	p1->x.col[2] = 0.0f;

	p2->x.col[0] = 0.5f;
	p2->x.col[1] = 0.5f;
	p2->x.col[2] = 0.5f;

	vclip.algorithm(p1->rp,p2->rp);


	delete p1;
	delete p2;

	int i;
	std::cin >> i;
	
	return 0;
}

