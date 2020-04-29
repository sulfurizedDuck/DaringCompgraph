// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma warning(disable:4996)
#include "cAssetManager.h"
#include "Globals.h"

cAssetManager::cAssetManager(void) {}
cAssetManager::~cAssetManager(void) {}

int cAssetManager::GetID(int img)
{
	return textures[img].GetID();
}

void cAssetManager::GetSize(int img, int *w, int *h)
{
	textures[img].GetSize(w, h);
}

bool cAssetManager::LoadImage(int img, char *filename, int type)
{
	int res;

	res = textures[img].Load(filename, type);
	if (!res) return false;

	return true;
}
bool cAssetManager::Load()
{
	int res;

	res = LoadImage(SPRITESHEET_PLAYERS, "Textures/Spritesheets/spritesheet_players.png", GL_RGBA);
	if (!res) return false;
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 8; i++) {
			float x0, y0, x1, y1;
			int tex_w, tex_h;
			GetSize(GetID(SPRITESHEET_PLAYERS), &tex_w, &tex_h);
			float sprite_width = 128.0f / tex_w;
			float sprite_height = 256.0f / tex_h;
			x0 = sprite_width*j;
			x1 = sprite_width*(j + 1);
			y0 = sprite_height*i;
			y1 = sprite_height*(i + 1);
			player->push_back(new cSprite(GetID(SPRITESHEET_PLAYERS), x0, y0, x1, y1));
			
		}
	}

	res = LoadImage(SPRITE_COLORED_GRASS, "Textures/PNG/Backgrounds/colored_grass.png", GL_RGBA);
	if (!res) return false;
	background = new cSprite(GetID(SPRITE_COLORED_GRASS), 0, 0, 1, 1);

	int size_x, size_y;
	res = LoadImage(SPRITESHEET_PERSON, "Textures/Spritesheets/spritesheet_person.png", GL_RGBA);
	if (!res) return false;
	size_x = 4;
	size_y = 4;
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			double x0, x1, y0, y1;
			x0 = (double) j / size_x;
			x1 = (double) (j + 1) / size_x;
			y0 = (double) i / size_y;
			y1 = (double) (i + 1) / size_y;
			person->push_back(new cSprite(GetID(SPRITESHEET_PERSON), x0, y0, x1, y1));
		}
	}

	return true;
}

