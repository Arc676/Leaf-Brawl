//
//  Enemy.cpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-13.
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

#include "Enemy.h"

Enemy::Enemy(LeafStyle style) : Entity() {
	entity = orxObject_CreateFromConfig("Enemy");
	orxObject_SetUserData(entity, this);
	setStyle(style);
}

void Enemy::update(Player *player, float dt) {
	orxObject_GetPosition(entity, &pos);
	orxVECTOR ppos = player->getPosition();
	float dx = ppos.fX - pos.fX;
	InputState dir = dx > 0 ? RIGHT : LEFT;
	if (dx > 50) {
		pos.fX += motionSpeed * dt;
	} else if (dx < -50) {
		pos.fX -= motionSpeed * dt;
	}
	if (orxMath_Abs(dx) < 10) {
		weapon->swing(dir);
	}
	orxObject_SetPosition(entity, &pos);
}
