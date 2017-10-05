#include "stdafx.h"
#include "world.h"
#include <algorithm>



int randNum(Player *player) {
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist1{ 5.0, player->GetXP() + 10 };
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
		cout << "\nYou see a couple of demons wrestling in the near vicinity. They turn to look at you" << endl;
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
			cout << "\nThe creatures in this room can be controlled by your class. \nWould you like to subjugate them, or battle them to train your existing monsters?" << endl;
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
		cout << "\nEnemies:" << endl;
		CFlav("red");
		for (iter = mobs.begin(); iter < mobs.end(); iter++) {
			CFlav("red");
			cout << (*iter)->GetName();
			CFlav("reset");
			cout << "'s HP: " << (*iter)->GetHealth() << endl;
		}
		CFlav("reset");
		cout << endl;
		//Player creature attack
		if (!mobs.empty() && !me->GetMonsters()->empty()) {
			cout << endl;
			cout << "\n\t\tYour turn: " << endl;
			cout << "***********************************************\n" << endl;
			for (iter = me->GetMonsters()->begin(); iter < me->GetMonsters()->end(); iter++)
			{
				(*iter)->PassTime();
				int choice;
				for (iter2 = mobs.begin(); iter2 < mobs.end(); iter2++)
				{
					if (iter == me->GetMonsters()->begin()) {
						cout << endl;
						CFlav("blue");
						cout << (*iter)->GetName();
						CFlav("reset");
						cout << "'s attack on ";
						CFlav("red");
						cout << (*iter2)->GetName();
						CFlav("reset");
						cout << ":" << endl;
						(*iter)->DisplayAttacks();
						cout << "\nChoice: ";
						while (true) {
							cin >> choice;
							if (choice > 0 && choice < 3)break;
							else cout << "Invalid choice. Try again:";
						}
						system("CLS");
						cout << "\n\t\tYour attacks:" << endl;
						cout << "***********************************************\n" << endl;
					}
					else { choice = 1; }
					switch (choice) {
					case 1: {if ((*iter2)->IsHitBy(**iter)) {
						(*iter)->Attack(*iter2);
						if (!(*iter2)->IsLiving()) {

							//Enemy Deletion
							mobs.erase(iter2);
							(*iter)->Training();
							(*iter)->SpecialRecharge();
							cout << "Your creature has consumed the soul of his defeated enemy, and has regained the use of special attacks" << endl;
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
					Sleep(900);
				}Sleep(900);
			}
		}

		//Mob attack
		if (!mobs.empty() && !me->GetMonsters()->empty()) {
			cout << "\n\t\tMonster attacks: " << endl;
			cout << "***********************************************" << endl;
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
					Sleep(900);
				}	Sleep(920);
			}
		}
		cout << endl;
		Sleep(4000);
		system("CLS");
		cout << "\nEnemies:" << endl;
		for (iter = mobs.begin(); iter < mobs.end(); iter++) {
			CFlav("red");
			cout << (*iter)->GetName();
			CFlav("reset");
			cout << "'s HP: " << (*iter)->GetHealth() << endl;
		}
		cout << endl;
		cout << "\nFriendly Monsters:" << endl;
		for (iter = me->GetMonsters()->begin(); iter < me->GetMonsters()->end(); iter++) {
			CFlav("blue");
			cout << (*iter)->GetName();
			CFlav("reset");
			cout << "'s HP: " << (*iter)->GetHealth() << endl;
		}
		cout << endl;
		system("pause");
		system("CLS");
	} 
}

void Rooms::Play(Player *me)
{
	//Room Flavour
	cout << m_RoomType << endl;
	//Combat check
	if (!m_Encounters->empty()) {
		Combat(*m_Encounters, me);
	}
	if (!me->GetMonsters()->empty()) {
		cout << "[Room Clear]" << endl;
		//Room Number
		cout << "\nCurrent Room XP: " << me->GetXP() << endl;

		//Creature care menu
		cout << "\nWould you like to take this time to inspect your creatures?(y/n)" << endl;
		char resp;
		cout << "Choice:";
		cin >> resp;
		if (resp == 'y' || resp == 'Y') {
			vector<Creature*>::iterator iter;
			for (iter = me->GetMonsters()->begin(); iter < me->GetMonsters()->end(); iter++) {
				//CURRENT WIP
				CFlav("blue");
				cout << (*iter)->GetName();
				CFlav("reset");
				cout << "\tHP:" << (*iter)->GetHealth() << " DAM:" << (*iter)->GetDam() << " DODGE:" << (*iter)->GetDodge() << " INITIATIVE:" << (*iter)->GetInit() << endl;
			}
			for (iter = me->GetMonsters()->begin(); iter < me->GetMonsters()->end(); iter++) {
				int tempN;
				while (true) {
					cout << "\nCreature: " << (*iter)->GetName() << endl;
					cout << "Options:" << endl;
					cout << "\t1:Make it eat the food it's carrying (if any)" << endl;
					cout << "\t2:Communicate with it" << endl;
					cout << "\t0:Next Creature/End" << endl;
					cout << "\nChoice: ";
					cin >> tempN;
					system("CLS");
					switch (tempN)
					{
					case 0: {break; }break;
					case 1: {(*iter)->Feed(); }break;
					case 2: {(*iter)->Talk(); }break;
					}
					if (tempN == 0)break;
				}
			}
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
	int chance = rand() % 7 + 1;
	switch (chance) {
	case 1: {
		string room = "You stand in the Necropolis. The city of the dead.\nYou feel 1000 piercing eyes staring at you yet cannot see a soul.";
		return room;
	}break;
	case 2: {
		string room = "You stand in a blazing inferno\nThe walls are engulfed in flames, and there is only one way out.\nDirectly forward";
		return room;
	}break;
	case 3: {
		string room = "You stand in the Soul Den\nThe floor is littered with wailing souls clawing for the door ahead of you.";
		return room;
	}break;
	case 4: {
		string room = "You stand in the Abyss\nDarkness surrounds you, The only light comes from the door ahead of you.";
		return room;
	}break;
	case 5: {
		string room = "You stand in a hall with walls comprised of lost souls\nThe screams of the tortured echo endlessly.";
		return room;
	}break;
	case 6: {
		string room = "You stand in the Unholy Temple\nHorrifying beasts stand in the atrium above you watching your every move";
		return room;
	}break;
	case 7: {
		string room = "You stand in a large butcher shop\nA hulking behemoth is slicing a man into chunks on a large slab in the corner";
		return room;
	}break;
	case 8: {
		string room = "You stand in a swamp filled with pieces of flesh and bone\nThe pieces are crawling and rolling toward one another.\nSlowly merging to form horrifying abominations";
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
	
	else {
		CFlav("yellow");
		cout << "\nThere is no going back" << endl;
		CFlav("reset");
	}

}
//Insert flavour for beginning of game**
void World::Play()
{
	//Inputs from player for class select and name (op)
	Player *Plyr = NULL;
	cout << "\n\t\tWelcome to DaskuG's Inferno" << endl;
	//Insert flavour for beginning of game
	cout << "\n\tClass Selection: " << endl;
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


