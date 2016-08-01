
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
 * DECORATEACTORLIST CLASS FUNCTIONS
 *******************************************************************/

/* DecorateActorList::DecorateActorList
 * DecorateActorList class constructor
 *******************************************************************/
DecorateActorList::DecorateActorList(wxWindow* parent, vector<tt_t>* actor_list) : VirtualListView(parent)
{
	// Init variables
	this->actor_list = actor_list;
	
	// Add columns
	InsertColumn(0, "Name");
	
	// Update
	updateList();
}

/* DecorateActorList::~DecorateActorList
 * DecorateActorList class destructor
 *******************************************************************/
DecorateActorList::~DecorateActorList()
{
}

/* TextureXListView::getItemText
 * Returns the string for [item] at [column]
 *******************************************************************/
string DecorateActorList::getItemText(long item, long column, long index) const
{
	// Check texture list exists
	if (!actor_list)
		return "INVALID INDEX";
	
	// Check index is ok
	if (index < 0 || (unsigned)index > actor_list->size())
		return "INVALID INDEX";
	
	// Get associated texture
	ThingType* actor = theGameConfiguration->thingType(index);
	
	if (column == 0)						// Name column
		return actor->getName();
	else
		return "INVALID COLUMN";
}

/* DecorateActorList::updateList
 * Clears the list if [clear] is true, and refreshes it
 *******************************************************************/
void DecorateActorList::updateList(bool clear)
{
	if (clear)
		ClearAll();
	
	// Set list size
	items.clear();
	if (actor_list)
	{
		unsigned count = actor_list->size();
		SetItemCount(count);
		for (unsigned a = 0; a < count; a++)
			items.push_back(a);
	}
	else
		SetItemCount(0);
	
	sortItems();
	updateWidth();
	Refresh();
}

/*******************************************************************
 * DECORATESTATELIST CLASS FUNCTIONS
 *******************************************************************/

/* DecorateStateList::DecorateStateList
 * DecorateStateList class constructor
 *******************************************************************/
DecorateStateList::DecorateStateList(wxWindow* parent, vector<string>* state_list) : VirtualListView(parent)
{
	// Init variables
	this->state_list = state_list;
	
	// Add columns
	InsertColumn(0, "Name");
	
	// Update
	updateList();
}

/* DecorateStateList::~DecorateStateList
 * DecorateStateList class destructor
 *******************************************************************/
DecorateStateList::~DecorateStateList()
{
}

/* DecorateStateList::getItemText
 * Returns the string for [item] at [column]
 *******************************************************************/
string DecorateStateList::getItemText(long item, long column, long index) const
{
	// Check texture list exists
	if (!state_list)
		return "INVALID INDEX";
	
	// Check index is ok
	if (index < 0 || (unsigned)index > state_list->size())
		return "INVALID INDEX";
	
	if (column == 0)						// Name column
		return state_list->at(index);
	else
		return "INVALID COLUMN";
}

/* DecorateStateList::updateList
 * Clears the list if [clear] is true, and refreshes it
 *******************************************************************/
void DecorateStateList::updateList(bool clear)
{
	if (clear)
		ClearAll();
	
	// Set list size
	items.clear();
	if (state_list)
	{
		unsigned count = state_list->size();
		SetItemCount(count);
		for (unsigned a = 0; a < count; a++)
			items.push_back(a);
	}
	else
		SetItemCount(0);
	
	sortItems();
	updateWidth();
	Refresh();
}

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
	
	theGameConfiguration->parseDecorateDefs(theArchiveManager->baseResourceArchive());
	theGameConfiguration->parseDecorateDefs(archive);
	actor_list = theGameConfiguration->allThingTypes();
	
	wxStaticBox* frame = new wxStaticBox(this, -1, "Actor List");
	wxStaticBoxSizer* framesizer = new wxStaticBoxSizer(frame, wxVERTICAL);
	actor_list_view = new DecorateActorList(this, &actor_list);
	framesizer->Add(actor_list_view, 1, wxEXPAND|wxALL, 4);
	mainSizer->Add(framesizer, 0, wxEXPAND|wxALL, 4);
	
	// Create preview area
	wxBoxSizer* actorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBox* preview_frame = new wxStaticBox(this, -1, "Preview");
	wxStaticBoxSizer* preview_frame_sizer = new wxStaticBoxSizer(preview_frame, wxVERTICAL);
	sprite_canvas = new GfxCanvas(this, -1);
	sprite_canvas->setViewType(0);
	preview_frame_sizer->Add(sprite_canvas, 1, wxEXPAND|wxALL, 4);
	actorSizer->Add(preview_frame_sizer, 1, wxEXPAND|wxALL, 4);
	
	// Create STATE list
	wxStaticBox* state_frame = new wxStaticBox(this, -1, "State List");
	wxStaticBoxSizer* state_framesizer = new wxStaticBoxSizer(state_frame, wxVERTICAL);
	state_list_view = new DecorateStateList(this, NULL);
	state_framesizer->Add(state_list_view, 1, wxEXPAND|wxALL, 4);
	actorSizer->Add(state_framesizer, 0, wxEXPAND|wxALL, 4);
	
	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	leftSizer->Add(actorSizer, 1, wxEXPAND|wxALL, 0);
	
	// Create text area
	wxStaticBox* button_frame = new wxStaticBox(this, -1, "Actions");
	wxStaticBoxSizer* button_frame_sizer = new wxStaticBoxSizer(button_frame, wxHORIZONTAL);
	wxButton* btn_open_text = new wxButton(this, -1, "Edit as Text");
	button_frame_sizer->Add(btn_open_text,0,NULL,4);
	leftSizer->Add(button_frame_sizer, 0, NULL, 4);
	
	mainSizer->Add(leftSizer, 1, wxEXPAND);
}

/* DecorateEditor::~DecorateEditor
 * DecorateEditor class destructor
 *******************************************************************/
DecorateEditor::~DecorateEditor()
{

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
