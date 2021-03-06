#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

#define NUM_LVLS 3
enum GameStatus
{
	PLAYING, MAINMENU, PAUSE, WINER
};

void Game::init()
{
	bPlay = true;
	game_status = MAINMENU;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init(false, 1);
	
	menu.init(scene.getProgram());
	pause.init(scene.getProgram());
}

bool Game::update(int deltaTime)
{
	switch (game_status){
		case PLAYING:
			if (scene.completed) {
				//menu.first_update = true;
				if (scene.level == NUM_LVLS) {
					menu.menu_status = 3;
					game_status = WINER;
				}
				else scene.init(true, scene.level+1);

				//game_status = MAINMENU;
			}
			else scene.update(deltaTime);
			break;
		case MAINMENU:
			menu.update(deltaTime);
			break;
		case PAUSE:
			pause.update(deltaTime);
			break;
		case WINER:
			menu.update(deltaTime);
			break;
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch (game_status){
		case PLAYING:
			scene.render();
			break;
		case MAINMENU:
			menu.render();
			break;
		case PAUSE:
			scene.render();
			pause.render();
			break;
		case WINER:
			menu.render();
			break;
	}
}

void Game::keyPressed(int key)
{
	
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	if (key == 80 || key == 112) // "P" key
	{
		switch (game_status){
		case PLAYING:
			game_status = PAUSE;
			break;
		case PAUSE:
			game_status = PLAYING;
			break;
		}
	}
	else if (key == 32){
		switch (game_status){
		case MAINMENU:
			game_status = PLAYING;
			break;
		}
	}
	else if (key == 82 || key == 114){
		switch (game_status){
		case PLAYING:
			menu.first_update = true;
			scene.init(true, 1);
			game_status = MAINMENU;
			break;
		
		}

	}
	else if (key == 83 || key == 115){
		switch (game_status){
		case PLAYING:
			scene.completed = true;
			break;
		}
	}
	else if ((key == 72 || key == 104) && game_status == MAINMENU){
		menu.menu_status = 1;
	}
	else if ((key == 67 || key == 99) && game_status == MAINMENU){
		menu.menu_status = 2;
	}
	else if ((key == 77 || key == 109) && (game_status == MAINMENU || game_status == WINER)){
		menu.first_update = true;
		scene.init(true, 1);
		game_status = MAINMENU;
		menu.menu_status = 0;
	}
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





