//
//  Combat.cpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-12.
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

#include "Combat.h"

Combat::Combat(Player *player, orxCAMERA *camera) : Scene(player, camera) {
	sceneType = COMBAT;

	spawnPoint = Entity::createVector(3950, 350, 0);

	orxVECTOR townPos = Entity::createVector(5375, 175, 0);
	toTown = new SceneTransition(townPos, TOWN);

	playerHPBar = orxObject_CreateFromConfig("HPBar");
	enemyHPBar = orxObject_CreateFromConfig("HPBar");

	orxObject_SetParent(playerHPBar, camera);
	orxObject_SetParent(enemyHPBar, camera);

	orxVECTOR hpPos = Entity::createVector(-450, -250, 0);
	orxObject_SetPosition(playerHPBar, &hpPos);
	hpPos.fX = 200;
	orxObject_SetPosition(enemyHPBar, &hpPos);

	orxObject_CreateFromConfig("Arena");
}

SceneType Combat::update(const orxCLOCK_INFO *clockInfo, void *context) {
	Scene::update(clockInfo, context);
	enemy->update(player, clockInfo->fDT);

	orxVECTOR scale = Entity::createVector(player->getHP() * 25 / 100, 1, 0);
	orxObject_SetScale(playerHPBar, &scale);

	scale.fX = enemy->getHP() * 25 / 100;
	orxObject_SetScale(enemyHPBar, &scale);
	orxVECTOR pos = Entity::createVector(450 - scale.fX * 10, -250, 0);
	orxObject_SetPosition(enemyHPBar, &pos);

	if (toTown->getActivation()) {
		player->leaveActionable();
		toTown->reset();
		return TOWN;
	}
	return COMBAT;
}

orxSTATUS Combat::EventHandler(const orxEVENT *currentEvent) {
	return Scene::EventHandler(currentEvent);
}

void Combat::loadEnemy(Enemy *enemy) {
	this->enemy = enemy;
}
