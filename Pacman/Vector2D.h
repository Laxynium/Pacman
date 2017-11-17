#pragma once
#include <cmath>

class Vector2D
{
	double _x=0, _y=0;
public:
	Vector2D(){}
	Vector2D(double x, double y);

	double X() const;

	void SetX(const double x);

	double Y() const;

	void SetY(const double y);

	double Length() const
	{
		return sqrt((_x*_x) + (_y*_y));
	}
	Vector2D operator + (const Vector2D&vec);

	Vector2D operator-(const Vector2D& vec);

	Vector2D& operator+=(const Vector2D& vec);

	Vector2D& operator-=(const Vector2D& vec);

	Vector2D operator *(double scalar);

	Vector2D& operator *=(double scalar);


	Vector2D operator /(double scalar);

	Vector2D& operator /=(double scalar);

	bool operator ==(const Vector2D& vec);

	Vector2D Normalized()const;

};
