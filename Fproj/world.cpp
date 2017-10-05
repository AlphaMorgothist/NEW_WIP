#include "stdafx.h"
#include "world.h"
#include <algorithm>
int randNum(Player *player) {
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist1{ 0.0, player->GetXP() };
	int num = dist1(engine);
	return num;
}

//TO DO: Add a chance for an empty room that contains a win key. (Collect 6 and win)
Rooms::Rooms():
m_RoomType(RandRoom()), m_pNext(NULL), m_pBack(NULL)
{
	
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist1{ 0.0, 300.0 };
	int chance = dist1(engine);
	if (chance > 200) {
		chance = 3;
	}
	else if (chance > 100) {
		chance = 2;
	}
	else if (chance > 0) {
		chance = 1;
	}

	switch (chance) {
	case 1: {
		m_Type = 1;
		Creature *En1 = new Dragon();
		Creature *En2 = new Dragon();
		m_Encounters = new vector<Creature*>;
		m_Encounters->push_back(En1);
		m_Encounters->push_back(En2); }break;
	case 2: {
		m_Type = 2;
		Creature *En1 = new Skeleton();
		Creature *En2 = new Skeleton();
		m_Encounters = new vector<Creature*>;
		m_Encounters->push_back(En1);
		m_Encounters->push_back(En2); }break;
	case 3: {
		m_Type = 3;
		Creature *En1 = new Spirit();
		Creature *En2 = new Spirit();
		m_Encounters = new vector<Creature*>;
		m_Encounters->push_back(En1);
		m_Encounters->push_back(En2); }break;
	}
}

//TO DO: Add special attack counter and choice ability
void Rooms::Combat(vector<Creature*> &mobs, Player *me)
{
	vector<Creature*>::iterator iter;
	vector<Creature*>::iterator iter2;

	//Subjugation check
	if (m_Type == me->GetType()) {
		int choice;
		while (true) {
			cout << "\nThe creatures in this room can be controlled by your class. Would you like to subjugate them, or battle them to train\n your existing monsters?" << endl;
			cout << "\n1: Subjugate" << endl;
			cout << "2: Battle" << endl;
			cout << "\nChoice: ";
			cin >> choice;
			if (choice == 1 || choice == 2) break;
		}
		if (choice == 1) {
			for ( iter = mobs.begin(); iter < mobs.end(); iter++)
			{
				me->GetMonsters()->push_back(*iter);
				mobs.erase(iter);
			}
			for (iter = mobs.begin(); iter < mobs.end(); iter++)
			{
				me->GetMonsters()->push_back(*iter);
				mobs.erase(iter);
			}
		}
	}

	//Combat phase
	while (!mobs.empty() && !(me->GetMonsters())->empty()) {

		cout << "\nThe creatures in the room are aggressive! You enter battle:" << endl;
		//Player creature attack
		if (!mobs.empty() && !me->GetMonsters()->empty()) {
			cout << "\n\t\tYour attacks: " << endl;
			for (iter = me->GetMonsters()->begin(); iter < me->GetMonsters()->end(); iter++)
			{
				(*iter)->PassTime();
				int choice;
				for (iter2 = mobs.begin(); iter2 < mobs.end(); iter2++)
				{
					if (iter == me->GetMonsters()->begin()) {
						cout << (*iter)->GetName() << "'s attack on " << (*iter2)->GetName() << ":" << endl;
						(*iter)->DisplayAttacks();
						cout << "\nChoice: ";
						while (true) {
							cin >> choice;
							if (choice > 0 && choice < 3)break;
							else cout << "Invalid choice. Try again:";
						}
						system("CLS");
					}
					else { choice = 1; }
					switch (choice) {
					case 1: {if ((*iter2)->IsHitBy(**iter)) {
						(*iter)->Attack(*iter2);
						if (!(*iter2)->IsLiving()) {

							//Enemy Deletion
							mobs.erase(iter2);
							(*iter)->Training();
							(*iter)->GetFood(randNum(me));
							break;
						}
					}
						}break;
					case 2: {if ((*iter2)->IsHitBy(**iter)) {
						if ((*iter)->GetSpecial() > 0) {
							(*iter)->SpecialAttack(*iter2);
							(*iter)->SpecialUse();
						}
						else {
							cout << "\nSpecial uses need recharging! Normal attack engaged." << endl;
							(*iter)->Attack(*iter2);
						}
						if (!(*iter2)->IsLiving()) {

							//Enemy Deletion
							mobs.erase(iter2);
							(*iter)->Training();
							(*iter)->GetFood(randNum(me));
							break;
						}
					}
					}break;
					}
				}
			}
		}

		//Mob attack
		if (!mobs.empty() && !me->GetMonsters()->empty()) {
			cout << "\n\t\tMonster attacks: " << endl;
			for (iter = mobs.begin(); iter < mobs.end(); iter++)
			{
				for (iter2 = me->GetMonsters()->begin(); iter2 < me->GetMonsters()->end(); iter2++)
				{
					//Substitute choice for reg or special attack ***
					if (!me->GetMonsters()->empty()) {
						if ((*iter2)->IsHitBy(**iter)) {
							(*iter)->Attack(*iter2);
							if (!(*iter2)->IsLiving()) {

								//DEATH DELETION*
								(me->GetMonsters())->erase(iter2);
								break;
							}
						}
					}
					Sleep(500);
				}	Sleep(520);
			}
		}
		cout << endl;
		cout << "\nEnemies:" << endl;
		for (iter = mobs.begin(); iter < mobs.end(); iter++) {
			cout << (*iter)->GetName() << "'s HP: " << (*iter)->GetHealth() << endl;
		}
		cout << endl;
		cout << "\nFriendly Monsters:" << endl;
		for (iter = me->GetMonsters()->begin(); iter < me->GetMonsters()->end(); iter++) {
			cout << (*iter)->GetName() << "'s HP: " << (*iter)->GetHealth() << endl;
		}
		cout << endl;
		system("pause");
		system("CLS");
	} 
}

