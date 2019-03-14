#define NOMINMAX

#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <SDL2\SDL.h>
#include "Display.h"
#include "Asteroid.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <math.h>
#include <random>
#include <ctime>
#include <algorithm>

static unsigned int	CompileShader(unsigned int type,const std::string& source ){
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id,1,&src,nullptr);
	glCompileShader(id);

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{

	unsigned int program = glCreateProgram();
	unsigned int vs =	CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program,vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
		 
	return program;

}

const float degree = 0.0017;


long unsigned int slow = 1000000;
float ShipMaxSpeed = 0.01;
float CurrentSpeed = 0;

unsigned int Score;

bool ScoreShown = false;

void AsteroidShot(Asteroid &target, float &ShotLocationX, float &ShotLocationY, float &ShotEndX, float &ShotEndY) {

	bool Collison = false;


	if(target.BigExist){
	float TopMostPoint = std::max(target.Corners[1], target.Corners[3]);
	TopMostPoint = std::max(TopMostPoint, target.Corners[5]);

	float BottomMostPoint = std::min(target.Corners[1], target.Corners[3]);
	BottomMostPoint = std::min(BottomMostPoint, target.Corners[5]);

	float LeftMostPoint = std::min(target.Corners[0], target.Corners[2]);
	LeftMostPoint = std::min(LeftMostPoint, target.Corners[4]);

	float RightMostPoint = std::max(target.Corners[0], target.Corners[2]);
	RightMostPoint = std::max(RightMostPoint, target.Corners[4]);

	if (ShotLocationY < TopMostPoint && ShotLocationY > BottomMostPoint && ShotLocationX < RightMostPoint && ShotLocationX > LeftMostPoint) { Collison = true; }

	if (Collison) {
		Collison = false;
		ShotLocationX = 2;
		ShotLocationY = 2;

		ShotEndX = 2.003;
		ShotEndY = 2;
		target.BigExist = false;
		target.FragmentAsteroid();
		Score = Score + 1;
	}}
	else {
		float TopMostPoint = std::max(target.CornersM2[1], target.CornersM2[3]);
		TopMostPoint = std::max(TopMostPoint, target.CornersM2[5]);

		float BottomMostPoint = std::min(target.CornersM2[1], target.CornersM2[3]);
		BottomMostPoint = std::min(BottomMostPoint, target.CornersM2[5]);

		float LeftMostPoint = std::min(target.CornersM2[0], target.CornersM2[2]);
		LeftMostPoint = std::min(LeftMostPoint, target.CornersM2[4]);

		float RightMostPoint = std::max(target.CornersM2[0], target.CornersM2[2]);
		RightMostPoint = std::max(RightMostPoint, target.CornersM2[4]);

		if (ShotLocationY < TopMostPoint && ShotLocationY > BottomMostPoint && ShotLocationX < RightMostPoint && ShotLocationX > LeftMostPoint) { Collison = true; }

		if (Collison) {
			Collison = false;
			ShotLocationX = 2;
			ShotLocationY = 2;

			ShotEndX = 2.003;
			ShotEndY = 2;

			target.PositionM2[0] = 400;
			target.PositionM2[1] = 400;

			target.Small2Exist = false;

			Score = Score + 2;}

		Collison = false;

		TopMostPoint = std::max(target.CornersM1[1], target.CornersM1[3]);
		TopMostPoint = std::max(TopMostPoint, target.CornersM1[5]);

		BottomMostPoint = std::min(target.CornersM1[1], target.CornersM1[3]);
		BottomMostPoint = std::min(BottomMostPoint, target.CornersM1[5]);

		LeftMostPoint = std::min(target.CornersM1[0], target.CornersM1[2]);
		LeftMostPoint = std::min(LeftMostPoint, target.CornersM1[4]);

		RightMostPoint = std::max(target.CornersM1[0], target.CornersM1[2]);
		RightMostPoint = std::max(RightMostPoint, target.CornersM1[4]);

		if (ShotLocationY < TopMostPoint && ShotLocationY > BottomMostPoint && ShotLocationX < RightMostPoint && ShotLocationX > LeftMostPoint) { Collison = true; }

		if (Collison) {
			Collison = false;
			ShotLocationX = 2;
			ShotLocationY = 2;

			ShotEndX = 2.003;
			ShotEndY = 2;

			target.PositionM1[0] = 400;
			target.PositionM1[1] = 400;

			target.Small1Exist = false;

			Score = Score + 2;
		}
	}
}

