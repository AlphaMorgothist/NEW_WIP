// Fproj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "world.h"


void TestWorld() {
	World uni;
	uni.Play();
}

int main()
{

	//TestFight();
	TestWorld();
	cout << "GAME OVER" << endl;
	cin.get();
	cin.ignore();
    return 0;
}

