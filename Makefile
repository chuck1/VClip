
#cppfiles = vclip_test.cpp CIRCULAR_CYLINDER.cpp POLYHEDRON.cpp RECTANGULAR_PARALLELEPIPED.cpp
cppfiles = vclip_test.cpp POLYHEDRON.cpp RECTANGULAR_PARALLELEPIPED.cpp

all:
	g++ ${cppfiles} -o test

