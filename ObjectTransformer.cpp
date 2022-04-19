#include "ObjectTransformer.h"

const Matrix<double> ObjectTransformer::getRotateXMatrix(double a) {
	return Matrix<double>
	{
		{ 1, 0, 0, 0 },
		{ 0, cos(a),sin(a), 0 },
		{ 0, -sin(a), cos(a), 0 },
		{ 0, 0, 0, 1 }
	};
}

const Matrix<double> ObjectTransformer::getRotateYMatrix(double a) {
	return Matrix<double>
	{
		{cos(a), 0, -sin(a), 0},
		{ 0, 1, 0, 0 },
		{ sin(a), 0, cos(a), 0 },
		{ 0, 0, 0, 1 }
	};
}

const Matrix<double> ObjectTransformer::getRotateZMatrix(double a) {
	return Matrix<double>
	{
		{cos(a), sin(a), 0, 0},
		{ -sin(a), cos(a), 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
}

const Matrix<double> ObjectTransformer::getScaleMatrix(const sf::Vector3f& f) {
	return Matrix<double>
	{
		{f.x, 0, 0, 0},
		{ 0, f.y, 0, 0 },
		{ 0, 0, f.z, 0 },
		{ 0, 0, 0, 1 }
	};
}

const Matrix<double> ObjectTransformer::getTransferMatrix(const sf::Vector3f& f) {
	return Matrix<double>
	{
		{1, 0, 0, 0},
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ f.x, f.y, f.z, 1 }
	};
}

Matrix<double> ObjectTransformer::updateGlobalMatrix(Object3D& obj)
{
	Matrix<double> result = obj.getMatrix() * getTransferMatrix(obj.getPosition());
	result = result * getRotateXMatrix(obj.getRotationVector().x);
	result = result * getRotateYMatrix(obj.getRotationVector().y);
	result = result * getRotateZMatrix(obj.getRotationVector().z);
	//obj.getGlobalMatrix() = result;
	return result;
}

void ObjectTransformer::rotateXlocal(Object3D& obj, double angle) {
	obj.getMatrix() = obj.getMatrix() * getRotateXMatrix(angle);
}

void ObjectTransformer::rotateYlocal(Object3D& obj, double angle) {
	obj.getMatrix() = obj.getMatrix() * getRotateYMatrix(angle);
}

void ObjectTransformer::rotateZlocal(Object3D& obj, double angle) {
	obj.getMatrix() = obj.getMatrix() * getRotateZMatrix(angle);
}

void ObjectTransformer::scale(Object3D& obj, const sf::Vector3f& v) {
	obj.getMatrix() = obj.getMatrix() * getScaleMatrix(v);
}

void ObjectTransformer::transfer(Object3D& obj, const sf::Vector3f& v) {
	obj.setPosition(sumVectors(obj.getPosition(), v));
}

void ObjectTransformer::rotateX(Object3D& obj, double angle)
{
	obj.getRotationVector().x += angle;
}

void ObjectTransformer::rotateY(Object3D& obj, double angle)
{
	obj.getRotationVector().y += angle;
}
void ObjectTransformer::rotateZ(Object3D& obj, double angle)
{
	obj.getRotationVector().z += angle;
}