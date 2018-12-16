//
//  Spore.cpp
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

#include "Spore.h"
#include "Entity.h"

Spore::Spore(int dmg, orxVECTOR pos, int xForce) : Weapon((orxSTRING)"Spore") {
	this->dmg = dmg;
	orxObject_SetPosition(entity, &pos);
	orxBODY *body = (orxBODY*)_orxObject_GetStructure(entity, orxSTRUCTURE_ID_BODY);
	orxVECTOR firepower = Entity::createVector(xForce, 0, 0);
	orxBody_ApplyForce(body, &firepower, orxNULL);
}

orxBOOL Spore::didImpact() {
	return impacted;
}

void Spore::contact(Entity *entity) {
	Weapon::contact(entity);
	impacted = orxTRUE;
	orxObject_SetLifeTime(this->entity, 0);
}
