Vector3 Vector3Base::operator - (Vector3 param)
{
	Vector3 ret;
	for ( int i = 0; i < 3; i++ ){ ret.col[i] = col[i] - param.col[i]; }
	return ret;
}

void Vector3Base::operator = (const Vector3 &param)
{
	col[0] = param.col[0];
	col[1] = param.col[1];
	col[2] = param.col[2];
}



Vector3::Vector3()
{
	col[0] = 0;
	col[1] = 0;
	col[2] = 0;
}

Vector3::Vector3( const Vector3Base &param )
{
	for ( int i = 0; i < 3; i++ )
	{
		col[i] = param.col[i];
	}
}

Vector3::Vector3( float x, float y, float z )
{
	col[0] = x;
	col[1] = y;
	col[2] = z;
}

Vector3 Vector3::operator + (Vector3 param)
{
	Vector3 ret;
	for ( int i = 0; i < 3; i++ ){ ret.col[i] = col[i] + param.col[i]; }
	return ret;
}

void Vector3::operator += (Vector3 param)
{
	for ( int j = 0; j < 3; j++ )
	{
		col[j] += param.col[j];
	}
}

void Vector3::operator -= (Vector3 param)
{
	for ( int j = 0; j < 3; j++ )
	{
		col[j] -= param.col[j];
	}
}
void Vector3::operator = (const Vector3 &param)
{
	col[0] = param.col[0];
	col[1] = param.col[1];
	col[2] = param.col[2];
}
void Vector3::operator = (const Vector3Base &param)
{
	col[0] = param.col[0];
	col[1] = param.col[1];
	col[2] = param.col[2];
}
Vector3 Vector3::operator - (Vector3 param) const
{
	Vector3 ret;
	for ( int i = 0; i < 3; i++ ){ ret.col[i] = col[i] - param.col[i]; }
	return ret;
}
float Vector3::dot(Vector3 param) const
{
	return ( col[0]*param.col[0] + col[1]*param.col[1] + col[2]*param.col[2] );
}
Vector3 Vector3::cross(Vector3 param) const
{
	Vector3 ret;
	ret.col[0] = col[1]*param.col[2] - col[2]*param.col[1];
	ret.col[1] = col[2]*param.col[0] - col[0]*param.col[2];
	ret.col[2] = col[0]*param.col[1] - col[1]*param.col[0];
	return ret;
}
void Vector3::normalize()
{
	float m = magnitude();
	if ( m != 0 )
	{
		for ( int i = 0; i < 3; i++ )
		{
			col[i] /= m;
		}
	}
}
void Vector3::zero()
{
	for ( int i = 0; i < 3; i++ )
	{
		col[i] = 0;
	}
}
Vector3 Vector3::operator * (float param) const
{
	Vector3 ret;
	for ( int j = 0; j < 3; j++ )
	{
		ret.col[j] = col[j] * param;
	}
	return ret;
}
void Vector3::operator /= (const float &param)
{
	for ( int i = 0; i < 3; i++ )
	{
		col[i] /= param;
	}
}
void Vector3::operator *= (const float &param)
{
	for ( int i = 0; i < 3; i++ )
	{
		col[i] *= param;
	}
}
float Vector3::magnitude() const
{
	return sqrt( col[0]*col[0] + col[1]*col[1] + col[2]*col[2] );
}
float Vector3::angle( const Vector3& param )
{
    Vector3 c = cross(param);
	
	if ( c.magnitude() == 0 )
	{
		if ( dot(param) < 0 )
		{
			return 180.0f;
		}
		else
		{
			return 0.0f;
		}
	}
	float ang;
    float ang0 = c.magnitude() / magnitude() / param.magnitude();

    if ( ang0 == 1 )
    {
         ang = 90.0f;
    }
    else if ( ang0 == -1 )
    {
         ang = 90.0f;
    }
    else
    {
		ang = abs( asin( ang0 )/ (float)PI * 180.0f );
    }
    
    if ( dot(param) < 0 )
    {
        ang = 180.0f - ang;
    }
    
    return ang;
}
#include <math.h>

Vector6::Vector6(){};
Vector6::Vector6(Vector3 upper, Vector3 lower)
{
	for ( int j = 0; j < 3; j++ )
	{
		col[j] = upper.col[j];
		col[j+3] = lower.col[j];
	}
}
float Vector6::dot(Vector6 param)
{
	return ( 
		col[0]*param.col[0] + col[1]*param.col[1] + col[2]*param.col[2] +
		col[3]*param.col[3] + col[4]*param.col[4] + col[5]*param.col[5] );
}
void Vector6::zero()
{
	for ( int i = 0; i < 6; i++ )
	{
		col[i] = 0.0f;
	}
}
Vector3 Vector6::upper()
{
	Vector3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		ret.col[i] = col[i];
	}
	return ret;
}
Vector3 Vector6::lower()
{
	Vector3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		ret.col[i] = col[i+3];
	}
	return ret;
}





