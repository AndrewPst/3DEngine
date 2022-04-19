#pragma once

#include <SFML/Graphics.hpp>
#include "Object3D.h"
#include <iostream>
#include "Point.h"
#include "ObjectTransformer.h"


class Cube3D : public Object3D
{
public:
	Cube3D()
	{
		_pointArray = PointArray({
			{0, 0, 0},
			{0, 1, 0},
			{1, 1, 0},
			{1, 0, 0},
			{0, 0, 1},
			{0, 1, 1},
			{1, 1, 1},
			{1, 0, 1}
			});


		_edges = E_A
		{
			{0, 1, 2},
			{0, 2, 3},
			{0, 4, 1},
			{4, 5, 1},
			{4, 5, 6},
			{6, 7, 4},
			{2, 3, 6},
			{6, 7, 3},
			{0, 4, 7},
			{7, 3, 0},
			{1, 5, 6},
			{6, 2, 1}
		};

		createMatrix();
	}
};



class Axis : public Object3D {
public:
	Axis()
	{
		_pointArray = PointArray({
			{0, 0, 0},
			{0, 0, 5},
			{0, 5, 0},
			{5, 0, 0}
			});
		_edges = E_A
		{
			{0, 1, 0},
			{0, 2, 0},
			{0, 3, 0}
		};
		createMatrix();
	}
};

class Plane : public Object3D {
public:
	Plane()
	{
		_pointArray = PointArray({
			{0, 0, 0},
			{1, 0, 0},
			{0, 0, 1}
			});
		_edges = E_A
		{
			{0, 1, 2},
		};
		createMatrix();
	}
};