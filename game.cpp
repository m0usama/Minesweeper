#include <string.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<fstream>
#include <ctime>
#include<stdio.h> 
using namespace std;

// grapics 

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}


void myLine(int x1, int y1, int x2, int y2, int color) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(color, color, color)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}

void myRect(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(192, 192, 192)); //Fill color is passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}

// elipce for 0
void myEllipse0(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(192, 192, 192));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}

// ellipce for bomb
void myBomb(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(255, 0, 0));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}

//check 0 around 0
void check_for_0(int arr[][20], int arr2[][20], int r, int c, int m, int n)
{
	if (arr[r][c] != -1 && arr2[r][c] == -2)
	{
		arr2[r][c] = arr[r][c];
		if (arr[r][c] == 0)
		{
			arr2[r][c] = arr[r][c];
			check_for_0(arr, arr2, r - 1, c, m, n);
			check_for_0(arr, arr2, r + 1, c, m, n);
			check_for_0(arr, arr2, r, c - 1, m, n);
			check_for_0(arr, arr2, r, c + 1, m, n);
			check_for_0(arr, arr2, r - 1, c - 1, m, n);
			check_for_0(arr, arr2, r - 1, c + 1, m, n);
			check_for_0(arr, arr2, r + 1, c - 1, m, n);
			check_for_0(arr, arr2, r + 1, c + 1, m, n);

		}
	}
}

