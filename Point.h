#pragma once

#include <valarray>
#include <initializer_list>
#include <SFML/System/Vector3.hpp>
#include "Matrix.h"

struct PointArray {
private:
	std::valarray<sf::Vector3f> _array;
public:

	PointArray() {}

	PointArray(std::initializer_list<sf::Vector3f> list) : _array(list) {
	};

	PointArray(Matrix<double>& m) {
		_array = std::valarray<sf::Vector3f>(m.getRowsCount());
		for (size_t i = 0; i < m.getRowsCount(); i++)
		{
			auto t = m[i];
			_array[i] = sf::Vector3f(t[0], t[1], t[2]);
		}
	}

	std::valarray<sf::Vector3f>& getArray() {
		return _array;
	}

	sf::Vector3f& operator[](const int index) {
		return _array[index];
	}

	Matrix<double> getMatrix() {
		Matrix<double>r(_array.size(), 4);
		for (size_t i = 0; i < _array.size(); i++) {
			auto t = r[i];
			t[0] = _array[i].x;
			t[1] = _array[i].y;
			t[2] = _array[i].z;
			t[3] = 1;
		}
		return r;
	}

};