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

	orxObject_CreateFromConfig("Arena");
}

SceneType Combat::update(const orxCLOCK_INFO *clockInfo, void *context) {
	Scene::update(clockInfo, context);
	return COMBAT;
}

orxSTATUS Combat::EventHandler(const orxEVENT *currentEvent) {
	return Scene::EventHandler(currentEvent);
}
