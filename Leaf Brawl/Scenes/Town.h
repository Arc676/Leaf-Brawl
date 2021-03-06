//
//  Town.h
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

#ifndef Town_h
#define Town_h

#include <vector>

#include "Scene.h"

#include "Enemy.h"

#include "Elevator.h"
#include "StyleChanger.h"
#include "PlayerIO.h"
#include "SceneTransition.h"

class Town : public Scene {
	SceneTransition *toCombat;

	Enemy *playerOpp = nullptr;
	std::vector<Enemy*> stakeFighers;
public:
	Town(Player *player, orxCAMERA *camera);

	virtual SceneType update(const orxCLOCK_INFO* clockInfo, void* context);
	virtual orxSTATUS EventHandler(const orxEVENT* currentEvent);

	virtual void activate();

	Enemy* getOpponent();
};

#endif
