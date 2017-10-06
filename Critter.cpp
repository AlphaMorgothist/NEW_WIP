#include "stdafx.h"
#include "Critter.h"

void TestFight() {

	//Initializations
	string Jaider = "Jaider";
	Creature* D1 = new Dragon(Jaider, 10);
	string Mike = "Mike";
	Creature* D2 = new Dragon(Mike, 10);

	//Training Test
	for (int i = 0; i < 5; i++)
	{
		D1->Training();
		Sleep(500);
		D2->Training();
		Sleep(500);
	}
	int Mikewin = 0;
	int Jaidwin = 0;

	//Combat Loop Test (make into a function)
	while (D1->IsLiving() && D2->IsLiving()) {
		if (D1->IsHitBy(*D2)) {
			D2->Attack(D1);
			if (D1->IsLiving() == false) {
				Mikewin++;
				ofstream writer1("Mwins.txt", ios::app);
				writer1 << "Mike Wins: " << Mikewin << endl;
				writer1.close();
				break;
			}
		}
		if (D2->IsHitBy(*D1)) {
			D1->Attack(D2);
			if (D2->IsLiving() == false) {
				Jaidwin++;
				ofstream writer("Jwins.txt", ios::app);
				writer << "Jaider Wins: " << Jaidwin << endl;
				writer.close();
				break;
			}
		}
		cout << endl;
		cout << D1->GetName() << " HP:" << D1->GetHealth() << endl;
		cout << D2->GetName() << " HP:" << D2->GetHealth() << endl;
		Sleep(2000);
		system("CLS");
	}
	system("pause");
}



//Creature class member functions 
Creature::Creature(string name, int dam = 10):
	m_Name(name), m_Hunger(0), m_Food(0), m_Bloodlust(0), m_Damage(dam)
{
}

void Creature::Talk()
{
	cout << m_Name << " says:" << endl;
	if (m_Hunger <= 5) {
		cout << "\nI am well fed." << endl;
	}
	else if (m_Hunger > 5) {
		cout << "\n I am fairly hungry, lets go hunting!" << endl;
	}
	else if (m_Hunger > 10) {
		cout << "\nI am starving!! If I don't eat soon I will die. Please tell me that we have food" << endl;
	}
	if (m_Bloodlust <= 5) {
		cout << "\nI am happy that we get to fight often" << endl;
	}
	else if (m_Bloodlust > 5) {
		cout << "\nWe should go find something to fight!" << endl;
	}
	else if (m_Bloodlust > 10) {
		cout << "\nI am itching for a fight!! Common! Lets take something down!!!!" << endl;
	}
}

void Creature::Feed()
{
	if (m_Food <= 0) {
		cout << "\nYou have no food to feed your creature!" << endl;
	}
	else {
		if (m_Hunger >= m_Food) {
			cout << "\nYou feed " << m_Name << " " << m_Food << " food." << endl;
			m_Hunger -= m_Food;
			cout << m_Name << " has a hunger level of " << m_Hunger << " left." << endl;
			m_Food = 0;
		}
		else {
			m_Food -= m_Hunger;
			cout << "\nYou feed " << m_Name << " " << m_Hunger << " food." << endl;
			m_Hunger = 0;
			cout << m_Name << " is fully fed." << endl;
		}
	}
}

string Creature::GetName()
{
	return m_Name;
}

float Creature::GetInit()
{
	return m_Initiative;
}

int Creature::GetHealth()
{
	return m_Health;
}

void Creature::SetHealth(int num)
{
	m_Health = num;
}

void Creature::TakeDam(int dam)
{
	m_Health -= dam;
}

bool Creature::IsLiving()
{
	if (m_Health > 0) {
		return true;
	}
	else {
		cout << m_Name << " has died!!" << endl;
		return false;
	}
}

bool Creature::IsHitBy(Creature other)
{
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist1{ 0.0, other.GetInit() };
	uniform_real_distribution<double> dist2{ 0.0, m_Dodge };
	double hitChance = dist1(engine);
	double dodgeChance = dist2(engine);
	if (hitChance > dodgeChance) {
		return true;
	}
	else {
		cout << "\n" << m_Name << " dodges!" << endl;
		return false;
	}
}

