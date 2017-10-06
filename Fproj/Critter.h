#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <fstream>
#include <Windows.h>


using namespace std;

void CFlav(string colour);

//Monster base class
class Creature {
public:
	Creature(string name, int dam);
	Creature(string name, int dam, int hp);
	Creature(string name, int dam, int hp, int dodge);
	void Talk();
	virtual void Feed();
	string GetName();
	float GetInit();
	int GetHealth();
	void SetHealth(int num);
	void TakeDam(int dam);
	int GetDam();
	int GetDodge();
	bool IsLiving();
	bool IsHitBy(Creature other);
	void Training();
	void GetFood(int food);
	int TurnFood();
	void PassTime();
	void DodgeDam(int dam);
	void InitDam(int dam);
	virtual void Attack(Creature *other);
	virtual void SpecialAttack(Creature *other);
	int GetSpecial();
	void SpecialUse();
	void SpecialRecharge();
	virtual void SpecialDefence();
	virtual void DisplayAttacks();

protected:
	int m_SpecUse = 2;
	int m_Hunger = 0;
	int m_Bloodlust = 0;
	int m_Food = 0;
	int m_Health = 100;
	int m_Damage;
	float m_Initiative = 10;
	float m_Dodge = 8;
	string m_Name;
};

//Derived class of monster
class Dragon : public Creature {
public:
	Dragon();
	Dragon(string name, int dam);
	void Attack(Creature *other) override;
	void SpecialAttack(Creature *other) override;
	void DisplayAttacks() override;
	void SpecialDefence() override;
	

};

class Skeleton : public Creature {
public:
	Skeleton();
	Skeleton(string name, int dam);
	void Attack(Creature *other) override;
	void SpecialAttack(Creature *other) override;
	void DisplayAttacks() override;
	void SpecialDefence() override;
};

class Spirit : public Creature {
public:
	Spirit();
	Spirit(string name, int dam);
	Spirit(string name, int dam, int hp);
	void Attack(Creature *other) override;
	void SpecialAttack(Creature *other) override;
	void DisplayAttacks() override;
	void SpecialDefence() override;
};


//Player base class
class Player {
public:
		Player(int type);
		~Player();
		vector<Creature*>* GetMonsters();
		virtual int GetType();
		double GetXP();
		void GiveXP();
		void GetKey();
		int KeyCount();

protected:
	vector<Creature*> *m_pMonsters;
	int m_Type;
	double m_XP = 1;
	int m_Keys;

	//MAKE CLASS FOR WEPS/POWER UPS;
	//vector<string>* inventory;
};

//Derived class of Player
class DemonKing : public Player {
public:
	DemonKing();
	int GetType() override;


private:
	//Type of player: 1-Demon 2-Necro 3-Spectre
	 const int m_Type = 1;
};

class Necromancer : public Player {
public:
	Necromancer();
	int GetType() override;

private:
	//Type of player: 1-Demon 2-Necro 3-Spectre
	const int m_Type = 2;
};

class Spectre : public Player {
public:
	Spectre();
	int GetType() override;

private:
	//Type of player: 1-Demon 2-Necro 3-Spectre
	const int m_Type = 3;
};

