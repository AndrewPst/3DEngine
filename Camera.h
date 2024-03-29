#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "Object3D.h"
#include "ObjectTransformer.h"
#include "Point.h"

#include "settings.h"

#include "VectorOperations.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <tuple>

enum CameraVector : char
{
	V_FORWARD = 0,
	V_UP = 1,
	V_RIGHT = 2
};

class Camera
{
private:
	PointArray vectors
	{
		{0, 0, 1},
		{0, 1, 0},
		{1, 0, 0}
	};

	sf::Vector3f _position;
	sf::Vector3f _rotationVector;


	const double H_FOV = M_PI / 3.f;
	const double V_FOV = H_FOV * ((double)HEIGHT / (double)WIDTH);

	const double NEAR_PLANE = 0.1;
	const double FAR_PLANE = 100;

	Matrix<double> _projectionMatrix;
	Matrix<double> _displayMatrix;

	Matrix<double> getTranslateMatrix()
	{
		return Matrix<double>
		{
			{1, 0, 0, 0},
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ -_position.x, -_position.y, -_position.z, 1 }
		};
	}

	Matrix<double> getRotateMatrix()
	{
		return Matrix<double>{
			{vectors[V_RIGHT].x, vectors[V_UP].x, vectors[V_FORWARD].x, 0},
			{ vectors[V_RIGHT].y, vectors[V_UP].y, vectors[V_FORWARD].y, 0 },
			{ vectors[V_RIGHT].z, vectors[V_UP].z, vectors[V_FORWARD].z, 0 },
			{ 0, 0, 0, 1 }
		};
	}

	Matrix<double> getCameraMatrix() {
		return getTranslateMatrix() * getRotateMatrix();
	}

	std::pair<sf::Vector3f, sf::Vector3f>  calculateLine(const sf::Vector3f& pos1, const sf::Vector3f& pos2) {
		sf::Vector3f pMin, pMax;
		if (pos1.z <= 0 && pos2.z <= 0)
			return std::make_pair(pos1, pos2);

		//getting the nearest point
		bool isSwap = false;
		if (pos1.z < pos2.z) 
		{
			pMin = pos1;
			pMax = pos2;
		}
		else 
		{
			isSwap = true;
			pMin = pos2;
			pMax = pos1;
		}

		if (pMin.z < 0) 
		{
			//correction the line
			pMin.x = (pMax.x + (pMax.x - pMin.x));
			pMin.y = (pMax.y + (pMax.y - pMin.y));

			//extending the vector to the screen border
			if (pMin.y > 0 && pMin.y < HEIGHT && pMin.x > 0 && pMin.x < WIDTH)
			{
				if (pMin.y == pMax.y)
				{
					pMin.x = pMin.x < pMax.x ? 0 : WIDTH;
				}
				else
				{
					double h2 = 0;
					if (pMin.y > pMax.y)
						h2 = (HEIGHT - pMax.y);
					else
						h2 = -pMax.y;
					sf::Vector3f subtractionV = subtractionVectors(pMin, pMax);
					double size = (h2 * sqrt(subtractionV.x * subtractionV.x + subtractionV.y * subtractionV.y)) / subtractionV.y;
					double koef = size / sqrt(subtractionV.x * subtractionV.x + subtractionV.y * subtractionV.y);
					subtractionV.x *= koef;
					subtractionV.y *= koef;
					pMin = sumVectors(subtractionV, pMax);
				}
			}
		}
		if (isSwap)
			return std::make_pair(pMax, pMin);
		return std::make_pair(pMin, pMax);
	}


	void drawPolygon(sf::Vector3f* vectors, sf::RenderWindow& window)
	{
		std::pair<sf::Vector3f, sf::Vector3f> arr[3];
		//Calculating polygon lines
		arr[0] = calculateLine(vectors[0], vectors[1]);
		arr[1] = calculateLine(vectors[1], vectors[2]);
		arr[2] = calculateLine(vectors[2], vectors[0]);

		sf::Vector3f polygon[4]{
			arr[0].first,
			arr[1].first,
			arr[2].first,
			arr[2].second
		};

		sf::Color ca[4]{
			sf::Color::Red,
			sf::Color::Green,
			sf::Color::Blue,
			sf::Color::Yellow,
		};

#pragma region LineDrawing

		//Drawing all lines as polygon
		for (int i = 0; i < 3; i++) {

			if (polygon[i].z < 0 && polygon[i + 1].z < 0)
				continue;
			sf::Vertex va[2]
			{
				sf::Vertex({polygon[i].x, polygon[i].y} , ca[i]),
				sf::Vertex({polygon[i + 1].x, polygon[i + 1].y}, ca[i + 1]),
			};
			window.draw(va, 2, sf::PrimitiveType::Lines);
		}
#pragma endregion
	}