void Rooms::Play(Player *me)
{
	//Room Number
	cout << "\nCurrent Room XP: " << me->GetXP() << endl;
	//Room Flavour
	cout << m_RoomType << endl;
	//Combat check
	if (!m_Encounters->empty()) {
		Combat(*m_Encounters, me);
	}
	if (!me->GetMonsters()->empty()) {
		cout << "[Room Clear]" << endl;
		cout << "\nWould you like to take this time to inspect your creatures?(y/n)" << endl;
		char resp;
		while (true) {
			cout << "Choice:";
			cin >> resp;
			//CURRENT WIP
			if (resp == 'y' || resp == 'Y');
		}
	}
	else {
		cout << "You have failed. Your monsters are dead and you are trapped in Hell forever." << endl;
	}
	system("pause");
	if (m_Visited == false) {
		me->GiveXP();
		m_Visited = true;
	}
	else { cout << "\nYou have already visited this room" << endl; }
}

string Rooms::RandRoom()
{
		srand(time(NULL));
		int chance = rand() % 300;
		if (chance > 200) chance = 1;
		else if (chance > 100) chance = 2;
		else chance = 3;
		switch (chance) {
		case 1: {
			string room = "You enter the necropolis";
			return room;
		}break;
		case 2: {
			string room = "You enter the inferno";
			return room;
		}break;
		case 3: {
			string room = "You enter the Soul Den";
			return room;
		}break;
		}
}

World::World():
m_pCurrent(new Rooms)
{ 
}

void World::NextRoom()
{
	if (m_pCurrent->m_pNext == NULL) {
		m_pCurrent->m_pBack = m_pCurrent;
		m_pCurrent->m_pNext = new Rooms();
		m_pCurrent = m_pCurrent->m_pNext;
	}
	else { m_pCurrent = m_pCurrent->m_pNext; }
}

void World::LastRoom()
{
	if (m_pCurrent->m_pBack != NULL) {
		m_pCurrent = m_pCurrent->m_pBack;
	}
	else { cout << "\nThere is no going back" << endl; }
}
//Insert flavour for beginning of game**
void World::Play()
{
	//Inputs from player for class select and name (op)
	//Creature *tmp = new Dragon("Hitachi", 50);
	Player *Plyr = NULL;
	cout << "Welcome to DaskuG's Inferno" << endl;
	//Insert flavour for beginning of game
	cout << "\n\t\tClass Selection: " << endl;
	cout << "\n1: Demon King (commands Demons)" << endl;
	cout << "2: Necromancer (commands Skeletons)" << endl;
	cout << "3: Spectre (Commands Spirits)" << endl;
	cout << "Choice: ";
	int choice;
	while (true) {
		cin >> choice;
		if (choice > 0 && choice < 4)break;
	}
	switch (choice) {
	default: break;
	case 1: {Plyr = new DemonKing();}break;
	case 2: {Plyr = new Necromancer(); }break;
	case 3: {Plyr = new Spectre(); }break;
	}
	
	vector<Creature*> temp = *(Plyr->GetMonsters());
	while (!temp.empty()) {
		m_pCurrent->Play(Plyr);
		temp = *(Plyr->GetMonsters());
		if (!temp.empty()) {
			while (true) {
				cout << "\nThe Room is cleared, would you like to go forward, or go back? (f/b)" << endl;
				cout << "Choice (f/b): ";
				char pick;
				cin >> pick;
				system("CLS");
				if (pick == 'f' || pick == 'F') {
					NextRoom();
					break;
				}
				else if (pick == 'b' || pick == 'B') {
					LastRoom();
					break;
				}
			}
		}
	}
}


