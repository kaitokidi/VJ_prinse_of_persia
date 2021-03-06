#include "Enemy.h"
#include <iostream>
#include <windows.h>
#include <MMSystem.h>
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int tp, Player *pl)
{
	old_frame = 0;
	eye_distance = 256;
	close_distance = 32;
	player = pl;
	type = tp;
	fightPosition = 1;
	alive = true;
	timer = 0;
	float stepX = 1.0f / 8.0f; //CHECK
	float stepY = 1.0f / 8.0f;
	tileMapDispl = tileMapPos;
	if (type == 1){
		health = 6;
		max_health = 6;
	}
	else {
		health = 3;
		max_health = 4;
	}
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);	//per a fer servir coordenades negatives i fer mirror
	if (type == 1) spritesheet.loadFromFile("images/Enemy.png", TEXTURE_PIXEL_FORMAT_RGBA);
	else if (type == 2) spritesheet.loadFromFile("images/Enemy2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(stepX, stepY), &spritesheet, &shaderProgram);

	fightTexture.loadFromFile("images/fight.png", TEXTURE_PIXEL_FORMAT_RGBA);
	fightTexture.setMagFilter(GL_NEAREST);

	fightPos = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25f, 1), &fightTexture, &shaderProgram);

	fightPos->setNumberAnimations(4);

	fightPos->setAnimationSpeed(0, 1);
	fightPos->addKeyframe(0, glm::vec2(0, 0));

	fightPos->setAnimationSpeed(1, 1);
	fightPos->addKeyframe(1, glm::vec2(0.25f, 0));

	fightPos->setAnimationSpeed(2, 1);
	fightPos->addKeyframe(2, glm::vec2(0.5f, 0));

	fightPos->setAnimationSpeed(3, 1);
	fightPos->addKeyframe(3, glm::vec2(0.75f, 0));

	fightPos->changeAnimation(1);

	//enemy animations
	sprite->setNumberAnimations(eANIMATION_COUNT);

	sprite->setAnimationSpeed(eSTAND_RIGHT, 1);
	sprite->addKeyframe(eSTAND_RIGHT, glm::vec2(0 * stepX, 0 * stepY));

	sprite->setAnimationSpeed(eSTAND_LEFT, 1);
	sprite->addKeyframe(eSTAND_LEFT, glm::vec2(-1 * stepX, 0 * stepY));

	sprite->setAnimationSpeed(eWALK_RIGHT, 8);
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(0 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(1 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(2 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(3 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(4 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(5 * stepX, 1 * stepY));

	sprite->setAnimationSpeed(eWALK_LEFT, 8);
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-1 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-2 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-3 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-4 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-5 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-6 * stepX, 1 * stepY));

	sprite->setAnimationSpeed(ePARRY_RIGHT, 8);
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(0 * stepX, 1 * stepY));
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(1 * stepX, 1 * stepY));
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(2 * stepX, 1 * stepY));
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_RIGHT, glm::vec2(1 * stepX, 2 * stepY));

	sprite->setAnimationSpeed(ePARRY_LEFT, 8);
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-1 * stepX, 1 * stepY));
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-2 * stepX, 1 * stepY));
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-3 * stepX, 1 * stepY));
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
	sprite->addKeyframe(ePARRY_LEFT, glm::vec2(-1 * stepX, 2 * stepY));

	sprite->setAnimationSpeed(eATACK_RIGHT, 7);
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(0 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(1 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(2 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(3 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(3 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(3 * stepX, 2 * stepY));

	sprite->setAnimationSpeed(eATACK_LEFT, 7);
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-2 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-3 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-4 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-4 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-4 * stepX, 2 * stepY));

	sprite->setAnimationSpeed(eDIE_RIGHT, 6);
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(2 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(3 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(4 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(5 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY)); //copy

	sprite->setAnimationSpeed(eDIE_LEFT, 6);
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-3 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-4 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-5 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-6 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY)); //copy

	sprite->setAnimationSpeed(eDAMAGE_RIGHT, 6);
	sprite->addKeyframe(eDAMAGE_RIGHT, glm::vec2(0 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_RIGHT, glm::vec2(1 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_RIGHT, glm::vec2(1 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDAMAGE_RIGHT, glm::vec2(1 * stepX, 4 * stepY)); //copy

	sprite->setAnimationSpeed(eDAMAGE_LEFT, 6);
	sprite->addKeyframe(eDAMAGE_LEFT, glm::vec2(-1 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_LEFT, glm::vec2(-2 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_LEFT, glm::vec2(-2 * stepX, 4 * stepY)); //copy
	sprite->addKeyframe(eDAMAGE_LEFT, glm::vec2(-2 * stepX, 4 * stepY)); //copy

	//sprite->addKeyframe(eATACK_RIGHT, glm::vec2(6 * stepX, 1 * stepY)); //maybe parry?

	setAnimation(eSTAND_LEFT);
	setState(STANDING_LEFT);
	direction = 0;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	size = glm::vec2(float(19), float(42));
	position_col = glm::vec2(float(posPlayer.x + 16), float(posPlayer.y + 16));
	old_position_col = position_col;
}
bool Enemy::canSeePlayer(){
	glm::vec2 p_center = glm::vec2((player->position_col.x + player->size.x / 2), (player->position_col.y + player->size.y / 2));
	//std::cout << p_center.y << " " << position_col.y << std::endl;
	if (p_center.y > position_col.y && p_center.y < position_col.y + size.y){
		int my_center = (position_col.x + size.x / 2);
		int dist = abs(p_center.x - my_center);
		if (dist < eye_distance){
			if (playerDirection()){
				for (int i = my_center; i < my_center+dist; i = i + 10){
					if (map->collisionPoint(glm::ivec2(i, p_center.y))) {
						return false;
					}
				}
			}
			else{
				for (int i = my_center; i < my_center-dist; i = i - 10){
					if (map->collisionPoint(glm::ivec2(i, p_center.y))) {
						return false;
					}
				}
			}
			return true;
			
		}
		else return false;
	}
	else{
		return false;
	}
}
bool Enemy::playerClose(){
	glm::vec2 p_center = glm::vec2((player->position_col.x + player->size.x / 2) , (player->position_col.y + player->size.y / 2));
	if (!player->alive) return false;
	if (p_center.y > position_col.y && p_center.y < position_col.y + size.y){
		int my_center = (position_col.x + size.x / 2) ;
		int dist = abs(p_center.x - my_center);
		return (dist < close_distance);
	}
	else{
		return false;
	}
}
bool Enemy::playerDirection(){
	glm::vec2 p_center = glm::vec2((player->position_col.x + player->size.x / 2), (player->position_col.y + player->size.y / 2));
	int my_center = (position_col.x + size.x / 2);
	return (p_center.x > my_center);
}
void Enemy::newDecision(){
	if (!player->alive){
		if (direction){
			setState(STANDING_RIGHT);
			setAnimation(eSTAND_RIGHT);
		}
		else {
			setState(STANDING_LEFT);
			setAnimation(eSTAND_LEFT);
		}
	}
	else if (canSeePlayer() && !playerClose()){
		if (playerDirection()){
			if (state != SWORD_STEPING_F_RIGHT) setAnimation(eWALK_RIGHT);
			setState(SWORD_STEPING_F_RIGHT);
			direction = 1;
			
		}
		else{
			if (state != SWORD_STEPING_F_LEFT)setAnimation(eWALK_LEFT);
			setState(SWORD_STEPING_F_LEFT);
			direction = 0;
			
		}
	}
	else if (playerClose()){
		std::cout << state << std::endl;
		if (state == SWORD_STEPING_F_RIGHT || state == SWORD_STEPING_F_LEFT){
			if (direction){
				setState(STANDING_RIGHT);
				setAnimation(eSTAND_RIGHT);
			}
			else {
				setState(STANDING_LEFT);
				setAnimation(eSTAND_LEFT);
			}
		}
		if (state == STANDING_RIGHT || state == STANDING_LEFT){
			
			//ESTO HAY QUE HACERLO PORQUE SINO A VECES NO MIRA DONDE TOCA
			if (direction){
				setState(STANDING_RIGHT);
				setAnimation(eSTAND_RIGHT);
			}
			else {
				setState(STANDING_LEFT);
				setAnimation(eSTAND_LEFT);
			}
			////////
			if (!wait){
				int random_variable = std::rand() % (4 - 1);
				
				if (random_variable == 1){
					if (direction){
						if (state != SWORD_ATTACKING_RIGHT) setAnimation(eATACK_RIGHT);
						setState(SWORD_ATTACKING_RIGHT);
					}
					else if (!direction){
						if (state != SWORD_ATTACKING_LEFT) setAnimation(eATACK_LEFT);
						setState(SWORD_ATTACKING_LEFT);
					}

				}
				else if (random_variable == 2){
					++fightPosition;
					fightPosition = fightPosition % 3 + 1;
				}
				else if (random_variable == 3) {
					fightPosition;
					fightPosition = fightPosition % 3 + 1;
				}
				else {
					wait = true;
					if (direction){
						setState(STANDING_RIGHT);
						setAnimation(eSTAND_RIGHT);
					}
					else {
						setState(STANDING_LEFT);
						setAnimation(eSTAND_LEFT);
					}
				}
			}

		}
	}
	else if(direction){
		setState(STANDING_RIGHT);
		setAnimation(eSTAND_RIGHT);
	}
	else {
		setState(STANDING_LEFT);
		setAnimation(eSTAND_LEFT);
	}
	
}
void Enemy::damage(bool direction, int dmg){
	if (health > 0){
		PlaySound(TEXT("sounds/pain1"), NULL, SND_ASYNC);
		if (direction){
			setState(DAMAGING_LEFT);
			setAnimation(eDAMAGE_LEFT);
		}
		else{
			setState(DAMAGING_RIGHT);
			setAnimation(eDAMAGE_RIGHT);
		}
	}
	else DIE();
	

}
void Enemy::update(int deltaTime)
{
	//deltaTime = 50;
	if (wait) timer = timer + deltaTime;
	if (timer > 1000) {
		timer = 0;
		
		wait = false;
	}
	//std::cout << timer << std::endl;
	if (alive) {
		old_position_col = position_col;
		sprite->update(deltaTime);
		fightPos->update(deltaTime);
		position_col = glm::vec2(float(posPlayer.x + 24), float(posPlayer.y + 22));
		glm::ivec2 new_pos;
		if (state != DYING_LEFT && state != DYING_RIGHT && state != PARRYING_RIGHT && state != PARRYING_LEFT) 
			newDecision();

		if (playerClose() && state != DYING_LEFT && state != DYING_RIGHT){
			
			if (player->state == SWORD_ATTACKING_RIGHT && !direction && state != PARRYING_LEFT && player->sprite->getCurrentKeyframe() < 6) {
				if (player->fightPosition == fightPosition) {
					setState(PARRYING_LEFT);
					setAnimation(ePARRY_LEFT);
				}
			}
			else if (player->state == SWORD_ATTACKING_RIGHT && !direction && player->sprite->getCurrentKeyframe() >= 6){
				

				if (player->fightPosition != fightPosition){
					//PlaySound(TEXT("sounds/pain1"), NULL, SND_ASYNC);
					damage(1, 1);
				}
				else {
					PlaySound(TEXT("sounds/parry"), NULL, SND_ASYNC);
				}
			}
			//LEFT
			else if (player->state == SWORD_ATTACKING_LEFT && direction && state != PARRYING_RIGHT && player->sprite->getCurrentKeyframe() < 6) {
				if (player->fightPosition == fightPosition) {
					setState(PARRYING_RIGHT);
					setAnimation(ePARRY_RIGHT);
				}
			}
			else if (player->state == SWORD_ATTACKING_LEFT && direction && player->sprite->getCurrentKeyframe() >= 6){

				if (player->fightPosition != fightPosition){
					//PlaySound(TEXT("sounds/pain1"), NULL, SND_ASYNC);
					damage(0, 1);
				}
				else {
					PlaySound(TEXT("sounds/parry"), NULL, SND_ASYNC);
				}
			}
		}
		switch (state) {
		case STANDING_RIGHT:
			direction = 1;
			break;
		case STANDING_LEFT:
			direction = 0;
			break;

		case SWORD_STEPING_F_RIGHT:
			direction = 1;
			new_pos = glm::ivec2((position_col.x + deltaTime / magic), position_col.y);
			if (!map->collisionMoveDown(glm::ivec2(new_pos.x + 10, position_col.y + 5), size, &position_col.y))
			{
				setState(STANDING_RIGHT);
				setAnimation(eSTAND_RIGHT);
			}
			else if (!map->collisionMoveRight(new_pos, size)) {
				position_col.x = new_pos.x;
			}
			break;
		case SWORD_STEPING_F_LEFT:
			direction = 0;
			new_pos = glm::ivec2(ceil(position_col.x - deltaTime / magic), position_col.y);
			if (!map->collisionMoveDown(glm::ivec2(new_pos.x - 10, position_col.y + 5), size, &position_col.y))
			{
				setState(STANDING_LEFT);
				setAnimation(eSTAND_LEFT);
			}
			else if (!map->collisionMoveLeft(new_pos, size)) {
				position_col.x = new_pos.x;
			}
			break;
		case SWORD_ATTACKING_LEFT:
			direction = 0;
			if (sprite->getCurrentKeyframe() < 4) {
				if (player->fightPosition == fightPosition && player->state != PARRYING_RIGHT && player->state != DYING_RIGHT) {
					player->setState(PARRYING_RIGHT);
					player->setAnimation(PARRY_RIGHT);
				}
			}
			else if (sprite->getCurrentKeyframe() >= 5 && player->state != DYING_LEFT && player->state != DYING_RIGHT) {
				if (player->fightPosition != fightPosition){
					player->damage(0, 1);
				}
				else if (player->fightPosition == fightPosition){
					PlaySound(TEXT("sounds/parry"), NULL, SND_ASYNC);
				}
				setState(STANDING_LEFT);
				setAnimation(eSTAND_LEFT);
			}
			break;
		case SWORD_ATTACKING_RIGHT:
			direction = 1;
			if (sprite->getCurrentKeyframe() < 4) {
				if (player->fightPosition == fightPosition) {
					player->setState(PARRYING_LEFT);
					player->setAnimation(PARRY_LEFT);
				}
			}
			else if (sprite->getCurrentKeyframe() >= 5 && player->state != DYING_LEFT && player->state != DYING_RIGHT) {
				if (player->fightPosition != fightPosition){
					player->damage(1, 1);
				}
				else if (player->fightPosition == fightPosition){
					PlaySound(TEXT("sounds/parry"), NULL, SND_ASYNC);
				}
				setState(STANDING_RIGHT);
				setAnimation(eSTAND_RIGHT);
			}
			break;
		case PARRYING_LEFT:
			direction = 0;
			if (sprite->getCurrentKeyframe() >= 6) {
				setState(STANDING_LEFT);
				setAnimation(eSTAND_LEFT);
			}
			break;
		case PARRYING_RIGHT:
			direction = 1;
			if (sprite->getCurrentKeyframe() >= 6) {
				setState(STANDING_RIGHT);
				setAnimation(eSTAND_RIGHT);
			}
			break;
		case DAMAGING_LEFT:
			direction = 0;
			if (sprite->getCurrentKeyframe() >= 1) {
				health = health - 1;
				if (health <= 0 && state != DYING_LEFT && state != DYING_RIGHT) {
					setState(DYING_LEFT);
					setAnimation(eDIE_LEFT);
				}
				else if (health > 0){
					setState(STANDING_LEFT);
					setAnimation(eSTAND_LEFT);
				}
			}
			break;
		case DAMAGING_RIGHT:
			direction = 1;
			if (sprite->getCurrentKeyframe() >= 1) {
				health = health - 1;
				if (health <= 0 && state != DYING_LEFT && state != DYING_RIGHT) {
					setState(DYING_RIGHT);
					setAnimation(eDIE_RIGHT);
				}
				else if (health > 0){
					setState(STANDING_RIGHT);
					setAnimation(eSTAND_RIGHT);
				}
			}
			break;
		case DYING_RIGHT:
			direction = 1;
			if (sprite->getCurrentKeyframe() >= 8) {
				alive = false;
			}
			break;
		case DYING_LEFT:
			direction = 0;
			if (sprite->getCurrentKeyframe() >= 8) {
				alive = false;
			}
			break;
		}
		posPlayer = glm::vec2(float(position_col.x - 24), float(position_col.y - 22));
		sprite->setPosition(glm::vec2(float(posPlayer.x + tileMapDispl.x), float(posPlayer.y + tileMapDispl.y)));
		fightPos->setPosition(glm::vec2(float(posPlayer.x + tileMapDispl.x + 20), float(posPlayer.y + tileMapDispl.y - 0)));
		if (fightPos->animation() != fightPosition) fightPos->changeAnimation(fightPosition);
	}
}


void Enemy::render()
{
	if (alive) {
		sprite->render();
		fightPos->render();
	}
}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	position_col = glm::vec2(float(posPlayer.x + 24), float(posPlayer.y + 22));
}

glm::vec2 Enemy::getPosition()
{
	return position_col;
}

void Enemy::setState(PlayerState newState) {
	state = newState;
}

void Enemy::setAnimation(EnemyAnims newAnim) {
	sprite->changeAnimation(newAnim);
}

void Enemy::DIE() {
	PlaySound(TEXT("sounds/die1"), NULL, SND_ASYNC);
	health = 0;
	if (direction){
		setState(DYING_RIGHT);
		setAnimation(eDIE_RIGHT);
	}
	else {
		setState(DYING_LEFT);
		setAnimation(eDIE_LEFT);
	}
}