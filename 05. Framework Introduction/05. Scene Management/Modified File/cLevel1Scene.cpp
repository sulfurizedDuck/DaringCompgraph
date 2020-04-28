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

	player1 = new cPlayer(cAssetManager::getInstance().player, 200, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player1);

	player2 = new cPlayer(cAssetManager::getInstance().player, 300, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player2);

	player3 = new cPlayer(cAssetManager::getInstance().player, 400, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player3);

	person = new cPerson(cAssetManager::getInstance().person, 100, 100, 2 * TILE_SIZE, 2 * TILE_SIZE);
	addGameObject(person);
}

void cLevel1Scene::Render()
{
	cScene::Render();
}

float countDown = 5;

void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);
	
	countDown -= tpf;
	if (countDown <= 0) {
		cGame::getInstance().UpdateScene(new cEndScene());
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

