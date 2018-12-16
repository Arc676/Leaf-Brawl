//
//  Entity.cpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-09.
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

#include "Entity.h"

Entity::Entity() {
	hp = 100;
	jumpForce = createVector(0, -250, 0);
}

void Entity::die() {
	setStyle(DEAD);
}

void Entity::despawn() {
	orxObject_SetLifeTime(entity, 0);
}

orxVECTOR Entity::createVector(orxFLOAT x, orxFLOAT y, orxFLOAT z) {
	orxVECTOR vector;
	vector.fX = x;
	vector.fY = y;
	vector.fZ = z;
	return vector;
}

void Entity::takeDamage(int dmg) {
	hp -= dmg;
	if (hp <= 0) {
		die();
	}
}

int Entity::getHP() {
	return hp;
}

int Entity::getStr() {
	return str;
}

int Entity::getDef() {
	return def;
}

orxVECTOR Entity::getPosition() {
	return pos;
}

void Entity::setPosition(orxVECTOR newpos) {
	orxVector_Copy(&pos, &newpos);
	orxObject_SetPosition(entity, &pos);
}

orxOBJECT* Entity::getEntity() {
	return entity;
}

void Entity::wieldWeapon(Weapon *weapon) {
	this->weapon = weapon;
	weapon->setWielder(this);
}

LeafStyle Entity::getStyle() {
	return style;
}

void Entity::cycleStyle() {
	LeafStyle newStyle = (LeafStyle)((style + 1) % (WILLOW + 1));
	setStyle(newStyle);
}

void Entity::setStyle(LeafStyle style) {
	this->style = style;
	orxObject_SetTargetAnim(entity, Entity::styleToName(style));
}

orxSTRING Entity::styleToName(LeafStyle style) {
	switch (style) {
		case MAPLE:
			return (orxSTRING)"Maple";
		case HORNBEAM:
			return (orxSTRING)"Hornbeam";
		case CHESTNUT:
			return (orxSTRING)"Chestnut";
		case WILLOW:
			return (orxSTRING)"Willow";
		default:
			return (orxSTRING)"Dead";
	}
}
