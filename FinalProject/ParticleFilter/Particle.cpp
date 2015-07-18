/*
 * Particle.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Particle.h"

Particle::Particle(int x, int y, int belief)
{
	this->_X = x;
	this->_Y = y;
	this->_belief = belief;
}

Particle::~Particle()
{
	// TODO Auto-generated destructor stub
}

void Particle::update(int newBelief)
{
	this->_belief = newBelief;
}

std::list<Particle> Particle::duplicate(int xMax, int yMax)
{
	std::list<Particle> newParticles;
	int i = 0,
		x,
		y,
		belief = this->_belief;
	srand(time(NULL));

	// Generate new particles
	for (; i < GROWTH_FACTOR; ++i)
	{
		int seed = 0;

		seed = rand() % RANDOMIZATION_FACTOR;

		if (this->_X - seed < xMax && this->_X - seed >= 0)
		{
			x = this->_X - seed;
		}
		else if (this->_X + seed < xMax && this->_X + seed >= 0)
		{
			x = this->_X + seed;
		}
		else continue;

		seed = rand() % RANDOMIZATION_FACTOR;

		if (this->_Y - seed < yMax && this->_Y - seed >= 0)
		{
			y = this->_Y - seed;
		}
		else if (this->_Y + seed < yMax && this->_Y + seed >= 0)
		{
			y = this->_Y + seed;
		}
		else continue;

		newParticles.push_back(Particle(x,y,belief));
	}

	return newParticles;
}

int Particle::distanceFrom(Particle other)
{
	return sqrt(((this->_Y - other._Y) * (this->_Y - other._Y)) +
	((this->_X - other._X) * (this->_X - other._X)));
}

void Particle::move(int offsetX, int offsetY)
{
	this->_X += offsetX;
	this->_Y += offsetY;
}

bool Particle::operator ==(const Particle& pOther)
{
	return (this->_X == pOther._X && this->_Y == pOther._Y);
}
