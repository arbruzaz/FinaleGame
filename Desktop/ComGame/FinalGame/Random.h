#pragma once
#include <stdio.h>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <functional>
using namespace std;
class Random
{
	Random();
	int generateRandom(int max);
	int generateRandom0(int max);
	bool generateRandombool();
};

