//
//  Weapon.cpp
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

#include "Weapon.h"
#include "Entity.h"

Weapon::Weapon(orxSTRING name) {
	entity = orxObject_CreateFromConfig(name);
	orxObject_SetUserData(entity, this);
}

void Weapon::contact(Entity *entity) {
	int dealt = dmg;
	if (orxMath_GetRandomS32(0, 99) < 50) {
		dealt *= 2;
	}
	entity->takeDamage(dealt);
}

int Weapon::getDmg() {
	return dmg;
}

void Weapon::swing(InputState direction) {}

void Weapon::setPosition(orxVECTOR pos) {
	pos.fZ = -0.01;
	orxObject_SetPosition(entity, &pos);
}

void Weapon::setWielder(Entity *entity) {
	wielder = entity;
}
