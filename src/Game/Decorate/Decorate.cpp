
/*******************************************************************
 * SLADE - It's a Doom Editor
 * Copyright (C) 2008-2014 Simon Judd
 *
 * Email:       sirjuddington@gmail.com
 * Web:         http://slade.mancubus.net
 * Filename:    Decorate.cpp
 * Description: DECORATE utilities
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *******************************************************************/


/*******************************************************************
 * INCLUDES
 *******************************************************************/
#include "Main.h"
#include "Decorate.h"

/*******************************************************************
 * DECORATEACTOR CLASS FUNCTIONS
 *******************************************************************/
DecorateActor::DecorateActor()
{
	
}

DecorateActor::~DecorateActor()
{
	
}

string DecorateActor::getName()
{
	return name;
}

void DecorateActor::setName(string value)
{
	name = value;
}

/*******************************************************************
 * DECORATE CLASS FUNCTIONS
 *******************************************************************/

/* Decorate::getActorByIndex
 * Returns the DecorateActor at [index]
 *******************************************************************/
DecorateActor* Decorate::getActorByIndex(unsigned index)
{
	// Check index
	if (index > actors.size())
		return NULL;
	
	return actors[index];
}

/* Decorate::onAnnouncement
 * Handles any announcements
 *******************************************************************/
void Decorate::onAnnouncement(Announcer* announcer, string event_name, MemChunk& event_data)
{
	return;
}
