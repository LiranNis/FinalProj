/*
 * Particle.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <list>
#include <ostream>
#define GROWTH_FACTOR 5
#define RANDOMIZATION_FACTOR 7

class Particle {
public:
	Particle(int x, int y, int belief);
	virtual ~Particle();
	int _X,_Y,_belief;

	// Update the belief
	void update(int newBelief);

	// Update the particle position by given offset
	void move(int offsetX, int offsetY);

	// Create duplicates of the particle around it and return as list
	std::list<Particle> duplicate(int xMax, int yMax);

	// Calculate distance from another particle
	int distanceFrom(Particle other);

	// Comparison operator overloaded to compare two particles
	bool operator ==(const Particle& pOther);

	// Output operator for debug purposes
	friend std::ostream &operator<<( std::ostream &output,
	                                   const Particle &p )
	{
		 output << "X : " << p._X << " Y : " << p._Y << " belief : " << p._belief;
		 return output;
	}
};

#endif /* PARTICLE_H_ */
