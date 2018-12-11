//
//  Town.cpp
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

#include "Town.h"

Town::Town(Player *player, orxCAMERA *camera) {
	this->player = player;
	this->camera = camera;
	sceneType = TOWN;

	orxVECTOR spawnPos = Entity::createVector(375, 700, 0);
	player->setPosition(spawnPos);

	orxVECTOR elevPos = Entity::createVector(2350, 700, 0);
	new Elevator(elevPos);

	orxObject_CreateFromConfig("Town");
}

SceneType Town::update(const orxCLOCK_INFO *clockInfo, void *context) {
	player->update(
				   orxInput_IsActive("InputLeft"),
				   orxInput_IsActive("InputRight"),
				   clockInfo->fDT);
	orxVECTOR camPos;
	orxCamera_GetPosition(camera, &camPos);
	camPos.fX = player->getPosition().fX;
	camPos.fY = player->getPosition().fY;
	orxCamera_SetPosition(camera, &camPos);
	return TOWN;
}

orxSTATUS Town::EventHandler(const orxEVENT *currentEvent) {
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