Vector6 Vector6::operator * (Matrix6 param)
{
	Vector6 ret;
	for ( int j = 0; j < 6; j++ )
	{
		ret.col[j] = 0;
		for ( int i = 0; i < 6; i++ ){ ret.col[j] += col[i]*param.row[i].col[j]; }
	}
	return ret;
}

Vector6 Vector6::operator * (float param)
{
	Vector6 ret;
	for ( int j = 0; j < 6; j++ )
	{
		ret.col[j] = col[j] * param;
	}
	return ret;
}

Vector6 Vector6::operator + (Vector6 param)
{
	Vector6 ret;
	for ( int j = 0; j < 6; j++ )
	{
		ret.col[j] = col[j] + param.col[j];
	}
	return ret;
}

void Vector6::operator += (Vector6 param)
{
	for ( int j = 0; j < 6; j++ )
	{
		col[j] += param.col[j];
	}
}

void Vector6::operator -= (Vector6 param)
{
	for ( int j = 0; j < 6; j++ )
	{
		col[j] -= param.col[j];
	}
}



Quaternion::Quaternion()
{
	w = 1;
	v.zero();
};

Quaternion::Quaternion(Vector3 param)
{
	w = 0.0f;
	v = param;
}

Quaternion::Quaternion(const Vector3 &axis, float angle)
{
	float sinAngle = sin(angle*0.5f);
	Vector3 axisn(axis);
	axisn.normalize();
	v = axisn * sinAngle;
	w = cos(angle*0.5f);
}

Quaternion Quaternion::getConjugate() const
{
	Quaternion ret;
	ret.w = w;
	ret.v = v * -1.0f;
	return ret;
}

void Quaternion::getMatrix( float * mat ) const
{
	mat[0]  = 1 - 2 * ( v.col[1] * v.col[1] + v.col[2] * v.col[2] );
    mat[1]  =     2 * ( v.col[0] * v.col[1] - v.col[2] * w );
    mat[2]  =     2 * ( v.col[0] * v.col[2] + v.col[1] * w );
    mat[4]  =     2 * ( v.col[0] * v.col[1] + v.col[2] * w );
    mat[5]  = 1 - 2 * ( v.col[0] * v.col[0] + v.col[2] * v.col[2] );
    mat[6]  =     2 * ( v.col[1] * v.col[2] - v.col[0] * w );
    mat[8]  =     2 * ( v.col[0] * v.col[2] - v.col[1] * w );
    mat[9]  =     2 * ( v.col[1] * v.col[2] + v.col[0] * w );
    mat[10] = 1 - 2 * ( v.col[0] * v.col[0] + v.col[1] * v.col[1] );
    mat[3]  = 0;
	mat[7]  = 0;
	mat[11] = 0;
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
    mat[15] = 1;
}

Quaternion Quaternion::operator* (const Quaternion &q2) const
{
	Quaternion ret;

	ret.w = w*q2.w - v.dot(q2.v);

	ret.v = ( q2.v * w ) + ( v * q2.w ) + v.cross(q2.v);

	return ret;
}

Vector3 Quaternion::operator* (const Vector3 &param) const
{
	Quaternion vecQuat(param);
	//vecQuat.v.normalize();

	Quaternion resQuat;
	
	resQuat = vecQuat * getConjugate();
	resQuat = *this * resQuat;

	return resQuat.v;
}

Matrix3 Quaternion::getMatrix3() const
{
	Matrix3 ret;

	ret.row[0].col[0] = 1 - 2 * ( v.col[1] * v.col[1] + v.col[2] * v.col[2] );
    ret.row[1].col[0] =     2 * ( v.col[0] * v.col[1] - v.col[2] * w );
    ret.row[2].col[0] =     2 * ( v.col[0] * v.col[2] + v.col[1] * w );
    ret.row[0].col[1] =     2 * ( v.col[0] * v.col[1] + v.col[2] * w );
    ret.row[1].col[1] = 1 - 2 * ( v.col[0] * v.col[0] + v.col[2] * v.col[2] );
    ret.row[2].col[1] =     2 * ( v.col[1] * v.col[2] - v.col[0] * w );
    ret.row[0].col[2] =     2 * ( v.col[0] * v.col[2] - v.col[1] * w );
    ret.row[1].col[2] =     2 * ( v.col[1] * v.col[2] + v.col[0] * w );
    ret.row[2].col[2] = 1 - 2 * ( v.col[0] * v.col[0] + v.col[1] * v.col[1] );

	return ret;
}

