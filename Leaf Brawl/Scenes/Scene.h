//
//  Scene.h
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

#ifndef Scene_h
#define Scene_h

#include "orx.h"

#include "Actionable.h"
#include "Player.h"
#include "Enums.h"

class Scene {
protected:
	SceneType sceneType;
	Player *player;
	orxVECTOR spawnPoint;
	orxCAMERA *camera;

	Scene(Player *player, orxCAMERA *camera);
public:
	SceneType getSceneType();

	virtual void activate();

	virtual SceneType update(const orxCLOCK_INFO* clockInfo, void* context);
	virtual orxSTATUS EventHandler(const orxEVENT* currentEvent);
};

#endif