void Creature::Training()
{
	cout << "\nYour creature " << m_Name << " has gained experience" << endl;
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<float> dist{ 0, 900 };

	int critchoice = dist(engine);
	if (critchoice <= 300) {
		critchoice = 0;
	}
	else if (critchoice <= 600) {
		critchoice = 1;
	}
	else if (critchoice > 600) {
		critchoice = 2;
	}
	switch (critchoice) {
	case 0: {
		cout << m_Name << "'s initiative has increased!" << endl;
		m_Initiative++; }break;
	case 1: {
		cout << m_Name << "'s dodge has increased!" << endl;
		m_Dodge++; }break;
	case 2: {
		cout << m_Name << "'s damage has increased!" << endl;
		m_Damage++; }break;
	}
}

void Creature::GetFood(int food)
{
	m_Food += food;
}

void Creature::PassTime()
{
	m_Hunger++;
	m_Bloodlust++;
}

void Creature::DodgeDam(int dam)
{
	m_Dodge -= dam;
}

void Creature::InitDam(int dam)
{
	m_Initiative -= dam;
}

void Creature::Attack(Creature *other)
{
}

void Creature::SpecialAttack(Creature * other)
{
}

int Creature::GetSpecial()
{
	return m_SpecUse;
}

void Creature::SpecialUse()
{
	m_SpecUse--;
}

void Creature::SpecialRecharge()
{
	m_SpecUse = 2;
}

void Creature::SpecialDefence()
{
}

void Creature::DisplayAttacks()
{
	cout << "\n1: Basic Attack\n2:Special Attack\n3:Special Defence" << endl;
}


//Sub classes of Creature
Dragon::Dragon():
	Creature("Demon",10)
{
}

Dragon::Dragon(string name, int dam):
	Creature(name, dam)
{
}

void Dragon::Attack(Creature *other)
{
	cout << "\n" << m_Name << " inflicts " << m_Damage << " damage on " << other->GetName() << endl;
	other->TakeDam(m_Damage);
}

void Dragon::SpecialAttack(Creature * other)
{
	int newdam = m_Damage * (rand() % 2);
	int initdam = m_Damage * (rand() % 2 + 1);
	cout << "\n" << m_Name << " performs a special attack inflicting " << newdam << " damage on " << other->GetName() << endl;
	cout << "Because of Demon Rage, the enemy is intimidated and takes " << initdam << " damage to it's initiative" << endl;
	other->TakeDam(newdam);
	other->InitDam(initdam);
}

void Dragon::DisplayAttacks()
{
	cout << "\n1: Demon Claw attack\n2:Demon Rage(Special Atk)" << endl;
}

Skeleton::Skeleton() :
	Creature("Skeleton", 10)
{
}

Skeleton::Skeleton(string name, int dam) :
	Creature(name, dam)
{
}

void Skeleton::Attack(Creature * other)
{
	cout << "\n" << m_Name << " inflicts " << m_Damage << " damage on " << other->GetName() << endl;
	other->TakeDam(m_Damage);
}

void Skeleton::SpecialAttack(Creature * other)
{
	int newdam = m_Damage * (rand() % 5 + 1);
	cout << "\n" << m_Name << " performs a special attack inflicting " << newdam << " damage on " << other->GetName() << endl;
	cout << "Your attack is heavier due to Revenge of the Dead" << endl;
	other->TakeDam(newdam);
}

void Skeleton::DisplayAttacks()
{
	cout << "\n1: Skeleton Bone attack\n2:Revenge of the Dead(Special Atk)" << endl;
}

Spirit::Spirit():
	Creature("Spirit", 10)
{
}

Spirit::Spirit(string name, int dam):
	Creature(name, dam)
{
}

void Spirit::Attack(Creature * other)
{
	cout << "\n" << m_Name << " inflicts " << m_Damage << " damage on " << other->GetName() << endl;
	other->TakeDam(m_Damage);
}

void Spirit::SpecialAttack(Creature * other)
{
	int newdam = m_Damage * (rand() % 2);
	int dodgedam = m_Damage * (rand() % 3);
	cout << "\n" << m_Name << " performs a special attack inflicting " << newdam << " damage on " << other->GetName() << endl;
	cout << "Because of Spectral Fear, the enemy takes " << dodgedam << " damage affecting it's ability to dodge" << endl;
	other->TakeDam(newdam);
	other->DodgeDam(dodgedam);
}

