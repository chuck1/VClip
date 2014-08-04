#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP


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