public:
	Camera() {

		double right = tan(H_FOV / 2.f);
		double left = -right;
		double top = tan(V_FOV / 2.f);
		double bottom = -top;

		double m00, m11, m22, m32;
		m00 = 2.f / (right - left);
		m11 = 2.f / (top - bottom);
		m22 = (FAR_PLANE + NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
		m32 = (NEAR_PLANE * FAR_PLANE) / (FAR_PLANE - NEAR_PLANE);

		_projectionMatrix = Matrix<double>{
			{m00, 0, 0 ,0},
			{0, m11, 0, 0},
			{0, 0, m22, 1},
			{0, 0, m32, 0}
		}; //Calculation the projection matrix
	}

	void setPosition(const sf::Vector3f& p)
	{
		_position = p;
	}

	sf::Vector3f& getPosition()
	{
		return _position;
	}

	void moveX(double speed)
	{
		_position = sumVectors(_position, multiplicationVectors(vectors[V_FORWARD], sf::Vector3f(speed, speed, speed)));
	}

	void moveY(double speed) {
		_position = sumVectors(_position, multiplicationVectors(vectors[V_RIGHT], sf::Vector3f(speed, speed, speed)));
	}

	void moveZ(double speed) {
		_position = sumVectors(_position, multiplicationVectors(vectors[V_UP], sf::Vector3f(speed, speed, speed)));
	}

	void rotateY(double angle) {
		auto rm = ObjectTransformer::getRotateYMatrix(angle);
		auto vm = vectors.getMatrix();
		vm = vm * rm;
		vectors = PointArray(vm);
		_rotationVector.y += angle;
	}

	void rotateZ(double angle)
	{
		auto rm = ObjectTransformer::getRotateXMatrix(angle * sin(_rotationVector.y));
		auto rm1 = ObjectTransformer::getRotateZMatrix(angle * cos(-_rotationVector.y));
		auto vm = vectors.getMatrix();
		vm = vm * rm * rm1;
		vectors = PointArray(vm);
		_rotationVector.z += angle;

	}

	void rotateX(double angle) {
		auto rm = ObjectTransformer::getRotateXMatrix(angle * cos(_rotationVector.y));
		auto rm1 = ObjectTransformer::getRotateZMatrix(angle * sin(-_rotationVector.y));
		auto vm = vectors.getMatrix();
		vm = vm * rm * rm1;
		vectors = PointArray(vm);
		_rotationVector.x += angle;

	}

	void drawObject(Object3D& object, sf::RenderWindow& window)
	{
		auto vertexes = ObjectTransformer::updateGlobalMatrix(object) * getCameraMatrix(); //��������� ���������� � ���������� � ����������� � ������������ ������
		vertexes = vertexes * _projectionMatrix; //��������� �� ����� �� -1 �� 1
		for (size_t i = 0; i < vertexes.getRowsCount(); i++) { //����� ������ ������� �� W (�����������?)
			auto t = vertexes[i];
			t[0] /= t[3];
			t[1] /= t[3];
			t[2] /= t[3];
			if (t[3] < 0)
				t[2] = -abs(t[2]); //��������� ������������� ��������
			t[3] /= t[3];
		}
		vertexes = vertexes * Matrix<double>{
			{WIDTH / 2.f, 0, 0, 0},
			{ 0, -HEIGHT / 2.f, 0, 0 },
			{ 0, 0, 1, 0 },
			{ WIDTH / 2, HEIGHT / 2, 0, 1 }
		}; //����������� ���������� �� �����

		auto& edges = object.getEdges(); //����� ��� �����

		for (auto& e : edges)
		{
			sf::Vector3f va[3]{
				{(float)vertexes[e.x][0], (float)vertexes[e.x][1],(float)vertexes[e.x][2]},
				{(float)vertexes[e.y][0], (float)vertexes[e.y][1],(float)vertexes[e.y][2]},
				{(float)vertexes[e.z][0], (float)vertexes[e.z][1],(float)vertexes[e.z][2]}
			};

			//BubbleSort hardcode
			if (va[2].z < va[1].z) std::swap(va[2], va[1]);
			if (va[1].z < va[0].z) std::swap(va[1], va[0]);
			if (va[2].z < va[1].z) std::swap(va[2], va[1]);

			drawPolygon(va, window);
		}
	}
};