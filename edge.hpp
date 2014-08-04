
#include <stdio.h>
#include <vector>

#include "VECTOR.h"

enum GEOMETRY_FEATURE_TYPE {
	GEOMETRY_FEATURE_TYPE_VERTEX,
	GEOMETRY_FEATURE_TYPE_EDGE, GEOMETRY_FEATURE_TYPE_FACE, GEOMETRY_FEATURE_TYPE_ALL, GEOMETRY_FEATURE_TYPE_NONE };
enum GEOMETRY_TYPE
{
	GEOMETRY_TYPE_CUBE,
	GEOMETRY_TYPE_RECTANGULAR_PARALLELEPIPED,
	GEOMETRY_TYPE_CIRCULAR_CYLINDER
};

class VERTEX;
class EDGE;
class FACE;
class POLYHEDRON;


class EDGE
{
	public:
		POLYHEDRON<U>* poly;

		VERTEX<U>* h;
		VERTEX<U>* t;
		FACE<U>* F1;
		FACE<U>* F2;

		std::vector<VERTEX<U>*> V;
		std::vector<FACE<U>*> F;

		EDGE()
		{
			poly = NULL;
			h = NULL;
			t = NULL;
			F1 = NULL;
			F2 = NULL;
		}
		EDGE( POLYHEDRON<U>* polyParam, VERTEX<U>* hParam, VERTEX<U>* tParam )
		{
			poly = polyParam;
			h = hParam;
			t = tParam;
			F1 = NULL;
			F2 = NULL;
		}

		Vector3 e(float lambda)
		{
			Vector3 ret = (t->x)*(1.0f-lambda) + (h->x)*lambda;
			return ret;
		}

		Vector3 u()
		{
			return ( h->x - t->x );
		}
};

