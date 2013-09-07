
#include <SFML/Graphics.hpp>
#include "ParticleEngine.h"
#include <Windows.h>

//Constant Game Speed indepenent of Variable FPS Game Loop implementation
//USING: http://www.koonsolo.com/news/dewitters-gameloop/

//TICKS_PER_SECOND = Update Speed
const int TICKS_PER_SECOND = 30;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Initialize variables to regulate update speed
	sf::Clock clock;
	int nextGameTick = clock.getElapsedTime().asMilliseconds();
	int loops;
	float interpolation;
	//--------------------------------------------


	sf::RenderWindow window(sf::VideoMode(640, 480), "Particle Engine Test!");

	ParticleEngine particleEngine(sf::Vector2f(-300,300),1000, sf::Color::Black);
	particleEngine.setSize(10);

	while (window.isOpen())
	{
		particleEngine.setDrawType(eRANDOM);
		loops = 0;
		window.clear();
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particleEngine.setEmitterLocation(window.mapPixelToCoords(mouse));
        sf::Event event;
		//input here
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		//controls update speed
		while (clock.getElapsedTime().asMilliseconds() > nextGameTick && loops < MAX_FRAMESKIP)
		{

			//updates here
			particleEngine.Update(0.7f);


			nextGameTick += SKIP_TICKS;
			loops++;
		}

		//calculate interpolation to (try to) smooth rendering between update
		interpolation = float(clock.getElapsedTime().asMilliseconds() + SKIP_TICKS - nextGameTick)
			/ float(SKIP_TICKS);

		//draw methods here
		particleEngine.Draw(&window, interpolation);

		window.display();
	}
}
