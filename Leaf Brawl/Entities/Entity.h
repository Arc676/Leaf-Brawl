//
//  Entity.h
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

#ifndef Entity_h
#define Entity_h

#include "orx.h"

#include "Enums.h"
#include "Weapon.h"

class Entity {
protected:
	const int motionSpeed = 200;

	LeafStyle style = HORNBEAM;

	int hp;
	orxVECTOR jumpForce;

	Weapon *weapon = nullptr;

	int str = 10;
	int def = 10;

	orxVECTOR pos;
	orxOBJECT *entity;
	orxBODY *body;

	Entity();
	Entity(orxSTRING configName);

	void setStyle(LeafStyle style);
public:
	static orxVECTOR createVector(orxFLOAT x, orxFLOAT y, orxFLOAT z);

	void takeDamage(int dmg);
	int getHP();

	void die();
	void despawn();

	int getStr();
	int getDef();

	void wieldWeapon(Weapon *weapon);

	orxVECTOR getPosition();
	void setPosition(orxVECTOR newpos);

	static orxSTRING styleToName(LeafStyle style);
	LeafStyle getStyle();
	void cycleStyle();

	orxOBJECT* getEntity();
};

#endif
