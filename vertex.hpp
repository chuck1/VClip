#ifndef VERTEX_HPP
#define VERTEX_HPP

class VERTEX {
	public:
		POLYHEDRON* poly;

		Vector3 x;
		Vector3 xRel;

		std::vector<EDGE*> E;

		VERTEX()
		{
			poly = NULL;
		};
};

#endif
