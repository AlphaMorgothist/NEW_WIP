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
	uniform_real_distribution<double> dist1{ 0.0, 1000.0 };
	int chance = dist1(engine);
	
		if (chance > 900) {chance = 1;}
	else if (chance > 800){chance = 2;}
	else if (chance > 700){chance = 3;}
	else if (chance > 600){chance = 4;}
	else if (chance > 500){chance = 5;}
	else if (chance > 400){chance = 6;}
	else if (chance > 300){chance = 7;}
	else if (chance > 200){chance = 8;}
	else if (chance > 100){chance = 9;}
	else if (chance >= 50) { chance = 10; }
	else if (chance < 50) { chance = 11; }

	

	//ROOM GEN
		switch (chance) {
		case 1: {
			m_Type = 1;
			cout << "\nA demon stands before you. It sees you as you walk in and waits on your every move." << endl;
			cout << chance << endl;
			Creature *En1 = new Dragon();
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1); }break;
		case 2: {
			m_Type = 2;
			cout << "\nA lone skeleton shambles about the room. It looks directly at you as you walk through the door" << endl;
			Creature *En1 = new Skeleton();
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1); }break;
		case 3: {
			m_Type = 3;
			cout << "\nA lost soul floats about the chambers. It immidetly twists its head and whips towards you" << endl;
			Creature *En1 = new Spirit();
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1); }break;
		case 4: {
			m_Type = 1;
			cout << "\nThree demons stand before you, biting and clawing at one another for entertainment.\nAs you walk into the cambers they all look directly at you." << endl;
			Creature *En1 = new Dragon();
			Creature *En2 = new Dragon();
			Creature *En3 = new Dragon();
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
			m_Encounters->push_back(En2);
			m_Encounters->push_back(En3); }break;
		case 5: {
			m_Type = 2;
			cout << "\nThree skeletons shamble through the chambers, their bones clacking as they walk.\nBones crunch under your feet drawing their attention to you\nand they run towards you cackling" << endl;
			Creature *En1 = new Skeleton();
			Creature *En2 = new Skeleton();
			Creature *En3 = new Skeleton();
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
			m_Encounters->push_back(En2);
			m_Encounters->push_back(En3); }break;
		case 6: {
			m_Type = 3;
			cout << "\nThree Spectres float throughout the chambers wailing at one another.\nThey sense you as you enter and scream as they fly violently towards you." << endl;
			Creature *En1 = new Spirit();
			Creature *En2 = new Spirit();
			Creature *En3 = new Spirit();
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
			m_Encounters->push_back(En2);
			m_Encounters->push_back(En3); }break;
		case 7: {
			m_Type = 1;
			cout << "\nAn entire group of demons are roaring and attacking one another.\nAs you walk through they rage towards you with joy/nLeading the charge, The Baron himself." << endl;
			Creature *En1 = new Dragon();
			Creature *En2 = new Dragon();
			Creature *En3 = new Dragon();
			Creature *En4 = new Dragon();
			Creature *En5 = new Dragon("Baron", 40);
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
			m_Encounters->push_back(En2);
			m_Encounters->push_back(En3);
			m_Encounters->push_back(En4);
			m_Encounters->push_back(En5); }break;
		case 8: {
			m_Type = 2;
			cout << "\nA large group of skeletons are dancing in a circle in the centre of the room.\nIn the centre stands a large Skeleton with glowing green eyes.\nThe Lich" << endl;
			Creature *En1 = new Skeleton();
			Creature *En2 = new Skeleton();
			Creature *En3 = new Skeleton();
			Creature *En4 = new Skeleton();
			Creature *En5 = new Skeleton("Lich", 40);
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
			m_Encounters->push_back(En2);
			m_Encounters->push_back(En3);
			m_Encounters->push_back(En4);
			m_Encounters->push_back(En5); }break;
		case 9: {
			m_Type = 3;
			cout << "\nA group of spirits are floating throughout the chamber screaming in a horrifying song.\nYou look to the centre of the room and see a floating skeleton wrapped in royal armour.\nA Revenant." << endl;
			Creature *En1 = new Spirit();
			Creature *En2 = new Spirit();
			Creature *En3 = new Spirit();
			Creature *En4 = new Spirit();
			Creature *En5 = new Spirit("Revenant", 40);
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
			m_Encounters->push_back(En2);
			m_Encounters->push_back(En3);
			m_Encounters->push_back(En4);
			m_Encounters->push_back(En5); }break;
		case 10: {
			m_Type = 0;
			cout << "\nThe cold embrace of the abyss spreads through your veins like a thousand knives\nThe darkness encroaches as the master of this domain approaches\nDeath has found you." << endl;
			Creature *En1 = new Spirit();
			Creature *En2 = new Dragon();
			Creature *En3 = new Skeleton();
			Creature *En4 = new Spirit();
			Creature *En5 = new Spirit("Death", 66, 1000);
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
			m_Encounters->push_back(En2);
			m_Encounters->push_back(En3);
			m_Encounters->push_back(En4);
			m_Encounters->push_back(En5);
		}break;
		case 11: {
			m_Type = 0;
			cout << "A shimmering pedestal stands before you.\n A small, imp-like creature scampers around with a piece of the 'Glyph of Redemption'" << endl;
			Creature *En1 = new Creature("Glyph Imp", 0, 500, 15);
			m_Encounters = new vector<Creature*>;
			m_Encounters->push_back(En1);
		}break;		
	}
}

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
							if (choice > 0 && choice < 4)break;
							else cout << "Invalid choice. Try again:";
						}
						system("CLS");
						cout << "\n\t\tYour attacks:" << endl;
						cout << "***********************************************\n";
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
					case 3: { (*iter)->SpecialDefence(); }break;
					}
					Sleep(300);
				}Sleep(200); 
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
					Sleep(400);
				}	Sleep(320);
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
	if (m_Type == 0) {
		me->GetKey();
		cout << "\n" << me->KeyCount() << " glyph pieces out of 6" << endl;
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
				CFlav("blue");
				cout << (*iter)->GetName();
				CFlav("reset");
				cout << "\tHP:" << (*iter)->GetHealth() << " DAM:" << (*iter)->GetDam() << " DODGE:" << (*iter)->GetDodge() << " INITIATIVE:" << (*iter)->GetInit() << " FOOD:" << (*iter)->TurnFood() << endl;
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
	system("CLS");
	CFlav("red");
	cout << "\n\t\tWelcome to DaskuG's 'DamnednatioN'" << endl;
	CFlav("reset");
	cout << endl;
	//Insert flavour for beginning of game
	cout << "The last thing you remember is robbing some dumb old broad of her bag." << endl;
	Sleep(2000);
	cout << "Then feeling of the cold metal barrel pressed against your head..." << endl;
	Sleep(2000);
	cout << "The BANG of a bullet blast..." << endl;
	Sleep(2000);
	cout << "The looming shadow of Death towering above you." << endl;
	Sleep(2000);
	cout << "The grim spectre grips you by the throat, and begins crushing your esophagus." << endl;
	Sleep(2000);
	cout << "A hole of flames opens up behind you as he motions to throw your soul into hell." << endl;
	Sleep(2000);
	cout << "As he pulls you in to drain your essence your theive's instinct reflexively reaches into his cloack and you catch\na glimpse of three Tomes." << endl;
	Sleep(2000);
	cout << endl;
	cout << "Which Tome do you grab?" << endl;
	cout << "Tome With Etched Horn - The Tome of Demons" << endl;
	cout << "Tome Bound with Flesh - The Tome of the Dead" << endl;
	cout << "Tome of Faces - The Tome of Lost Souls" << endl;
	cout << "Choice: ";
	int choice;
	while (true) {
		cin >> choice;
		if (choice > 0 && choice < 4)break;
	}
	cout << endl;
	switch (choice) {
	default: break;
	case 1: {Plyr = new DemonKing();}break;
	case 2: {Plyr = new Necromancer(); }break;
	case 3: {Plyr = new Spectre(); }break;
	}
	
	vector<Creature*> temp = *(Plyr->GetMonsters());
	while (!temp.empty() && Plyr->KeyCount() != 6) {
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
	if (Plyr->KeyCount() == 6) {
		system("CLS");
		cout << "\n\tYou have used the 'Glyph of Redemption' to cleanse your soul and escape from Hell" << endl;
		cout << "Congratulations, you have won the game. Not even Death can stop you!!" << endl;
	}
}


