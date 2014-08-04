
EDGE::EDGE()
{
	poly = NULL;
	h = NULL;
	t = NULL;
	F1 = NULL;
	F2 = NULL;
}
EDGE::EDGE( POLYHEDRON<U>* polyParam, VERTEX<U>* hParam, VERTEX<U>* tParam )
{
	poly = polyParam;
	h = hParam;
	t = tParam;
	F1 = NULL;
	F2 = NULL;
}

Vector3		EDGE::e(float lambda)
{
	Vector3 ret = (t->x)*(1.0f-lambda) + (h->x)*lambda;
	return ret;
}

Vector3		EDGE::u()
{
	return ( h->x - t->x );
}

