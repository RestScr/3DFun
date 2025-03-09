#include <iostream>
#include <windows.h>
#include "matrix3d.h"
#include "vector3d.h"
#include "constants.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

char ScreenBuffer[(SCREEN_WIDTH + 1) * SCREEN_HEIGHT + 1];

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

void ClearScreenBuffer()
{
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			ScreenBuffer[y * (SCREEN_WIDTH + 1) + x] = ' ';
		}

		ScreenBuffer[(y + 1) * (SCREEN_WIDTH + 1) - 1] = '\n';
	}
}

void PutCharacter(char character, int x, int y)
{
	ScreenBuffer[y * (SCREEN_WIDTH + 1) + x] = character;
}

/// <summary>
/// Нарисовать линию на экране
/// </summary>
void RenderLine(Vector3D& firstPoint, Vector3D& secondPoint)
{
	int x1 = firstPoint.Coordinates.X;
	int x2 = secondPoint.Coordinates.X;
	int y1 = firstPoint.Coordinates.Y;
	int y2 = secondPoint.Coordinates.Y;

	int dx = 1;
	int dy = 1;

	int deltaX = x2 - x1;
	int deltaY = y2 - y1;

	if (deltaX < 0)
	{
		dx = -1;
	}
	else if (deltaX == 0)
	{
		dx = 0;
	}

	if (deltaY < 0)
	{
		dy = -1;
	}
	else if (deltaY == 0)
	{
		dy = 0;
	}

	deltaX = abs(deltaX);
	deltaY = abs(deltaY);

	int x = max(0, min(SCREEN_WIDTH, x1));
	int y = max(0, min(SCREEN_HEIGHT, y1));

	int endX = max(0, min(SCREEN_WIDTH, x2));
	int endY = max(0, min(SCREEN_HEIGHT, y2));

	int d = 0;

	while (x != endX && y != endY)
	{
		if (d >= deltaX)
		{
			y += dy;
			d -= deltaX;
		}
		else
		{
			x += dx;
			d += deltaY;
		}

		PutCharacter('@', x, y);
	}
}

void PrintScreenBuffer()
{
	std::cout << ScreenBuffer;
}

int main()
{
	ScreenBuffer[(SCREEN_WIDTH + 1) * SCREEN_HEIGHT] = '\0';

	Vector3D point1 = Vector3D(20, -20, 0);
	Vector3D point2 = Vector3D(1, 5, 0);

	while (1)
	{
		ClearScreenBuffer();
		RenderLine(point1, point2);
		PrintScreenBuffer();
	};

	return 0;
}