bool ShipCollison(Asteroid obs, float position[6]) {

	bool Collide = false;

	float TopMostPoint = std::max(position[1], position[3]);
	TopMostPoint = std::max(TopMostPoint, position[5]);

	float BottomMostPoint = std::min(position[1], position[3]);
	BottomMostPoint = std::min(BottomMostPoint, position[5]);

	float LeftMostPoint = std::min(position[0], position[2]);
	LeftMostPoint = std::min(LeftMostPoint, position[4]);

	float RightMostPoint = std::max(position[0], position[2]);
	RightMostPoint = std::max(RightMostPoint, position[4]);


	if ((obs.Corners[1] < TopMostPoint) && (obs.Corners[1] > BottomMostPoint) && (obs.Corners[0] < RightMostPoint) && (obs.Corners[0] > LeftMostPoint)) { Collide = true; }
	if ((obs.Corners[3] < TopMostPoint) && (obs.Corners[3] > BottomMostPoint) && (obs.Corners[2] < RightMostPoint) && (obs.Corners[2] > LeftMostPoint)) { Collide = true; }
	if ((obs.Corners[5] < TopMostPoint) && (obs.Corners[5] > BottomMostPoint) && (obs.Corners[4] < RightMostPoint) && (obs.Corners[4] > LeftMostPoint)) { Collide = true; }



	TopMostPoint = std::max(obs.Corners[1], obs.Corners[3]);
	TopMostPoint = std::max(TopMostPoint, obs.Corners[5]);

	BottomMostPoint = std::min(obs.Corners[1], obs.Corners[3]);
	BottomMostPoint = std::min(BottomMostPoint, obs.Corners[5]);

	LeftMostPoint = std::min(obs.Corners[0], obs.Corners[2]);
	LeftMostPoint = std::min(LeftMostPoint, obs.Corners[4]);

	RightMostPoint = std::max(obs.Corners[0], obs.Corners[2]);
	RightMostPoint = std::max(RightMostPoint, obs.Corners[4]);


	if ((position[1] < TopMostPoint) && (position[1] > BottomMostPoint) && (position[0] < RightMostPoint) && (position[0] > LeftMostPoint)) { Collide = true; }
	if ((position[3] < TopMostPoint) && (position[3] > BottomMostPoint) && (position[2] < RightMostPoint) && (position[2] > LeftMostPoint)) { Collide = true; }
	if ((position[5] < TopMostPoint) && (position[5] > BottomMostPoint) && (position[4] < RightMostPoint) && (position[4] > LeftMostPoint)) { Collide = true; }


	return Collide;

}

