

FACE::FACE()
		{
			poly = NULL;
		}

		void FACE::update()
		{
			n = E.at(1)->u().cross(E.at(0)->u());
			n.normalize();
			x = ( E.at(0)->e(0.5f) + E.at(1)->t->x ) * 0.5f;

			w = n.dot(x);
		}

