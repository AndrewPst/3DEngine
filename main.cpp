#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "settings.h"
#include "Matrix.h"
#include "Object3D.h"
#include "Cube3D.h"
#include "ObjectTransformer.h"
#include "Camera.h"
#include "FPS.h"

using sf::Keyboard;

constexpr double MOVE_SPEED = 0.016;
constexpr double ROTATION_SPEED = 0.008;

Camera camera;
FPS fps;

void checkKeys()
{

	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		camera.moveX(MOVE_SPEED);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		camera.moveX(-MOVE_SPEED);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		camera.moveZ(MOVE_SPEED);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		camera.moveZ(-MOVE_SPEED);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		camera.rotateY(ROTATION_SPEED);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		camera.rotateY(-ROTATION_SPEED);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
		camera.rotateZ(-ROTATION_SPEED);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		camera.rotateZ(ROTATION_SPEED);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		camera.rotateX(-ROTATION_SPEED);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		camera.rotateX(ROTATION_SPEED);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		camera.moveY(MOVE_SPEED);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		camera.moveY(-MOVE_SPEED);
	}
}

int main()
{
	camera.setPosition({ 0, 0, -4 });
	Cube3D cube;
	Axis axis;

	sf::ContextSettings context;
	context.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Debug", sf::Style::Default, context);
	window.setFramerateLimit(60);

	double time = 0;

	ObjectTransformer::transfer(cube, { 1, 0, 0 });

	Plane plane;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		checkKeys();

		window.clear();

		//ObjectTransformer::updateGlobalMatrix(cube);

		camera.drawObject(plane, window);
		//camera.drawObject(axis, window);

		//cube.setPosition({ 1, (float)abs(sin(time)), 0 });
		//ObjectTransformer::rotateY(cube, 0.012);

		time += 0.05;

		window.display();

		fps.update();
		std::ostringstream ss;
		ss << fps.getFPS();
		window.setTitle(ss.str());
	}
	return 0;
}