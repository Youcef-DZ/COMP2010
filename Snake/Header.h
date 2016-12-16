#include <iostream>
#include <windows.h>

using namespace std;

struct Position
{
	Position() : x(0), y(0) {}
	Position(int a, int b) : x(a), y(b) {}
	int x;
	int y;
};

char **world_ptr;
void gameOver();

class World {
public:
	World(int h, int w);
	~World();

	void draw(int y, int x, char what);
	void print();
	void clear();
	int get_width() const { return width; }
	int get_height() const { return height; }

private:
	int height;
	int width;

} world(25, 80);

class Food {

public:
	Food() : symbol('X'), 
		pos() {	pos.x = pos.y = -1;	}

	void set_pos(int x, int y) {
		pos.x = x;	pos.y = y;
	}

	void newFood(const World & field) {
		pos.x = rand() % field.get_width();
		pos.y = rand() % field.get_height();
	}

	int get_x() const { return pos.x; }
	int get_y() const { return pos.y; }
	char get_symbol() const { return symbol; }
private:
	Position pos;
	char symbol;
} food;

class Snake {
	enum { UP, DOWN, LEFT, RIGHT } dir;
	char symbol, head_symbol;
	Position pos[100];
	Position & head;
	int speed;
	int size;
	bool can_turn;
	bool alive = true;
public:
	Snake(int x, int y) :
		symbol('*'), head_symbol('O'), pos(),
		speed(1), size(1), dir(RIGHT),
		head(pos[0]), can_turn(true)
	{
		pos[0].x = x;
		pos[0].y = y;
	}

	bool isItFood(const Food & food);
	bool isAlive() { return alive; }
	void setAlive(bool l) { alive = l; }
	void getKey(const World & field);
	void move(const World & field);
	void draw(World & field);

	int get_x() const { return head.x; }
	int get_y() const { return head.y; }
	char get_symbol() const { return symbol; }
} snake(1, 1);
