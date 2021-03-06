#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	int menu_status;
	bool first_update;
private:
	void initShaders();
	ShaderProgram texProgram;
	glm::mat4 projection;
	Texture menu_tex;
	Texture menu_tex2;
	Texture menu_tex3;
	Texture menu_tex4;
	Sprite *sprite;
	Sprite *sprite_help;
	Sprite *sprite_credits;
	Sprite *sprite_win;
	
};

#endif // _MENU_INCLUDE