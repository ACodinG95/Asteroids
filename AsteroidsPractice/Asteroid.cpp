#include "Asteroid.h"


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

const float degree = 0.157;

static unsigned int	CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{

	unsigned int program = glCreateProgram();
	unsigned int vS = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fS = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vS);
	glAttachShader(program, fS);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vS);
	glDeleteShader(fS);

	return program;

}

Asteroid::Asteroid()
{
	size = 2;
	sizeM1 = 1;
	sizeM2 = 1;
}


Asteroid::~Asteroid()
{
}


void Asteroid::SetCorners(){
	Corners[0] = Position[0];
	Corners[1] = Position[1];

	Corners[2] = Position[2] + 0.1*size*std::cos(-angle);
	Corners[3] = Position[3] + 0.1*size*std::sin(-angle);

	Corners[4] = Position[4] + 0.1*size*std::cos(90 * degree - angle);
	Corners[5] = Position[5] + 0.1*size*std::sin(90 * degree - angle);

	Distance = std::sqrt(pow(Position[0], 2) + pow((Position[1] - 0.10), 2));




	CornersM1[0] = PositionM1[0];
	CornersM1[1] = PositionM1[1];

	CornersM1[2] = PositionM1[2] + 0.1*sizeM1*std::cos(-angleM1);
	CornersM1[3] = PositionM1[3] + 0.1*sizeM1*std::sin(-angleM1);

	CornersM1[4] = PositionM1[4] + 0.1*sizeM1*std::cos(90 * degree - angleM1);
	CornersM1[5] = PositionM1[5] + 0.1*sizeM1*std::sin(90 * degree - angleM1);

	DistanceM1 = std::sqrt(pow(PositionM1[0], 2) + pow(PositionM1[1], 2));




	CornersM2[0] = PositionM2[0];
	CornersM2[1] = PositionM2[1];

	CornersM2[2] = PositionM2[2] + 0.1*sizeM2*std::cos(-angleM2);
	CornersM2[3] = PositionM2[3] + 0.1*sizeM2*std::sin(-angleM2);

	CornersM2[4] = PositionM2[4] + 0.1*sizeM2*std::cos(90 * degree - angleM2);
	CornersM2[5] = PositionM2[5] + 0.1*sizeM2*std::sin(90 * degree - angleM2);

	DistanceM2 = std::sqrt(pow(PositionM2[0], 2) + pow(PositionM2[1], 2));



}

void Asteroid::DrawAst(){
	
	unsigned int AstBuffer; 
	glGenBuffers(0, &AstBuffer);  
	glBindBuffer(GL_ARRAY_BUFFER, AstBuffer); 
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), Corners, GL_DYNAMIC_DRAW); 

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	unsigned int AstM1Buffer; 
	glGenBuffers(0, &AstM1Buffer);    
	glBindBuffer(GL_ARRAY_BUFFER, AstM1Buffer); 
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), CornersM1, GL_DYNAMIC_DRAW); 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	unsigned int AstM2Buffer; 
	glGenBuffers(0, &AstM2Buffer);   
	glBindBuffer(GL_ARRAY_BUFFER, AstM2Buffer); 
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), CornersM2, GL_DYNAMIC_DRAW); 

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);


}

void Asteroid::Move() { Position[0] = Position[0] + speed*std::cos(angle);
						Position[1] = Position[1] + speed*std::sin(angle);

						PositionM1[0] = PositionM1[0] + speedM1*std::cos(angleM1);
						PositionM1[1] = PositionM1[1] + speedM1*std::sin(angleM1);

						PositionM2[0] = PositionM2[0] + speedM2*std::cos(angleM2);
						PositionM2[1] = PositionM2[1] + speedM2*std::sin(angleM2);
};

void Asteroid::SetPosition(){
	BigExist = true;
	angle = rand();

	short unsigned int Side = rand()%4;

	switch(Side){

		case 0:
			Position[0] = std::rand() % 201 / 100 - 0.8;
			Position[1] = 1;

			break;

		case 1:
			Position[0] = std::rand() % 201 / 100 - 0.8;
			Position[1] = -1;

			while (angle < -90*degree | angle > 90 * degree) { angle = rand(); }
			break;

		case 2:
			Position[0] = 1;
			Position[1] = std::rand() % 201 / 100 - 0.8;
			break;

		case 3:
			Position[0] = -1;
			Position[1] = std::rand() % 201 / 100 - 0.8;
			break;
	}

}

void Asteroid::FragmentAsteroid() {
	BigExist = false;
	Small1Exist = true;
	Small2Exist = true;

	sizeM1 = 1;
	PositionM1[0] = Position[0];
	PositionM1[1] = Position[1];

	sizeM2 = 1;
	PositionM2[0] = Position[0];
	PositionM2[1] = Position[1];

	speedM1 = rand();
	speedM2 = rand();
	angleM1 = rand();
	angleM2 = rand();

	do { speedM1 = rand(); } while ((sizeM1*speedM1 > size*speed) | speedM1 < 0.001);
	angleM1 = (rand()%360)*degree;

	speedM2 = std::pow(size*speed,2) + std::pow(sizeM1*speedM1, 2) - 2 *size*speed*sizeM1*speedM1*std::cos(angle + angleM1);
	speedM2 = std::sqrt(speedM2);
	
	angleM2 = (std::acos(size*speed - sizeM1*speedM1) / (sizeM2*speedM2));
		
	


	Position[0] = 1000;
	Position[1] = 1000;}