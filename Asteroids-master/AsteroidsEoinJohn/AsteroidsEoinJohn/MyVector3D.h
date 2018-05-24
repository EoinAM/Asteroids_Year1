#ifndef MYVECTOR3D
#define MYVECTOR3D

/// <summary>
/// @author John Foley
/// @date Dec 2016
/// 3D Vector Class
/// </summary>

#include <iostream>
#include <SFML/Graphics.hpp>

class MyVector3D
{
public:
	MyVector3D(); // default constructor
	MyVector3D(double x, double y, double z); // constructor taking three double
	MyVector3D(sf::Vector3f sfVector); // cast sf vector3f into a MyVector3D vector
	MyVector3D(sf::Vector3i sfVector); // cast sf vector3i into a MyVector3D vector
	MyVector3D(sf::Vector2i sfVector); // cast sf vector2i into a MyVector3D vector
	MyVector3D(sf::Vector2u sfVector); // cast sf vector2u into a MyVector3D vector
	MyVector3D(sf::Vector2f sfVector); // cast sf vector2f into a MyVector3D vector
	~MyVector3D(); // default destructor
	std::string toString(); // converts vectors into strings
	double X() const; // just return the value of m_x
	double Y() const; // just return the value of m_y
	double Z() const; // just return the value of m_z

	MyVector3D operator +(const MyVector3D right) const; // overloads the addition operator to add MyVector3D vectors
	MyVector3D operator -(const MyVector3D right) const; // overloads the subtraction operator to subtract MyVector3D vectors
	MyVector3D operator *(const double scalar) const; // overloads the multiplication operator to multiply MyVector3D vectors by a given scalar
	MyVector3D operator /(const double divisor) const; // overloads the division operator to divide MyVector3D vectors by a given divisor
	MyVector3D operator +=(const MyVector3D right); // overloads the plusequals operator to add one MyVector3D vector to another, and assign the result to the first vector
	MyVector3D operator -=(const MyVector3D right); // overloads the minusequals operator to subtract one MyVector3D vector from another and assign the value to the first vector

	bool operator ==(const MyVector3D right); // overloads the equalsequals operator so it checks the equivalency of MyVector3D vectors
	bool operator !=(const MyVector3D right); // overloads the notequals operator so it checks the not equivalency of MyVector3D vectors

	MyVector3D operator -();   // negative of a vector 
							   //new methods for bouncing off sides of table in billiards
	void reverseX();
	void reverseY();

	double length()const; // calculate the length of a MyVector3D and return it
	double lengthSquared()const; // calculate the length squared of a MyVector3D and return it
	double dot(const MyVector3D other)const; // calculate the dot product of MyVector3D vectors and return
	MyVector3D crossProduct(const MyVector3D other)const; // calculates the cross product of two vectors and returns it
	double angleBetween(const MyVector3D other)const; // calculates the anglebetween two MyVector3D vectors and returns
	MyVector3D unit() const; // calculates a unit vector of a MyVector3D and returns it
	void normalise(); // normalises a MyVector3D
	MyVector3D projection(const MyVector3D other)const;
	//projection of the other vector on the current vector so answer will be parallel to the current vector
	MyVector3D rejection(const MyVector3D other)const; // the other vector minus the projectionof the other vector on the current vector

	operator sf::Vector2i() { return sf::Vector2i(static_cast<int>(m_x), static_cast<int>(m_y)); }; //overloads the sf::Vector2i operator
	operator sf::Vector2f() { return sf::Vector2f(static_cast<float>(m_x), static_cast<float>(m_y)); }; //overloads the sf::Vector2f operator
	operator sf::Vector2u() { return sf::Vector2u(static_cast<unsigned int>(m_x), static_cast<unsigned int>(m_y)); }; //overloads the sf::Vector2u operator
	operator sf::Vector3i() { return sf::Vector3i(static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_z)); }; //overloads the sf::Vector3i operator
	operator sf::Vector3f() { return sf::Vector3f(static_cast<float>(m_x), static_cast<float>(m_y), static_cast<float>(m_z)); }; //overloads the sf::Vector3f operator

	double m_x;
	double m_y;
	double m_z;
};

#endif // !MYVECTOR3D
