template <class U> void VCLIP<U>::algorithm( POLYHEDRON<U> * poly1, POLYHEDRON<U> * poly2 )
{
	Vector3 n;
	
	POLYHEDRON<U> * polyTemp;

	V1final = NULL;
	E1final = NULL;
	F1final = NULL;
	V2final = NULL;
	E2final = NULL;
	F2final = NULL;
	
	S1.clear();
	S2.clear();

	poly1->highlight_type = GEOMETRY_FEATURE_TYPE_NONE;
	poly2->highlight_type = GEOMETRY_FEATURE_TYPE_NONE;

	poly1->globalize_vertex();
	poly2->globalize_vertex();
	
	VCLIP_RETURN result = VVstate(poly1->V.at(0),poly2->V.at(0));
	
	poly1->penetrating = false;
	poly2->penetrating = false;

	printf( "algorithm done\n" );
	
	
	if ( poly1 == poly2 )
	{
		printf( "oh dear god\n" );
	}

	flipped = false;

	if ( V1final != NULL)
	{
		if ( V1final->poly == poly2 )
		{
			flipped = true;
		}
	}
	if ( E1final != NULL)
	{
		if ( E1final->poly == poly2 )
		{
			flipped = true;
		}
	}
	if ( F1final != NULL)
	{
		if ( F1final->poly == poly2 )
		{
			flipped = true;
		}
	}
	
	if ( flipped )
	{
		polyTemp = poly1;
		poly1 = poly2;
		poly2 = polyTemp;
	}

	switch ( result )
	{
	case VC_PENETRATION_EF:
		printf( "VC_PENETRATION_EF\n" );
		
		n = F2final->n;

		poly1->EHighlight = E1final;
		poly2->FHighlight = F2final;
		poly1->highlight_type = GEOMETRY_FEATURE_TYPE_EDGE;
		poly2->highlight_type = GEOMETRY_FEATURE_TYPE_FACE;
		
		poly1->penetrating = true;
		poly2->penetrating = true;
		


		S1.E.push_back( E1final );
		CheckNeighbors( E1final, S1, poly2 );

		printf( "S1 %i %i %i\n", S1.V.size(), S1.E.size(), S1.F.size() );
		
		S2.F.push_back( F2final );
		CheckNeighbors( F2final, S2, poly1 );

		printf( "S2 %i %i %i\n", S2.V.size(), S2.E.size(), S2.F.size() );
		



		//solveRBC( poly1, poly2, n, x, penetration );

		//track = true;

		break;
	case VC_PENETRATION_VF:
		printf( "VC_PENETRATION_VF\n" );
		//MessageBox(NULL, _T(), NULL, MB_OK);

		n = F2final->n;

		poly1->VHighlight = V1final;
		poly2->FHighlight = F2final;
		poly1->highlight_type = GEOMETRY_FEATURE_TYPE_VERTEX;
		poly2->highlight_type = GEOMETRY_FEATURE_TYPE_FACE;
		
		
		poly1->penetrating = true;
		poly2->penetrating = true;
		


		S1.V.push_back( V1final );
		CheckNeighbors( V1final, S1, poly2 );

		printf( "S1 %i %i %i\n", S1.V.size(), S1.E.size(), S1.F.size() );
		
		S2.F.push_back( F2final );
		CheckNeighbors( F2final, S2, poly1 );

		printf( "S2 %i %i %i\n", S2.V.size(), S2.E.size(), S2.F.size() );



		break;
	case VC_DONE_VV:
		printf( "VC_DONE_VV\n" );

		poly1->VHighlight = V1final;
		poly2->VHighlight = V2final;
		poly1->highlight_type = GEOMETRY_FEATURE_TYPE_VERTEX;
		poly2->highlight_type = GEOMETRY_FEATURE_TYPE_VERTEX;
		
		break;
	case VC_DONE_VE:
		printf( "VC_DONE_VE\n" );
		
		poly1->VHighlight = V1final;
		poly2->EHighlight = E2final;
		poly1->highlight_type = GEOMETRY_FEATURE_TYPE_VERTEX;
		poly2->highlight_type = GEOMETRY_FEATURE_TYPE_EDGE;
		
		break;
	case VC_DONE_VF:
		printf( "VC_DONE_VF\n" );
		poly1->VHighlight = V1final;
		poly2->FHighlight = F2final;
		poly1->highlight_type = GEOMETRY_FEATURE_TYPE_VERTEX;
		poly2->highlight_type = GEOMETRY_FEATURE_TYPE_FACE;
		
		break;
	case VC_DONE_EE:
		printf( "VC_DONE_EE\n" );
		poly1->EHighlight = E1final;
		poly2->EHighlight = E2final;
		poly1->highlight_type = GEOMETRY_FEATURE_TYPE_EDGE;
		poly2->highlight_type = GEOMETRY_FEATURE_TYPE_EDGE;
		
		break;
	default:
		printf( "WTF!" );
		break;
	}
}
template <class U> template <class clipTool, class W> bool VCLIP<U>::clipEdge( EDGE<U>* E, clipTool* X, const std::vector<W*> &S, float &lambdaMin, float &lambdaMax, W* &NMin, W* &NMax )
{
	if (track)
	{
		printf( "clipEdge E X %p %p", E, X );
	}
	
	NMin = NULL;
	NMax = NULL;
	lambdaMin = 0.0f;
	lambdaMax = 1.0f;

	float lambda = 0;
	W* N = NULL;
	float dt = 0;
	float dh = 0;
	PLANE<U> VP;
	for ( int i = 0; i < S.size(); i++ )
	{
		N = S.at(i);
		VP = PLANE<U>( X, N );
		dt = D( &VP, E->t );
		dh = D( &VP, E->h );

		if (track)
		{
			printf( "clipEdge N dt dh %p %f %f", N, dt, dh );
		}

		if (( dt < 0 ) && ( dh < 0 ))
		{
			if (track)
			{
				
				//swprintf_s( msgbox_tchar, _T("simply excluded"));
				//MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
			}

			NMin = N;
			NMax = N;
			return false;
		}
		else if ( dt < 0 )
		{
			lambda = dt/(dt-dh);
			if ( lambda > lambdaMin )
			{
				lambdaMin = lambda;
				NMin = N;
				if ( lambdaMin > lambdaMax )
				{
					return false;
				}
			}
		}
		else if ( dh < 0 )
		{
			lambda = dt/(dt-dh);
			if ( lambda < lambdaMax )
			{
				lambdaMax = lambda;
				NMax = N;
				if ( lambdaMin > lambdaMax )
				{
					return false;
				}
			}
		}
	}
	return true;
}
template <class U> float VCLIP<U>::D( FACE<U>* F, VERTEX<U>* V )
{
	return ( F->n.dot(V->x) - F->w );
}
template <class U> float VCLIP<U>::D( FACE<U>* F, const Vector3 &y )
{
	return ( F->n.dot(y) - F->w );
}
template <class U> float VCLIP<U>::D( PLANE<U>* P, VERTEX<U>* V )
{
	return ( P->n.dot(V->x) - P->w );
}
template <class U> bool VCLIP<U>::Dprime( EDGE<U>* E, VERTEX<U>* V, float lambda )
{
	return ( E->u().dot( E->e(lambda) - V->x ) > 0 );
}
template <class U> bool VCLIP<U>::Dprime( EDGE<U>* E, FACE<U>* F, float lambda )
{
	if ( D( F, E->e(lambda) ) > 0 )
	{
		return ( E->u().dot(F->n) > 0 );
	}
	else
	{
		return ( E->u().dot(F->n) < 0 );
	}
}
template <class U> VCLIP_RETURN VCLIP<U>::handleLocalMin( VERTEX<U>* V, FACE<U>* F )
{
	printf( "handleLocalMin %p %p\n", V, F );
	
	
	float dMax = -std::numeric_limits<float>::infinity();
	float d = 0;
	FACE<U>* F0 = NULL;
	for ( int i = 0; i < F->poly->F.size(); i++ )
	{
		d = D(F->poly->F.at(i),V);
		if ( d > dMax )
		{
			dMax = d;
			F0 = F->poly->F.at(i);
		}
	}
	/*
	if ( dMax <= 0 )
	{
		V1final = V;
		F2final = F;
		x = V->x;
		penetration = dMax;
		return VC_PENETRATION_VF;
	}
	*/
	return VFstate(V,F0);
}
template <class U> VCLIP_RETURN VCLIP<U>::VVstate   ( VERTEX<U>* V1, VERTEX<U> * V2 )
{
	if (track)
	{
		printf( "VVstate %p %p", V1, V2 );
	}

	VCLIP_RETURN result;
	
	result = VVstateSub( V1, V2 );
	if ( result != VC_CONTINUE ){ return result; }
	
	flipped = !flipped;
	result = VVstateSub( V2, V1 );
	if ( result != VC_CONTINUE ){ return result; }
	flipped = !flipped;

	V1final = V1;
	V2final = V2;
	return VC_DONE_VV;
}
template <class U> VCLIP_RETURN VCLIP<U>::VVstateSub( VERTEX<U>* V1, VERTEX<U> * V2 )
{
	if (track)
	{
		printf( "VVstateSub %p %p", V1, V2 );
	}
	
	for ( int i = 0; i < V1->E.size(); i++ )
	{
		PLANE<U> VP(V1,V1->E.at(i));
		if ( D(&VP,V2) < 0 )
		{
			return VEstate( V2, V1->E.at(i) );
		}
	}
	return VC_CONTINUE;
}
template <class U> VCLIP_RETURN VCLIP<U>::VEstate   ( VERTEX<U>* V,  EDGE<U> * E )
{
	if (track)
	{
		printf( "VEstate %p %p", V, E );
	}

	PLANE<U> VP( E, E->h );
	if ( D( &VP, V ) < 0 )
	{
		return VVstate( V, E->h );
	}

	VP = PLANE<U>( E, E->t );
	if ( D( &VP, V ) < 0 )
	{
		return VVstate( V, E->t );
	}

	VP = PLANE<U>( E, E->F1 );
	if ( D( &VP, V ) < 0 )
	{
		return VFstate( V, E->F1 );
	}

	VP = PLANE<U>( E, E->F2 );
	if ( D( &VP, V ) < 0 )
	{
		return VFstate( V, E->F2 );
	}

	float lambdaMin = 0;
	float lambdaMax = 1;
	EDGE<U>* EMin = NULL;
	EDGE<U>* EMax = NULL;
	clipEdge( E, V, V->E, lambdaMin, lambdaMax, EMin, EMax );

	if (track)
	{
		printf( "VEstate EMin EMax %p %p", EMin, EMax );
	}

	if (( EMin == EMax ) && ( EMin != NULL ))
	{
		return EEstate( EMin, E );
	}
	else
	{
		if (( EMin != NULL ) && Dprime( E, V, lambdaMin ) )
		{
			return EEstate( EMin, E );
		}
		else if (( EMax != NULL ) && !Dprime( E, V, lambdaMax ) )
		{
			return EEstate( EMax, E );
		}
	}
	
	V1final = V;
	E2final = E;
	return VC_DONE_VE;
}
template <class U> VCLIP_RETURN VCLIP<U>::VFstate   ( VERTEX<U>* V,  FACE<U>* F )
{
	printf( "VFstate %p %p\n", V, F );
	
	float d = 0;
	float dMin = 0;
	EDGE<U> * E0 = NULL;

	PLANE<U> VP;
	for ( unsigned int i = 0; i < F->E.size(); i++ )
	{
		VP = PLANE<U>( F, F->E.at(i) );
		d = D(&VP, V );
		if ( d < dMin )
		{
			dMin = d;
			E0 = F->E.at(i);
		}
	}

	if ( E0 != NULL )
	{
		return VEstate( V, E0 );
	}

	float dh = D( F, V );
	float dt;
	for ( unsigned int i = 0; i < V->E.size(); i++ )
	{
		if ( V == V->E.at(i)->h )
		{
			dt = D( F, V->E.at(i)->t );
			if ( dh*dt < 0 )
			{
				return EFstate( V->E.at(i), F );
			}
			else
			{
				if ( abs(dh) > abs(dt) )
				{
					return EFstate( V->E.at(i), F );
				}
			}
		}
		else
		{
			printf( "VFstate bad neighbor\n" );
			return VC_DONE_VF;
		}
	}
	if ( D( F, V ) > 0 )
	{
		V1final = V;
		F2final = F;
		return VC_DONE_VF;
	}
	return handleLocalMin(V,F);
}
template <class U> VCLIP_RETURN VCLIP<U>::EEstate   ( EDGE<U>  * E1, EDGE<U>* E2 )
{
	if (track)
	{
		//swprintf_s( msgbox_tchar, _T("EEstate %p %p"), E1, E2);
		//MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
	}

	VCLIP_RETURN result;
	
	result = EEstateSub( E1, E2 );
	if ( result != VC_CONTINUE ){ return result; }
	
	result = EEstateSub( E2, E1 );
	if ( result != VC_CONTINUE ){ return result; }

	E1final = E1;
	E2final = E2;
	return VC_DONE_EE;
}
template <class U> VCLIP_RETURN VCLIP<U>::EEstateSub( EDGE<U>  * E1, EDGE<U>* E2 )
{
	float lambdaMin = 0.0f;
	float lambdaMax = 1.0f;
	VERTEX<U> * VMin = NULL;
	VERTEX<U> * VMax = NULL;

	clipEdge( E2, E1, E1->V, lambdaMin, lambdaMax, VMin, VMax );
	if (( VMin == VMax ) && ( VMax != NULL ))
	{
		return VEstate(VMin,E2);
	}
	else
	{
		if (( VMin != NULL ) && Dprime( E2, VMin, lambdaMin ) )
		{
			return VEstate(VMin,E2);
		}
		else if (( VMax != NULL ) && !Dprime( E2, VMax, lambdaMax ) )
		{
			return VEstate(VMax,E2);
		}
	}

	lambdaMin = 0.0f;
	lambdaMax = 1.0f;
	FACE<U> * FMin = NULL;
	FACE<U> * FMax = NULL;
	clipEdge( E2, E1, E1->F, lambdaMin, lambdaMax, FMin, FMax );
	if (( FMin == FMax ) && ( FMin != NULL ))
	{
		return EFstate(E2,FMin);
	}
	else
	{
		if (( FMin != NULL ) && Dprime( E2, FMin, lambdaMin ) )
		{
			return EFstate(E2,FMin);
		}
		else if (( FMax != NULL ) && !Dprime( E2, FMax, lambdaMax ) )
		{
			return EFstate(E2,FMax);
		}
	}
	return VC_CONTINUE;
}
template <class U> VCLIP_RETURN VCLIP<U>::EFstate   ( EDGE<U>  * E,  FACE<U>* F )
{
	printf( "EFstate %p %p\n", E, F );
	

	float lambdaMin = 0;
	float lambdaMax = 1;
	float lambdaPen;
	EDGE<U> * EMin = NULL;
	EDGE<U> * EMax = NULL;
	if ( !clipEdge( E, F, F->E, lambdaMin, lambdaMax, EMin, EMax ) )
	{
		return EEstate(E,EMin);
	}
	float dMin = D( F, E->e(lambdaMin));
	float dMax = D( F, E->e(lambdaMax));
	float dh   = D( F, E->h);
	float dt   = D( F, E->t);

	if (track){
		/*
		swprintf_s( msgbox_tchar, _T("F.n F.w %f %f %f %f"), F->n.col[0], F->n.col[1], F->n.col[2], F->w );
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		swprintf_s( msgbox_tchar, _T("F.x F.w %f %f %f %f"), F->x.col[0], F->x.col[1], F->x.col[2], F->w );
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		swprintf_s( msgbox_tchar, _T("F.E.h %f %f %f "), F->E.at(0)->h->x.col[0], F->E.at(0)->h->x.col[1], F->E.at(0)->h->x.col[2] );
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);

		swprintf_s( msgbox_tchar, _T("EFstate lambda min max %f %f"), lambdaMin, lambdaMax);
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		swprintf_s( msgbox_tchar, _T("EFstate d min max %f %f"), dMin, dMax);
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		*/
	}

	if ( dMin*dMax <= 0 )
	{
		E1final = E;
		F2final = F;
		lambdaPen = dt/(dt-dh);

		/*
		swprintf_s( msgbox_tchar, _T("lambdaPen %f %f %f"), dh,dt,lambdaPen );
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		*/
		if ( dMin <= 0 )
		{
			x = E->t->x;
			penetration = dMin;
		}
		else if ( dMax <= 0 )
		{
			x = E->h->x;
			penetration = dMax;
		}
		//x = E->e(lambdaPen);
		return VC_PENETRATION_EF;
	}
	if ( Dprime( E, F, lambdaMin ) )
	{
		if ( EMin != NULL )
		{
			return EEstate(E,EMin);
		}
		else
		{
			return VFstate(E->t,F);
		}
	}
	else
	{
		if ( EMax != NULL )
		{
			return EEstate(E,EMax);
		}
		else
		{
			return VFstate(E->h,F);
		}
	}
}
template <class U> bool         VCLIP<U>::Vpenetrate( VERTEX<U>* V,  POLYHEDRON<U>* poly )
{
	for ( unsigned int i = 0; i < poly->F.size(); i++ )
	{
		if ( D(poly->F.at(i),V) > 0 )
		{
			return false;
		}
	}
	printf( "Vpenetrate %p\n", V );
	return true;
}
template <class U> bool         VCLIP<U>::Epenetrate( EDGE<U>*   E,   POLYHEDRON<U>* poly )
{
	FACE<U>* F;
	EDGE<U>* EMin;
	EDGE<U>* EMax;
	float lambdaMin;
	float lambdaMax;
	float dMin;
	float dMax;
	for ( int i = 0; i < poly->F.size(); i++ )
	{
		F = poly->F.at(i);
		if ( clipEdge( E, F, F->E, lambdaMin, lambdaMax, EMin, EMax ) )
		{
			dMin = D( F, E->e(lambdaMin));
			dMax = D( F, E->e(lambdaMax));
			if ( dMin*dMax <= 0 )
			{
				printf( "Epenetrate %p\n", E );
				return true;
			}
		}
	}
	return false;
}
template <class U> bool         VCLIP<U>::Fpenetrate( FACE<U>*   F,   POLYHEDRON<U>* poly )
{
	EDGE<U>* E;
	EDGE<U>* EMin;
	EDGE<U>* EMax;
	float lambdaMin;
	float lambdaMax;
	float dMin;
	float dMax;
	for ( int i = 0; i < poly->E.size(); i++ )
	{
		E = poly->E.at(i);
		if ( clipEdge( E, F, F->E, lambdaMin, lambdaMax, EMin, EMax ) )
		{
			dMin = D( F, E->e(lambdaMin));
			dMax = D( F, E->e(lambdaMax));
			if ( dMin*dMax <= 0 )
			{
				printf( "Fpenetrate %p\n", F );
				return true;
			}
		}
	}
	return false;
}
template <class U> void         VCLIP<U>::CheckNeighbors( VERTEX<U>* V, GEOMETRY_SET<U> &S, POLYHEDRON<U>* poly )
{
	EDGE<U>* E = NULL;
	for ( unsigned int i = 0; i < V->E.size(); i++ )
	{
		E = V->E.at(i);
		if ( !S.find(E) )
		{
			if ( Epenetrate( E, poly ) )
			{
				S.E.push_back(E);
				CheckNeighbors( E, S, poly );
			}
		}
	}
}
template <class U> void         VCLIP<U>::CheckNeighbors( EDGE  <U>* E, GEOMETRY_SET<U> &S, POLYHEDRON<U>* poly )
{
	VERTEX<U>* V = NULL;
	FACE  <U>* F = NULL;
	for ( unsigned int i = 0; i < E->V.size(); i++ )
	{
		V = E->V.at(i);
		if ( !S.find(V) )
		{
			if ( Vpenetrate( V, poly ) )
			{
				S.V.push_back(V);
				CheckNeighbors( V, S, poly );
			}
		}
	}
	for ( unsigned int i = 0; i < E->F.size(); i++ )
	{
		F = E->F.at(i);
		if ( !S.find(F) )
		{
			if ( Fpenetrate( F, poly ) )
			{
				S.F.push_back(F);
				CheckNeighbors( F, S, poly );
			}
		}
	}
}
template <class U> void         VCLIP<U>::CheckNeighbors( FACE  <U>* F, GEOMETRY_SET<U> &S, POLYHEDRON<U>* poly )
{
	EDGE<U>* E = NULL;
	for ( unsigned int i = 0; i < F->E.size(); i++ )
	{
		E = F->E.at(i);
		if ( !S.find(E) )
		{
			if ( Epenetrate( E, poly ) )
			{
				S.E.push_back(E);
				CheckNeighbors( E, S, poly );
			}
		}
	}
}
