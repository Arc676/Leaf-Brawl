//
//  Scene.cpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-11.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2018 Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3)

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README and LICENSE for more details

#include "Scene.h"

Scene::Scene(Player *player, orxCAMERA *camera) {
	this->player = player;
	this->camera = camera;
}

SceneType Scene::update(const orxCLOCK_INFO* clockInfo, void* context) {
	player->update(
				   orxInput_IsActive("InputLeft"),
				   orxInput_IsActive("InputRight"),
				   clockInfo->fDT);
	orxVECTOR camPos;
	orxCamera_GetPosition(camera, &camPos);
	camPos.fX = player->getPosition().fX;
	camPos.fY = player->getPosition().fY;
	orxCamera_SetPosition(camera, &camPos);
	return getSceneType();
}

orxSTATUS Scene::EventHandler(const orxEVENT *currentEvent) {
	switch (currentEvent->eType) {
		case orxEVENT_TYPE_PHYSICS:
		{
			orxOBJECT* objs[] = {
				orxOBJECT(currentEvent->hSender),
				orxOBJECT(currentEvent->hRecipient)
			};
			switch (currentEvent->eID) {
				case orxPHYSICS_EVENT_CONTACT_ADD:
				case orxPHYSICS_EVENT_CONTACT_REMOVE:
					for (int i = 0; i < 2; i++) {
						orxSTRING name1 = (orxSTRING)orxObject_GetName(objs[i]);
						orxSTRING name2 = (orxSTRING)orxObject_GetName(objs[1 - i]);
						if (!orxString_Compare(name1, "Player")) {
							orxConfig_PushSection(name2);
							orxBOOL isActionable = orxConfig_GetBool("IsActionable");
							orxConfig_PopSection();
							if (isActionable) {
								Actionable* act = (Actionable*)orxObject_GetUserData(objs[1 - i]);
								if (currentEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD) {
									player->approachActionable(act);
								} else {
									player->leaveActionable();
									act->controlLoss();
								}
							}
						} else if (currentEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD) {
							orxConfig_PushSection(name1);
							orxBOOL isWeapon = orxConfig_GetBool("IsWeapon");
							orxConfig_PopSection();
							if (isWeapon) {
								Weapon *weapon = (Weapon*)orxObject_GetUserData(objs[i]);
								Entity *hit = (Entity*)orxObject_GetUserData(objs[1 - i]);
								weapon->contact(hit);
							}
						}
					}
					break;
				default:
					break;
			}
			break;
		}
		default:
			break;
	}
	return orxSTATUS_SUCCESS;
}

SceneType Scene::getSceneType() {
	return sceneType;
}

void Scene::activate() {
	player->setPosition(spawnPoint);
}