void Spirit::DisplayAttacks()
{
	cout << "\n1: Spirit Spite attack\n2:Spectral Fear(Special Atk)" << endl;
}


//Player member functions
Player::Player(int type):
	m_pMonsters(NULL)
{
	cout << "As you fall towards the ground the flames burn around you." << endl;
	system("Pause");
	cout << "You slam into the ground and hear footsteps around you" << endl;
	system("Pause");
	m_pMonsters = new vector<Creature*>;
	switch (type) {
	case 1: {
		cout << "You look up and you see a wretched Demon with 3 foot horns" << endl;
		system("Pause");
		cout << "It barrels towards you mouth agape preparing to tear you to shreds" << endl;
		system("Pause");
		cout << "As it approaches you throw your hands out in front of you without any hope of survival and yell 'STOP'.\nThe beast stops dead in its tracks and stares directly at you." << endl;
		system("Pause");
		cout << "You point to the door ahead of you 'There!'.\nThe demon run towards the door." << endl;
		system("Pause");
		cout << "You realise you are no longer speaking in English, this must be the work of the book.\nWhatever the case, you need to find a way out of here. And the only door out is ahead of you" << endl;
		cout << "What will you name your first servant?" << endl;
		cout << "Name: " << endl;
		string name;
		cin >> name;
		Creature *C1 = new Dragon(name, 40);
		cin.ignore();
		m_pMonsters->push_back((C1));
	}break;
	case 2: {
		cout << "You look up and see a shambling skeleton lurching towards you with laughter" << endl;
		system("Pause");
		cout << "It Runs towards you with maniacal laughter ready to tear at your flesh" << endl;
		system("Pause");
		cout << "As it approaches you throw your hands out in front of you without any hope of survival and yell 'STOP'.\nIt stops dead in its tracks and stares directly at you." << endl;
		system("Pause");
		cout << "You point to the door ahead of you 'There!'.\nThe skeleton run towards the door." << endl;
		system("Pause");
		cout << "You realise you are no longer speaking in English, this must be the work of the book.\nWhatever the case, you need to find a way out of here. And the only door out is ahead of you" << endl;
		cout << "What will you name your first servant?" << endl;
		cout << "Name: ";
		string name;
		cin >> name;
		Creature *C1 = new Skeleton(name, 40);
		m_pMonsters->push_back((C1));
	}break;
	case 3: {
		cout << "You look up and you see a spirit whisping around the room wailing" << endl;
		system("Pause");
		cout << "It sees you and begins to soar towards you hands stretched out ready to tear you to pieces" << endl;
		system("Pause");
		cout << "As it approaches you throw your hands out in front of you without any hope of survival and yell 'STOP'.\nThe ghoul stops dead in its tracks and stares directly at you." << endl;
		system("Pause");
		cout << "You point to the door ahead of you 'There!'.\nThe spirit run towards the door." << endl;
		system("Pause");
		cout << "You realise you are no longer speaking in English, this must be the work of the book.\nWhatever the case, you need to find a way out of here. And the only door out is ahead of you" << endl;
		cout << "What will you name your first creature servant?" << endl;
		cout << "Name: ";
		string name;
		cin >> name;
		Creature *C1 = new Spirit(name, 40);
		m_pMonsters->push_back((C1));
	}break;
	}
}

Player::~Player()
{
	m_pMonsters->clear();
	m_pMonsters = NULL;
}

vector<Creature*>* Player::GetMonsters()
{
	return m_pMonsters;
}

int Player::GetType()
{
	return 0;
}

double Player::GetXP()
{
	return m_XP;
}

void Player::GiveXP()
{
	m_XP++;
}


//Sub classes of Player
DemonKing::DemonKing():
	Player(1)
{
}

int DemonKing::GetType()
{
	return m_Type;
}

Necromancer::Necromancer():
	Player(2)
{
}

int Necromancer::GetType()
{
	return m_Type;
}

Spectre::Spectre():
	Player(3)
{
}

int Spectre::GetType()
{
	return m_Type;
}


