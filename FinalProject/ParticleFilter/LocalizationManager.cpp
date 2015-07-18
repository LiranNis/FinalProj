/*
 * LocalizationManager.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */



#include "Particle.h"
#include "LocalizationManager.h"
#include "../WriteToPng/pngUtil.h"
#include <stdlib.h>
#include <time.h>
#include <ostream>

LocalizationManager::LocalizationManager(int** grid, int width, int height)
{
	this->_grid = grid;
	this->_width = width;
	this->_height = height;
	scatterParticles();
}

// Scatters particles
void LocalizationManager::scatterParticles()
{
	int i,j;

	srand(time(NULL));

	for (i = 0; i < this->_height; ++i)
	{
		for (j = 0; j < this->_width; ++j)
		{
			if (this->_grid[i][j] == FREE && rand() % 100 < SCATTER_FACTOR)
			{
				//std::cout << "Added particle [" << i << "][" << j << "]" << std::endl;
				this->_particles.push_back(Particle(i, j, THRESHOLD));
			}
		}
	}

	std::cout << "Added " << this->_particles.size() << " particles." << std::endl;
}

LocalizationManager::~LocalizationManager()
{
}

void LocalizationManager::updateByScan(int** sample, int width, int height)
{
	std::list<Particle>::iterator iter = this->_particles.begin();
	std::list<Particle> newParticles;

	while (iter != this->_particles.end())
	{
		int belief;

		// Validate the goodness of the particle
		if (!this->isValidOffset(iter->_X, iter->_Y, 0, 0))
		{
			std::cout << *iter << std::endl;

		}
		if ((this->_grid[(*iter)._X][(*iter)._Y] == BLOCKED) ||
			(belief = this->matrixMatch(sample, width, height, (*iter)._X, (*iter)._Y)) < THRESHOLD)
		{
			std::list<Particle>::iterator temp = iter;
			++iter;
			this->_particles.erase(temp);
		}
		else
		{
			iter->update(belief);
			std::list<Particle> dupParticles = iter->duplicate(this->_height, this->_width);
			newParticles.insert(newParticles.begin(), dupParticles.begin(), dupParticles.end());
			++iter;
		}
	}

	this->addParticles(newParticles);
	this->duplicateSignificant();
}

// Updates the position of the particles according to the robot movement
void LocalizationManager::updateByMove(int offsetX, int offsetY)
{
	std::list<Particle>::iterator iter = this->_particles.begin();

	while(iter != this->_particles.end())
	{
		std::list<Particle>::iterator temp = iter;
		iter++;
		if (this->isValidOffset((*temp)._X, (*temp)._Y, offsetX, offsetY))
		{
			(*temp).move(offsetX, offsetY);
		}
		else
		{
			this->_particles.erase(temp);
		}
	}
}

// Validates the offset for the new particle
bool LocalizationManager::isValidOffset(int x, int y, int offsetX, int offsetY)
{
	return 	(x + offsetX >= 0 && x + offsetX < this->_height) &&
			(y + offsetY >= 0 && y + offsetY < this->_width);
}

int LocalizationManager::matrixMatch(int** sample, int width, int height, int xCenter, int yCenter)
{
	int offX = -height / 2, offY = -width / 2, sampleX = 0, sampleY = 0;
	double 	similarity = 0,
			indications = 0;

	for (; sampleX < height; ++offX, ++sampleX)
	{
		for (offY = -width / 2, sampleY = 0; sampleY < width; ++offY, ++sampleY)
		{
			if (this->isValidOffset(xCenter, yCenter, offX, offY))
			{
				similarity += (this->_grid[xCenter + offX][yCenter + offY] == sample[sampleX][sampleY]);
				indications += (sample[sampleX][sampleY] != UNKNOWN);
			}
		}
	}

	if (indications == 0)
	{
		std::cout << ("[Particle Filter] WARNNING: sample passed in brought no indications.") << std::endl;
		indications = 1;
	}

	return ((int) ((similarity / indications) * 100));
}

void LocalizationManager::addParticles(std::list<Particle> newParticles)
{
	std::list<Particle>::iterator iterNew;

	for (iterNew = newParticles.begin(); iterNew != newParticles.end(); ++iterNew)
	{
		if (this->isValidOffset(iterNew->_X, iterNew->_Y, 0 ,0) &&
			this->_grid[iterNew->_X][iterNew->_Y] == FREE)
		{
			this->_particles.push_back(*iterNew);
		}
	}
}

int LocalizationManager::getApporxLocation(int* apprX, int* apprY)
{
	list<Particle>::iterator currPar, otherPar;
	Particle bestParticle(-1,-1,-1);
	int bestAdjCount = 0, currAdjCount = 0;

	for (currPar = this->_particles.begin(); currPar != this->_particles.end(); ++currPar)
	{
		currAdjCount = 0;
		for (otherPar = this->_particles.begin(); otherPar != this->_particles.end(); ++otherPar)
		{
			if (currPar->distanceFrom(*otherPar) < PAR_ADJ_FACTOR)
			{
				++currAdjCount;
				if (currAdjCount > bestAdjCount)
				{
					bestAdjCount = currAdjCount;
					bestParticle = *currPar;
				}
			}
		}
	}
	*apprX = bestParticle._X;
	*apprY = bestParticle._Y;
	return bestParticle._belief;
}

void LocalizationManager::duplicateSignificant()
{
	int belief,x,y;
	belief = this->getApporxLocation(&x, &y);
	Particle sigPar(x, y, belief);
	this->addParticles(sigPar.duplicate(this->_height, this->_width));
}

//------------------------------------------------------------------
//-----------------------DEBUG SECTION------------------------------
//------------------------------------------------------------------

#include "../Map.h"
void LocalizationManager::printParticles(void* m)
{
	Map* map = (Map*)m;
	char* filename = "Particles.png";
	std::list<int> particles;
	std::list<Particle>::iterator iter = this->_particles.begin();

	while(iter != this->_particles.end())
	{
		int point = iter->_X * this->_width + iter->_Y;
		if (point < 0 || point > (this->_width * this->_height))
			std::cout << "Invalid point to draw [ " << point << "]" << std::endl;
		particles.push_back(point);
		++iter;
	}

	std::cout << "Prints " << particles.size() << " points" << std::endl;

	map->Set_A_StarGridPointsOnMap(particles, filename);
}

//------------------------------------------------------------------
//-----------------------DEBUG SECTION END--------------------------
//------------------------------------------------------------------
