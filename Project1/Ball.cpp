#include "Ball.h"

#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void base::gotoxy(int eex, int eey)
{ //cout << "----------------------------------------------------------------------------------\n" ;
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "                                                                                 |\n";
	cout << "----------------------------------------------------------------------------------\n";
	COORD coord;
	coord.X = eex;
	coord.Y = eey;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int base:: ballsim()
{
	int ball[80][23]; //2D array boundary
	void gotoxy(int, int);
	int k = 14;
	int noOfCoords = 0;
	int origX=5; //ball to start from
	int origY=5; //ball to start from
	char mov1; //initial move
	char mov2; //initial move
	int x;
	int y;
	cout << "Would you like the ball to move [u]p or [d]own? ";
	cin >> mov1;
	cout << endl;
	cout << "would you like the ball to move [l]eft or [r]ight? ";
	cin >> mov2;
	cout << endl;
	x = origX;			//make x and y equal the original entries	
	y = origY;

	for (int row = 0; row < 79; row++) //initialize the ball array's elements to 0
	{
		for (int col = 0; col < 22; col++)
			ball[row][col] = 0; // helps in count coordinates 
	}
	gotoxy(x, y);			//go to the coordinate	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	{
		SetConsoleTextAttribute(hConsole, k);
		cout << "O" << endl;
	}			//print O at the coordinate	

	if (ball[x][y] == 0)
	{
		ball[x][y] = 1;
		noOfCoords++;
	}

	//moving ball once

	if (mov1 == 'u')
	{
		if (y > 0)
		{
			y--;
		}
		else
		{
			
			mov1 = 'd';
		}
	}
	if (mov1 == 'd')
	{
		if (y < 22)
		{
			y++;
		}
		else
		{
			mov1 = 'u';
		}
	}
	if (mov2 == 'r')
	{
		if (x < 79)
		{
			x++;
		}
		else
		{
			mov2 = 'l';
		}
	}
	if (mov2 == 'l')
	{
		if (x > 0)
		{
			x--;
		}
		else
		{
			
			mov2 = 'r';
		}
	}
	gotoxy(x, y);			//go to coordinate

	{
		SetConsoleTextAttribute(hConsole, k);
		cout << "O" << endl;
		//print O at the coordinate

		//takes screenshot and saves to clipboard
		
	}

	if (ball[x][y] == 0) //when its in the border it helps
	{
		ball[x][y] = 1;
		noOfCoords++;
	}


	while ((x != origX) || (y != origY)) //loop  continues as long as it satisfies condition
	{
		//move the ball in the correct direction
		if (mov1 == 'u')
		{
			if (y > 0)
			{
				y--;
			}
			else
			{
				mov1 = 'd';
			}
		}

		if (mov1 == 'd')
		{
			if (y < 22)
			{
				y++;
			}
			else
			{
				mov1 = 'u';
			}
		}
		if (mov2 == 'r')
		{
			if (x < 79)
			{
				x++;
			}
			else
			{
				mov2 = 'l';
			}
		}
		if (mov2 == 'l')
		{
			if (x > 0)
			{
				x--;
			}
			else
			{
				mov2 = 'r';
			}
		}
		gotoxy(x, y);

		{
			SetConsoleTextAttribute(hConsole, k);
			cout << "O" << endl;
		}

		if (ball[x][y] == 0)
		{
			ball[x][y] = 1;
			noOfCoords++;
		}


		system("CLS");
	}
	//output the number of coordinates 
	cout << endl;
	cout << "The ball crossed " << noOfCoords << " unique coordinates.";
	cout << endl;
	system("PAUSE");

	return 0;
}

