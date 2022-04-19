#include "Object3D.h"

Object3D::Object3D()
{

}

Object3D::Object3D(const sf::Vector3f& pos) : _pos(pos) {

}

Object3D::Object3D(const PointArray& pointArr) : _pointArray(pointArr) {
	createMatrix();
}

Object3D::Object3D(const Matrix<double>& matrix) : _matrix(matrix)
{
	
}

void Object3D::createMatrix() {
	_matrix = _pointArray.getMatrix();
}

void Object3D::setPosition(const sf::Vector3f& pos) {
	_pos = pos;
}

sf::Vector3f Object3D::getPosition() {
	return _pos;
}

Matrix<double>& Object3D::getMatrix() {
	return _matrix;
}

PointArray& Object3D::getPointArray() {
	return _pointArray;
}

void Object3D::resetAllTransform()
{
	_pos = sf::Vector3f(0, 0, 0);
	_matrix = _pointArray.getMatrix();
}

sf::Vector3f& Object3D::getRotationVector() {
	return _rotationVector;
}

E_A& Object3D::getEdges() {
	return _edges;
}