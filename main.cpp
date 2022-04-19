/*
The MIT License(MIT)

Copyright © «year» «copyright holders»

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the “Software”),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Author: Andrew Pustovit

	_______
   /      /|
  /      / |
 |------|  |
 |      |  /
 |      | /
 |______|/
 SFML 3d engine

*/



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

Camera camera;
FPS fps;

void checkKeys();

int main()
{
	camera.setPosition({ 0, 0, -4 });

	//Created objects
	Cube3D cube;
	Axis axis;

	//---------Create window--------
	sf::ContextSettings context;
	context.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Debug", sf::Style::Default, context);
	window.setFramerateLimit(60);

	//--------Live cycle----------
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

		//Draw objects

		camera.drawObject(cube, window);
		camera.drawObject(axis, window);

		//Update display
		window.display();

		//Calculate fps
		fps.update();
		std::ostringstream ss;
		ss << fps.getFPS();
		window.setTitle(ss.str());
	}
	return 0;
}

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