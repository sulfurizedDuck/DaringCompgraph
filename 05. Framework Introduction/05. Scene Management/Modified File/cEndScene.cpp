// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cEndScene.h"
#include "cLevel1Scene.h"
#include "cGame.h"

cEndScene::cEndScene()
{

}

cEndScene::~cEndScene()

{

}

void cEndScene::Init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.top = GAME_HEIGHT;
	visible_area.bottom = 0;
	visible_area.left = 0;
	visible_area.right = GAME_WIDTH;
	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void cEndScene::Update(float tpf /*= 0.0333*/)
{
}

void cEndScene::Render()
{
	renderBitmapString(300, 300, 9, GLUT_BITMAP_HELVETICA_18, "End Scene", 1, 0, 0);

	// glEnable(GL_TEXTURE_2D);
	// glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().background->Texture());
	// glBegin(GL_QUADS);

	// glTexCoord2f(0, 1);	glVertex3i(0, 0, 49);
	// glTexCoord2f(1, 1);	glVertex3i(GAME_WIDTH, 0, 49);
	// glTexCoord2f(1, 0);	glVertex3i(GAME_WIDTH, GAME_HEIGHT, 49);
	// glTexCoord2f(0, 0);	glVertex3i(0, GAME_HEIGHT, 49);
	// glEnd();
	// glDisable(GL_TEXTURE_2D);
}

void cEndScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	printf("Normal key: %d\n", key);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}

	if (key == 13) {
		cGame::getInstance().UpdateScene(new cLevel1Scene());
	}
}

void cEndScene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	printf("Special key: %d", key);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}


}

void cEndScene::ReadMouse(int button, int state, int x, int y)
{
}
