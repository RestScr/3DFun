#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>
#include <algorithm>
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

double Aspect = (double)SCREEN_HEIGHT / SCREEN_WIDTH;
double SymbolAspect = 16.0 / 9.0;
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

	projection.Coordinates.Z = SCREEN_HEIGHT / tan(FOV);
	projection.Coordinates.Y = -pointRelativePosition.Coordinates.Y / pointRelativePosition.Coordinates.Z * projection.Coordinates.Z;
	projection.Coordinates.X = pointRelativePosition.Coordinates.X / (pointRelativePosition.Coordinates.Z * Aspect * SymbolAspect) * projection.Coordinates.Z;

	projection += ScreenCoordinateSystemOffset;

	//std::cout << projection.ToString() << std::endl;

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
static void RenderLine(Vector3D firstPoint, Vector3D secondPoint)
{
	int x1 = firstPoint.Coordinates.X;
	int x2 = secondPoint.Coordinates.X;
	int y1 = firstPoint.Coordinates.Y;
	int y2 = secondPoint.Coordinates.Y;

	int startX = max(0, min(SCREEN_WIDTH, x1));
	int startY = max(0, min(SCREEN_HEIGHT, y1));
	int endX = max(0, min(SCREEN_WIDTH, x2));
	int endY = max(0, min(SCREEN_HEIGHT, y2));;

	int deltaX = endX - startX;
	int deltaY = endY - startY;

	int absDeltaX = abs(deltaX);
	int absDeltaY = abs(deltaY);

	int accretion = 0;

	if (absDeltaY >= absDeltaX) {
		int direction = (deltaX != 0) ? ((deltaX > 0) ? 1 : -1) : 0;
		int x = startX;
		for (int y = startY; (deltaY > 0) ? (y <= endY) : (y >= endY); (deltaY > 0) ? (y++) : (y--))
		{
			PutCharacter('@', x, y);
			accretion += absDeltaX;
			if (accretion >= absDeltaY)
			{
				x += direction;
				accretion -= absDeltaY;
			}
		}
	}
	else
	{
		int direction = (deltaY != 0) ? ((deltaY > 0) ? 1 : -1) : 0;
		int y = startY;
		for (int x = startX; (deltaX > 0) ? (x <= endX) : (x >= endX); (deltaX > 0) ? (x++) : (x--))
		{
			PutCharacter('@', x, y);
			accretion += absDeltaY;
			if (accretion >= absDeltaX)
			{
				y += direction;
				accretion -= absDeltaX;
			}
		}
	}

}

static Edge ProjectEdge(Edge edge)
{
	Vector3D point1 = ProjectPointOnScreen(edge.FirstVertex);
	Vector3D point2 = ProjectPointOnScreen(edge.SecondVertex);
	Vector3D point3 = ProjectPointOnScreen(edge.ThirdVertex);

	return Edge(point1, point2, point3);
}

bool Comparator(Edge edge1, Edge edge2)
{
	return edge1.Center().Coordinates.Z > edge2.Center().Coordinates.Z;
}

static void DrawEdgedObject(EdgedObject edgedObject)
{
	std::vector<Edge> projectedEdges(edgedObject.EdgesAmount());
	for (int i = 0; i < edgedObject.EdgesAmount(); i++)
	{
		projectedEdges[i] = ProjectEdge(edgedObject.Edges()[i]);
	}

	std::sort(projectedEdges.begin(), projectedEdges.end(), Comparator);

	for (int i = 0; i < edgedObject.EdgesAmount(); i++)
	{
		Vector3D point1 = projectedEdges[i].FirstVertex;
		Vector3D point2 = projectedEdges[i].SecondVertex;
		Vector3D point3 = projectedEdges[i].ThirdVertex;

		RenderLine(point1, point2);
		RenderLine(point2, point3);
		RenderLine(point3, point1);
	}
}

static void RotateCubeByX(Cube &cube, double angle)
{
	for (int i = 0; i < 12; i++)
	{
		cube.Edges()[i].MoveBy(cube.Center * (-1));
		cube.Edges()[i].TransformBy(MatrixVariations().GetMatrixRotateRelativelyByX(angle));
		cube.Edges()[i].MoveBy(cube.Center);
	}
}

static void RotateCubeByY(Cube& cube, double angle)
{
	for (int i = 0; i < 12; i++)
	{
		cube.Edges()[i].MoveBy(cube.Center * (-1));
		cube.Edges()[i].TransformBy(MatrixVariations().GetMatrixRotateRelativelyByY(angle));
		cube.Edges()[i].MoveBy(cube.Center);
	}
}

static void PrintScreen()
{
	std::cout << ScreenBuffer;
}

int main()
{
	ScreenBuffer[(SCREEN_WIDTH + 1) * SCREEN_HEIGHT] = '\0';

	Vector3D center(0, 0, 240);
	double side = 50;
	Cube cube(center, side);
	
	while (1)
	{
		ClearScreenBuffer();

		DrawEdgedObject(cube);
		RotateCubeByY(cube, 1);
		RotateCubeByX(cube, 1);

		PrintScreen();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	};

	return 0;
}
