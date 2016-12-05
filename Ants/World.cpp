#include "Header.h"

void Empty::draw()
{
	gotoxy(getPosition().x, getPosition().y);
	cout << " ";
}

void DoodleBug::draw()
{
	gotoxy(getPosition().x, getPosition().y);
	setConsuleColor(4, 4, 4);
	cout << "X";
	setConsuleColor(4, 2, 1);
}

void Ant::draw()
{
	gotoxy(getPosition().x, getPosition().y);
	setConsuleColor(2, 2, 2);
	cout << "O";
	setConsuleColor(4, 2, 1);
}

World::World()
{
	int ants = 100;
	int doodleBugs = 5;

	width = 20;
	height = 20;
	grid = new OrganismPtr*[height];
	for (int i = 0; i < height; i++)
	{
		grid[i] = new OrganismPtr[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (ants > 0)
			{
				grid[i][j] = new Ant(j, i);
				ants--;
			}
			else if (doodleBugs > 0)
			{
				grid[i][j] = new DoodleBug(j, i);
				doodleBugs--;
			}
			else
			{
				grid[i][j] = new Empty(j, i);
			}
		}
	}
	shuffle();
}

void World::shuffle()
{
	for (int i = 0; i < 10000; i++)
	{
		int x1 = rand() % width;
		int y1 = rand() % height;
		int x2 = rand() % width;
		int y2 = rand() % height;

		critterSwap(grid[y1][x1], grid[y2][x2]);
	}
}

void Organism::positionSwap(Organism& other)
{
	swap(position, other.position);
}

void World::critterSwap(OrganismPtr& first, OrganismPtr& second)
{
	first->positionSwap(*second);
	swap(first, second);
}

void DoodleBug::move(World& w)
{
	int x1, y1, x2 = -1, y2 = -1;

	x1 = getPosition().x;
	y1 = getPosition().y;

	if (y1 > 0 && w.grid[y1 - 1][x1]->who() == ANT) // try eat an ant up first
	{
		w.grid[y1 - 1][x1] = new DoodleBug(x1, y1 - 1);
		w.grid[y1][x1] = new Empty(x1, y1);
		setStarveLife(0);
	}
	else if ((y1 < w.getHeight() - 1) && (w.grid[y1 + 1][x1]->who() == ANT))// try eat an ant  down
	{
		w.grid[y1 + 1][x1] = new DoodleBug(x1, y1 + 1);
		w.grid[y1][x1] = new Empty(x1, y1);
		setStarveLife(0);
	}
	else if ((x1 > 0) && (w.grid[y1][x1 - 1]->who() == ANT))// try eat an ant  left
	{
		w.grid[y1][x1 - 1] = new DoodleBug(x1 - 1, y1);
		w.grid[y1][x1] = new Empty(x1, y1);
		setStarveLife(0);
	}
	else if ((x1 < w.getWidth() - 1) && (w.grid[y1][x1 + 1]->who() == ANT))// try eat an ant  right
	{
		w.grid[y1][x1 + 1] = new DoodleBug(x1 + 1, y1);
		w.grid[y1][x1] = new Empty(x1, y1);
		setStarveLife(0);
	}
	else {
		setStarveLife(getStarveLife() + 1);
		Direction direction;
		direction = static_cast<Direction>(rand() % NUMBER_OF_DIRECTIONS);
		switch (direction)
		{
		case UP:
			if (y1 > 0)
			{
				if (w.grid[y1 - 1][x1]->who() == EMPTY)
				{
					x2 = x1;
					y2 = y1 - 1;
				}
			}
			break;
		case DOWN:
			if (y1 < w.getHeight() - 1)
			{
				if (w.grid[y1 + 1][x1]->who() == EMPTY)
				{
					x2 = x1;
					y2 = y1 + 1;
				}
			}
			break;
		case LEFT:
			if (x1 > 0)
			{
				if (w.grid[y1][x1 - 1]->who() == EMPTY)
				{
					x2 = x1 - 1;
					y2 = y1;
				}
			}
			break;
		case RIGHT:
			if (x1 < w.getWidth() - 1)
			{
				if (w.grid[y1][x1 + 1]->who() == EMPTY)
				{
					x2 = x1 + 1;
					y2 = y1;
				}
			}
			break;
		}
		if (x2 != -1)
		{
			w.critterSwap(w.grid[y1][x1], w.grid[y2][x2]);
		}
	}
	setLife(getLife() + 1);

	if (getStarveLife() > 2) {
		starve(w);
	}
	else if (getLife() > 7) {
		breed(w);
	}
}

