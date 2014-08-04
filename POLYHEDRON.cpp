#include "polyhedron.hpp"

void POLYHEDRON::recalculate_constants()
{
	// inertia in part coordinates
	I = q.getMatrix3() * I;

	I.row[0].col[0] += m*(offset.col[1]*offset.col[1] + offset.col[2]*offset.col[2]);
	I.row[1].col[1] += m*(offset.col[2]*offset.col[2] + offset.col[0]*offset.col[0]);
	I.row[2].col[2] += m*(offset.col[0]*offset.col[0] + offset.col[1]*offset.col[1]);

	I.row[0].col[1] += m*offset.col[0]*offset.col[1];
	I.row[1].col[0] += m*offset.col[0]*offset.col[1];

	I.row[1].col[2] += m*offset.col[1]*offset.col[2];
	I.row[2].col[1] += m*offset.col[1]*offset.col[2];

	I.row[2].col[0] += m*offset.col[2]*offset.col[0];
	I.row[0].col[2] += m*offset.col[2]*offset.col[0];
}
void POLYHEDRON::globalize_vertex()
{
	Vector3 x;
	for ( int i = 0; i < V.size(); i++ )
	{
		//V.at(i)->x = part->q.getConjugate() * (( q.getConjugate() * V.at(i)->xRel ) + offset ) + part->x;
		
		x = parent->q.getConjugate() * V.at(i)->xRel;
		/*
		swprintf_s( msgbox_tchar, _T("xRel.mag %f %f"), V.at(i)->xRel.magnitude(), x.magnitude() );
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		*/
		


		V.at(i)->x = x + parent->x;
		//printf( "xRel %f %f %f\n", V.at(i)->xRel.col[0], V.at(i)->xRel.col[1], V.at(i)->xRel.col[2] );
		printf( "x    %f %f %f\n", V.at(i)->x.col[0], V.at(i)->x.col[1], V.at(i)->x.col[2] );
	}
	for ( int i = 0; i < F.size(); i++ )
	{
		F.at(i)->update();
	}
}
void POLYHEDRON::quad( int a, int b, int c, int d )
{
	EDGE * ETemp = NULL;
	FACE * FTemp = new FACE;
	
	FTemp->poly = this;

	ETemp = new EDGE(this,V.at(a),V.at(b));
	E.push_back(ETemp);
	V.at(a)->E.push_back(E.back());
	FTemp->E.push_back(E.back());

	ETemp = new EDGE(this,V.at(b),V.at(c));
	E.push_back(ETemp);
	V.at(b)->E.push_back(E.back());
	FTemp->E.push_back(E.back());
	
	ETemp = new EDGE(this,V.at(c),V.at(d));
	E.push_back(ETemp);
	V.at(c)->E.push_back(E.back());
	FTemp->E.push_back(E.back());
	
	ETemp = new EDGE(this,V.at(d),V.at(a));
	E.push_back(ETemp);
	V.at(d)->E.push_back(E.back());
	FTemp->E.push_back(E.back());
	
	F.push_back(FTemp);
}
void POLYHEDRON::render_poly()
{
	glPushMatrix();

	glTranslatef( offset.col[0], offset.col[1], offset.col[2] );

	float * mat = new float[16];
	q.getMatrix(mat);
	glMultMatrixf(mat);
	delete[] mat;
	
	Vector3 xTemp;


	for ( int i = 0; i < F.size(); i++ )
	{
		
		glColor3f(1.0f,1.0f,1.0f);
		glBegin( GL_LINE_LOOP );
		
		for ( int j = 0; j < F.at(i)->E.size(); j++ )
		{
			xTemp = F.at(i)->E.at(j)->h->x;
			glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );
		}
		
		glEnd();
		
		glColor3f(0.0f,1.0f,0.0f);
		glBegin( GL_LINES );
		
		xTemp = F.at(i)->E.at(0)->h->x;
		glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );

		xTemp = F.at(i)->x;
		glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );
		
		glEnd();

		glColor3f(0.0f,0.0f,1.0f);
		glBegin( GL_LINES );
		
		xTemp = F.at(i)->x;
		glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );

		xTemp = F.at(i)->x + F.at(i)->n;
		glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );
		
		glEnd();
	}
	/*
	for ( int i = 0; i < V.size(); i++ )
	{
		for ( int j = 0; j < V.at(i)->E.size(); j++ )
		{
			glColor3f(1.0f,1.0f,0.0f);
			glBegin( GL_LINES );
		
			xTemp = V.at(i)->x;
			glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );

			xTemp = V.at(i)->x + V.at(i)->E.at(j)->u();
			glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );
		
			glEnd();
		}
	}
	*/
	glClear( GL_DEPTH_BUFFER_BIT );


	if ( penetrating )
	{
		glColor3f(1.0f,0.0f,0.0f);
	}
	else
	{
		glColor3f(1.0f,0.0f,1.0f);
	}

	switch ( highlight_type )
	{
	case GEOMETRY_FEATURE_TYPE_VERTEX:
		
		if ( VHighlight == NULL )
		{
			swprintf_s( msgbox_tchar, _T("null pointer"), V, F);
			MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		}
		
		

		try
		{
			xTemp = VHighlight->x;
		}
		catch ( std::exception &e )
		{
			swprintf_s( msgbox_tchar, _T("VHighlight bad"), V, F);
			MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		}

		glBegin( GL_LINES );
		//glVertex3f( VHighlight->xRel.col[0]+0.02f, VHighlight->xRel.col[1]+0.02f, VHighlight->xRel.col[2] );
		glVertex3f( VHighlight->x.col[0], VHighlight->x.col[1], VHighlight->x.col[2] );
		glVertex3f(0.0f,0.0f,-3.0f);
		glEnd();

		break;
	case GEOMETRY_FEATURE_TYPE_EDGE:
		if ( EHighlight == NULL )
		{
			swprintf_s( msgbox_tchar, _T("null pointer"), V, F);
			MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		}
		
		try
		{
			xTemp = EHighlight->h->x;
		}
		catch ( std::exception &e )
		{
			swprintf_s( msgbox_tchar, _T("EHighlight bad"), V, F);
			MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		}

		glBegin( GL_LINES );
		//glVertex3f( EHighlight->h->xRel.col[0], EHighlight->h->xRel.col[1], EHighlight->h->xRel.col[2] );
		//glVertex3f( EHighlight->t->xRel.col[0], EHighlight->t->xRel.col[1], EHighlight->t->xRel.col[2] );
		glVertex3f( EHighlight->h->x.col[0], EHighlight->h->x.col[1], EHighlight->h->x.col[2] );
		glVertex3f( EHighlight->t->x.col[0], EHighlight->t->x.col[1], EHighlight->t->x.col[2] );
		glEnd();

		break;
	case GEOMETRY_FEATURE_TYPE_FACE:
		if ( FHighlight == NULL )
		{
			swprintf_s( msgbox_tchar, _T("null pointer"), V, F);
			MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		}

		try
		{
			xTemp = FHighlight->x;
		}
		catch ( std::exception &e )
		{
			swprintf_s( msgbox_tchar, _T("FHighlight bad"), V, F);
			MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
		}

		glBegin( GL_QUADS );
		for( int j = 0; j < FHighlight->E.size(); j++ )
		{
			//xTemp = FHighlight->E.at(j)->h->xRel;
			xTemp = FHighlight->E.at(j)->h->x;
			glVertex3f( xTemp.col[0], xTemp.col[1], xTemp.col[2] );
		}
		glEnd();
		break;
	}
	/*
	if ( penetrating )
	{
		swprintf_s( msgbox_tchar, _T("penetrating render done"), V, F);
		MessageBox(NULL, msgbox_tchar, NULL, MB_OK);
	}
	*/
	glPopMatrix();
}
