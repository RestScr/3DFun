#include "vector3d.h"


Vector3D::Vector3D(double x, double y, double z)
{
	Coordinates = Position3D(x, y, z);
}

Vector3D::Vector3D() {}

Vector3D::Vector3D(Position3D point)
{
	Coordinates = point;
}

Vector3D Vector3D::operator+(Vector3D& right)
{
	Vector3D result;

	result.Coordinates.X = Coordinates.X + right.Coordinates.X;
	result.Coordinates.Y = Coordinates.Y + right.Coordinates.Y;
	result.Coordinates.Z = Coordinates.Z + right.Coordinates.Z;

	return result;
}

Vector3D Vector3D::operator-(Vector3D& right)
{
	Vector3D result;

	result.Coordinates.X = Coordinates.X - right.Coordinates.X;
	result.Coordinates.Y = Coordinates.Y - right.Coordinates.Y;
	result.Coordinates.Z = Coordinates.Z - right.Coordinates.Z;

	return result;
}

Vector3D Vector3D::operator*(double k)
{
	Vector3D result;

	result.Coordinates.X = Coordinates.X * k;
	result.Coordinates.Y = Coordinates.Y * k;
	result.Coordinates.Z = Coordinates.Z * k;

	return result;
}

void Vector3D::operator+=(Vector3D &right)
{
	Coordinates.X += right.Coordinates.X;
	Coordinates.Y += right.Coordinates.Y;
	Coordinates.Z += right.Coordinates.Z;
}

void Vector3D::operator-=(Vector3D& right)
{
	Coordinates.X -= right.Coordinates.X;
	Coordinates.Y -= right.Coordinates.Y;
	Coordinates.Z -= right.Coordinates.Z;
}

void Vector3D::operator*=(double k)
{
	Coordinates.X *= k;
	Coordinates.Y *= k;
	Coordinates.Z *= k;
}

double Vector3D::operator*(Vector3D &right)
{
	return Coordinates.X * right.Coordinates.X + Coordinates.Y * right.Coordinates.Y + Coordinates.Z * right.Coordinates.Z;
}

Vector3D Vector3D::VectorMultiply(Vector3D& right)
{
	Vector3D result;

	result.Coordinates.X = Coordinates.Y * right.Coordinates.Z - Coordinates.Z * right.Coordinates.Y;
	result.Coordinates.Y = -(Coordinates.X * right.Coordinates.Z - Coordinates.Z * right.Coordinates.X);
	result.Coordinates.Z = Coordinates.X * right.Coordinates.Y - Coordinates.Y * right.Coordinates.X;

	return result;
}

std::string Vector3D::ToString()
{
	std::string result;

	result += std::to_string(Coordinates.X) + ' ';
	result += std::to_string(Coordinates.Y) + ' ';
	result += std::to_string(Coordinates.Z);

	return result;
}

double Vector3D::Absolute()
{
	return sqrt(pow(Coordinates.X, 2) + pow(Coordinates.Y, 2) + pow(Coordinates.Z, 2));
}

double Vector3D::ProjectionOn(Vector3D& right)
{
	return (*this * right) / right.Absolute();
}
