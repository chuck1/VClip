template <class U> RECTANGULAR_PARALLELEPIPED<U>::RECTANGULAR_PARALLELEPIPED( float offset_x, float offset_y, float offset_z, float p, float n, float s, float width, float depth, float height, float rho )
{
	geometry_type = GEOMETRY_TYPE_RECTANGULAR_PARALLELEPIPED;
	density = rho;
	b = width;
	a = depth;
	c = height;
	m = a*b*c*density;
	I.row[0].col[0] = m*(b*b+c*c)/12;
	I.row[1].col[1] = m*(a*a+c*c)/12;
	I.row[2].col[2] = m*(b*b+a*a)/12;

	// position relative to part coordinates
	offset.col[0] = offset_x;
	offset.col[1] = offset_y;
	offset.col[2] = offset_z;

	recalculate_constants();

	float x2[] = { -0.5f, -0.5f, -0.5f, -0.5f,  0.5f,  0.5f,  0.5f, 0.5f };
	float y2[] = { -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, 0.5f };
	float z2[] = { -0.5f,  0.5f, -0.5f,  0.5f, -0.5f,  0.5f, -0.5f, 0.5f };
	
	VERTEX<U> * VTemp = NULL;
	
	Vector3 x;

	for ( int i = 0; i < 8; i++ )
	{
		VTemp = new VERTEX<U>;
		VTemp->poly = this;

		x = ( X * x2[i] ) * a + ( Y * y2[i] ) * b + ( Z * z2[i] ) * c;
		VTemp->xRel = x;

		V.push_back(VTemp);
	}

	// x+
	quad(4,5,7,6);
	// x-
	quad(0,2,3,1);
	// y+
	quad(2,6,7,3);
	// y-
	quad(0,1,5,4);
	// z+
	quad(1,3,7,5);
	// z-
	quad(0,4,6,2);
	
	for ( int i = 0; i < E.size(); i++ )
	{
		for ( int j = 0; j < F.size(); j++ )
		{
			for ( int k = 0; k < F.at(j)->E.size(); k++ )
			{
				if ( E.at(i) == F.at(j)->E.at(k) )
				{
					E.at(i)->F1 = F.at(j);
				}
			}
		}
	}

	for ( int i = 0; i < E.size(); i++ )
	{
		for ( int j = 0; j < E.size(); j++ )
		{
			if ( i != j )
			{
				if ( E.at(i)->h == E.at(j)->t )
				{
					if ( E.at(i)->t == E.at(j)->h )
					{
						E.at(i)->F2 = E.at(j)->F1;
					}
				}
			}
		}

		E.at(i)->F.push_back(E.at(i)->F1);
		E.at(i)->F.push_back(E.at(i)->F2);

		E.at(i)->V.push_back(E.at(i)->t);
		E.at(i)->V.push_back(E.at(i)->h);
	}

	for ( int i = 0; i < V.size(); i++ )
	{
		if ( V.at(i)->poly == NULL )
		{
			printf( "missing parent" );
		}
	}
	for ( int i = 0; i < F.size(); i++ )
	{
		if ( F.at(i)->poly == NULL )
		{
			printf( "missing parent" );
		}
	}
	for ( int i = 0; i < E.size(); i++ )
	{
		if ( E.at(i)->poly == NULL )
		{
			printf( "missing parent" );
		}
		if ( ( E.at(i)->h == NULL ) || ( E.at(i)->t == NULL ) || ( E.at(i)->F1 == NULL ) || ( E.at(i)->F2 == NULL ) )
		{
			printf( "missing neighbor" );
		}
	}
	for ( int i = 0; i < E.size(); i++ )
	{
		//swprintf_s( msgbox_tchar, _T("%p %p %p %p"), E.at(i)->h, E.at(i)->t, E.at(i)->F1, E.at(i)->F2 );
		//MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
	}
};
/*
template <class U> bool RECTANGULAR_PARALLELEPIPED<U>::interact( INTERACT_TYPE type, const Vector3 &O, const Vector3 &vn, float &dist )
{
	Vector3 OA = Vector3(-0.5f*a,-0.5f*b,-0.5f*c) - O;
	Vector3 OB = Vector3( 0.5f*a, 0.5f*b, 0.5f*c) - O;

	float k;

	int ia;
	int ib;
	int ic;

	int ia_[] = {0,1,2};
	int ib_[] = {1,2,0};
	int ic_[] = {2,0,1};

	_for(ind,3)
	{
		ia = ia_[ind];
		ib = ib_[ind];
		ic = ic_[ind];

		if ( vn.col[ia] != 0 )
		{
			if ( vn.col[ia] > 0 )
			{
				k = OA.col[ia] / vn.col[ia];
			}
			else if ( vn.col[ia] < 0 )
			{
				k = OB.col[ia] / vn.col[ia];
			}

			if ( OA.col[ib] <= ( k * vn.col[ib] ) )
			{
				if ( OB.col[ib] >= ( k * vn.col[ib] ) )
				{
					if ( OA.col[ic] <= ( k * vn.col[ic] ) )
					{
						if ( OB.col[ic] >= ( k * vn.col[ic] ) )
						{
							dist = k;
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}
*/
template <class U> void RECTANGULAR_PARALLELEPIPED<U>::collision( POLYHEDRON * polyhedron )
{
}
template <class U> void RECTANGULAR_PARALLELEPIPED<U>::physics()
{
}
