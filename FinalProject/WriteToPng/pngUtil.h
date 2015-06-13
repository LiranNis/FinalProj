/*
 * pngUtil.h
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */

#ifndef PNGUTIL_H_
#define PNGUTIL_H_
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
void decodeOneStep(const char* filename);
void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename);
void InflateToGridMap(string filename, double InflateNumber, double PixelToCM, double GridSize);

#define BLOCKED 1
#define FREE 0


#endif /* PNGUTIL_H_ */
