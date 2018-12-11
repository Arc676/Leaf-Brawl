//
//  Player.h
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

#ifndef Player_h
#define Player_h

#include "Entity.h"
#include "Actionable.h"

enum InputState : int {
	NONE  = 0b00,
	LEFT  = 0b01,
	RIGHT = 0b10,
	BOTH  = 0b11
};

enum PlayerStyle {
	MAPLE,
	HORNBEAM,
	CHESTNUT,
	WILLOW
};

class Player : public Entity {
	PlayerStyle style = HORNBEAM;

	InputState inputState;

	Actionable* currentActionable = nullptr;

	InputState computeState(bool left, bool right);
public:
	Player();

	void update(bool left, bool right, float dt);
	InputState getInputState();

	PlayerStyle getStyle();

	void approachActionable(Actionable* act);
	void leaveActionable();
};

#endif
