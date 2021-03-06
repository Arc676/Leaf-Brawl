//
//  Player.cpp
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

#include "Player.h"

Player::Player() : Entity((orxSTRING)"Player") {
	orxInput_Load(orxSTRING_EMPTY);
}

void Player::update(bool left, bool right, float dt) {
	orxObject_GetPosition(entity, &pos);
	InputState newInput = computeState(left, right);
	switch (newInput) {
		case LEFT:
			pos.fX -= motionSpeed * dt;
			if (weapon) {
				weapon->setDirection(LEFT);
			}
			break;
		case RIGHT:
			pos.fX += motionSpeed * dt;
			if (weapon) {
				weapon->setDirection(RIGHT);
			}
			break;
		case BOTH:
			switch (inputState) {
				case LEFT:
				case RIGHT:
					if (weapon) {
						weapon->swing(inputState);
					}
					break;
				case NONE:
					if (currentActionable) {
						currentActionable->action(this);
					} else {
						orxBody_ApplyForce(body, &jumpForce, orxNULL);
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	orxObject_SetPosition(entity, &pos);
	if (weapon) {
		weapon->setPosition(pos);
	}
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

void Player::approachActionable(Actionable *act) {
	currentActionable = act;
}

void Player::leaveActionable() {
	currentActionable = nullptr;
}

orxSTATUS Player::read() {
	if (!orxConfig_HasSection("PlayerData")) {
		orxConfig_Load(orxFile_GetApplicationSaveDirectory("LeafBrawl/SaveData"));
	}
	if (orxConfig_HasSection("PlayerData") && orxConfig_PushSection("PlayerData")) {
		hp = orxConfig_GetU32("HP");
		str = orxConfig_GetU32("Str");
		def = orxConfig_GetU32("Def");
		gold = orxConfig_GetU32("Gold");
		style = (LeafStyle)orxConfig_GetU32("Style");
		setStyle(style);

		orxConfig_ClearSection("PlayerData");
		return orxSTATUS_SUCCESS;
	}
	return orxSTATUS_FAILURE;
}

orxSTATUS Player::write() {
	if (orxConfig_PushSection("PlayerData")) {
		orxConfig_SetU32("HP", hp);
		orxConfig_SetU32("Str", str);
		orxConfig_SetU32("Def", def);
		orxConfig_SetU32("Gold", gold);
		orxConfig_SetU32("Style", style);

		orxConfig_PopSection();
		return orxConfig_Save(orxFile_GetApplicationSaveDirectory("LeafBrawl/SaveData"), orxFALSE, sectionFilter);
	}
	return orxSTATUS_FAILURE;
}

orxBOOL Player::sectionFilter(const orxSTRING _zSectionName, const orxSTRING _zKeyName, const orxSTRING _zFileName, orxBOOL _bUseEncryption) {
	return orxString_Compare(_zSectionName, "PlayerData") == 0;
}
