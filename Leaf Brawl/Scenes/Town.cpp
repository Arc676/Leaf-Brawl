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

Town::Town(Player *player, orxCAMERA *camera) : Scene(player, camera) {
	sceneType = TOWN;

	spawnPoint = Entity::createVector(1000, 700, 0);
	player->setPosition(spawnPoint);

	orxVECTOR elevPos = Entity::createVector(2350, 700, 0);
	new Elevator(elevPos);

	orxVECTOR stylePos = Entity::createVector(325, 675, 0);
	new StyleChanger(stylePos);

	orxVECTOR savePos = Entity::createVector(75, 675, 0);
	new PlayerIO(savePos);

	orxVECTOR weaponSwitchPos = Entity::createVector(1525, 675, 0);
	new WeaponSwitcher(weaponSwitchPos);

	orxVECTOR combatPos = Entity::createVector(725, 375, 0);
	toCombat = new SceneTransition(combatPos, COMBAT);

	stakeFighers = std::vector<Enemy*>(6);

	orxObject_CreateFromConfig("Town");
}

SceneType Town::update(const orxCLOCK_INFO *clockInfo, void *context) {
	Scene::update(clockInfo, context);
	if (toCombat->getActivation()) {
		player->leaveActionable();
		toCombat->reset();
		return COMBAT;
	}
	return TOWN;
}

orxSTATUS Town::EventHandler(const orxEVENT *currentEvent) {
	return Scene::EventHandler(currentEvent);
}

void Town::activate() {
	if (playerOpp) {
		playerOpp->despawn();
		delete playerOpp;
		for (int i = 0; i < 6; i++) {
			delete stakeFighers.at(i);
		}
		stakeFighers.clear();
	}
	playerOpp = Enemy::createRandomEnemy(player, false);
	playerOpp->setEnabled(orxFALSE);
	for (int i = 0; i < 6; i++) {
		stakeFighers.push_back(Enemy::createRandomEnemy(orxNULL, true));
	}
	Scene::activate();
}

Enemy* Town::getOpponent() {
	return playerOpp;
}
