//
//  Player.cpp
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

#include "Player.h"

void Player::update(bool left, bool right, float dt) {
	orxObject_GetPosition(entity, &pos);
	InputState newInput = computeState(left, right);
	switch (newInput) {
		case LEFT:
			pos.fX -= motionSpeed * dt;
			break;
		case RIGHT:
			pos.fX += motionSpeed * dt;
			break;
		case BOTH:
			switch (inputState) {
				case LEFT:
					break;
				case RIGHT:
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	orxObject_SetPosition(entity, &pos);
	inputState = newInput;
}

InputState Player::computeState(bool left, bool right) {
	InputState state = NONE;
	if (left) {
		state = (InputState)(state | LEFT);
	}
	if (right) {
		state = (InputState)(state | RIGHT);
	}
	return state;
}

InputState Player::getInputState() {
	return inputState;
}
