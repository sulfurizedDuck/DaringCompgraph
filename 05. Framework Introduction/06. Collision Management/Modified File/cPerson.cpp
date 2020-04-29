// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cPerson.h"



cPerson::cPerson()
{
}


cPerson::~cPerson()
{
}

void cPerson::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, playerSheet->at(animControl->Index())->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x, y, 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width(), y, 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width(), y + Height(), 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x, y + Height(), 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cPerson::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_south", 0, 3, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_north", 4, 7, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_west", 8, 11, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_east", 12, 15, 0.2f);
	animControl->AddAnim("NoLoop", "idle", 0, 0, 0.2f);
}

void cPerson::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);

	if (keys['w'] || keys['W']) {
		if (animControl->ActiveName() != "walk_north")
			animControl->SetActiveAnim("walk_north");
	} 
	else if (keys['a'] || keys['A']) {
		if (animControl->ActiveName() != "walk_west")
			animControl->SetActiveAnim("walk_west");
	}
	else if (keys['s'] || keys['S']) {
		if (animControl->ActiveName() != "walk_south")
			animControl->SetActiveAnim("walk_south");
	}
	else if (keys['d'] || keys['D']) {
		if (animControl->ActiveName() != "walk_east")
			animControl->SetActiveAnim("walk_east");
	}
	else {
		if (animControl->ActiveName() != "idle")
			animControl->SetActiveAnim("idle");
	}
}

void cPerson::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cPerson::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cPerson::ReadMouse(int button, int state, int x, int y)
{

}