int main()
{


	int flaggame = 1,win_streak=0;
	ofstream score_file;
	while (flaggame == 1)
	{
		char diff;
		int flag1 = 1;
		int r, c,q, arr[20][20];
		// Difficulty level
		while (flag1 == 1)
		{
			cout << "ENTER THE DIFFICULTY LEVEL (b/p) = ";
			cin >> diff;
			if (diff == 'b')
			{
				//int arr[10][10] = { 0 };
				r = 10;
				c = 10;
				q = 275;
				cout << "BEGINNER level selected \n";
				flag1 = 0;
			}
			else if (diff == 'p')
			{
				//int arr[20][20] = { 0 };
				r = 20;
				c = 20;
				q = 525;
				cout << "PROFESSIONAL level selected\n";
				flag1 = 0;
			}
			else
			{
				cout << "Invalid input \n";
			}
		}
		// bombs input
		int bomb;
		int flag2 = 1;
		while (flag2 == 1)
		{
			cout << "ENTER THE NUMBER BOMBS (10-20) = ";
			cin >> bomb;
			if (bomb >= 10  && bomb <= 20 )
			{
				cout << "Your BOMBS are = " << bomb << endl;
				flag2 = 0;
			}
			else
				cout << "Invalid input";

		}

		// 0 the arr
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
				arr[i][j] = 0;
		}
		if (diff == 'b')
			bomb++;
		// planting bombs
		int countb = 0;
		srand(time(0));
		for (int i = 0; i < bomb; i++)
		{
			arr[rand() % r][rand() % c] = -1;
		}

		int countal = 0;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				countal = 0;
				if (arr[i][j] == -1)
					;
				else
				{
					if (i > 0 && j > 0 && i < r - 1 && j < c - 1) // mid
					{
						if (arr[i - 1][j - 1] == -1) //NW
							countal++;
						if (arr[i - 1][j] == -1) // N
							countal++;
						if (arr[i - 1][j + 1] == -1) //NE
							countal++;
						if (arr[i][j + 1] == -1) //E
							countal++;
						if (arr[i + 1][j + 1] == -1) //SE
							countal++;
						if (arr[i + 1][j] == -1) //S
							countal++;
						if (arr[i + 1][j - 1] == -1) //SW
							countal++;
						if (arr[i][j - 1] == -1) //W
							countal++;
						arr[i][j] = countal;
					}
					else if (i == 0 && j == 0) // top left corner
					{

						if (arr[i][j + 1] == -1) //E
							countal++;
						if (arr[i + 1][j + 1] == -1) //SE
							countal++;
						if (arr[i + 1][j] == -1) //S
							countal++;

						arr[i][j] = countal;
					}
					else if (i == 0 && j == c - 1) // top right corner
					{


						if (arr[i + 1][j] == -1) //S
							countal++;
						if (arr[i + 1][j - 1] == -1) //SW
							countal++;
						if (arr[i][j - 1] == -1) //W
							countal++;
						arr[i][j] = countal;
					}
					else if (i == r - 1 && j == 0) // bottom left corner
					{

						if (arr[i - 1][j] == -1) // N
							countal++;
						if (arr[i - 1][j + 1] == -1) //NE
							countal++;
						if (arr[i][j + 1] == -1) //E
							countal++;

						arr[i][j] = countal;
					}
					else if (i == r - 1 && j == c - 1) // bootom right corner
					{

						if (arr[i - 1][j] == -1) // N
							countal++;
						if (arr[i + 1][j - 1] == -1) //SW
							countal++;
						if (arr[i][j - 1] == -1) //W
							countal++;
						arr[i][j] = countal;
					}
					else if (i == 0 && j > 0 && j < c - 1) // upper edge
					{

						if (arr[i][j + 1] == -1) //E
							countal++;
						if (arr[i + 1][j + 1] == -1) //SE
							countal++;
						if (arr[i + 1][j] == -1) //S
							countal++;
						if (arr[i + 1][j - 1] == -1) //SW
							countal++;
						if (arr[i][j - 1] == -1) //W
							countal++;
						arr[i][j] = countal;
					}
					else if (i == 9 && j > 0 && j < c - 1) // lower edge
					{
						if (arr[i - 1][j - 1] == -1) //NW
							countal++;
						if (arr[i - 1][j] == -1) // N
							countal++;
						if (arr[i - 1][j + 1] == -1) //NE
							countal++;
						if (arr[i][j + 1] == -1) //E
							countal++;

						if (arr[i][j - 1] == -1) //W
							countal++;
						arr[i][j] = countal;
					}
					else if (j == 0 && i > 0 && i < c - 1) // left edge
					{

						if (arr[i - 1][j] == -1) // N
							countal++;
						if (arr[i - 1][j + 1] == -1) //NE
							countal++;
						if (arr[i][j + 1] == -1) //E
							countal++;
						if (arr[i + 1][j + 1] == -1) //SE
							countal++;
						if (arr[i + 1][j] == -1) //S
							countal++;

						arr[i][j] = countal;
					}
					else if (j == 9 && i > 0 && i < c - 1) // right edge
					{
						if (arr[i - 1][j - 1] == -1) //NW
							countal++;
						if (arr[i - 1][j] == -1) // N
							countal++;

						if (arr[i + 1][j] == -1) //S
							countal++;
						if (arr[i + 1][j - 1] == -1) //SW
							countal++;
						if (arr[i][j - 1] == -1) //W
							countal++;
						arr[i][j] = countal;
					}

				}
			}
		}
		_getch;
		system("CLS ");

		cout << "x for select \n u for up \n j for down \n h for left \nk for right \n n for new game \n q for quit ";
		_getch();
		system("cls");

		int arr2[20][20];

		// -2 the arr2
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
				arr2[i][j] = -2;
		}
		myRect(25, 25, q, q, 192, 192, 192);
		for (int i = 25; i < q; i = i + 25)
		{
			for (int j = 25; j < q; j = j + 25)
			{
				myRect(j, i, j + 25, i + 25, 105, 105, 105);
			}
		}

		int row = 0, col = 0, flagg = 1;
		int xcrs = 0, ycrs = 0;
		myRect(25 + xcrs, 25 + ycrs, 50 + xcrs, 50 + ycrs, 255, 0, 0);
		while (flagg == 1)
		{
			


			char crsr = _getch();
			if (crsr == 'h') //left
			{
				col = col - 1;
				xcrs = xcrs - 25;
			}
			if (crsr == 'k') //right
			{
				col = col + 1;
				xcrs = xcrs + 25;
			}
			if (crsr == 'u') //up
			{
				row = row - 1;
				ycrs = ycrs - 25;
			}
			if (crsr == 'j') //down
			{
				row = row + 1;
				ycrs = ycrs + 25;
			}
			if (crsr == 's') //save
				;
			if (crsr == 'l') //load
				;
			if (crsr == 'q') //quit game
			{

				flaggame = 0;
				flagg = 0;
			}
			if (crsr == 'n') //new game
			{
				cout << "\n\n STUCK! (',') ...Ok I will LOAD a New game for you";
				Sleep(2000);
				flagg = 0;
			}

			if (crsr == 'x')
			{

				if (arr[row][col] == -1)
					flagg = 0;
				else if (arr[row][col] == 0)
				{
					check_for_0(arr, arr2, row, col, row, col);
				}
				else
					arr2[row][col] = arr[row][col];
				
			}

			//check win
			int countw = 0;
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (arr2[i][j] <= 0 || arr2[i][j] == -2 && arr[i][j] != -1)
						countw++;
				}
			}
			if (countw++ == (r * c) - bomb)
			{
				win_streak++;
				flagg = 2;
			}

			//diplay
			myRect(25, 25, q, q, 192, 192, 192);
			for (int i = 25; i < q; i = i + 25)
			{
				for (int j = 25; j < q; j = j + 25)
				{
					myRect(j, i, j + 25, i + 25, 105, 105, 105);
				}
			}

			myRect(25 + xcrs, 25 + ycrs, 50 + xcrs, 50 + ycrs, 255, 0, 0);
			// print arr2[m][n]
			int xcord = 0, ycord = 0;
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{

					if (arr2[i][j] == -1)
						myBomb(30 + xcord, 28 + ycord, 40 + xcord, 43 + ycord, 0, 0, 0);
					else if (arr2[i][j] == 0)
						myEllipse0(30 + xcord, 28 + ycord, 40 + xcord, 43 + ycord, 0, 0, 0);
					else if (arr2[i][j] == -2)
						;
					else
					{
						if (arr2[i][j] == 1)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
						}
						else if (arr2[i][j] == 2)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
							myLine(33 + xcord, 28 + ycord, 33 + xcord, 43 + ycord, 0);
						}
						else if (arr2[i][j] == 3)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
							myLine(33 + xcord, 28 + ycord, 33 + xcord, 43 + ycord, 0);
							myLine(36 + xcord, 28 + ycord, 36 + xcord, 43 + ycord, 0);
						}
						else if (arr2[i][j] == 4)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
							myLine(33 + xcord, 28 + ycord, 33 + xcord, 43 + ycord, 0);
							myLine(36 + xcord, 28 + ycord, 36 + xcord, 43 + ycord, 0);
							myLine(39 + xcord, 28 + ycord, 39 + xcord, 43 + ycord, 0);
						}

					}
					xcord = xcord + 25;
				}
				ycord = ycord + 25;
				xcord = 0;

			}
			
			

		}
		string p_name;
		if (flagg == 0)
		{
			system("cls");
			myRect(25, 25, q, q, 192, 192, 192);
			for (int i = 25; i < q; i = i + 25)
			{
				for (int j = 25; j < q; j = j + 25)
				{
					myRect(j, i, j + 25, i + 25, 105, 105, 105);
				}
			}
			
			int xcord = 0, ycord = 0;
			cout << "     " << "bomb : " << bomb << "      " << "winstreak : " << win_streak;
			// print arr2[m][n]
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (arr[i][j] == -1)
						myBomb(30 + xcord, 28 + ycord, 40 + xcord, 43 + ycord, 0, 0, 0);
					else if (arr2[i][j] == 0)
						myEllipse0(30 + xcord, 28 + ycord, 40 + xcord, 43 + ycord, 0, 0, 0);
					else
					{
						if (arr2[i][j] == 1)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
						}
						else if (arr2[i][j] == 2)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
							myLine(33 + xcord, 28 + ycord, 33 + xcord, 43 + ycord, 0);
						}
						else if (arr2[i][j] == 3)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
							myLine(33 + xcord, 28 + ycord, 33 + xcord, 43 + ycord, 0);
							myLine(36 + xcord, 28 + ycord, 36 + xcord, 43 + ycord, 0);
						}
						else if (arr2[i][j] == 4)
						{
							myLine(30 + xcord, 28 + ycord, 30 + xcord, 43 + ycord, 0);
							myLine(33 + xcord, 28 + ycord, 33 + xcord, 43 + ycord, 0);
							myLine(36 + xcord, 28 + ycord, 36 + xcord, 43 + ycord, 0);
							myLine(39 + xcord, 28 + ycord, 39 + xcord, 43 + ycord, 0);
						}
					}
					xcord = xcord + 25;
				}
				ycord = ycord + 25;
				xcord = 0;
				
			}
			
			cout << "press any key";
			_getch();
			system("cls");
			cout << "\n\n YOU LOST the GAME \n\n";
		}
		else if (flagg == 2)
		{
			system("cls");
			cout << "\n\n YOU WIN the GAME \n\n ";
			cout << "\n\nEnter YOUR name :";
			cin >> p_name;
			score_file.open("game_scores.txt");
			score_file << p_name << "  :  " << win_streak;
			score_file.close();
		}
		cout << "\n\nDO YOU WANT TO PLAY AGAIN (y/n) : ";
		char p_again;
		cin >> p_again;
		if (p_again == 'n')
			flaggame = 0;

	}
	cout << "\n\nTHE GAME is QUIT ";
	
	
	system("pause");
	return 0;

}
