//
//  StandAlone.cpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-09.
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

#include "StandAlone.h"

StandAlone* StandAlone::m_Instance = orxNULL;

Scene* StandAlone::currentScene = orxNULL;
orxVIEWPORT* StandAlone::currentViewport = orxNULL;

Town* StandAlone::townScene = orxNULL;
orxVIEWPORT* StandAlone::townViewport = orxNULL;

Combat* StandAlone::combatScene = orxNULL;
orxVIEWPORT* StandAlone::combatViewport = orxNULL;

Player* StandAlone::player = orxNULL;

StandAlone* StandAlone::Instance() {
	if (m_Instance != orxNULL) {
		return m_Instance;
	}
	m_Instance = new StandAlone();
	return m_Instance;
}

//written by Wayne "Sausage" Johnson
void StandAlone::paintTiles(const orxSTRING mapSection, const orxVECTOR startPos, int tilesWide) {
	int tileSize = 50;
	orxVECTOR position;
	orxVector_Copy(&position, &startPos);

	orxConfig_PushSection(mapSection);
	orxU32 groupID = orxString_GetID(mapSection);

	int baseMapIndex = 0;

	orxU32 propertyCount = orxConfig_GetKeyCount();

	for (orxS32 propertyIndex = 1; propertyIndex < propertyCount + 1; propertyIndex++) {
		orxCHAR property[30]; //good maximum length
		orxString_Print(property, "MapPart%d", propertyIndex);

		orxU32 listCount = orxConfig_GetListCount(property);

		for (int listIndex = 0; listIndex < listCount; listIndex++) {
			const orxSTRING tile = orxConfig_GetListString(property, listIndex);
			if (orxString_Compare(tile, "NONE") == 0) {
				baseMapIndex++;
				continue;
			}

			position.fX = startPos.fX + (baseMapIndex % tilesWide) * tileSize;
			position.fY = startPos.fY + (baseMapIndex / tilesWide) * tileSize;
			position.fZ = orxFLOAT_0;

			orxCHAR formattedTileObject[30]; //good maximum length
			orxString_Print(formattedTileObject, "%sObject", tile);

			orxOBJECT *obj = orxObject_CreateFromConfig(formattedTileObject);

			if (obj != orxNULL) {
				orxObject_SetPosition(obj, &position);
				orxObject_SetGroupID(obj, groupID);
			}
			baseMapIndex++;
		}
	}
	orxConfig_PopSection();
}

StandAlone::StandAlone() {}

orxSTATUS orxFASTCALL StandAlone::Init() {
	player = new Player();

	townViewport = orxViewport_CreateFromConfig("MainViewport");
	orxCAMERA *townCam = orxViewport_GetCamera(townViewport);

	townScene = new Town(player, townCam);
	townScene->activate();
	currentScene = townScene;
	currentViewport = townViewport;

	combatViewport = orxViewport_CreateFromConfig("BattleViewport");
	orxViewport_Enable(combatViewport, orxFALSE);
	orxCAMERA *battleCam = orxViewport_GetCamera(combatViewport);

	combatScene = new Combat(player, battleCam);

	paintTiles("TownTiles", orxVECTOR_0, 50);

	orxVECTOR arenaPos = Entity::createVector(3500, 0, 0);
	paintTiles("ArenaTiles", arenaPos, 40);

	orxCLOCK* upClock = orxClock_FindFirst(-1.0f, orxCLOCK_TYPE_CORE);
	orxClock_Register(upClock, Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

	orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, StandAlone::EventHandler);

	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL StandAlone::Run() {
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit() {
	return;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	SceneType nextScene = currentScene->update(clockInfo, context);
	if (nextScene != currentScene->getSceneType()) {
		orxViewport_Enable(currentViewport, orxFALSE);
		switch (nextScene) {
			case TOWN:
				currentViewport = townViewport;
				currentScene = townScene;
				break;
			case COMBAT:
				combatScene->loadEnemy(townScene->getOpponent());
				currentViewport = combatViewport;
				currentScene = combatScene;
				break;
			default:
				break;
		}
		currentScene->activate();
		orxViewport_Enable(currentViewport, orxTRUE);
	}
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	return currentScene->EventHandler(currentEvent);
}
