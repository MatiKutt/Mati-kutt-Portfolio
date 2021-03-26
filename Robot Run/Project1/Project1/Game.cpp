//Mati Kutt
//https://instituteoftechnol663-my.sharepoint.com/:v:/g/personal/c00250720_itcarlow_ie/ET7MfdaXqgBPsPlBpAkTy1oBANNCEDhLj3D4wRxUZSLTHQ?email=Noel.OHara%40itcarlow.ie&e=8TzVXg
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 
#include "Game.h"


int main()
{


	Game game;


	game.init();

	game.run();



	return 0;
}

