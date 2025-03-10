#include <iostream>
#include <windows.h>
#include "matrix3d.h"
#include "vector3d.h"
#include "constants.h"
#include "edge.h"
#include "edged_object.h"
#include "cube.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

char ScreenBuffer[(SCREEN_WIDTH + 1) * SCREEN_HEIGHT + 1];

#define SCREEN_INGAME_WIDTH 1.0
#define SCREEN_INGAME_HEIGHT 1.0

double FOV = 60;
Vector3D CameraPosition(0, 0, 0);
Vector3D ScreenCoordinateSystemOffset(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
Vector3D CameraNormal(0, 0, 1);

/// <summary>
/// Спроецировать точку на экран
/// </summary>
/// <returns> 3Д вектор, определяющий позицию точки на экране </returns>
static Vector3D ProjectPointOnScreen(Vector3D& point)
{
	Vector3D pointRelativePosition = point - CameraPosition;
	Vector3D projection;

	projection.Coordinates.Y = 
		pointRelativePosition.Coordinates.Y * SCREEN_INGAME_HEIGHT / 
		(pointRelativePosition.Coordinates.Z * tan(FOV));
	projection.Coordinates.X = 
		pointRelativePosition.Coordinates.X * SCREEN_INGAME_WIDTH /
		(pointRelativePosition.Coordinates.Z * tan(FOV));
	projection.Coordinates.Z = SCREEN_INGAME_HEIGHT / tan(FOV);

	projection.Coordinates.Y *= (-1);
	projection += ScreenCoordinateSystemOffset;

	return projection;
}

static void ClearScreenBuffer()
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

static void PutCharacter(char character, int x, int y)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}
	ScreenBuffer[y * (SCREEN_WIDTH + 1) + x] = character;
}

/// <summary>
/// Нарисовать линию на экране
/// </summary>
static void RenderLine(Vector3D& firstPoint, Vector3D& secondPoint)
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

	while (x != endX || y != endY)
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

		PutCharacter('+', x, y);
	}
}

static void PrintScreenBuffer()
{
	std::cout << ScreenBuffer;
}

static void ProjectEdgeToScreenBuffer(Edge edge)
{
	Vector3D point1 = ProjectPointOnScreen(edge.FirstVertex);
	Vector3D point2 = ProjectPointOnScreen(edge.SecondVertex);
	Vector3D point3 = ProjectPointOnScreen(edge.ThirdVertex);

	RenderLine(point1, point2);
	RenderLine(point2, point3);
	RenderLine(point3, point1);
}

static void DrawEdgedObject(EdgedObject edgedObject)
{
	for (int i = 0; i < edgedObject.EdgesAmount(); i++)
	{
		//std::cout << edgedObject.Edges()[i].ToString() << std::endl;
		ProjectEdgeToScreenBuffer(edgedObject.Edges()[i]);
	}
}

static void RotateCube(Cube &cube, double angle)
{
	for (int i = 0; i < 12; i++)
	{
		cube.Edges()[i].MoveBy(cube.Center * (-1));
		cube.Edges()[i].TransformBy(MatrixVariations().GetMatrixRotateRelativelyByY(angle));
		cube.Edges()[i].MoveBy(cube.Center);
	}
}

int main()
{
	ScreenBuffer[(SCREEN_WIDTH + 1) * SCREEN_HEIGHT] = '\0';

	Vector3D center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2);
	double side = 10;
	Cube cube(center, side);
	int angle = 0;

	double dx = 0.01;
	
	while (1)
	{
		ClearScreenBuffer();

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			angle = (angle + 1) % 360;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			angle--;
			if (angle < 0)
			{
				angle = 360;
			}
		}
		//RotateCube(cube, angle);

		if (cube.Center.Coordinates.X < 10)
		{
			dx = 0.01;
		}
		else if (cube.Center.Coordinates.X > 90)
		{
			dx = -0.01;
		}

		cube.MoveBy(Vector3D(dx, 0, 0));

		DrawEdgedObject(cube);

		PrintScreenBuffer();
	};

	return 0;
}
