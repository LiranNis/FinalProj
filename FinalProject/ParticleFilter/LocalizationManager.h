/*
 * LocalizationManager.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#define UNKNOWN 2

#include "Particle.h"

class LocalizationManager
{
private:
	static const int THRESHOLD = 65,		// Threshold to keep particle
					 PAR_ADJ_FACTOR = 10,	// Indicates max distance between particles to consider them neighbors
			  	  	 SCATTER_FACTOR = 10;	// Scatter density, percentage of the map to fill
	std::list<Particle> _particles;			// Particles scattered on the grid
	int _width,_height; 					// Grid dimension
	int ** _grid; 							// The grid matrix
	void scatterParticles();				// Scatters particles on map
	void duplicateSignificant();			// Duplicates the significant particle
public:

	// Initializes the location manager and scatters particles on the grid
	LocalizationManager(int** grid, int width, int height);
	virtual ~LocalizationManager();

	// Updates the belief of the particles according to a new sample scan
	// NOTE - width and height must be odd so the center of the sample is the tested particle
	void updateByScan(int** sample, int width, int height);

	// Calculates similarity between the sample and the particle center area
	int matrixMatch(int** sample, int width, int height, int xCenter, int yCenter);

	// Updates the particle upon movement
	void updateByMove(int offsetX, int offsetY);

	// Validates offset of a point on the grid
	bool isValidOffset(int x, int y, int offsetX, int offsetY);

	// Scan the particles for the current best guess for location
	int getApporxLocation(int* apprX, int* apprY);

	void addParticles(std::list<Particle> newParticles);

	void printParticles(void* m); // DEBUG
};

#endif /* LOCALIZATIONMANAGER_H_ */
