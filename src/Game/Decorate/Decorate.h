
#ifndef __DECORATE_H__
#define __DECORATE_H__

#include "General/ListenerAnnouncer.h"

class DecorateActor
{
private:
	string name;
public:
	DecorateActor();
	~DecorateActor();
	
	string		getName();
	void		setName(string name);
};

class Decorate
{
private:
	vector<DecorateActor*>		actors;
	
public:
	unsigned			nActors() { return actors.size(); }
	DecorateActor*		getActorByIndex(unsigned index);
	
	// Events
	void	onAnnouncement(Announcer* announcer, string event_name, MemChunk& event_data);
};

#endif//__DECORATE_H__
