// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cLevel1Scene.h"
#include "cAssetManager.h"
#include "cGame.h"
#include "cMenuScene.h"
#include "cEndScene.h"
#pragma warning(disable:4996)

cLevel1Scene::cLevel1Scene()
{

}

cLevel1Scene::~cLevel1Scene()
{
}

void cLevel1Scene::Init()
{
	player = new cPlayer(cAssetManager::getInstance().player, 100, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player);

	person = new cPerson(cAssetManager::getInstance().person, 500, 100, 2 * TILE_SIZE, 2 * TILE_SIZE);
	addGameObject(person);
}

void cLevel1Scene::Render()
{
	cScene::Render();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().background->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);	glVertex3i(0, 0, 49);
	glTexCoord2f(1, 1);	glVertex3i(GAME_WIDTH, 0, 49);
	glTexCoord2f(1, 0);	glVertex3i(GAME_WIDTH, GAME_HEIGHT, 49);
	glTexCoord2f(0, 0);	glVertex3i(0, GAME_HEIGHT, 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.left = player->X() - 100;
	visible_area.right = player->X() + player->Width() + 100;

	double ratio = (double) GAME_HEIGHT / GAME_WIDTH;
	double camera_width = visible_area.right - visible_area.left;

	visible_area.bottom = player->Y() - 50;
	visible_area.top = visible_area.bottom + (ratio * camera_width);

	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
}

float countDown = 5;

void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);
	
	countDown -= tpf;
	if (countDown <= 0) {
		// cGame::getInstance().UpdateScene(new cEndScene());
	}

	if (IsCollide(person, player)) {
		cSound::getInstance().Play(SOUND_EXPLOSION);
		removeGameObject(person);
	}
}

void cLevel1Scene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	cScene::ReadKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cLevel1Scene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	cScene::ReadSpecialKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cLevel1Scene::ReadMouse(int button, int state, int x, int y)
{
	cScene::ReadMouse(button, state, x, y);
}

bool cLevel1Scene::IsCollide(cPerson *obj1, cPlayer *obj2)
{

	float obj1x0 = obj1->X();
	float obj1x1 = obj1->X() + obj1->Width();
	float obj1y0 = obj1->Y();
	float obj1y1 = obj1->Y() + obj1->Height();

	float obj2x0 = obj2->X();
	float obj2x1 = obj2->X() + obj2->Width();
	float obj2y0 = obj2->Y();
	float obj2y1 = obj2->Y() + obj2->Height();

	if (obj1y0 < obj2y1 && obj1y1 > obj2y0
		&& obj1x0 < obj2x1 && obj1x1 > obj2x0) 
	{
		return true;
	}
	return false;
}

