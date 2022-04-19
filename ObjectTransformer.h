#pragma once

#include "Matrix.h"
#include "Object3D.h"
#include "VectorOperations.h"

class ObjectTransformer
{
public:

	static const Matrix<double> getRotateXMatrix(double);
	static const Matrix<double> getRotateYMatrix(double);
	static const Matrix<double> getRotateZMatrix(double);

	static const Matrix<double> getScaleMatrix(const sf::Vector3f&);
	static const Matrix<double> getTransferMatrix(const sf::Vector3f&);

	static Matrix<double> updateGlobalMatrix(Object3D&);

	static void rotateX(Object3D&, double);
	static void rotateY(Object3D&, double);
	static void rotateZ(Object3D&, double);

	static void scale(Object3D&, const sf::Vector3f&);
	static void transfer(Object3D&, const sf::Vector3f&);

	static void rotateXlocal(Object3D&, double);
	static void rotateYlocal(Object3D&, double);
	static void rotateZlocal(Object3D&, double);
};