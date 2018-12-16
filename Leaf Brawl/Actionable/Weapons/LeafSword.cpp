//
//  LeafSword.cpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-15.
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

#include "LeafSword.h"
#include "Entity.h"

LeafSword::LeafSword() : Weapon((orxSTRING)"LeafBlade") {
	dmg = 20;
	orxEvent_AddHandler(orxEVENT_TYPE_ANIM, LeafSword::AnimListener);
}

void LeafSword::setDirection(InputState direction) {
	orxObject_SetFlip(entity, direction == LEFT, orxFALSE);
	Weapon::setDirection(direction);
}

int LeafSword::getDmg() {
	return dmg * wielder->getStr() / 6;
}

void LeafSword::swing(InputState direction) {
	isSwinging = orxTRUE;
	orxObject_SetTargetAnim(entity, "Swinging");
	if (inContact) {
		contact(inContact);
	}
}

void LeafSword::contact(Entity *entity) {
	inContact = entity;
	if (isSwinging) {
		Weapon::contact(entity);
	}
}

void LeafSword::leaveContact() {
	inContact = nullptr;
}

orxSTATUS LeafSword::AnimListener(const orxEVENT *currentEvent) {
	if (currentEvent->eID == orxANIM_EVENT_STOP) {
		orxOBJECT *obj = (orxOBJECT*)currentEvent->hRecipient;
		LeafSword *sword = (LeafSword*)orxObject_GetUserData(obj);
		sword->isSwinging = orxFALSE;
	}
	return orxSTATUS_SUCCESS;
}
