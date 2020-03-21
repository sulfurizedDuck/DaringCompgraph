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
	animControl->AddAnim("StraightLoop", "walk_forward", 0, 1, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_backward", 5, 6, 0.2f);
	animControl->AddAnim("NoLoop", "jump", 2, 2, 0.2f);
	animControl->AddAnim("NoLoop", "idle", 4, 4, 0.2f);
}

void cPerson::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);

	if (keys[GLUT_KEY_RIGHT])
	{
		if (animControl->ActiveName() != "walk_forward")
			animControl->SetActiveAnim("walk_forward");
	}
	else if (keys[GLUT_KEY_LEFT])
	{
		if (animControl->ActiveName() != "walk_backward")
			animControl->SetActiveAnim("walk_backward");
	}
	else
	{
		if (animControl->ActiveName() != "idle")
			animControl->SetActiveAnim("idle");
	}

	if (keys[GLUT_KEY_LEFT]) {
		x -= 300 * tpf;
	}
	else if (keys[GLUT_KEY_RIGHT]) {
		x += 300 * tpf;
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