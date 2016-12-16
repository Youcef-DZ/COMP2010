#include "Header.h"

int main() {
	world.clear();

	food.set_pos(5, 5);

	while (snake.isAlive()) {
		world.clear();

		snake.getKey(world);
		try {
			snake.move(world);
		}
		catch (const char * er) {
			world.clear();
			cerr << er << endl;
			system("pause");
			return -1;
		}
		snake.draw(world);
		world.draw(food.get_y(), food.get_x(), food.get_symbol());


		if (snake.isItFood(food)) {
			food.newFood(world);
		}

		world.print();

		Sleep(250);
		system("cls");
	}

	return 0;
}

World::World(int h, int w)
{
	height = h; width = w;
	world_ptr = new char*[World::height];
	for (int c = 0; c < World::height; ++c) {
		world_ptr[c] = new char[World::width];
	}
}

World::~World()
{
	for (int c = 0; c < World::height; ++c) {
		delete[] world_ptr[c];
	}
	delete[] world_ptr;
}

void World::print()
{
	for (int c = 0; c < height; ++c) {
		for (int r = 0; r < width; ++r) {
			cout << world_ptr[c][r];
		}
		cout << endl;
	}
}

void World::clear()
{
	for (int c = 0; c < height; ++c) {
		for (int r = 0; r < width; ++r) {
			world_ptr[c][r] = ' ';
		}
	}
}

void World::draw(int y, int x, char what)
{
	world_ptr[y][x] = what;
}

bool Snake::isItFood(const Food & food)
{
	if (food.get_x() == head.x && food.get_y() == head.y) {
		size += 1;
		return true;
	}
	return false;
}

void Snake::getKey(const World & field)
{
	if (GetAsyncKeyState(VK_UP) && dir != DOWN) {
		dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN) && dir != UP) {
		dir = DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) && dir != RIGHT) {
		dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) && dir != LEFT) {
		dir = RIGHT;
	}
}

void Snake::move(const World & field)
{
	Position next = { 0, 0 };
	switch (dir) {
	case UP:
		next.y = -speed;
		break;
	case DOWN:
		next.y = speed;
		break;
	case LEFT:
		next.x = -speed;
		break;
	case RIGHT:
		next.x = speed;
	}
	for (int c = size - 1; c > 0; --c) {
		pos[c] = pos[c - 1];
	}
	head.x += next.x;
	head.y += next.y;

	if (head.x < 0 || head.y < 0 || head.x >= field.get_width() || head.y >= field.get_height()) {
		snake.setAlive(false);
		gameOver();
	}
}

void gameOver() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | 4 | 4);

	cout << "                                    \n" <<
		"OOOoooO   OooooOo OooooooOo Ooooo		\n" <<
		"O     o   O     O O   O   O O			\n" <<
		"O oOo     OoooooO O   O   O Ooooo		\n" <<
		"O    o    O     O O       O O			\n" <<
		"OooooO    O     O O       O Ooooo		\n" <<
		"										 \n" <<
		"OoooooO  oOo  oOo  Ooooo   OooooOo		\n" <<
		"o     o    O  O    O       O     O	 \n" <<
		"o     o    O  O    Ooooo   Oooooooo	\n" <<
		"o     o    O  o    O       O     O		\n" <<
		"OoooooO     oo     Ooooo   O     Oo	\n" <<
		"										\n" <<
		"										\n";
	system("pause");
	exit(0);
}

void Snake::draw(World & world)
{
	for (int c = 0; c < size; ++c) {
		if (c == 0) {
			world.draw(pos[c].y, pos[c].x, head_symbol);
		}
		else {
			world.draw(pos[c].y, pos[c].x, symbol);
		}
	}
}