bool ShipCollisonM1(Asteroid obs, float position[6]) {

	bool Collide = false;

	float TopMostPoint = std::max(position[1], position[3]);
	TopMostPoint = std::max(TopMostPoint, position[5]);

	float BottomMostPoint = std::min(position[1], position[3]);
	BottomMostPoint = std::min(BottomMostPoint, position[5]);

	float LeftMostPoint = std::min(position[0], position[2]);
	LeftMostPoint = std::min(LeftMostPoint, position[4]);

	float RightMostPoint = std::max(position[0], position[2]);
	RightMostPoint = std::max(RightMostPoint, position[4]);


	if ((obs.CornersM1[1] < TopMostPoint) && (obs.CornersM1[1] > BottomMostPoint) && (obs.CornersM1[0] < RightMostPoint) && (obs.CornersM1[0] > LeftMostPoint)) { Collide = true; }
	if ((obs.CornersM1[3] < TopMostPoint) && (obs.CornersM1[3] > BottomMostPoint) && (obs.CornersM1[2] < RightMostPoint) && (obs.CornersM1[2] > LeftMostPoint)) { Collide = true; }
	if ((obs.CornersM1[5] < TopMostPoint) && (obs.CornersM1[5] > BottomMostPoint) && (obs.CornersM1[4] < RightMostPoint) && (obs.CornersM1[4] > LeftMostPoint)) { Collide = true; }



	TopMostPoint = std::max(obs.CornersM1[1], obs.CornersM1[3]);
	TopMostPoint = std::max(TopMostPoint, obs.CornersM1[5]);

	BottomMostPoint = std::min(obs.CornersM1[1], obs.CornersM1[3]);
	BottomMostPoint = std::min(BottomMostPoint, obs.CornersM1[5]);

	LeftMostPoint = std::min(obs.CornersM1[0], obs.CornersM1[2]);
	LeftMostPoint = std::min(LeftMostPoint, obs.CornersM1[4]);

	RightMostPoint = std::max(obs.CornersM1[0], obs.CornersM1[2]);
	RightMostPoint = std::max(RightMostPoint, obs.CornersM1[4]);


	if ((position[1] < TopMostPoint) && (position[1] > BottomMostPoint) && (position[0] < RightMostPoint) && (position[0] > LeftMostPoint)) { Collide = true; }
	if ((position[3] < TopMostPoint) && (position[3] > BottomMostPoint) && (position[2] < RightMostPoint) && (position[2] > LeftMostPoint)) { Collide = true; }
	if ((position[5] < TopMostPoint) && (position[5] > BottomMostPoint) && (position[4] < RightMostPoint) && (position[4] > LeftMostPoint)) { Collide = true; }


	return Collide;

}

bool ShipCollisonM2(Asteroid obs, float position[6]) {

	bool Collide = false;

	float TopMostPoint = std::max(position[1], position[3]);
	TopMostPoint = std::max(TopMostPoint, position[5]);

	float BottomMostPoint = std::min(position[1], position[3]);
	BottomMostPoint = std::min(BottomMostPoint, position[5]);

	float LeftMostPoint = std::min(position[0], position[2]);
	LeftMostPoint = std::min(LeftMostPoint, position[4]);

	float RightMostPoint = std::max(position[0], position[2]);
	RightMostPoint = std::max(RightMostPoint, position[4]);


	if ((obs.CornersM2[1] < TopMostPoint) && (obs.CornersM2[1] > BottomMostPoint) && (obs.CornersM2[0] < RightMostPoint) && (obs.CornersM2[0] > LeftMostPoint)) { Collide = true; }
	if ((obs.CornersM2[3] < TopMostPoint) && (obs.CornersM2[3] > BottomMostPoint) && (obs.CornersM2[2] < RightMostPoint) && (obs.CornersM2[2] > LeftMostPoint)) { Collide = true; }
	if ((obs.CornersM2[5] < TopMostPoint) && (obs.CornersM2[5] > BottomMostPoint) && (obs.CornersM2[4] < RightMostPoint) && (obs.CornersM2[4] > LeftMostPoint)) { Collide = true; }



	TopMostPoint = std::max(obs.CornersM2[1], obs.CornersM2[3]);
	TopMostPoint = std::max(TopMostPoint, obs.CornersM2[5]);

	BottomMostPoint = std::min(obs.CornersM2[1], obs.CornersM2[3]);
	BottomMostPoint = std::min(BottomMostPoint, obs.CornersM2[5]);

	LeftMostPoint = std::min(obs.CornersM2[0], obs.CornersM2[2]);
	LeftMostPoint = std::min(LeftMostPoint, obs.CornersM2[4]);

	RightMostPoint = std::max(obs.CornersM2[0], obs.CornersM2[2]);
	RightMostPoint = std::max(RightMostPoint, obs.CornersM2[4]);


	if ((position[1] < TopMostPoint) && (position[1] > BottomMostPoint) && (position[0] < RightMostPoint) && (position[0] > LeftMostPoint)) { Collide = true; }
	if ((position[3] < TopMostPoint) && (position[3] > BottomMostPoint) && (position[2] < RightMostPoint) && (position[2] > LeftMostPoint)) { Collide = true; }
	if ((position[5] < TopMostPoint) && (position[5] > BottomMostPoint) && (position[4] < RightMostPoint) && (position[4] > LeftMostPoint)) { Collide = true; }


	return Collide;

}





