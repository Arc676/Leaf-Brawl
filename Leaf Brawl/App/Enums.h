//
//  Enums.h
//  Leaf Brawl
//
//  Created by Alessandro Vinciguerra on 2018-12-12.
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

#ifndef Enums_h
#define Enums_h

enum SceneType {
	TOWN, COMBAT
};

enum LeafStyle : int {
	MAPLE,
	HORNBEAM,
	CHESTNUT,
	WILLOW,
	DEAD
};

enum InputState : int {
	NONE  = 0b00,
	LEFT  = 0b01,
	RIGHT = 0b10,
	BOTH  = 0b11
};

#endif
