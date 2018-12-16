//
//  Peat.cpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-16.
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

#include "Peat.h"

Peat::Peat() : Weapon((orxSTRING)"Peat") {
	dmg = 5;
}

void Peat::setDirection(InputState direction) {
	for (int i = 0; i < spores.size();) {
		if (spores[i]->didImpact()) {
			delete spores[i];
			spores.erase(spores.begin() + i);
		} else {
			i++;
		}
	}
	orxObject_SetFlip(entity, direction == LEFT, orxFALSE);
	Weapon::setDirection(direction);
}

void Peat::contact(Entity *entity) {}

void Peat::swing(InputState direction) {
	orxVECTOR pos;
	orxObject_GetPosition(entity, &pos);
	int xForce = direction == LEFT ? -50 : 50;
	pos.fX += xForce;
	spores.push_back(new Spore(dmg, pos, xForce * 4));
}
