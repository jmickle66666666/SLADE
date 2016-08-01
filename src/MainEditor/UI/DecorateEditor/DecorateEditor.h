
#ifndef __DECORATE_EDITOR_H__
#define __DECORATE_EDITOR_H__

#include "UI/Browser/BrowserWindow.h"
#include "General/ListenerAnnouncer.h"
#include "Archive/Archive.h"
#include "UI/TextEditor/TextEditor.h"
#include "UI/Lists/VirtualListView.h"
#include "MapEditor/GameConfiguration/GameConfiguration.h"

class Archive;

class DecorateEditor : public wxPanel, Listener
{
private:
	Archive*					archive;
	TextEditor*					decorate_text_area;
	wxListCtrl*			list_actors;
	wxListCtrl*			list_states;
	void				initializeActorList();
	void				addActor(long int, string name);

public:
	DecorateEditor(wxWindow* parent);
	~DecorateEditor();
	
	Archive*		getArchive() { return archive; }
	
	void	setSelection(size_t index);
	void	setSelection(ArchiveEntry* entry);
	bool	openArchive(Archive* archive);

	// Events
	void	onAnnouncement(Announcer* announcer, string event_name, MemChunk& event_data);
};

#define theGameConfiguration GameConfiguration::getInstance()
#endif//__DECORATE_EDITOR_H__
