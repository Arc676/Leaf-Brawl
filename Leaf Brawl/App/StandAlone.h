//
//  StandAlone.h
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

#ifndef StandAlone_h
#define StandAlone_h

#include "orx.h"

#include "Town.h"
#include "Combat.h"

class StandAlone {
public:
	static StandAlone* Instance();

	static void paintTiles(const orxSTRING mapSection, const orxVECTOR startPos, int tilesWide);

	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();

	static void orxFASTCALL Exit();

	static void orxFASTCALL Update(const orxCLOCK_INFO*, void*);

	static orxSTATUS orxFASTCALL EventHandler(const orxEVENT*);
protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator= (const StandAlone&);
private:
	static StandAlone* m_Instance;

	static Scene *currentScene;
	static orxVIEWPORT *currentViewport;

	static Town *townScene;
	static orxVIEWPORT *townViewport;

	static Combat *combatScene;
	static orxVIEWPORT *combatViewport;

	static Player* player;
};

#endif
