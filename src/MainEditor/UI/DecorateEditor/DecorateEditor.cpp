
/*******************************************************************
 * SLADE - It's a Doom Editor
 * Copyright (C) 2008-2014 Simon Judd
 *
 * Email:       sirjuddington@gmail.com
 * Web:         http://slade.mancubus.net
 * Filename:    DecorateEditor.cpp
 * Description: The UI for the DECORATE editor
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
#include "DecorateEditor.h"
#include "Archive/ArchiveManager.h"
#include "General/Misc.h"
#include "General/ResourceManager.h"
#include "Graphics/CTexture/CTexture.h"
#include "Graphics/CTexture/TextureXList.h"
#include "Graphics/SImage/SImage.h"
#include "MainEditor/MainWindow.h"
#include "MapEditor/GameConfiguration/GameConfiguration.h"

/*******************************************************************
 * DECORATEEDITOR CLASS FUNCTIONS
 *******************************************************************/

/* DecorateEditor::DecorateEditor
 * DecorateEditor class constructor
 *******************************************************************/
DecorateEditor::DecorateEditor(wxWindow* parent, Archive* archive) : wxPanel(parent, -1)
{
	SetName("decorate");
	this->archive = archive;
	
	// Main Sizer
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	SetSizer(mainSizer);
	
	// Create preview area
	wxBoxSizer* actorSizer = new wxBoxSizer(wxHORIZONTAL);
	sprite_canvas = new GfxCanvas(this, 0);
	actorSizer->Add(sprite_canvas, 1, wxEXPAND, 0);
	
	// Create STATE list
	list_states = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	actorSizer->Add(list_states, 1, wxSTRETCH_NOT, 0);
	
	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
										
	leftSizer->Add(actorSizer, 1, wxEXPAND, 0);
	
	// Create text area
	decorate_text_area = new TextEditor(this, -1);
	leftSizer->Add(decorate_text_area, 1, wxEXPAND, 0);
	
	mainSizer->Add(leftSizer, 1, wxEXPAND);
	
	// Create ACTOR list
	list_actors = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	initializeActorList();
	mainSizer->Add(list_actors, 1, wxEXPAND);
}

/* DecorateEditor::~DecorateEditor
 * DecorateEditor class destructor
 *******************************************************************/
DecorateEditor::~DecorateEditor()
{

}

void DecorateEditor::initializeActorList()
{
	wxListItem col;
	col.SetId(0);
	col.SetText("Actor List");
	col.SetWidth(200);
	list_actors->InsertColumn(0, col);
	
	// Read DECORATE definitions if any
	theGameConfiguration->parseDecorateDefs(theArchiveManager->baseResourceArchive());
	
	theGameConfiguration->parseDecorateDefs(archive);
	
	unsigned nThingTypes = theGameConfiguration->allThingTypes().size();
	
	for (unsigned i = 0; i < nThingTypes; i++) {
		ThingType* tt = theGameConfiguration->thingType(i);
		addActor(i, tt->getName());
	}
}

void DecorateEditor::addActor(long id, string name)
{
	wxListItem new_item;
	new_item.SetText(name);
	new_item.SetId(id);
	list_actors->InsertItem(new_item);
}

bool DecorateEditor::openArchive(Archive* archive)
{
	return true;
}

void DecorateEditor::setSelection(size_t index)
{
	return;
}

void DecorateEditor::setSelection(ArchiveEntry* entry)
{
	return;
}

/* PatchBrowser::onAnnouncement
 * Handles any announcements
 *******************************************************************/
void DecorateEditor::onAnnouncement(Announcer* announcer, string event_name, MemChunk& event_data)
{
	return;
}
