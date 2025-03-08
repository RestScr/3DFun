#include <iostream>
#include <Windows.h>
#include "matrix3d.h"
#include "vector3d.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

wchar_t ScreenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT + 1];

Vector3D CameraPosition(0, 0, 0);
Vector3D CameraNormal(0, 0, 1);

/// <summary>
/// Спроецировать точку на экран
/// </summary>
/// <returns> 3Д вектор, определяющий позицию точки на экране </returns>
Vector3D ProjectPointOnScreen(Vector3D& point)
{
	Vector3D pointRelativePosition = point - CameraPosition;
	Vector3D ProjectedNormal = CameraNormal * pointRelativePosition.ProjectionOn(CameraNormal);
	Vector3D projection = pointRelativePosition - ProjectedNormal;

	return projection;
}

int main()
{
	ScreenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT] = '\0';

	return 0;
}
