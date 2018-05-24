#include "MyVector3D.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// @author John Foley
/// @date Dec 2016
///  3D Vector Class
/// </summary>

/// <summary>
/// default constructor
/// results in a zero vector
/// </summary>
MyVector3D::MyVector3D() :
	m_x(0.0),
	m_y(0.0),
	m_z(0.0)
{
}

/// <summary>
/// Constructor taking three doubles
/// </summary>
/// <param name="x">X component</param>
/// <param name="y">Y component</param>
/// <param name="z">Z component</param>
MyVector3D::MyVector3D(double x, double y, double z) :
	m_x(x),
	m_y(y),
	m_z(z)
{
}

/// <summary>
/// constructor taking an SFML vector3f
/// float
/// </summary>
/// <param name="sfVector">existing vector</param>
MyVector3D::MyVector3D(sf::Vector3f sfVector)
{
	m_x = static_cast<double>(sfVector.x);
	m_y = static_cast<double>(sfVector.y);
	m_z = static_cast<double>(sfVector.z);
}

/// <summary>
/// constructor taking an SFML vector3i
/// integer
/// </summary>
/// <param name="sfVector">existing vector</param>
MyVector3D::MyVector3D(sf::Vector3i sfVector)
{
	m_x = static_cast<double>(sfVector.x);
	m_y = static_cast<double>(sfVector.y);
	m_z = static_cast<double>(sfVector.z);
}

/// <summary>
/// Constructor taking an SFML vector2i
/// integer
/// </summary>
/// <param name="sfVector">existing vector</param>
MyVector3D::MyVector3D(sf::Vector2i sfVector)
{
	m_x = static_cast<double>(sfVector.x);
	m_y = static_cast<double>(sfVector.y);
	m_z = 0;
}

/// <summary>
/// constructor taking an SFML vector2u
/// unsigned int
/// </summary>
/// <param name="sfVector">existing vector</param>
MyVector3D::MyVector3D(sf::Vector2u sfVector)
{
	m_x = static_cast<double>(sfVector.x);
	m_y = static_cast<double>(sfVector.y);
	m_z = 0;
}

/// <summary>
/// constructor taking an SFML vector2f
/// float
/// </summary>
/// <param name="sfVector">existing vector</param>
MyVector3D::MyVector3D(sf::Vector2f sfVector)
{
	m_x = static_cast<double>(sfVector.x);
	m_y = static_cast<double>(sfVector.y);
	m_z = 0;
}

/// <summary>
/// default destuctor
/// only have native data types used
/// automatically retuned to
/// system so there's nothing to do
/// </summary>
MyVector3D::~MyVector3D()
{
}

/// <summary>
/// create a string for the vector of form [x,y,z]
/// using std::to_string
/// </summary>
/// <returns>the value of the vector in square brackets</returns>
std::string MyVector3D::toString()
{
	char tmpbuf[256];
	sprintf_s(tmpbuf, "[ %g, %g, %g ]", m_x, m_y, m_z);
	return tmpbuf;
}

/// <summary>
/// find the x co-ord of a vector
/// </summary>
/// <returns>x value of existing vector</returns>
double MyVector3D::X() const
{
	return m_x;
}

/// <summary>
/// find the y co-ord of a vector
/// </summary>
/// <returns>y value of existing vector</returns>
double MyVector3D::Y() const
{
	return m_y;
}

/// <summary>
/// find the z co-ord of a vector
/// </summary>
/// <returns>z value of existing vector</returns>
double MyVector3D::Z() const
{
	return m_z;
}

/// <summary>
/// defines an operation to add two vectors
/// </summary>
/// <param name="right"></param>
/// <returns>new vector</returns>
MyVector3D MyVector3D::operator +(const MyVector3D right) const
{
	return MyVector3D(m_x + right.m_x, m_y + right.m_y, m_z + right.m_z);
}

/// <summary>
/// defines an operation to subtract two vectors
/// </summary>
/// <param name="right"></param>
/// <returns>new vector</returns>
MyVector3D MyVector3D::operator-(const MyVector3D right) const
{
	return MyVector3D(m_x - right.m_x, m_y - right.m_y, m_z - right.m_z);
}

/// <summary>
/// defines an operation to multiply a vector by a scalar
/// </summary>
/// <param name="scalar">a number which is multiplied by each member of a vector</param>
/// <returns>a vector of same direction but greater or lesser magnitude</returns>
MyVector3D MyVector3D::operator*(const double scalar) const
{
	return MyVector3D(m_x * scalar, m_y * scalar, m_z * scalar);
}

/// <summary>
/// defines an operation to divide a vectior by a divisor
/// </summary>
/// <param name="divisor">a number which each member of the vector is divided by</param>
/// <returns>a vector of same direction but lesser or greater magnitude magnitude</returns>
MyVector3D MyVector3D::operator/(const double divisor) const
{
	if (divisor != 0)
	{
		return MyVector3D(m_x / divisor, m_y / divisor, m_z / divisor);
	}
	return MyVector3D();
}

