#include "matrix3d.h"

Matrix3D::Matrix3D(double matrix[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_matrix[i][j] = matrix[i][j];
		}
	}
}

Matrix3D::Matrix3D() {}

double (*Matrix3D::Matrix())[3]
{
	return _matrix;
}

double* Matrix3D::operator[](int index)
{
	return _matrix[index];
}

Matrix3D Matrix3D::operator+ (Matrix3D& right)
{
	Matrix3D result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result[i][j] = _matrix[i][j] + right[i][j];
		}
	}

	return result;
}

Matrix3D Matrix3D::operator*(double k)
{
	Matrix3D result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result[i][j] = _matrix[i][j] * k;
		}
	}

	return result;
}

Matrix3D Matrix3D::operator*(Matrix3D& right)
{
	Matrix3D result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				result[i][j] += _matrix[i][k] * right[k][j];
			}
		}
	}

	return result;
}

Vector3D Matrix3D::operator*(Vector3D& right)
{
	Vector3D result;

	result.Coordinates.X = 
		_matrix[0][0] * right.Coordinates.X +
		_matrix[0][1] * right.Coordinates.Y + 
		_matrix[0][2] * right.Coordinates.Z;
	result.Coordinates.Y = 
		_matrix[0][0] * right.Coordinates.X +
		_matrix[0][1] * right.Coordinates.Y + 
		_matrix[0][2] * right.Coordinates.Z;
	result.Coordinates.Z = 
		_matrix[0][0] * right.Coordinates.X + 
		_matrix[0][1] * right.Coordinates.Y + 
		_matrix[0][2] * right.Coordinates.Z;
	
	return result;
}

void Matrix3D::operator+=(Matrix3D &right)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_matrix[i][j] += right[i][j];
		}
	}
}

void Matrix3D::operator*=(Matrix3D& right)
{
	Matrix3D result = *this * right;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_matrix[i][j] = result[i][j];
		}
	}
}

void Matrix3D::operator*=(double k)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_matrix[i][j] *= k;
		}
	}
}

std::string Matrix3D::ToString()
{
	std::string result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result += std::to_string(_matrix[i][j]) + ' ';
		}
		result += '\n';
	}

	return result;
}

double Matrix3D::Determinant()
{
	double firstComponent = 
		_matrix[0][0] * _matrix[1][1] * _matrix[2][2] + 
		_matrix[1][0] * _matrix[2][1] * _matrix[0][2] + 
		_matrix[0][1] * _matrix[1][2] * _matrix[2][0];

	double secondComponent = 
		_matrix[0][2] * _matrix[1][1] * _matrix[2][0] + 
		_matrix[0][0] * _matrix[1][2] * _matrix[2][1] + 
		_matrix[0][1] * _matrix[1][0] * _matrix[2][2];

	return firstComponent - secondComponent;
}

Matrix3D MatrixVariations::GetMatrixRotateRelativelyByX(double angle)
{
	double radians = angle / 180.0 * M_PI;
	double matrix[3][3] = {
		{1, 0, 0},
		{0, cos(radians), -sin(radians)},
		{0, sin(radians), cos(radians)}
	};

	return Matrix3D(matrix);
}

Matrix3D MatrixVariations::GetMatrixRotateRelativelyByY(double angle)
{
	double radians = angle / 180.0 * M_PI;
	double matrix[3][3] = {
		{cos(radians), 0, -sin(radians)},
		{0, 1, 0},
		{sin(radians), 0, cos(radians)}
	};

	return Matrix3D(matrix);
}

Matrix3D MatrixVariations::GetMatrixRotateRelativelyByZ(double angle)
{
	double radians = angle / 180.0 * M_PI;
	double matrix[3][3] = {
		{cos(radians), -sin(radians), 0},
		{sin(radians), cos(angle), 0},
		{0, 0, 1}
	};

	return Matrix3D(matrix);
}
