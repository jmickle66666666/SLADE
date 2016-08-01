
#ifndef __DECORATE_EDITOR_H__
#define __DECORATE_EDITOR_H__

#include "UI/Browser/BrowserWindow.h"
#include "General/ListenerAnnouncer.h"
#include "Archive/Archive.h"
#include "UI/TextEditor/TextEditor.h"
#include "UI/Lists/VirtualListView.h"
#include "MapEditor/GameConfiguration/GameConfiguration.h"
#include "UI/Canvas/GfxCanvas.h"

class Archive;

class DecorateActorList : public VirtualListView
{
private:
	vector<tt_t>*	actor_list;
protected:
	string	getItemText(long item, long column, long index) const;
public:
	DecorateActorList(wxWindow* parent, vector<tt_t>* actor_list);
	~DecorateActorList();
	void			updateList(bool clear = false);
};

class DecorateStateList : public VirtualListView
{
private:
	vector<string>*	state_list;
protected:
	string	getItemText(long item, long column, long index) const;
public:
	DecorateStateList(wxWindow* parent, vector<string>* state_list);
	~DecorateStateList();
	void			updateList(bool clear = false);
};

class DecorateEditor : public wxPanel, Listener
{
private:
	vector<tt_t>				actor_list;
	Archive*					archive;
	TextEditor*					decorate_text_area;
	DecorateActorList*			actor_list_view;
	DecorateStateList*			state_list_view;
	GfxCanvas*			sprite_canvas;

public:
	DecorateEditor(wxWindow* parent,Archive* archive);
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
