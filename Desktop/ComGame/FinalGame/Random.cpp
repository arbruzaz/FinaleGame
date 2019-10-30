#include "Random.h"

Random::Random()
{
}

int Random::generateRandom(int max)
{
	int randomnumber = rand();
	float random = (randomnumber % max) + 1;
	int myrandom = random;

	return myrandom;
}

int Random::generateRandom0(int max)
{
	int randomnumber = rand();
	float random = (randomnumber % max);
	int myrandom = random;

	return myrandom;
}

bool Random::generateRandombool()
{
	int randomnumber = rand();
	float random = (randomnumber % 2) + 1;
	int myrandom = random;
	if (myrandom == 1) { return true; }
	else { return false; }
}
