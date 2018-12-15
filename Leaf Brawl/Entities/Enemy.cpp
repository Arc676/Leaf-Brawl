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

Enemy::Enemy() {}

Enemy::Enemy(LeafStyle style) : Entity() {
	entity = orxObject_CreateFromConfig("Enemy");
	orxObject_SetUserData(entity, this);
	setStyle(style);
}

void Enemy::update(Player *player, float dt) {
	if (hp <= 0) {
		return;
	}
	orxObject_GetPosition(entity, &pos);
	orxVECTOR ppos = player->getPosition();
	float dx = ppos.fX - pos.fX;
	if (dx > 50) {
		pos.fX += motionSpeed * dt;
	} else if (dx < -50) {
		pos.fX -= motionSpeed * dt;
	}
	if (orxMath_Abs(dx) < 10) {
		weapon->swing(dx > 0 ? RIGHT : LEFT);
	}
	orxObject_SetPosition(entity, &pos);
}

Enemy* Enemy::createRandomEnemy(Entity *opponent, bool isVirtual) {
	Enemy *e = isVirtual ? new Enemy() : new Enemy((LeafStyle)orxMath_GetRandomS32(MAPLE, WILLOW));
	e->str += orxMath_GetRandomS32(-5, 5);
	e->def += orxMath_GetRandomS32(-5, 5);
	if (opponent) {
		e->str += opponent->getStr();
		e->def += opponent->getDef();
	}
	return e;
}
