//
//  Player.h
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

#ifndef Player_h
#define Player_h

#include "Entity.h"
#include "Actionable.h"

class Player : public Entity {
	InputState inputState;
	
	int gold = 0;

	Actionable* currentActionable = nullptr;

	InputState computeState(bool left, bool right);
	
	static orxBOOL sectionFilter(const orxSTRING, const orxSTRING, const orxSTRING, orxBOOL);
public:
	Player();

	orxSTATUS read();
	orxSTATUS write();

	void update(bool left, bool right, float dt);
	InputState getInputState();

	void approachActionable(Actionable* act);
	void leaveActionable();
};

#endif
