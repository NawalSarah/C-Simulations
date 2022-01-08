// Simulation2.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <fstream>
#include "Ball.h"

using namespace std;

void screenshot() // Press shift for screeenshot , saves screenshot to clipboard
{
		keybd_event(VK_MENU, 0, 0, 0); //Alt Press
		keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press


		keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release

}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



int matrix[8][20];
// drawing the cars
void drawCar(int x, int y) {
	if (y < 20 && y >= -0)
	{
		matrix[x][y] = 1; //successfully drawn a point '$' at coordinate

	}

}

void clearBoard() {
	for (int j = 0; j < 20; j++) {
		for (int i = 1; i < 7; i++) {
			matrix[i][j] = 0;

		}

	}

}


//SOME IMPORTANT STUCTURES (GAME ELEMENTS)



struct EnemiesCar {

	int xPos = 5;
	int yPos = -3;

public:
	void appear(); // randomly moves the enemy car to left or to right
	void draw();
	void move();

};

void EnemiesCar::appear() // randomly moves the enemy car to left or to right
{
	if (yPos == 20) {
		int randomNo = rand() % 2;
		if (randomNo == 0) {
			xPos = 2;

		}
		else {
			xPos = 5;

		}
		yPos = -3;

	}

}

void EnemiesCar::draw() {

	drawCar(xPos, yPos); // drawing the car
	drawCar(xPos - 1, yPos + 1);
	drawCar(xPos + 1, yPos + 1);
	drawCar(xPos, yPos + 1);
	drawCar(xPos, yPos + 2);
	drawCar(xPos - 1, yPos + 3);
	drawCar(xPos + 1, yPos + 3);
	drawCar(xPos, yPos + 3);

}

void EnemiesCar::move() {
	yPos++; //or else enm car stays in 1 place

}


struct car {

	int xPos = 2;
	int yPos = 16;

public:
	void draw();
	void moveLeft();
	void moveRight();
	void checkCollusion(EnemiesCar* EC, bool* running);
};

void car::draw() {
	drawCar(xPos, yPos);
	drawCar(xPos - 1, yPos + 1);
	drawCar(xPos + 1, yPos + 1);
	drawCar(xPos, yPos + 1);
	drawCar(xPos, yPos + 2);
	drawCar(xPos - 1, yPos + 3);
	drawCar(xPos + 1, yPos + 3);
	drawCar(xPos, yPos + 3);

}

void car::moveLeft() {
	xPos = 2;

}
void car::moveRight() {
	xPos = 5;

}
void car::checkCollusion(EnemiesCar* EC, bool* running) {
	if (EC->xPos == xPos && EC->yPos > 13) //if x axis is same and y axis collides
	{
		*running = false;

	}

}

//Listens to keyboard inputs  

void keyinput(car* c) {
	while (1) {
		if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)) {
			c->moveLeft();
			keybd_event(VK_MENU, 0, 0, 0); //Alt Press
			keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press


			keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
			keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release
		}
		else if (GetAsyncKeyState(VK_RIGHT) & (0x8000 != 0)) {
			c->moveRight();

		}

	}

}

void startGame() {
	system("Color E4");
	car mycar = car(); //objects
	EnemiesCar myEnmCar = EnemiesCar(); //objects
	// starts the second thread (The input listener )  
	thread forThread(keyinput, &mycar); //executing multiple things at same time
	// This is the game engine/game loop  
	bool running = true;
	while (running)// as long as it doesnt  collide
	{
		clearBoard();
		myEnmCar.appear();
		myEnmCar.draw();
		myEnmCar.move();
		mycar.draw();
		mycar.checkCollusion(&myEnmCar, &running);

		for (int j = 0; j < 20; j++) {
			for (int i = 0; i < 8; i++) {
				if (i == 0 || i == 7) {
					gotoXY(i, j);
					cout << "+"; // loop  for border

				}
				else if (matrix[i][j] == 1)
				{
					gotoXY(i, j);
					cout << "$$";

				}
				else {
					gotoXY(i, j);
					cout << " ";

				}

			}
			
		}

		Sleep(50); //too fast without it

	}
	//The game ended  

	//Show the Game Over  
	system("cls");
	gotoXY(5, 4);
	cout << "GAME OVER!!!";

	// Kills the thread  
	forThread.detach();

}

void ss() {
	fstream my_file;
	my_file.open("my_file", ios::out);
	if (!my_file) {
		cout << "File not created!";
	}
	else {
		cout << "";
	}
	
}
void open()
{
	fstream my_file;
	my_file.open("my_file.txt", ios::out);
	if (!my_file) {
		cout << "File not created!";
	}
	else {
		cout << "";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+    $ +\n";
		my_file << "+   $$$+\n";
		my_file << "+    $ +\n";
		my_file << "+   $$$+\n";
		my_file << "+    $ +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+      +\n";
		my_file << "+ $    +\n";
		my_file << "+$$$   +\n";
		my_file << "+ $    +\n";
		my_file << "+$$$   +\n";
		my_file << "+ $    +\n";

		my_file.close();
	}
}


int main()
{
	if (GetAsyncKeyState(VK_SHIFT) & (0x8000 != 0))
	{
		screenshot();

	}
	
	int c;
	cout << " 1. Do you want to see a bouncy ball simulation ? \n";
	cout << " \t \t OR\n";
	cout << " 2. Do you want to play a Car Game ? \n";
	cin >> c;
	system("CLS");

	
	if (c == 1)
	{ 
		base::ballsim(); 
		system("PAUSE");
		

	} 
	else {
		if (GetAsyncKeyState(VK_SPACE) & (0x8000 != 0)) //press space for car output file
		{
			ss();
			open();
		}
		startGame();
		
	}

	return 0;
}



