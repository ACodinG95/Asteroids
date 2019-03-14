#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>
#include <SDL2\SDL.h>
#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <iostream>
#include <math.h>
#include "Display.h"
#include <random>

class Asteroid
{
public:

	int size;
	float Position[2];
	float Corners[6];
	float Distance;


	float speed;
	float angle;


	int sizeM1;
	float PositionM1[2];
	float CornersM1[6];
	float DistanceM1;
	float speedM1;
	float angleM1;

	int sizeM2;
	float PositionM2[2];
	float CornersM2[6];
	float DistanceM2;
	float speedM2;
	float angleM2;

	bool BigExist;
	bool Small1Exist;
	bool Small2Exist;


	Asteroid();
	virtual ~Asteroid();

	void SetCorners();
	void DrawAst();
	void Move();
	void SetPosition();
	void FragmentAsteroid();


};







#endif
