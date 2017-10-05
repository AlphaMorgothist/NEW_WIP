#pragma once
#include "Critter.h"



class Rooms {
public:
	Rooms();
	vector<Creature*> *m_Encounters;
	void Combat(vector<Creature*> &mobs, Player *me );
	void Play(Player *me);
	string RandRoom();
	string m_RoomType;
	int m_Type;
	bool m_Visited = false;
	Rooms* m_pBack;
	Rooms* m_pNext;
	//inventory etc
};

class World {
public:
	friend Rooms;
	World();
	void NextRoom();
	void LastRoom();
	void Play();
private:
	Rooms* m_pCurrent;
	
};





