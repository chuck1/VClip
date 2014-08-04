#ifndef PLANE_HPP
#define PLANE_HPP

class PLANE {
	public:
		Vector3 n;
		float w;

		PLANE(){}

		PLANE( VERTEX* V, EDGE* E )
		{
			if ( V == E->t )
			{
				n = V->x - E->h->x;
			}
			else if ( V == E->h )
			{
				n = V->x - E->t->x;
			}
			else
			{
				MessageBox(NULL, _T("problem!!!!!!"), NULL, MB_OK);
			}
			n.normalize();
			w = n.dot(V->x);
		}
		PLANE( EDGE* E, VERTEX* V )
		{
			if ( V == E->t )
			{
				n = E->h->x - V->x;
			}
			else
			{
				n = E->t->x - V->x;
			}
			n.normalize();
			w = n.dot(V->x);
		}
		PLANE( EDGE* E, FACE *F )
		{
			n = F->n.cross( E->u() );
			n.normalize();
			w = n.dot( E->h->x );
			if ( ( n.dot( F->x ) - w ) > 0 )
			{
				n *= -1.0f; w *= -1.0f;
			}
		}
		PLANE( FACE *F, EDGE *E )
		{
			n = F->n.cross( E->u() );
			n.normalize();
			w = n.dot( E->h->x );
			if ( ( n.dot( F->x ) - w ) < 0 )
			{
				n *= -1.0f; w *= -1.0f;
			}
		}

};


#endif