void DoodleBug::breed(World & w)
{
	setLife(0); // reset life timer
	int x1, y1, x2 = -1, y2 = -1;
	x1 = getPosition().x;
	y1 = getPosition().y;

	if (y1 > 0 && w.grid[y1 - 1][x1]->who() == EMPTY) // try breed up first
	{
		w.grid[y1 - 1][x1] = new DoodleBug(x1, y1 - 1);
	}
	else if ((y1 < w.getHeight() - 1) && (w.grid[y1 + 1][x1]->who() == EMPTY))// try breed down
	{
		w.grid[y1 + 1][x1] = new DoodleBug(x1, y1 + 1);
	}
	else if ((x1 > 0) && (w.grid[y1][x1 - 1]->who() == EMPTY))// try breed left
	{
		w.grid[y1][x1 - 1] = new DoodleBug(x1 - 1, y1);
	}
	else if ((x1 < w.getWidth() - 1) && (w.grid[y1][x1 + 1]->who() == EMPTY))// try breed right
	{
		w.grid[y1][x1 + 1] = new DoodleBug(x1 + 1, y1);
	}
}

void DoodleBug::starve(World & w)
{
	int x1, y1;
	x1 = getPosition().x;
	y1 = getPosition().y;
	w.grid[y1][x1] = new Empty(x1, y1);
}

void Ant::move(World& w)
{
	Direction direction;
	int x1, y1, x2 = -1, y2 = -1;

	direction = static_cast<Direction>(rand() % NUMBER_OF_DIRECTIONS);
	x1 = getPosition().x;
	y1 = getPosition().y;
	switch (direction)
	{
	case UP:
		if (y1 > 0)
		{
			if (w.grid[y1 - 1][x1]->who() == EMPTY)
			{
				x2 = x1;
				y2 = y1 - 1;
			}
		}
		break;
	case DOWN:
		if (y1 < w.getHeight() - 1)
		{
			if (w.grid[y1 + 1][x1]->who() == EMPTY)
			{
				x2 = x1;
				y2 = y1 + 1;
			}
		}
		break;
	case LEFT:
		if (x1 > 0)
		{
			if (w.grid[y1][x1 - 1]->who() == EMPTY)
			{
				x2 = x1 - 1;
				y2 = y1;
			}
		}
		break;
	case RIGHT:
		if (x1 < w.getWidth() - 1)
		{
			if (w.grid[y1][x1 + 1]->who() == EMPTY)
			{
				x2 = x1 + 1;
				y2 = y1;
			}
		}
		break;
	}
	if (x2 != -1)
	{
		w.critterSwap(w.grid[y1][x1], w.grid[y2][x2]);
	}

	setLife(getLife() + 1);
	if (getLife() > 2) {
		breed(w);
	}
}

void Ant::breed(World & w)
{
	setLife(0); // reset life timer
	int x1, y1, x2 = -1, y2 = -1;
	x1 = getPosition().x;
	y1 = getPosition().y;

	if (y1 > 0 && w.grid[y1 - 1][x1]->who() == EMPTY) // try breed up first
	{
		w.grid[y1 - 1][x1] = new Ant(x1, y1 - 1);
	}
	else if ((y1 < w.getHeight() - 1) && (w.grid[y1 + 1][x1]->who() == EMPTY))// try breed down
	{
		w.grid[y1 + 1][x1] = new Ant(x1, y1 + 1);
	}
	else if ((x1 > 0) && (w.grid[y1][x1 - 1]->who() == EMPTY))// try breed left
	{
		w.grid[y1][x1 - 1] = new Ant(x1 - 1, y1);
	}
	else if ((x1 < w.getWidth() - 1) && (w.grid[y1][x1 + 1]->who() == EMPTY))// try breed right
	{
		w.grid[y1][x1 + 1] = new Ant(x1 + 1, y1);
	}
}

OrganismPtr* World::operator[](int index)
{
	return grid[index];
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setFontSize(int FontSize)
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize;
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

void setConsuleColor(int c1, int c2, int c3)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c1 | c2 | c3);
}