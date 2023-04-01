//#include<iostream>
//#include<Windows.h>
//#include<conio.h>
//#include<thread>
//using namespace std;
//
//const int HEAD = 153;
//const int BODY = 228;
//const int MAX_ROW = 30;
//const int MAX_COL = 80;
//const int RIGHT = 0;
//const int LEFT = 1;
//const int UP = 2;
//const int DOWN = 3;
//#define BLACK 0
//#define BROWN 6
//#define WHITE 7
//#define BWHITE 15
//#define GREEN 2
//#define RED 4
//#define YELL 12
//#define LBLUE 9
//#define BLUE 1
//#define AQUA 3
//#define LAQUA 11
//struct Coordinate {
//	int row, col;
//};
//struct snake {
//	int length;
//	int direction;
//	int score;
//	Coordinate* body;
//	int color;
//};
//struct Food {
//	Coordinate foodPos;
//};
//void SetClr(int tcl, int bcl)
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
//}
//bool isThisTouchingAnySnake(int S, snake* players, int playerCount)
//{
//	for (int j = 0; j < playerCount; j++)
//	{
//		for (int i = 1; i < players[j].length; i++)
//		{
//			if (players[S].body[0].row == players[j].body[i].row && players[S].body[0].col == players[j].body[i].col)
//				return true;
//		}
//	}
//	return false;
//}
//void gotoRowCol(int rpos, int cpos)
//{
//	COORD scrn;
//	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
//	scrn.X = cpos;
//	scrn.Y = rpos;
//	SetConsoleCursorPosition(hOuput, scrn);
//}
//void DisplayWalls()
//{
//	//201 left top corner
//	//187 top right corner
//	//200 bottom left corner
//	//188 bottom right corner
//	//186 wall STRAIGHT 
//	//205 wall horizontal
//	for (int i = 0; i < MAX_ROW; i++)
//	{
//		for (int j = 0; j < MAX_COL; j++)
//		{
//			if ((i == 0 && j == 0))
//			{
//				gotoRowCol(i, j);
//				cout << char(201);
//			}
//			else if (i == 0 && j == MAX_COL - 1)
//			{
//
//				gotoRowCol(i, j);
//				cout << char(187);
//			}
//			else if (i == MAX_ROW - 1 && j == 0)
//			{
//
//				gotoRowCol(i, j);
//				cout << char(200);
//			}
//			else if (i == MAX_ROW - 1 && j == MAX_COL - 1)
//			{
//				gotoRowCol(i, j);
//				cout << char(188);
//			}
//			else if (j == 0 && (i >= 0 && i <= MAX_ROW - 1))
//			{
//
//				gotoRowCol(i, j);
//				cout << char(186);
//			}
//			else if (j == MAX_COL - 1 && (i >= 0 && i <= MAX_ROW - 1))
//			{
//				gotoRowCol(i, j);
//				cout << char(186);
//			}
//			else if (i == 0 && (j >= 0 && j <= MAX_COL - 1))
//			{
//				gotoRowCol(i, j);
//				cout << char(205);
//
//			}
//			else if (i == MAX_ROW - 1 && (j >= 0 && j <= MAX_COL - 1))
//			{
//				gotoRowCol(i, j);
//				cout << char(205);
//
//			}
//
//		}
//	}
//}
//void InitSnake(snake*& players, int playerCount)
//{
//	players = new snake[playerCount];
//	for (int i = 0; i < playerCount; i++)
//	{
//		players[i].length = 4;
//		players[i].body = new Coordinate[MAX_ROW * MAX_COL];
//		players[i].direction = RIGHT;
//		for (int j = 0; j < players[i].length; j++)
//		{
//			players[i].body[j].col = MAX_COL / 2 - j;
//			players[i].body[j].row = MAX_ROW / 2 - 5 * i;
//
//		}
//		players[i].score = 0;
//		players[i].color = YELL;
//	}
//	players[1].color = LAQUA;
//}
//void DisplaySnake(snake* players, int playerCount)
//{
//	for (int i = 0; i < playerCount; i++)
//	{
//		for (int j = 0; j < players[i].length; j++)
//		{
//			SetClr(players[i].color, BLACK);
//			if (j == 0)
//			{
//				gotoRowCol(players[i].body[j].row, players[i].body[j].col);
//				cout << char(HEAD);
//			}
//			else
//			{
//				gotoRowCol(players[i].body[j].row, players[i].body[j].col);
//				cout << char(BODY);
//			}
//		}
//		SetClr(WHITE, BLACK);
//		gotoRowCol(20, 0);
//		/*if (players[i].direction == UP || players[i].direction == DOWN)
//			Sleep(60);
//		else
//			Sleep(30);*/
//	}
//}
//bool isTouchingWall(Coordinate pos)
//{
//	return (pos.row == 0 || pos.col == MAX_COL - 1 || pos.row == MAX_ROW - 1 || pos.col == 0);
//}
//void moveHead(snake& player)
//{
//	if (player.direction == RIGHT)
//		player.body[0].col++;
//	else if (player.direction == LEFT)
//		player.body[0].col--;
//	else if (player.direction == UP)
//		player.body[0].row--;
//	else if (player.direction == DOWN)
//		player.body[0].row++;
//}
//bool IsEmptySpace(Coordinate foodCord, snake* players, int PlayerCount)
//{
//	for (int i = 0; i < PlayerCount; i++)
//	{
//		for (int j = 0; j < players[i].length; j++)
//		{
//			if (foodCord.row == players[i].body[j].row || foodCord.col == players[i].body[j].col)
//				return false;
//		}
//	}
//	if (foodCord.row == 0 || foodCord.col == MAX_COL - 1 || foodCord.row == MAX_ROW - 1 || foodCord.col == 0)
//		return false;
//	return true;
//}
//void foodDisplay(Food& food, snake* players, int playerCount)
//{
//	do {
//		food.foodPos.row = rand() % MAX_ROW;
//		food.foodPos.col = rand() % MAX_COL;
//	} while (!IsEmptySpace(food.foodPos, players, playerCount));
//	gotoRowCol(food.foodPos.row, food.foodPos.col);
//	cout << "O";
//}
//void updateSnake(snake* players, int playerCount, Food& food)
//{
//	for (int t = 0; t < playerCount; t++)
//	{
//		// making a copy :
//		Coordinate* prevBody = new Coordinate[players[t].length];
//		for (int i = 0; i < players[t].length; i++)
//		{
//			prevBody[i] = players[t].body[i];
//		}
//		/*for (int i = players[t].length - 1; i - 1 >= 0; i--)
//		{
//			players[t].body[i] = players[t].body[i-1];
//		}*/
//		moveHead(players[t]);
//		if (!isTouchingWall(players[t].body[0]))
//		{
//			gotoRowCol(players[t].body[players[t].length - 1].row, players[t].body[players[t].length - 1].col);
//			cout << " ";
//		}
//		if (players[t].body[0].row == food.foodPos.row && players[t].body[0].col == food.foodPos.col)
//		{
//			players[t].length++;
//			Coordinate* HA = new Coordinate[players[t].length];
//			for (int p = 0; p < players[t].length - 1; p++)
//				HA[p] = players[t].body[p];
//			delete[]players[t].body;
//			players[t].body = HA;
//			foodDisplay(food, players, playerCount);
//			players[t].body[players[t].length - 1] = prevBody[players[t].length - 2];
//			players[t].score++;
//		}
//		for (int i = 1; i < players[t].length; i++)
//		{
//			players[t].body[i] = prevBody[i - 1];
//		}
//		if (isTouchingWall(players[t].body[0]) )
//		{
//
//			exit(0);
//			
//		}
//		if (isThisTouchingAnySnake(t, players, playerCount))
//		{
//			cout << t; system("pause");
//			exit(0);
//		}
//		delete[]prevBody;
//	}
//}
//void userInput(snake *players)
//{
//
//		if (_kbhit())
//		{
//			switch (_getch())
//			{
//			case 'w':
//				if(players[0].direction!=DOWN)
//					players[0].direction = UP;
//				break;
//			case 's':
//				if(players[0].direction!=UP)
//					players[0].direction = DOWN;
//				break;
//			case 'a':
//				if(players[0].direction!=RIGHT)
//					players[0].direction = LEFT;
//				break;
//			case 'd':
//				if(players[0].direction!=LEFT)
//					players[0].direction = RIGHT;
//				break;
//			case 72:
//				if (players[1].direction != DOWN)
//					players[1].direction = UP;
//				break;
//			case 80:
//				if (players[1].direction != UP)
//					players[1].direction = DOWN;
//				break;
//			case 75:
//				if (players[1].direction != RIGHT)
//					players[1].direction = LEFT;
//				break;
//			case 77:
//				if (players[1].direction != LEFT)
//					players[1].direction = RIGHT;
//				break;
//			default :
//				break;
//			}
//		}
//}
////void userInput(int &direction)
////{
////	char input = 'a';
////		//do
////		//{
////			input = _getch();
////			switch (input)
////			{
////			case 'w':
////				if(direction!=DOWN)
////					direction = UP;
////				break;
////			case 's':
////				if(direction!=UP)
////					direction = DOWN;
////				break;
////			case 'a':
////				if(direction!=RIGHT)
////					direction = LEFT;
////				break;
////			case 'd':
////				if(direction!=LEFT)
////					direction = RIGHT;
////				break;
////			}
////		//} while (input != 'e');
////}
////void userInput(snake* players)
////{
////	do
////	{
////		switch (_getch())
////		{
////		case 'w':
////			if (players[0].direction != DOWN)
////				players[0].direction = UP;
////			break;
////		case 's':
////			if (players[0].direction != UP)
////				players[0].direction = DOWN;
////			break;
////		case 'a':
////			if (players[0].direction != RIGHT)
////				players[0].direction = LEFT;
////			break;
////		case 'd':
////			if (players[0].direction != LEFT)
////				players[0].direction = RIGHT;
////			break;
////		case 72:
////			if (players[1].direction != DOWN)
////				players[1].direction = UP;
////			break;
////		case 80:
////			if (players[1].direction != UP)
////				players[1].direction = DOWN;
////			break;
////		case 75:
////			if (players[1].direction != RIGHT)
////				players[1].direction = LEFT;
////			break;
////		case 77:
////			if (players[1].direction != LEFT)
////				players[1].direction = RIGHT;
////			break;
////		default:
////			break;
////		}
////	} while (true);
////}
//
//
//
//int main()
//{
//	srand(time(0));
//	int playerCount = 2;
//	snake* players;
//	Food food;
//	InitSnake(players, playerCount);
//	DisplayWalls();
//	DisplaySnake(players, playerCount);
//	foodDisplay(food, players, playerCount);
//
//	//thread p1(userInput, players);
//
//	while (true)
//	{
//		userInput(players);
//		updateSnake(players, playerCount, food);
//		DisplaySnake(players, playerCount);
//		Sleep(70);
//
//	}
//
//	gotoRowCol(40, 0);
//}