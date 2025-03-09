#pragma once

#include <string>
#include <cmath>
#include "vector3d.h"
#include "constants.h"

class Matrix3D {
private:
	double _matrix[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};

public:
	Matrix3D(double[3][3]);
	Matrix3D();

	double (*Matrix())[3];

	double* operator[](int);
	Matrix3D operator+(Matrix3D&);
	Matrix3D operator*(double);
	Matrix3D operator*(Matrix3D&);
	Vector3D operator*(Vector3D&);
	void operator+=(Matrix3D&);
	void operator*=(Matrix3D&);
	void operator*=(double);

	std::string ToString();

	double Determinant();
};

/// <summary>
/// Статический класс, который генерирует специальные матрицы
/// преобразования
/// </summary>
static class MatrixVariations
{
public:
	static Matrix3D GetMatrixRotateRelativelyByX(double);
	static Matrix3D GetMatrixRotateRelativelyByY(double);
	static Matrix3D GetMatrixRotateRelativelyByZ(double);
};
