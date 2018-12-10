//
//  Entity.hpp
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2017-12-09.
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

class Entity {
protected:
	const int motionSpeed = 60;

	int hp;

	orxVECTOR pos;
	orxOBJECT* entity;
	
	static orxVECTOR createVector(orxFLOAT x, orxFLOAT y, orxFLOAT z);
public:
	int getHP();
	orxVECTOR getPosition();
	orxOBJECT* getEntity();
};

#endif