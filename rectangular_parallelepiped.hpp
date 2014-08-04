#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

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







class PLANE
{
	public:
		Vector3 n;
		float w;

		PLANE(){}

		PLANE(VERTEX* V, EDGE* E);
		PLANE(EDGE* E, VERTEX* V);
		PLANE(EDGE* E, FACE *F);
		PLANE(FACE *F, EDGE *E);

};


class GEOMETRY_SET
{
	public:
		std::vector<VERTEX*> V;
		std::vector<EDGE*> E;
		std::vector<FACE*> F;

		void clear()
		{
			V.clear();
			E.clear();
			F.clear();
		}
		bool find( VERTEX* Vparam )
		{
			for ( int i = 0; i < V.size(); i++ )
			{
				if ( V.at(i) == Vparam ){ return true; }
			}
			return false;
		}
		bool find( EDGE * Eparam )
		{
			for ( int i = 0; i < E.size(); i++ )
			{
				if ( E.at(i) == Eparam ){ return true; }
			}
			return false;
		}
		bool find( FACE * Fparam )
		{
			for ( int i = 0; i < F.size(); i++ )
			{
				if ( F.at(i) == Fparam ){ return true; }
			}
			return false;
		}
};
class RECTANGULAR_PARALLELEPIPED: public POLYHEDRON
{
	public:
		float a;
		float b;
		float c;

		RECTANGULAR_PARALLELEPIPED(){};
		RECTANGULAR_PARALLELEPIPED( float offset_x, float offset_y, float offset_z, float p, float n, float s, float width, float depth, float height, float rho );

		// virtuals
		void collision( POLYHEDRON * polyhedron );
		//bool interact( INTERACT_TYPE type, const Vector3 &O, const Vector3 &vn, float &dist );
		void render();
		void physics();
};
class CIRCULAR_CYLINDER: public POLYHEDRON
{
	public:
		float r;
		float h;
		CIRCULAR_CYLINDER( float offset_x, float offset_y, float offset_z, float p, float n, float s, float radius, float height, float rho );
};
class SQUARE: public POLYHEDRON
{
	public:
		float a;
		float b;
		float c;

		SQUARE(){};
		SQUARE( float offset_x, float offset_y, float offset_z, float p, float n, float s, float width, float depth, float height, float rho ){};

		int get_point_collision( U * p, float * n, float * r, float * A, float &penetration );

		bool interact( const Vector3 &O, const Vector3 &vn, float &dist );
		void render();
		void collision( POLYHEDRON * polyhedron );
};

#endif
