#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include <vector>

#include "Matrix.h"
#include "Point.h"
#include <tuple>

typedef std::vector<sf::Vector3<int>> E_A;


/// <summary>
/// base class for 3D objects
/// </summary>
class Object3D
{
private:

	Matrix<double> _matrix;

protected:
	E_A _edges;

	sf::Vector3f _pos;
	sf::Vector3f _originPoint;
	sf::Vector3f _rotationVector;

	PointArray _pointArray;

	void createMatrix();
public:

	Object3D();
	Object3D(const sf::Vector3f& pos);

	explicit Object3D(const PointArray& pointArr);
	explicit Object3D(const Matrix<double>& matrix);

	void setPosition(const sf::Vector3f& pos);
	sf::Vector3f getPosition();

	sf::Vector3f& getRotationVector();

	PointArray& getPointArray();
	Matrix<double>& getMatrix();

	E_A& getEdges();

	void resetAllTransform();
};