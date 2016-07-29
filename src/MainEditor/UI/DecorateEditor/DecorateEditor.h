
#ifndef __DECORATE_EDITOR_H__
#define __DECORATE_EDITOR_H__

#include "UI/Browser/BrowserWindow.h"
#include "General/ListenerAnnouncer.h"
#include "Archive/Archive.h"

class Archive;

class DecorateEditor : public wxPanel, Listener
{
private:
	Archive*					archive;

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

#endif//__DECORATE_EDITOR_H__
