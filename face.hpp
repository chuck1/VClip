
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

template <class U> class VERTEX;
template <class U> class EDGE;
template <class U> class FACE;
template <class U> class POLYHEDRON;


template <class U> class FACE
{
	public:
		POLYHEDRON<U> * poly;

		Vector3 n;
		Vector3 x; // reference point on face for determining normal of VP(F,E)
		float w;

		std::vector<EDGE<U>*> E;

		FACE();

		void update();
};

