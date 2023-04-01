#include<iostream>
#include<Windows.h>
#include<conio.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
const int HEAD = 1;
const int BODY = 2;
const int MAX_ROW = 70;
const int MAX_COL = 70;
const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;
#define BLACK 0
#define BROWN 12
#define WHITE 7
#define RED 4
#define YELL 6
#define LBLUE 9
#define BLUE 1
#define LAQUA 11
#define LYELL 14
#define LPUR 13
#define LGREEN 10
struct Coordinate {
	int row, col;
};
struct snake {
	int length;
	int direction;
	int score;
	Coordinate* body;
	int color;
	int Ukey, Dkey, Lkey, Rkey;
	bool isAlive;
	int lives;
};
struct life {
	Coordinate pos;
	int spawnTime;
	bool isDisplayed;
};
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void DisplayDigit(int N)
{
	if (N < 10 && N >= 0)
	{
		cout << " 0" << N << " ";
	}
	else if (N < 0 && N>-10)
	{
		cout << "-0" << abs(N) << " ";
	}
	else
	{
		cout << " " << N << ' ';
	}
}
void scoreDisplay(snake* players, int playerCount,int i)
{
	int j = (i * 10 + 4);
	
	gotoRowCol(j, MAX_COL + 5);
	cout << "Player " << i + 1 << ": ";
	j += 2;
	gotoRowCol(j, MAX_COL + 5);
	cout << "Length: ";
	DisplayDigit(players[i].length);
	j += 2;
	gotoRowCol(j, MAX_COL + 5);
	cout << " Score: ";
	DisplayDigit(players[i].score);
	j += 2;
	gotoRowCol(j, MAX_COL + 5);
	cout << " lives: "; DisplayDigit(players[i].lives);
	j += 4;

}
struct Food {
	Coordinate foodPos;
};
void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void InitSnake(snake*& players, int playerCount)
{
	players = new snake[playerCount];
	for (int i = 0; i < playerCount; i++)
	{
		players[i].length = 3;
		players[i].body = new Coordinate[players[i].length];
		players[i].score = 0;
		players[i].isAlive = true;
		players[i].lives = 3;

	}
	if (playerCount >= 1)
	{
		for (int j = 0; j < players[0].length; j++)
		{
			players[0].body[j].col = 1;
			players[0].body[j].row = 1;
			players[0].direction = RIGHT;

		}
		players[0].color = YELL;
		players[0].Ukey = 'w';
		players[0].Lkey = 'a';
		players[0].Dkey = 's';
		players[0].Rkey = 'd';
	}
	if (playerCount > 1)
	{
		for (int j = 0; j < players[0].length; j++)
		{
			players[1].body[j].row = MAX_ROW-2;
			players[1].body[j].col = 1;
			players[1].direction = RIGHT;

		}
		players[1].color = LAQUA;
		players[1].Ukey = 72;
		players[1].Lkey = 75;
		players[1].Dkey = 80;
		players[1].Rkey = 77;

	}
	if (playerCount > 2)
	{
		for (int j = 0; j < players[0].length; j++)
		{
			players[2].body[j].row = 1;
			players[2].body[j].col= MAX_COL-2;
			players[2].direction = LEFT;

		}
		players[2].Ukey = 'i';
		players[2].Lkey = 'j';
		players[2].Dkey = 'k';
		players[2].Rkey = 'l';
		players[2].color = BLUE;
	}
	if (playerCount > 3)
	{
		for (int j = 0; j < players[0].length; j++)
		{
			players[3].body[j].row = MAX_ROW-2;
			players[3].body[j].col = MAX_COL -2;
			players[3].direction = LEFT;

		}
		players[3].Ukey = '1';
		players[3].Lkey = '2';
		players[3].Dkey = '3';
		players[3].Rkey = '4';
		players[3].color = LPUR;

	}
}
void DisplaySnake(snake* players, int playerCount)
{
	for (int i = 0; i < playerCount; i++)
	{
		for (int j = 0; j < players[i].length && players[i].isAlive; j++)
		{
			SetClr(players[i].color, BLACK);
			if (j == 0)
			{
				gotoRowCol(players[i].body[j].row, players[i].body[j].col);
				cout << char(HEAD);
			}
			else
			{
				gotoRowCol(players[i].body[j].row, players[i].body[j].col);
				cout << char(BODY);
			}
		}

		SetClr(WHITE, BLACK);
	}
}
void moveHead(snake& player)
{
	if (player.direction == RIGHT)
		player.body[0].col++;
	else if (player.direction == LEFT)
		player.body[0].col--;
	else if (player.direction == UP)
		player.body[0].row--;
	else if (player.direction == DOWN)
		player.body[0].row++;
	if (player.body[0].col == -1)
		player.body[0].col = MAX_COL - 1;
	else if (player.body[0].row == -1)
		player.body[0].row = MAX_ROW - 1;
	else if (player.body[0].col == MAX_COL)
		player.body[0].col = 0;
	else if (player.body[0].row == MAX_ROW)
		player.body[0].row = 0;
}
void EraseSnake(snake* players, int playerCount)
{
	for (int i = 0; i < playerCount; i++)
	{
		for (int j = 0; j < players[i].length; j++)
		{

			gotoRowCol(players[i].body[j].row, players[i].body[j].col);
			cout << " ";
		}
		//gotoRowCol(20, 0);
	}
	//gotoRowCol(20, 0);
}
void FoodDisplay(int row, int col)
{
	SetClr(10, BLACK);
	gotoRowCol(row, col);
	cout << char(6);
	SetClr(WHITE, BLACK);

}
void moveSnakes(snake* players, int playerCount)
{
	for (int t = 0; t < playerCount; t++)
	{
		if (players[t].isAlive)
		{
			gotoRowCol(players[t].body[players[t].length - 1].row, players[t].body[players[t].length - 1].col);
			cout << " ";

			for (int i = players[t].length - 1; i - 1 >= 0; i--)
			{
				players[t].body[i] = players[t].body[i - 1];
			}
			moveHead(players[t]);
		}
	}
}
void userInput(snake* players, int playerCount,bool& isPaused)
{

	if (_kbhit())
	{
		char input = _getch();

		for (int i = 0; i < playerCount; i++)
		{
			if (players[i].isAlive)
			{
				if (input == players[i].Ukey)
				{

					if (players[i].direction != DOWN)
						players[i].direction = UP;
					break;
				}
				if (input == players[i].Dkey)
				{
					if (players[i].direction != UP)
						players[i].direction = DOWN;
					break;

				}
				if (input == players[i].Lkey)
				{

					if (players[i].direction != RIGHT)
						players[i].direction = LEFT;
					break;
				}
				if (input == players[i].Rkey)
				{

					if (players[i].direction != LEFT)
						players[i].direction = RIGHT;
					break;
				}
				if (input == 'p')
				{
					isPaused = true;
					system("pause>0");
					break;

				}

			}
			
		}

	}
}
void snakeExpand(snake& player)
{
	player.length++;
	Coordinate* HA = new Coordinate[player.length];
	for (int i = 0; i + 1 < player.length; i++)
		HA[i + 1] = player.body[i];
	HA[0] = player.body[0];
	delete[]player.body;
	player.body = HA;
	//moveHead(player);
}
bool IsEmptySpace(Coordinate foodCord, snake* players, int PlayerCount,Coordinate *AllFood, Coordinate* hurdles, int hCount)
{
	for (int i = 0; i < PlayerCount; i++)
	{
		for (int j = 0; j < players[i].length && players[i].isAlive; j++)
		{
			if (foodCord.row == players[i].body[j].row && foodCord.col == players[i].body[j].col)
				return false;
			if (foodCord.row == AllFood[i].row && foodCord.col == AllFood[i].col)
				return false;
		}
	}
	for (int i = 0; i < hCount; i++)
	{
		if (foodCord.row == hurdles[i].row && foodCord.col == hurdles[i].col)
			return false;
	}
	if (foodCord.row == 0 || foodCord.col == (MAX_COL - 1) || foodCord.row == (MAX_ROW - 1) || foodCord.col == 0)
		return false;
	return true;
}
void foodGenerate(Coordinate* food, snake* players, int playerCount,int i,Coordinate *hurdles, int hCount)
{
	Coordinate temp;
	
		do {
			temp.row = rand() % (MAX_ROW-1);
			temp.col = rand() % (MAX_COL-1);
		} while (!IsEmptySpace(temp, players, playerCount,food,hurdles,hCount));
		food[i].row = temp.row;
		food[i].col = temp.col;
		FoodDisplay(food[i].row, food[i].col);


}
void isfoodCaptured(Coordinate* foodCord, snake* players, int playerCount, Coordinate *hurdles, int hCount)
{
	for (int i = 0; i < playerCount; i++)
	{

		for (int index = 0; index < playerCount; index++)
		{
			if (players[index].isAlive)
			{

				if (foodCord[i].row == players[index].body[0].row && foodCord[i].col == players[index].body[0].col)
				{
					snakeExpand(players[index]);
					moveHead(players[index]);
					foodGenerate(foodCord, players, playerCount,i, hurdles,hCount);
					players[index].score += 5; 
					scoreDisplay(players, playerCount,index);
					PlaySound(TEXT("coinsound.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
			}
		}
	}
	
}
void DisplayWalls()
{
	//201 left top corner
	//187 top right corner
	//200 bottom left corner
	//188 bottom right corner
	//186 wall STRAIGHT 
	//205 wall horizontal
	SetClr(BROWN, BLACK);
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if ((i == 0 && j == 0))
			{
				gotoRowCol(i, j);
				cout << char(201);
			}
			else if (i == 0 && j == MAX_COL - 1)
			{

				gotoRowCol(i, j);
				cout << char(187);
			}
			else if (i == MAX_ROW - 1 && j == 0)
			{

				gotoRowCol(i, j);
				cout << char(200);
			}
			else if (i == MAX_ROW - 1 && j == MAX_COL - 1)
			{
				gotoRowCol(i, j);
				cout << char(188);
			}
			else if (j == 0 && (i >= 0 && i <= MAX_ROW - 1))
			{

				gotoRowCol(i, j);
				cout << char(186);
			}
			else if (j == MAX_COL - 1 && (i >= 0 && i <= MAX_ROW - 1))
			{
				gotoRowCol(i, j);
				cout << char(186);
			}
			else if (i == 0 && (j >= 0 && j <= MAX_COL - 1))
			{
				gotoRowCol(i, j);
				cout << char(205);

			}
			else if (i == MAX_ROW - 1 && (j >= 0 && j <= MAX_COL - 1))
			{
				gotoRowCol(i, j);
				cout << char(205);

			}

		}
	}
	SetClr(WHITE, BLACK);
}
void EraseSnake(snake player)
{
	for (int i = 0; i < player.length; i++)
	{

		gotoRowCol(player.body[i].row, player.body[i].col);
		cout << " ";
	}

}
bool IsEmptySpace(snake* players, int playerCount, Coordinate spawnL)
{
	for (int i = 0; i < playerCount; i++)
	{
		for (int j = 0; j < players[i].length && players[i].isAlive; j++)
		{
			if (spawnL.row == players[i].body[j].row && spawnL.col == players[i].body[j].col)
				return false;
		}
	}
	return true;
}
void respawn(snake& player, snake* players, int playerCount)
{
	Coordinate spawnLoc;
	do
	{
		int t = rand() % 4;
		if (t == 0)
		{
			spawnLoc.row = 4;
			spawnLoc.col = 1;
			player.direction = RIGHT;
		}
		else if (t == 1)
		{
			spawnLoc.row = MAX_ROW - 5;
			spawnLoc.col = 1;
			player.direction = RIGHT;
		}
		else if (t == 2)
		{
			spawnLoc.row = 4;
			spawnLoc.col = MAX_COL - 2;
			player.direction = LEFT;
		}
		else
		{
			spawnLoc.row = MAX_ROW - 5;
			spawnLoc.col = MAX_COL - 2;
			player.direction = LEFT;
		}
	} while (!IsEmptySpace(players, playerCount, spawnLoc));

	for (int i = 0; i < player.length; i++)
	{
		player.body[i] = spawnLoc;
	}
	player.length = 3;

}
bool isThisTouchingAnySnake(int S, snake* players, int playerCount)
{
	for (int j = 0; j < playerCount; j++)
	{
		if ((players[S].body[0].row == players[j].body[0].row) && players[S].body[0].col == players[j].body[0].col && S != j)
		{
			EraseSnake(players[j]);
			respawn(players[j], players, playerCount);
			players[j].lives--;
			players[j].score -= 10;
			scoreDisplay(players, playerCount, j);
			return true;
		}
		for (int i = 1; i < players[j].length && players[j].isAlive; i++)
		{
			if (players[S].isAlive)
			{

				if (players[S].body[0].row == players[j].body[i].row && players[S].body[0].col == players[j].body[i].col)
				{
					return true;
				}
			}
		}
	}
	return false;
}


void InitGameScreen(int& playerCount,bool &walls, bool &hurdles)
{
	cout << "Enter How many Players: (1-4): ";
	do
	{
		cin >> playerCount;
	} while (playerCount < 1 || playerCount>4);
	system("cls");
	if (playerCount >= 1)
	{
		SetClr(YELL, BLACK);
		cout << " W A S D For player 1" << endl << endl;
	}
	if (playerCount >= 2)
	{
		SetClr(LAQUA, BLACK);
		cout << "Arrow keys For player 2" << endl << endl;
	}
	if (playerCount >= 3)
	{
		SetClr(BLUE, BLACK);
		cout << " I J K L For player 3" << endl << endl;
	}
	if (playerCount == 4)
	{

		SetClr(LPUR, BLACK);
		cout << " 1 2 3 4 For player 1" << endl << endl;
	}
	SetClr(WHITE, BLACK);
	cout << "HURDLES (1/0): ";
	cin >> hurdles;
	cout << "WALLS (1/0): ";
	cin >> walls;
	system("pause");
	system("cls");

}

int timer(unsigned int InitialTime,unsigned int TimeSec,unsigned int TotalTime)
{
	int Time = TimeSec - InitialTime;
	
		gotoRowCol(2, MAX_COL+21);
		cout << "           ";
		gotoRowCol(2, MAX_COL+5);
		cout <<"Time Remaining: ";
		DisplayDigit(TotalTime-Time);
		cout << " s";
		return TotalTime - Time;
}
void checkWhichSnakeDies(snake* players, int playerCount)
{
	bool change = false;
	for (int S = 0; S < playerCount; S++)
	{
		if (players[S].isAlive && isThisTouchingAnySnake(S, players, playerCount))
		{
			EraseSnake(players[S]);
			respawn(players[S],players,playerCount);
			players[S].lives--;
			players[S].score -= 10;
			scoreDisplay(players, playerCount,S);
		}
	}
}
void isTouchingWall(snake* players, int playerCount)
{
	bool hitOnWall = false;
	for (int i = 0; i < playerCount; i++)
	{
		if (players[i].isAlive)
		{
			if (players[i].body[0].row == 0 || players[i].body[0].col == MAX_COL - 1 || players[i].body[0].row == MAX_ROW - 1 || players[i].body[0].col == 0)
			{
				EraseSnake(players[i]);
				respawn(players[i],players,playerCount);
				players[i].lives--;
				players[i].score -= 10;
				hitOnWall = true;
				scoreDisplay(players, playerCount,i);
			}
		}
	}
	if (hitOnWall)
	{
		DisplayWalls();
	}

}
int calculateTimeForPause(int tBefore, int tAfter)
{
	return tAfter - tBefore;
}
void initHurdles(Coordinate *hurdles, int&i)
{
	SetClr(LYELL, BLACK);

	//201 left top corner
	//187 top right corner
	//200 bottom left corner
	//188 bottom right corner
	//186 wall STRAIGHT 
	//205 wall horizontal
	int row,col;
	for (row = 1; row <= MAX_ROW / 4.9; row++)
	{
		
			gotoRowCol(row, MAX_COL / 2);
			cout << char(186);
			hurdles[i].row = row;
			hurdles[i].col = MAX_COL / 2;
			i++;
	}
	gotoRowCol(row, MAX_COL / 2);
	cout << char(202);
	hurdles[i].row = row;
	hurdles[i].col = MAX_COL / 2;
	i++;

	col = MAX_COL / 2.5 ;
	gotoRowCol(row, col-1);
	cout << char(201);
	hurdles[i].row = row;
	hurdles[i].col = col-1;
	i++;
	for (; col < MAX_COL / 2; col++)
	{
		gotoRowCol(row, col);
		cout << char(205);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	for (col = MAX_COL / 2 + 1; col < MAX_COL / 1.6; col++)
	{
		gotoRowCol(row, col);
		cout << char(205);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	gotoRowCol(row, col);
	cout << char(188);
	for (int j = 1; j <= 3; j++)
	{
		row--;
		gotoRowCol(row, col);
		cout << char(186);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	col--;
	for (int j = 1; j <= 3; j++,col++)
	{
		gotoRowCol(row - 1, col);
		cout << char(-37);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	col = MAX_COL / 2.5 - 1;
	row+=4;
	for (; row <= MAX_ROW / 3.5; row++)
	{
		gotoRowCol(row, col);
		cout << char(186);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	col--;
	for (int j = 1; j <= 3; j++, col++)
	{
		gotoRowCol(row, col);
		cout << char(-37);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	row = MAX_ROW / 1.2;
	gotoRowCol(row - 1, MAX_COL / 2);
	cout << char(203);
	hurdles[i].row = row - 1;
	hurdles[i].col = MAX_COL / 2;
	i++;
	//------------------------
	for (col = MAX_COL / 2 + 1; col <= MAX_COL / 1.5; col++)
	{
		gotoRowCol(row - 1, col);
		cout << char(205);
		hurdles[i].row = row - 1;
		hurdles[i].col = col;
		i++;
	}
	row++;
	for (int j = 1; j <= 3; j++, row--)
	{
		gotoRowCol(row, col);
		cout << char(-37);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	row += 2;
	//-----------------------
	for (col = MAX_COL / 2 - 1; col >= MAX_COL / 2.8; col--)
	{
		gotoRowCol(row - 1, col);
		cout << char(205);
		hurdles[i].row = row - 1;
		hurdles[i].col = col;
		i++;
	}
	row--;
	for (int j = 1; j <= 3; j++, row--)
	{
		gotoRowCol(row, col);
		cout << char(-37);
		hurdles[i].row = row;
		hurdles[i].col = col;
		i++;
	}
	row += 4;
	for (; row < MAX_ROW - 1; row++)
	{
		gotoRowCol(row, MAX_COL / 2);
		cout << char(186);
		hurdles[i].row = row;
		hurdles[i].col = MAX_COL / 2;
		i++;
	}
	for (row = MAX_ROW / 2.5; row >= MAX_ROW / 2.5 && row <= MAX_ROW / 1.6; row++)
	{
		gotoRowCol(row, MAX_COL / 2);
		cout << char(-37);
		hurdles[i].row = row;
		hurdles[i].col = MAX_COL / 2;
		i++;
	}
	for (row = MAX_ROW / 3; row >= MAX_ROW / 3 && row <= MAX_ROW / 1.4; row++)
	{
		gotoRowCol(row, MAX_COL / 4);
		cout << char(-37);
		hurdles[i].row = row;
		hurdles[i].col = MAX_COL / 4;
		i++;
	}
	for (row = MAX_ROW / 3; row >= MAX_ROW / 3 && row <= MAX_ROW / 1.4; row++)
	{
		gotoRowCol(row, MAX_COL / 1.3);
		cout << char(-37);
		hurdles[i].row = row;
		hurdles[i].col = MAX_COL / 1.3;
		i++;
	}
	SetClr(WHITE, BLACK);

}
void displayHurdles()
{
	SetClr(LYELL, BLACK);
	int row, col;
	for (row = 1; row <= MAX_ROW / 4.9; row++)
	{

		gotoRowCol(row, MAX_COL / 2);
		cout << char(186);
	}
	gotoRowCol(row, MAX_COL / 2);
	cout << char(202);

	col = MAX_COL / 2.5;
	gotoRowCol(row, col - 1);
	cout << char(201);
	for (; col < MAX_COL / 2; col++)
	{
		gotoRowCol(row, col);
		cout << char(205);
	}
	for (col = MAX_COL / 2 + 1; col < MAX_COL / 1.6; col++)
	{
		gotoRowCol(row, col);
		cout << char(205);
	}
	gotoRowCol(row, col);
	cout << char(188);
	for (int j = 1; j <= 3; j++)
	{
		row--;
		gotoRowCol(row, col);
		cout << char(186);
	}
	col--;
	for (int j = 1; j <= 3; j++, col++)
	{
		gotoRowCol(row - 1, col);
		cout << char(-37);
	}
	col = MAX_COL / 2.5 - 1;
	row += 4;
	for (; row <= MAX_ROW / 3.5; row++)
	{
		gotoRowCol(row, col);
		cout << char(186);
	}
	col--;
	for (int j = 1; j <= 3; j++, col++)
	{
		gotoRowCol(row, col);
		cout << char(-37);

	}
	row = MAX_ROW / 1.2;
	gotoRowCol(row - 1, MAX_COL / 2);
	cout << char(203);

	for (col = MAX_COL / 2 + 1; col <= MAX_COL / 1.5; col++)
	{
		gotoRowCol(row - 1, col);
		cout << char(205);
	}
	//----------------
	row++;
	for (int j = 1; j <= 3; j++, row--)
	{
		gotoRowCol(row, col);
		cout << char(-37);
	}
	row += 2;
	for (col = MAX_COL / 2 - 1; col >= MAX_COL / 2.8; col--)
	{
		gotoRowCol(row - 1, col);
		cout << char(205);
	}
	row--;
	for (int j = 1; j <= 3; j++, row--)
	{
		gotoRowCol(row, col);
		cout << char(-37);
	}
	row += 4;
	for (; row < MAX_ROW - 1; row++)
	{
		gotoRowCol(row, MAX_COL / 2);
		cout << char(186);
	}
	for (row = MAX_ROW / 2.5; row >= MAX_ROW / 2.5 && row <= MAX_ROW / 1.6; row++)
	{
		gotoRowCol(row, MAX_COL / 2);
		cout << char(-37);
	}
	for (row = MAX_ROW / 3; row >= MAX_ROW / 3 && row <= MAX_ROW / 1.4; row++)
	{
		gotoRowCol(row, MAX_COL / 4);
		cout << char(-37);
	}
	for (row = MAX_ROW / 3; row >= MAX_ROW / 3 && row <= MAX_ROW / 1.4; row++)
	{
		gotoRowCol(row, MAX_COL / 1.3);
		cout << char(-37);
	}
	SetClr(WHITE, BLACK);

}
void isHitOnHurdles(snake* players, int playerCount, Coordinate* hurdles, int hCount)
{
	bool isHitOnHurdle = false;
	for (int i = 0; i < playerCount; i++)
	{
		for (int t = 0; t < hCount && players[i].isAlive; t++)
		{
			if (players[i].body[0].row == hurdles[t].row && players[i].body[0].col == hurdles[t].col)
			{
				EraseSnake(players[i]);
				respawn(players[i],players,playerCount);
				isHitOnHurdle= true;
				players[i].lives--;
				players[i].score -= 10;
				scoreDisplay(players, playerCount,i);
				break;
			}
		}
	}
	if (isHitOnHurdle)
	{
		displayHurdles();
	}
}
void areLivesFinished(snake* players, int playerCount, int &playersRem)
{
	for (int i = 0; i < playerCount; i++)
	{
		if (players[i].lives == 0 && players[i].isAlive)
		{
			playersRem--;
			players[i].isAlive = false;
		}
	}
}

void initLifeFruit(life* &fruit, int playerCount, int TotalTime)
{
	fruit = new life[playerCount];
	for (int i = 0; i < playerCount; i++)
	{
		fruit[i].isDisplayed = false;
		fruit[i].spawnTime = rand() % (TotalTime/2)+ (TotalTime/3); // 39 to 89 sec of game time randomly spawn
	}
}
void GenerateLifeFruit(life *lifefruit, snake* players, int playerCount, int TimeLeft, Coordinate* food, Coordinate* hurdles, int hCount)
{
	for (int i = 0; i < playerCount; i++)
	{
		if (lifefruit[i].spawnTime == TimeLeft && !lifefruit[i].isDisplayed)
		{
			Coordinate temp;
			do
			{
				temp.row = rand() % (MAX_ROW - 1);
				temp.col = rand() % (MAX_COL - 1);

			} while (!IsEmptySpace(temp, players, playerCount, food, hurdles, hCount));
			lifefruit[i].pos = temp;
			lifefruit[i].isDisplayed = true;
			gotoRowCol(lifefruit[i].pos.row, lifefruit[i].pos.col);
			SetClr(RED, BLACK);
			cout << char(3);
			SetClr(WHITE, BLACK);
		}
		
	}
}
void disAppearLifeFruit(life* fruit, int playerCount, int TimeLeft)
{
	for (int i = 0; i < playerCount; i++)
	{
		if ((fruit[i].spawnTime - TimeLeft) == 10)
		{
			gotoRowCol(fruit[i].pos.row, fruit[i].pos.col);
			cout << " ";
			fruit[i].pos.row = MAX_ROW+1, fruit[i].pos.col = MAX_COL+1;
		}
	}
}
void isLifeFruitCollected(life* fruit, snake* players, int playerCount)
{
	for (int j = 0; j < playerCount; j++)
	{
		for (int i = 0; i < playerCount; i++)
		{
			if (players[i].body[0].row == fruit[j].pos.row && players[i].body[0].col == fruit[j].pos.col)
			{
				players[i].lives++;
				players[i].score += 10;
				scoreDisplay(players, playerCount,i);
				fruit[j].pos.row = MAX_ROW+1, fruit[j].pos.row = MAX_COL+1;
			}
		}
	}
	
}
void endScreen(snake* players, int playerCount)
{
	gotoRowCol(MAX_ROW -20, MAX_COL +5);
	cout << "---GAME OVER!----";
	/*int maxi = 0;
	for (int i = 0; i < playerCount; i++)
	{
		if (players[i].score > players[maxi].score)
			maxi = i;
	}
	if (players[maxi].score == players[!maxi].score)
	{
		gotoRowCol(MAX_ROW / 2 + 4, MAX_COL / 2);
		cout << "MATCH RESULTED IN DRAW";
		return;
	}
	gotoRowCol(MAX_ROW / 2 +4, MAX_COL / 2);

	cout << "PLAYER " << maxi + 1 << " has WON";*/
}
void DisplayBoundary()
{
	SetClr(8, BLACK);
	for (int i = 0; i < MAX_COL; i++)
	{
		gotoRowCol(MAX_ROW, i);
		cout << char(176);
	}
	for (int i = 0; i <= MAX_ROW; i++)
	{
		gotoRowCol(i, MAX_COL);
		cout << char(176);
	}
	SetClr(WHITE, BLACK);
}
int main()
{
	srand(time(0));
	snake* players{};
	Coordinate* food = new Coordinate[4];
	Coordinate* hurdles = new Coordinate[200];
	life* fruit{};
	int playerCount = 1,hCount=0,timeLeft=0,TotalTime=120;
	unsigned int timeForPause = 0,ftime=0;
	bool isPaused = false,wallsOn=false,hurdlesOn=false;

	InitGameScreen(playerCount,wallsOn,hurdlesOn);

	initLifeFruit(fruit, playerCount,TotalTime);

	int playersRemaining = playerCount;

	ShowConsoleCursor(false);

	InitSnake(players, playerCount);
	if(hurdlesOn)
		initHurdles(hurdles,hCount);

	for (int i = 0; i < playerCount; i++)
	{
		
		foodGenerate(food, players, playerCount,i,hurdles,hCount);
	}
	if (wallsOn)
		DisplayWalls();
	else
		DisplayBoundary();
	for(int i=0; i<playerCount; i++)
		scoreDisplay(players, playerCount,i);

	int Itime = time(0);
	//game flow--------------
	while (true)
	{
		ftime = time(0);

		userInput(players, playerCount,isPaused);

		if (isPaused)
		{
			isPaused = false;
			timeForPause += calculateTimeForPause(ftime, time(0));
		}

		moveSnakes(players, playerCount);

		DisplaySnake(players, playerCount);

		isfoodCaptured(food, players, playerCount,hurdles,hCount);

		checkWhichSnakeDies(players, playerCount);

		if(wallsOn)
			isTouchingWall(players, playerCount);

		if(hurdlesOn)
			isHitOnHurdles(players, playerCount, hurdles, hCount);

		areLivesFinished(players, playerCount, playersRemaining);

		if(((ftime - timeForPause)- TotalTime)!=0)
			timeLeft=timer(Itime, ftime-timeForPause,TotalTime);

		GenerateLifeFruit(fruit, players, playerCount, timeLeft, food, hurdles, hCount);

		disAppearLifeFruit(fruit, playerCount, timeLeft);

		isLifeFruitCollected(fruit, players, playerCount);

		if (playersRemaining == 0)
			break;

		if (timeLeft == 0)
			break;
		if (playersRemaining == 1)
			Sleep(55);
		else if (playersRemaining == 2)
			Sleep(52);
		else if (playersRemaining == 3)
			Sleep(49);
		else
			Sleep(46);
	}
	endScreen(players, playerCount);
	int x=_getch();
	return 0;
}