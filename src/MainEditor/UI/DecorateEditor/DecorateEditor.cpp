
/*******************************************************************
 * SLADE - It's a Doom Editor
 * Copyright (C) 2008-2014 Simon Judd
 *
 * Email:       sirjuddington@gmail.com
 * Web:         http://slade.mancubus.net
 * Filename:    DecorateEditor.cpp
 * Description: A specialisation of the Browser class for browsing
 *              the contents of a patch table. Splits the patches
 *              into three categories - Base, Archive and Unknown
 *              for patches existing in the base resource, the
 *              current archive, and entries not found, respectively
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

/*******************************************************************
 * DECORATEEDITOR CLASS FUNCTIONS
 *******************************************************************/

/* DecorateEditor::DecorateEditor
 * DecorateEditor class constructor
 *******************************************************************/
DecorateEditor::DecorateEditor(wxWindow* parent) : wxPanel(parent, -1)
{
	SetName("decorate");
	this->archive = NULL;
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