void Quaternion::operator = (const Quaternion &param)
{
	w = param.w;
	for ( int i = 0; i < 3; i++ )
	{
		v.col[i] = param.v.col[i];
	}
}

void Quaternion::operator = (const QuaternionBase &param)
{
	w = param.w;
	for ( int i = 0; i < 3; i++ )
	{
		v.col[i] = param.v.col[i];
	}
}

float Quaternion::magnitude() const
{
	return sqrt( w*w + v.col[0]*v.col[0] + v.col[1]*v.col[1] + v.col[2]*v.col[2] );
}



void QuaternionBase::operator= (const Quaternion &param)
{
	w = param.w;
	for ( int i = 0; i < 3; i++ )
	{
		v.col[i] = param.v.col[i];
	}
}





Vector6 Matrix6::operator * (Vector6 param)
{
	Vector6 ret;
	for ( int j = 0; j < 6; j++ )
	{
		ret.col[j] = row[j].dot(param);
	}
	return ret;
}

Matrix6::Matrix6(Matrix3 ul, Matrix3 ur, Matrix3 ll, Matrix3 lr)
{
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			row[i].col[j] = ul.row[i].col[j];
			row[i].col[j+3] = ur.row[i].col[j];
			row[i+3].col[j] = ll.row[i].col[j];
			row[i+3].col[j+3] = lr.row[i].col[j];
		}
	}
}



Matrix3::Matrix3()
{
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			row[i].col[j] = 0;
		}
	}
}

void Matrix3::operator += (const Matrix3 &param )
{
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			row[i].col[j] += param.row[i].col[j];
		}
	}
}

Matrix3 Matrix3::operator * (const Matrix3 &param)
{
	Matrix3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			ret.row[i].col[j] = 0;
			for ( int k = 0; k < 3; k++ )
			{
				ret.row[i].col[j] += row[i].col[k] * param.row[k].col[j];
			}
		}
	}
	return ret;
}
Vector3 Matrix3::operator * (const Vector3 &param)
{
	Vector3 ret;
	for ( int j = 0; j < 3; j++ )
	{
		ret.col[j] = row[j].dot(param);
	}
	return ret;
}
Matrix3 Matrix3::operator * (float param)
{
	Matrix3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			ret.row[i].col[j] = row[i].col[j] * param;
		}
	}
	return ret;
}

float Matrix3::determinant()
{
	return ( 
		row[0].col[0]*( row[1].col[1] * row[2].col[2] - row[1].col[2]*row[2].col[1] ) -
		row[0].col[1]*( row[1].col[0] * row[2].col[2] - row[1].col[2]*row[2].col[0] ) +
		row[0].col[2]*( row[1].col[0] * row[2].col[1] - row[1].col[1]*row[2].col[0] ) );
}

Matrix3 Matrix3::cofactor()
{
	Matrix3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			ret.row[i].col[j] = minor_determinant( i, j ) * pow( -1.0f, i+j );
		}
	}
	return ret;
}

float Matrix3::minor_determinant( int i, int j )
{
	int row1 = (i==0) ? 1 : 0;
	int row2 = (i==2) ? 1 : 2;

	int col1 = (j==0) ? 1 : 0;
	int col2 = (j==2) ? 1 : 2;

	return ( row[row1].col[col1] * row[row2].col[col2] - row[row1].col[col2] * row[row2].col[col1] );
}

Matrix3 Matrix3::transpose()
{
	Matrix3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			ret.row[i].col[j] = row[j].col[i];
		}
	}
	return ret;
}

Matrix3 Matrix3::inverse()
{
	
	Matrix3 tra = transpose();
	Matrix3 cof = tra.cofactor();

	Matrix3 inv = cof / determinant();
	
	return inv;
}


Matrix3 Matrix3::operator / (float param)
{
	Matrix3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			ret.row[i].col[j] = row[i].col[j] / param;
		}
	}
	return ret;
}



Matrix3 Matrix3::Eye()
{
	Matrix3 ret;
	for ( int i = 0; i < 3; i++ )
	{
		ret.row[i].col[i] = 1.0f;
	}
	return ret;
}
