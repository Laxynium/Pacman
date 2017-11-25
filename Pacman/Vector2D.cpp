#include "Vector2D.h"

Vector2D::Vector2D(double x, double y): _x(x),
                                        _y(y)
{
}

double Vector2D::X() const
{
	return _x;
}

void Vector2D::SetX(const double x)
{
	_x = x;
}

double Vector2D::Y() const
{
	return _y;
}

void Vector2D::SetY(const double y)
{
	_y = y;
}

Vector2D Vector2D::operator+(const Vector2D& vec)
{
	return Vector2D(this->_x + vec.X(), this->_y + vec.Y());
}

Vector2D Vector2D::operator-(const Vector2D& vec)
{
	return Vector2D(this->_x - vec.X(), this->_y - vec.Y());
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	this->_x += vec.X();
	this->_y += vec.Y();
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	this->_x -= vec.X();
	this->_y -= vec.Y();
	return *this;
}

Vector2D Vector2D::operator*(double scalar)
{
	return Vector2D(this->_x*scalar, this->_y*scalar);
}

Vector2D& Vector2D::operator*=(double scalar)
{
	this->_x *= scalar;
	this->_y *= scalar;
	return *this;
}

Vector2D Vector2D::operator/(double scalar)
{
	return Vector2D(this->_x/scalar, this->_y/scalar);
}

Vector2D& Vector2D::operator/=(double scalar)
{
	this->_x /= scalar;
	this->_y /= scalar;
	return *this;
}

bool Vector2D::operator==(const Vector2D& vec)
{
	return _x == vec.X() && _y == vec.Y();
}

bool Vector2D::operator!=(const Vector2D& vec)
{
	return !(*this==vec);
}

Vector2D Vector2D::Normalized()const
{
	Vector2D newVec = *this;
	
	double len = Length();

	if (len <= 0)
		return Vector2D{};

	newVec *= 1.f / len;

	return newVec;
}