/// <summary>
/// overload for plusequals operator
/// this not a const operation becuase the vector changes
/// </summary>
/// <param name="right">vector to add</param>
/// <returns>vector sum</returns>
MyVector3D MyVector3D::operator+=(const MyVector3D right)
{
	m_x += right.m_x;
	m_y += right.m_y;
	m_z += right.m_z;
	return MyVector3D(m_x, m_y, m_z);
}

/// <summary>
/// overload for plusequals operator
/// this not a const operation becuase the vector changes
/// </summary>
/// <param name="right">vector to subtract</param>
/// <returns>vector difference</returns>
MyVector3D MyVector3D::operator-=(const MyVector3D right)
{
	m_x -= right.m_x;
	m_y -= right.m_y;
	m_z -= right.m_z;
	return MyVector3D(m_x, m_y, m_z);
}


/// <summary>
/// equality operator overloaded
/// is x&y&z are equal then is equal
/// </summary>
/// <param name="right">2nd vector</param>
/// <returns>true if vectors are the same</returns>
bool MyVector3D::operator==(const MyVector3D right)
{
	return (m_x == right.m_x && m_y == right.m_y && m_z == right.m_z);
}

/// <summary>
/// overloaded inequality is the opposite of equality
/// </summary>
/// <param name="right">2nd vector</param>
/// <returns>true if not the same vectors</returns>
bool MyVector3D::operator!=(const MyVector3D right)
{
	return !this->operator==(right);
}

/// <summary>
/// operator overload for uniary negative
/// </summary>
/// <returns>the negative of the vector</returns>
MyVector3D MyVector3D::operator-()
{
	return MyVector3D(-m_x, -m_y, -m_z);
}

/// <summary>
/// negate the x component for use when hitting the left & right cushions
/// </summary>
void MyVector3D::reverseX()
{
	m_x = -m_x;
}

/// <summary>
/// negate the y component for use when hitting the top and bottom cushions
/// </summary>
void MyVector3D::reverseY()
{
	m_y = -m_y;
}



/// <summary>
/// get the lenght of vector using square root of the sum of the components squared
/// </summary>
/// <returns>lenght</returns>
double MyVector3D::length() const
{
	const double length = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); //square root the sum of the square of all of the components of the vector
	return length;
}

/// <summary>
/// get the length squared of vector using the sum of the components squared
/// </summary>
/// <returns>length squared</returns>
double MyVector3D::lengthSquared() const
{
	const double result = (m_x * m_x) + (m_y * m_y) + (m_z * m_z); //sum the square of all the components of the vector
	return result;
}

/// <summary>
/// get the dot product of two vetors
/// </summary>
/// <param name="other">other vector</param>
/// <returns>dot product</returns>
double MyVector3D::dot(const MyVector3D other) const
{
	return (m_x*other.m_x + m_y*other.m_y + m_z*other.m_z);
}

/// <summary>
/// get teh cross product of two vectors
/// </summary>
/// <param name="other">other vector</param>
/// <returns>cross product</returns>
MyVector3D MyVector3D::crossProduct(const MyVector3D other) const
{
	return MyVector3D((m_y*other.m_z - m_z*other.m_y), (m_z*other.m_x - m_x*other.m_z), (m_x*other.m_y - m_y*other.m_x));
}

/// <summary>
/// get the anglebetween two vectors
/// </summary>
/// <param name="other">other vector</param>
/// <returns>angle</returns>
double MyVector3D::angleBetween(const MyVector3D other) const
{
	const double cosine = unit().dot(other.unit());
	const double angleInRadians = std::acos(cosine);
	const double angleInDegrees = angleInRadians * 180 / 3.14159265359;
	return angleInDegrees;;
}

/// <summary>
/// get a unit vector
/// </summary>
/// <returns>unit vector</returns>
MyVector3D MyVector3D::unit() const
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double vectorLength = length();
	if (vectorLength != 0) // never divide zero unless the zombies have overun the compound
	{
		x = m_x / vectorLength;
		y = m_y / vectorLength;
		z = m_z / vectorLength;
	}
	return MyVector3D(x, y, z);
}

/// <summary>
/// normalise a vector
/// </summary>
void MyVector3D::normalise()
{
	double vectorLength = this->length();//need to stroe the length as it chamges after components are changed

	if (vectorLength != 0)
	{
		m_x /= vectorLength;
		m_y /= vectorLength;
		m_z /= vectorLength;
	}
}

/// <summary>
/// projection of one vector onto another using the projection formula
/// </summary>
/// <param name="other">other vector</param>
/// <returns>projection</returns>
MyVector3D MyVector3D::projection(const MyVector3D other) const
{
	MyVector3D vectorV(m_x, m_y, m_z);
	return MyVector3D((vectorV / (vectorV.length()))*((other.dot(vectorV)) / (vectorV.length())));
}


/// <summary>
/// get the rejection of the vectors byt taking the projection of a vector onto another and taking it away from the first vector(rejection = b-a.proj(b))
/// </summary>
/// <param name="other">other vector</param>
/// <returns>rejection</returns>
MyVector3D MyVector3D::rejection(const MyVector3D other) const
{
	MyVector3D vectorR(m_x, m_y, m_z);

	return (other - vectorR.projection(other));
}
