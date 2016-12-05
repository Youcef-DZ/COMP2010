#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>

using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT, NUMBER_OF_DIRECTIONS };
enum TYPE { EMPTY, DOODLEBUG, ANT, NUMBER_OF_TYPES };

class World;
class Organism;
typedef Organism* OrganismPtr;

void setConsuleColor(int c1, int c2, int c3);
void setFontSize(int FontSize);
void gotoxy(int x, int y);

struct Position
{
	Position(int a, int b) : x(a), y(b) {}
	int x;
	int y;
};

class Organism
{
public:
	Organism() :position(0, 0) {}
	Organism(int a, int b) : position(a, b) {}
	Position getPosition() { return position; }
	void setPosition(Position pos) { position = pos; }
	int getLife() { return life; }
	void setLife(int l) { life = l; }
	void positionSwap(Organism& other);
	virtual void draw() = 0;
	virtual void move(World& w) = 0;
	virtual void breed(World& w) = 0;
	virtual TYPE who() = 0;

private:
	Position position;
	int life = 0;
};

class Empty : public Organism
{
public:
	Empty() {}
	Empty(int a, int b) : Organism(a, b) {}
	virtual void draw();
	virtual void move(World& w) {}
	virtual void breed(World& w) {}
	virtual TYPE who() { return EMPTY; }

private:
};

class DoodleBug : public Organism
{
public:
	DoodleBug() {}
	DoodleBug(int a, int b) : Organism(a, b) {}
	virtual void draw();
	virtual void move(World& w);
	virtual void breed(World& w);
	virtual void starve(World& w);
	virtual TYPE who() { return DOODLEBUG; }
	void setStarveLife(int val) { starveLife = val; }
	int getStarveLife() { return starveLife; }

private:
	int starveLife = 0;
};

class Ant : public Organism
{
public:
	Ant() {}
	Ant(int a, int b) : Organism(a, b) {}
	virtual void draw();
	virtual void move(World& w);
	virtual void breed(World& w);
	virtual TYPE who() { return ANT; }

private:
};

class World
{
public:
	World();
	void critterSwap(OrganismPtr& first, OrganismPtr& second);
	int getHeight() { return height; }
	int getWidth() { return width; }
	OrganismPtr* operator[](int index);

private:
	int width;
	int height;
	void shuffle();

public:
	OrganismPtr** grid;
};