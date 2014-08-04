#ifndef VECTOR_H
#define VECTOR_H


#define PI 3.141592653589793239

class Vector3;
class Matrix3;
class Matrix6;
class Quaternion;
class QuaternionBase;

class Vector3Base
{
public:
	float col[3];

	void operator = (const Vector3 &param);

	Vector3 operator - (Vector3 param);
};

class Vector3
{
public:
	float col[3];

	Vector3();
	Vector3( const Vector3Base &param );
	Vector3( float x, float y, float z );

	Vector3 operator + (Vector3 param);
	void operator += (Vector3 param);
	void operator -= (Vector3 param);
	void operator /= (const float &param);
	void operator *= (const float &param);
	void operator = (const Vector3 &param);
	void operator = (const Vector3Base &param);
	Vector3 operator - (Vector3 param) const;
	Vector3 operator * (float param) const;

	float dot(Vector3 param) const;
	Vector3 cross(Vector3 param) const;
	void normalize();
	float magnitude() const;
	void zero();
	float angle( const Vector3& param );
};

class Vector6
{
public:
	float col[6];

	Vector6();
	Vector6(Vector3 upper, Vector3 lower);

	float dot(Vector6 param);
	void zero();
	Vector3 upper();
	Vector3 lower();

	Vector6 operator * (Matrix6 param);
	Vector6 operator * (float param);
	Vector6 operator + (Vector6 param);
	void operator += (Vector6 param);
	void operator -= (Vector6 param);
};

class QuaternionBase
{
public:
	float w;
	Vector3Base v;

	Quaternion getConjugate() const;
	void getMatrix( float * ) const;
	Matrix3 getMatrix3() const;

	Quaternion operator* (const Quaternion &q2) const;
	Vector3 operator* (const Vector3 &param) const;
	void operator= (const Quaternion &param);
};

class Quaternion
{
public:
	float w;
	Vector3 v;

	Quaternion();
	Quaternion(Vector3 param);
	Quaternion(const Vector3 &axis, float angle);

	Quaternion getConjugate() const;
	void getMatrix( float * ) const;
	Matrix3 getMatrix3() const;
	float magnitude() const;

	Quaternion operator* (const Quaternion &q2) const;
	Vector3 operator* (const Vector3 &param) const;
	void operator = (const Quaternion &param);
	void operator = (const QuaternionBase &param);
};

class Matrix6
{
public:
	Vector6 row[6];

	Matrix6()
	{
		for ( int i = 0; i < 6; i++ )
		{
			for ( int j = 0; j < 6; j++ )
			{
				row[i].col[j] = 0;
			}
		}
	}

	Matrix6(Matrix3 ur, Matrix3 ul, Matrix3 lr, Matrix3 ll);

	Vector6 operator * (Vector6 param);
};

class Matrix3
{
public:
	Vector3 row[3];

	Matrix3();

	void operator += (const Matrix3 &param );

	Vector3 operator * (const Vector3 &param);
	Matrix3 operator * (const Matrix3 &param);
	Matrix3 operator / (float param);
	Matrix3 operator * (float param);

	static Matrix3 Eye();

	Matrix3 inverse();
	Matrix3 transpose();
	Matrix3 cofactor();
	float minor_determinant( int i, int j );
	float determinant();
};

#endif
