
#include <vector>

class VERTEX;
class EDGE;
class FACE;

template <class U> class POLYHEDRON
{
	public:
		//U * parent;
		
		std::vector<VERTEX*>	V;
		std::vector<EDGE*>	E;
		std::vector<FACE*>	F;

		bool penetrating;

		VERTEX* VHighlight;
		EDGE*   EHighlight;
		FACE*   FHighlight;

		GEOMETRY_FEATURE_TYPE highlight_type;

		GEOMETRY_TYPE geometry_type;

		float m;
		float density;

		// shape, convert to part by calculate_constants
		Matrix3 I;

		// part
		Vector3 offset;

		// part to shape
		Quaternion q;


		POLYHEDRON()
		{
			highlight_type = GEOMETRY_FEATURE_TYPE_NONE;

			VHighlight = NULL;
			EHighlight = NULL;
			FHighlight = NULL;

			penetrating = false;
		};


		// construction
		void quad( int a,int b,int c,int d);

		void recalculate_constants();
		void globalize_vertex();
		void render_poly();

		// virtuals
		virtual void collision( POLYHEDRON * polyhedron ){};
		//virtual bool interact( INTERACT_TYPE type, const Vector3 &O, const Vector3 &vn, float &dist ){ return false; };
		virtual void physics(){};
};

