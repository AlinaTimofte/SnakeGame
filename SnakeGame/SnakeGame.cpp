#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver;
const int height = 25;
const int width = 25;

int x, y, fruitx, fruity, score;
int tailx[100], taily[100], nrtail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection direction;
void Setup() {
	gameOver = false;
	direction = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height; //random
}
void Draw() {
	
	system("cls"); //system("clear")
	
	for (int i = 0; i < width; i++) {
		cout << "x";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "x";
			else if (i == y && j == x)
				cout << "O";
			else if (i == fruity && j == fruitx)
				cout << "*";
			else
			{
				bool show = false;
				for (int p = 0; p < nrtail; p++)
					if (tailx[p] == j && taily[p] == i)
					{
						cout << "o";
						show = true;
					}
				if(!show) cout << " ";
			}
			
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++) {
		cout << "x";
	}
	cout << endl;
	cout << "Scorul obtinut: " << score << endl;
}
void Input() {
	if (_kbhit()) {  //verifica ce tasta a fost apasata din API
		switch (_getch()) { //pentru a identifica litera tastaturii din libraria conio
		case 'w':
			direction = UP;
			break;
		case 's':
			direction = DOWN;
			break;
		case 'd':
			direction = RIGHT;
			break;
		case 'a':
			direction = LEFT;
			break;
		default:
			break;
		}
	}
}

void Logic() {

	int copiex = tailx[0];
	int copiey = taily[0];
	
	tailx[0] = x;
	taily[0] = y;
	
	int copiex2, copiey2;
	for (int i = 1; i < nrtail; i++)
	{
		copiex2 = tailx[i];
		copiey2 = taily[i];

		tailx[i] = copiex;
		taily[i] = copiey;

		copiex = copiex2;
		copiey = copiey2;
	}
	
	switch (direction) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	
	for(int k=0;k<nrtail;k++)
		if (tailx[k] == x && taily[k] == y)
			gameOver = true;
	
	if (x == fruitx && y == fruity) {
		score++;
		fruitx = rand() % width;
		fruity = rand() % height;
		nrtail++;
	}
	
}


int main()
{
    Setup();
    while(!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(40);
	}
    return 0;
}
