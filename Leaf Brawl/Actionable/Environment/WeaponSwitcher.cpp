//
//  WeaponSwitcher.cpp
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

#include "WeaponSwitcher.h"
#include "Player.h"

WeaponSwitcher::WeaponSwitcher(orxVECTOR pos) {
	entity = orxObject_CreateFromConfig("WeaponSwitcher");
	orxObject_SetPosition(entity, &pos);
	orxObject_SetUserData(entity, this);

	poisonIvy = new PoisonIvy();
	leafSword = new LeafSword();
	peat = new Peat();
	
	poisonIvy->setEnabled(orxFALSE);
	leafSword->setEnabled(orxFALSE);
	peat->setEnabled(orxFALSE);

	equipped = -1;
}

void WeaponSwitcher::action(Player *player) {
	equipped = (equipped + 1) % 3;
	poisonIvy->setEnabled(orxFALSE);
	leafSword->setEnabled(orxFALSE);
	peat->setEnabled(orxFALSE);
	switch (equipped) {
		case 0:
			poisonIvy->setEnabled(orxTRUE);
			player->wieldWeapon(poisonIvy);
			break;
		case 1:
			leafSword->setEnabled(orxTRUE);
			player->wieldWeapon(leafSword);
			break;
		case 2:
			peat->setEnabled(orxTRUE);
			player->wieldWeapon(peat);
			break;
		default:
			break;
	}
}
