//#include<iostream>
//#include<Windows.h>
//#include<thread>
//#include<conio.h>
//using namespace std;
//const int HEAD = 153;
//const int BODY = 228;
//const int MAX_ROW = 30;
//const int MAX_COL = 80;
//const int SNAKE = -1;
//const int EMPTY = 0;
//const int WALL = -2;
//const int FOOD = 1;
//const int EXIT = 4;
//int Ground[MAX_ROW][MAX_COL] = { 0 };
//
//const int RIGHT = 0;
//const int LEFT = 1;
//const int UP = 2;
//const int DOWN = 3;
// 0 direciton right (0,1)
//1 direction left   (0,-1)
//2 direction up      (-1,0)
// 3 direction down   (1,0)
//const int DirectionRow[5] = { 0,  0,-1, 1 };
//const int DirectionCol[5] = { 1, -1, 0 ,0};
//
//
//
//struct Coordinate {
//	int row, col;
//};
//struct snake {
//	int length;
//	int direction;
//	int score;
//	Coordinate *body;
// };
//
//void snakeInit(snake &player, int **Ground)
//{
//	player.length = 4;
//	player.body = new Coordinate[MAX_ROW * MAX_COL];
//	player.direction = RIGHT;
//	player.body[0].col = MAX_COL / 2;
//	player.body[0].row = MAX_ROW / 2;
//	player.score = 0;
//
//	for (int i = 1; i < player.length; i++)
//	{
//		player.body[i].col = player.body[i - 1].col - DirectionCol[player.direction];
//		player.body[i].row = player.body[i - 1].row - DirectionRow[player.direction];
//	}
//	for (int i = 0; i < player.length; i++)
//	{
//		Ground[player.body[i].row][player.body[i].col] = SNAKE;
//	}
//}
//
//
//
//
//
//
//
//
//void gotoRowCol(int rpos, int cpos)
//{
//	COORD scrn;
//	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
//	scrn.X = cpos;
//	scrn.Y = rpos;
//	SetConsoleCursorPosition(hOuput, scrn);
//}
//void GameOver(int D)
//{
//	if (D == 4)
//	{
//		gotoRowCol(MAX_ROW / 2, MAX_COL / 2);
//		cout << "GAME EXITED";
//		return;
//	}
//	gotoRowCol(MAX_ROW / 2, MAX_COL / 2);
//	cout << "GAME OVER";
//}
//void initGround(int **Ground)
//{
//	201 left top corner
//	187 top right corner
//	200 bottom left corner
//	188 bottom right corner
//	186 wall STRAIGHT 
//	205 wall horizontal
//	for (int i = 0; i < MAX_ROW; i++)
//	{
//		for (int j = 0; j < MAX_COL; j++)
//		{
//			if ((i == 0 && j == 0))
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(201);
//			}
//			else if (i == 0 && j == MAX_COL - 1)
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(187);
//			}
//			else if (i == MAX_ROW - 1 && j == 0)
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(200);
//			}
//			else if (i == MAX_ROW - 1 && j == MAX_COL - 1)
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(188);
//			}
//			else if (j == 0 && (i >= 0 && i <= MAX_ROW - 1))
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(186);
//			}
//			else if (j == MAX_COL - 1 && (i >= 0 && i <= MAX_ROW - 1))
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(186);
//			}
//			else if (i == 0 && (j >= 0 && j <= MAX_COL - 1))
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(205);
//
//			}
//			else if (i == MAX_ROW - 1 && (j >= 0 && j <= MAX_COL - 1))
//			{
//				Ground[i][j] = WALL;
//				gotoRowCol(i, j);
//				cout << char(205);
//
//			}
//			else
//				Ground[i][j] = 0;
//			
//		}
//	}
//}
//void DrawFirstScreen(Coordinate body[], int** Ground)
//{
//	for (int i = 0; i < MAX_ROW; i++)
//	{
//		for (int j = 0; j < MAX_COL; j++)
//		{
//			if (Ground[i][j] == SNAKE)
//			{
//				if (body[0].col == j && body[0].row == i)
//				{
//
//					gotoRowCol(i, j);
//					cout << char(HEAD);
//				}
//				else
//				{
//					gotoRowCol(i, j);
//					cout << char(BODY);
//				}
//			}
//			if (Ground[i][j] == FOOD)
//			{
//				gotoRowCol(i, j);
//				cout << "+";
//			}
//		}
//	}
//}
//void ScoreCard(int score)
//{
//	gotoRowCol(5, 85);
//	cout << "SCORE IS:  " << score;
//}
//void placeFood(int** Ground)
//{
//	int i=0,j=0;
//	do {
//
//		 i = rand() % MAX_ROW;
//		 j = rand() % MAX_COL;
//		
//	} while (Ground[i][j] != EMPTY);
//	Ground[i][j] = FOOD;
//
//}
//bool updateSnake(int** Ground, snake &player)
//{
//	 making a copy :
//	Coordinate* prevBody = new Coordinate[player.length];
//	for (int i = 0; i < player.length; i++)
//	{
//		prevBody[i].row = player.body[i].row;
//		prevBody[i].col = player.body[i].col;
//	}
//	player.body[0].col = player.body[0].col + DirectionCol[player.direction];
//	player.body[0].row = player.body[0].row + DirectionRow[player.direction];
//
//	
//	if (Ground[player.body[0].row][player.body[0].col] == EMPTY)
//	{
//		gotoRowCol(player.body[player.length - 1].row, player.body[player.length - 1].col);
//		cout << " ";
//		Ground[player.body[player.length - 1].row][player.body[player.length - 1].col] = EMPTY;
//	}
//	for (int i = 1; i < player.length; i++)
//	{
//		player.body[i].row = prevBody[i - 1].row;
//		player.body[i].col = prevBody[i - 1].col;
//	}
//	if (Ground[player.body[0].row][player.body[0].col] == FOOD)
//	{
//		placeFood(Ground);
//		player.length++;
//		player.body[player.length - 1] = prevBody[player.length - 2];
//		player.score++;
//	}
//	if (Ground[player.body[0].row][player.body[0].col] <EMPTY)
//	{
//		return false;
//	}
//	for (int i = 0; i < player.length; i++)
//	{
//		/*gotoRowCol(player.body[i].row, player.body[i].col);
//		cout << "-";*/
//		Ground[player.body[i].row][player.body[i].col] = SNAKE;
//	}
//	DrawFirstScreen(player.body, Ground);
//
//	delete[]prevBody;
//	return true;
//}
//void userInput(int &direction)
//{
//
//		if (_kbhit())
//		{
//			switch (_getch())
//			{
//			case 'w':
//				if(direction!=DOWN)
//					direction = UP;
//				break;
//			case 's':
//				if(direction!=UP)
//					direction = DOWN;
//				break;
//			case 'a':
//				if(direction!=RIGHT)
//					direction = LEFT;
//				break;
//			case 'd':
//				if(direction!=LEFT)
//					direction = RIGHT;
//				break;
//			case 72:
//				if (direction != DOWN)
//					direction = UP;
//				break;
//			case 80:
//				if (direction != UP)
//					direction = DOWN;
//				break;
//			case 75:
//				if (direction != RIGHT)
//					direction = LEFT;
//				break;
//			case 77:
//				if (direction != LEFT)
//					direction = RIGHT;
//				break;
//			default :
//				break;
//			}
//		}
//}
//void userInput(int &direction)
//{
//	char input = 'a';
//		do
//		{
//			input = _getch();
//			switch (input)
//			{
//			case 'w':
//				if(direction!=DOWN)
//					direction = UP;
//				break;
//			case 's':
//				if(direction!=UP)
//					direction = DOWN;
//				break;
//			case 'a':
//				if(direction!=RIGHT)
//					direction = LEFT;
//				break;
//			case 'd':
//				if(direction!=LEFT)
//					direction = RIGHT;
//				break;
//			case 72:
//				if (direction != DOWN)
//					direction = UP;
//				break;
//			case 80:
//				if (direction != UP)
//					direction = DOWN;
//				break;
//			case 75:
//				if (direction != RIGHT)
//					direction = LEFT;
//				break;
//			case 77:
//				if (direction != LEFT)
//					direction = RIGHT;
//				break;
//			case 'e':
//				direction = EXIT;
//				break;
//			default :
//				break;
//			}
//		} while (input != 'e');
//}
//
//int main()
//{
//	srand(time(0));
//	int** Ground = new int* [MAX_ROW];
//	for (int i = 0; i < MAX_ROW; i++)
//	{
//		Ground[i] = new int[MAX_COL];
//	}
//	snake player1;
//	initGround(Ground);
//	snakeInit(player1, Ground);
//	placeFood(Ground);
//	DrawFirstScreen(player1.body, Ground);
//	thread p1(userInput, ref(player1.direction));
//	while (updateSnake(Ground, player1) && player1.direction!=4)
//	{
//		userInput(player1.direction);
//		ScoreCard(player1.score);
//		gotoRowCol(20, 0);
//		if (player1.direction == UP || player1.direction == DOWN)
//			Sleep(80);
//		else
//			Sleep(50);
//	}
//	GameOver(player1.direction);
//	p1.join();
//	_getch();
//	return 0;
//}