int main(int argc, char *args[]){

	Display display(800, 600, "Asteroids");

	Score = 0;
	bool Lost = false;

	Asteroid comet;
	comet.size = 2;
	comet.Position[0] = -0.5;
	comet.Position[1] = 0.5;
	comet.angle = 90 * degree;
	comet.speed = 0.004;
	comet.sizeM1 = 1;
	comet.PositionM1[0] = 5;
	comet.PositionM1[1] = 5;
	comet.angleM1 = 90 * degree;
	comet.speedM1 = 0.004;
	comet.sizeM2 = 1;
	comet.PositionM2[0] = 5;
	comet.PositionM2[1] = 5;
	comet.angleM2 = 90 * degree;
	comet.speedM2 = 0.004;
	comet.SetCorners();
	comet.BigExist = true;
	comet.Small1Exist = false;
	comet.Small2Exist = false;

	Asteroid ceres;
	ceres.size = 2;
	ceres.Position[0] = 0.5;
	ceres.Position[1] = 0.5;
	ceres.angle = 90 * degree;
	ceres.speed = 0.004;
	ceres.sizeM1 = 1;
	ceres.PositionM1[0] = 5;
	ceres.PositionM1[1] = 5;
	ceres.angleM1 = 90 * degree;
	ceres.speedM1 = 0.004;
	ceres.sizeM2 = 1;
	ceres.PositionM2[0] = 5;
	ceres.PositionM2[1] = 5;
	ceres.angleM2 = 90 * degree;
	ceres.speedM2 = 0.004;
	ceres.SetCorners();
	ceres.BigExist = true;
	ceres.Small1Exist = false;
	ceres.Small2Exist = false;

	float ShipAngle = 90*degree;

	float ShipPosition[6] = {
	   -0.06, -0.06,
		0.06, -0.06,
		0.00,  0.10 };

	float ShipTranslation[6] = { 0,0,0,0,0,0 };

	bool AllowShot = true;
	float MissileFront[2] = { 12,12 };
	float MissileEnd[2] = { 12,12 };
	float MissileAngle = 0;











	std::string vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec4 ShipPosition;\n"
		"void main()\n"
		"{gl_Position = ShipPosition;}"

		;

	std::string fragmentShader = "#version 330 core\n"
		"layout(location = 0) out vec4 color;\n"
		"void main()\n"
		"{color = vec4(1.0, 1.0, 1.0, 1.0);}"

		;


	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);













	while (!display.isClosed()) {

		display.Clear(0.0f, 0.0f, 0.0f, 0.0f);




		comet.Move();
		comet.SetCorners();
		ceres.Move();
		ceres.SetCorners();



		if (GetKeyState('W') & 0x8000) {
			CurrentSpeed = ShipMaxSpeed;
			ShipTranslation[0] = ShipTranslation[0] - ShipMaxSpeed*std::sin(ShipAngle);
			ShipTranslation[2] = ShipTranslation[2] - ShipMaxSpeed*std::sin(ShipAngle);
			ShipTranslation[4] = ShipTranslation[4] - ShipMaxSpeed*std::sin(ShipAngle);

			ShipTranslation[1] = ShipTranslation[1] + ShipMaxSpeed*std::cos(ShipAngle);
			ShipTranslation[3] = ShipTranslation[3] + ShipMaxSpeed*std::cos(ShipAngle);
			ShipTranslation[5] = ShipTranslation[5] + ShipMaxSpeed*std::cos(ShipAngle);
		}


		if (!(GetKeyState('W') & 0x8000)) {
			CurrentSpeed = CurrentSpeed / 1.01;
			ShipTranslation[0] = ShipTranslation[0] - CurrentSpeed*std::sin(ShipAngle);
			ShipTranslation[2] = ShipTranslation[2] - CurrentSpeed*std::sin(ShipAngle);
			ShipTranslation[4] = ShipTranslation[4] - CurrentSpeed*std::sin(ShipAngle);

			ShipTranslation[1] = ShipTranslation[1] + CurrentSpeed*std::cos(ShipAngle);
			ShipTranslation[3] = ShipTranslation[3] + CurrentSpeed*std::cos(ShipAngle);
			ShipTranslation[5] = ShipTranslation[5] + CurrentSpeed*std::cos(ShipAngle);
		}






		if (GetKeyState('D') & 0x8000) { ShipAngle = ShipAngle - 15 * degree; }

		if (GetKeyState('A') & 0x8000) { ShipAngle = ShipAngle + 15 * degree; }










		ShipPosition[0] = -0.06*std::cos(ShipAngle) + 0.06*std::sin(ShipAngle) + ShipTranslation[0];
		ShipPosition[1] = -0.06*std::sin(ShipAngle) - 0.06*std::cos(ShipAngle) + ShipTranslation[1];

		ShipPosition[2] = 0.06*std::cos(ShipAngle) + 0.06*std::sin(ShipAngle) + ShipTranslation[2];
		ShipPosition[3] = 0.06*std::sin(ShipAngle) - 0.06*std::cos(ShipAngle) + ShipTranslation[3];

		ShipPosition[4] = -0.1*std::sin(ShipAngle) + ShipTranslation[4];
		ShipPosition[5] = 0.1*std::cos(ShipAngle) + ShipTranslation[5];


		while (ShipTranslation[5] > 1) { ShipTranslation[5] = ShipTranslation[5] - 2; }
		while (ShipTranslation[3] > 1) { ShipTranslation[3] = ShipTranslation[3] - 2; }
		while (ShipTranslation[1] > 1) { ShipTranslation[1] = ShipTranslation[1] - 2; }

		while (ShipTranslation[5] < -1) { ShipTranslation[5] = ShipTranslation[5] + 2; }
		while (ShipTranslation[3] < -1) { ShipTranslation[3] = ShipTranslation[3] + 2; }
		while (ShipTranslation[1] < -1) { ShipTranslation[1] = ShipTranslation[1] + 2; }

		while (ShipTranslation[4] > 1) { ShipTranslation[4] = ShipTranslation[4] - 2; }
		while (ShipTranslation[2] > 1) { ShipTranslation[2] = ShipTranslation[2] - 2; }
		while (ShipTranslation[0] > 1) { ShipTranslation[0] = ShipTranslation[0] - 2; }

		while (ShipTranslation[4] < -1) { ShipTranslation[4] = ShipTranslation[4] + 2; }
		while (ShipTranslation[2] < -1) { ShipTranslation[2] = ShipTranslation[2] + 2; }
		while (ShipTranslation[0] < -1) { ShipTranslation[0] = ShipTranslation[0] + 2; }


		unsigned int ShipBuffer; // create integer has will be used to make the ships buffer
		glGenBuffers(0, &ShipBuffer);    // create buffer associatd with the integers address
		glBindBuffer(GL_ARRAY_BUFFER, ShipBuffer); // bind the buffer to the integer
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), ShipPosition, GL_DYNAMIC_DRAW); // establish the buffer is of the corner positions and will be altered and drawn alot
		glEnableVertexAttribArray(0); // need to enable vertex attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		comet.DrawAst();
		ceres.DrawAst();

		if (GetKeyState(VK_SPACE) & 0x8000 && AllowShot) {

			AllowShot = false;
			MissileAngle = ShipAngle;

			MissileEnd[0] = -0.1*std::sin(ShipAngle) + ShipTranslation[4];
			MissileEnd[1] = 0.1*std::cos(ShipAngle) + ShipTranslation[5];




		}

		if (!AllowShot) {
			MissileEnd[0] = MissileEnd[0] + 0.02*std::sin(-MissileAngle);
			MissileEnd[1] = MissileEnd[1] + 0.02*std::cos(MissileAngle);
		}

		MissileFront[0] = MissileEnd[0] + 0.03*std::sin(-MissileAngle);
		MissileFront[1] = MissileEnd[1] + 0.03*std::cos(MissileAngle);

		if (MissileEnd[0] > 1.414 | MissileEnd[0] < -1.414 | MissileEnd[1] > 1.414 | MissileEnd[1] < -1.414) {

			AllowShot = true;

			MissileEnd[0] = 12;
			MissileEnd[1] = 12;

			MissileFront[0] = MissileEnd[0] + 0.03*std::sin(-MissileAngle);
			MissileFront[1] = MissileEnd[1] + 0.03*std::cos(MissileAngle);
		}

		if (comet.Distance > 1.414  && comet.BigExist) { comet.SetPosition(); }
		if (comet.DistanceM1 > 1.414 && !comet.BigExist) { comet.Small1Exist = false; }
		if (comet.DistanceM2 > 1.414 && !comet.BigExist) { comet.Small2Exist = false; }
		if (ceres.Distance > 1.414  && ceres.BigExist) { ceres.SetPosition(); }
		if (ceres.DistanceM1 > 1.414 && !ceres.BigExist) { ceres.Small1Exist = false; }
		if (ceres.DistanceM2 > 1.414 && !ceres.BigExist) { ceres.Small2Exist = false; }



		AsteroidShot(comet, MissileFront[0], MissileFront[1], MissileEnd[0], MissileEnd[0]);
		AsteroidShot(ceres, MissileFront[0], MissileFront[1], MissileEnd[0], MissileEnd[0]);


		if(!comet.BigExist){
			if (ShipCollisonM1(comet, ShipPosition) | ShipCollisonM2(comet, ShipPosition)) { Lost = true; }
		
		
		}
		if (!ceres.BigExist) {
			if (ShipCollisonM1(ceres, ShipPosition) | ShipCollisonM2(ceres, ShipPosition)) { Lost = true; }


		}







		if (!comet.BigExist && !comet.Small1Exist && !comet.Small2Exist ){
			do { comet.SetPosition(); Lost = false; } while (ShipCollison(comet, ShipPosition) && !Lost);
			comet.BigExist = true;}
		if (!ceres.BigExist && !ceres.Small1Exist && !ceres.Small2Exist) {
			do { ceres.SetPosition(); Lost = false; } while (ShipCollison(ceres, ShipPosition) && !Lost);
			ceres.BigExist = true;
		}






		glLineWidth(2.5);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(MissileEnd[0], MissileEnd[1]);
		glVertex2f(MissileFront[0], MissileFront[1]);
		glEnd();









		
		if (GetKeyState('R') & 0x8000 && Lost == true) {
									ShipAngle = 0;
									ShipTranslation[0] = 0;
									ShipTranslation[1] = 0;
									ShipTranslation[2] = 0;
									ShipTranslation[3] = 0;
									ShipTranslation[4] = 0;
									ShipTranslation[5] = 0;

									comet.angle = rand();
									comet.SetPosition();

									comet.BigExist =  true;
									comet.Small1Exist = false;
									comet.Small2Exist = false;

									comet.PositionM1[0] = 11;
									comet.PositionM1[1] = 11;
									comet.PositionM2[0] = 11;
									comet.PositionM2[1] = 11;

									ceres.angle = rand();
									ceres.SetPosition();

									ceres.BigExist = true;
									ceres.Small1Exist = false;
									ceres.Small2Exist = false;

									ceres.PositionM1[0] = 11;
									ceres.PositionM1[1] = 11;
									ceres.PositionM2[0] = 11;
									ceres.PositionM2[1] = 11;

									AllowShot = true;
									Lost = false;
									ScoreShown = false;
									Score = 0;

									MissileEnd[0] = 1.414;
									MissileEnd[1] = 1.414;
											}
		



		if (ShipCollison(comet, ShipPosition)| ShipCollison(ceres, ShipPosition)){Lost = true;}
		if (Lost) {
			display.Clear(1.0f, 0.0f, 0.0f, 0.0f);

			if (!ScoreShown) {

			std::cout << "You Scored" << " " << Score << std::endl;
		}

		ScoreShown = true;
		}

		display.Update();



	}

	return 0;
}
