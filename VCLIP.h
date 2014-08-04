
#include "GEOMETRY.h"

enum VCLIP_RETURN
{
	VC_CONTINUE,
	VC_PENETRATION_EF,
	VC_PENETRATION_VF,
	VC_DONE_VV,
	VC_DONE_VE,
	VC_DONE_VF,
	VC_DONE_EE
};
template <class U> class VCLIP
{
public:
	char msgbox_tchar[64];
	
	VERTEX * V1final;
	EDGE   * E1final;
	FACE   * F1final;
	VERTEX * V2final;
	EDGE   * E2final;
	FACE   * F2final;

	bool flipped;
	bool track;

	GEOMETRY_SET S1;
	GEOMETRY_SET S2;

	VCLIP()
	{ 
		track = false;
	}

	Vector3 x;
	float penetration;

	std::vector<FACE*> allFaces;

	void algorithm( POLYHEDRON * poly1, POLYHEDRON * poly2 );
	float D( FACE* F, VERTEX* V );
	float D( FACE* F, const Vector3 &y );
	float D( PLANE* P, VERTEX* V );
	bool Dprime( EDGE* E, VERTEX* V, float lambda );
	bool Dprime( EDGE* E, FACE* F, float lambda );
	template <class T, class W> bool clipEdge( EDGE* E, T* X, const std::vector<W*> &S, float &lambdaMin, float &lambdaMax, W* &NMin, W* &NMax );
	VCLIP_RETURN handleLocalMin( VERTEX* V, FACE* F );
	VCLIP_RETURN VVstate   ( VERTEX * V1, VERTEX * V2 );
	VCLIP_RETURN VVstateSub( VERTEX * V1, VERTEX * V2 );
	VCLIP_RETURN VEstate   ( VERTEX* V, EDGE * E );
	VCLIP_RETURN VFstate   ( VERTEX* V, FACE* F );
	VCLIP_RETURN EEstate   ( EDGE* E1, EDGE * E2 );
	VCLIP_RETURN EEstateSub( EDGE* E1, EDGE * E2 );
	VCLIP_RETURN EFstate   ( EDGE* E, FACE* F );
	bool         Vpenetrate( VERTEX* V, POLYHEDRON* poly );
	bool         Epenetrate( EDGE*   E, POLYHEDRON* poly );
	bool         Fpenetrate( FACE*   F, POLYHEDRON* poly );
	void         CheckNeighbors( VERTEX* V, GEOMETRY_SET &S, POLYHEDRON* poly );
	void         CheckNeighbors( EDGE  * E, GEOMETRY_SET &S, POLYHEDRON* poly );
	void         CheckNeighbors( FACE  * F, GEOMETRY_SET &S, POLYHEDRON* poly );
};


/*
swprintf_s( msgbox_tchar, _T("%d"), GetLastError());
MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
*/
/*

class DERIVED_POLYHEDRON
{


	// virtuals
	void collision( POLYHEDRON * polyhedron );
	bool interact( INTERACT_TYPE type, const Vector3 &O, const Vector3 &vn, float &dist );
	void render();
	void physics();


}



void DERIVED_POLYHEDRON::collision( POLYHEDRON * polyhedron )
{
}

bool DERIVED_POLYHEDRON::interact( INTERACT_TYPE type, const Vector3 &O, const Vector3 &vn, float &dist )
{
	return false;
}

void DERIVED_POLYHEDRON::render()
{
}

void DERIVED_POLYHEDRON::physics()
{
}


*/
