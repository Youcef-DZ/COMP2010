#include <iostream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

const int DEFAULT_WORLD_SIZE = 20;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Position
{
	Position(int a, int b) : x(a), y(b) {}
	int x;
	int y;
};

class Tile;
typedef Tile* Tile_ptr;

class Tile
{
public:
	Tile() : position(0, 0) {}
	Tile(int a, int b) : position(a, b) {}
	Position get_position() { return position; }
	void set_position(Position pos) { position = pos; }
	virtual void draw() = 0;
	friend void swap_position(Tile_ptr& first, Tile_ptr& second);

private:
	Position position;
};

typedef Tile* Tile_ptr;

class Blob : public Tile
{
public:
	Blob() : health(1) {}
	Blob(int a, int b) : Tile(a, b), health(1) {}
	Blob(int a, int b, int h) : Tile(a, b), health(h) {}

private:
	int health;
};

class Empty : public Tile
{
public:
	Empty() {}
	Empty(int a, int b) : Tile(a, b) {}
	virtual void draw();


private:
};

class Yellow_blob : public Blob
{
public:
	Yellow_blob() {}
	Yellow_blob(int a, int b) : Blob(a, b) {}
	virtual void draw();


private:
};

class Cyan_blob : public Blob
{
public:
	Cyan_blob() {}
	Cyan_blob(int a, int b) : Blob(a, b) {}
	void draw();


private:
};

class World
{
public:
	World();
	explicit World(int length);
	World(int width, int height);


	//private:
	void shuffle();
	//private:
	int height;
	int width;
	Tile_ptr** grid;
};


int main()
{
	World world;

	for (int i = 0; i < world.height; i++)
	{
		for (int j = 0; j < world.width; j++)
		{
			world.grid[i][j]->draw();
		}
	}

	system("pause");
	return 0;
}

void Empty::draw()
{
	gotoxy(get_position().x, get_position().y);
	cout << " " << endl;
}

void Yellow_blob::draw()
{
	gotoxy(get_position().x, get_position().y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "O" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Cyan_blob::draw()
{
	gotoxy(get_position().x, get_position().y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN |
		FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "O" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);
}

World::World()
{
	int cyan_blobs = 10;
	int yellow_blobs = 20;
	height = width = DEFAULT_WORLD_SIZE;

	grid = new Tile_ptr*[height];
	for (int i = 0; i < height; i++)
	{
		grid[i] = new Tile_ptr[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (cyan_blobs > 0)
			{
				grid[i][j] = new Cyan_blob(j, i);
				cyan_blobs--;
			}
			else if (yellow_blobs > 0)
			{
				grid[i][j] = new Yellow_blob(j, i);
				yellow_blobs--;
			}
			else
			{
				grid[i][j] = new Empty(j, i);
			}
		}
	}
	shuffle();

}

World::World(int length)
{

}

World::World(int width, int height)
{

}

void World::shuffle()
{
	int x1, x2;
	int y1, y2;

	for (int i = 0; i < 10000; i++)
	{
		x1 = rand() % width;
		x2 = rand() % width;

		y1 = rand() % height;
		y2 = rand() % height;

		swap_position(grid[y1][x1], grid[y2][x2]);
	}

}

void swap_position(Tile_ptr& first, Tile_ptr& second)
{
	swap(first->position, second->position);
	swap(first, second);
}