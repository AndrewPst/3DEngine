#pragma once

#include <SFML/Graphics.hpp>

inline sf::Vector3f sumVectors(const sf::Vector3f& v1, const sf::Vector3f& v2) {
	auto result = sf::Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	return result;
}

inline sf::Vector3f multiplicationVectors(const sf::Vector3f& v1, const sf::Vector3f& v2) {
	auto result = sf::Vector3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	return result;
}

inline sf::Vector3f subtractionVectors(const sf::Vector3f& v1, const sf::Vector3f& v2) {
	auto result = sf::Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return result;
}

inline sf::Vector2f subtractionVectors(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	auto result = sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
	return result;
}

inline double scalarMultiplication(const sf::Vector3f& v1, const sf::Vector3f& v2) {
	double result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

//inline sf::Vector3f divisionVectors(const sf::Vector3f& v1, const sf::Vector3f& v2) {
//	auto result = sf::Vector3f(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
//	return result;
//}
