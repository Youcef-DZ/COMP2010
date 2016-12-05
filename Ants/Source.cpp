#include "Header.h"

int main()
{
	srand(time(0));
	setFontSize(20);
	World world;

	for (;;)
	{
		vector<OrganismPtr> doodleBugs;
		vector<OrganismPtr> ants;
		for (int i = 0; i < world.getHeight(); i++)
		{
			for (int j = 0; j < world.getWidth(); j++)
			{
				world.grid[i][j]->draw();
				if (world.grid[i][j]->who() == DOODLEBUG)
				{
					doodleBugs.push_back(world[i][j]);
				}
				if (world[i][j]->who() == ANT)
				{
					ants.push_back(world[i][j]);
				}
			}
		}

		for (auto p = doodleBugs.begin(); p != doodleBugs.end(); p++)
		{
			(*p)->move(world);
		}

		for (auto p = ants.begin(); p != ants.end(); p++)
		{
			(*p)->move(world);
		}

		cin.get();
	}
	return 0;
}
