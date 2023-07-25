#pragma once
#include <iostream>
#include <vector>
#include "particle.h"
#include "force.h"
#include <cmath>
#include "obstacle.h"


class emitter {
public:
	std::vector<particle> particles;
	std::vector<std::shared_ptr<obstacle>> allObstacles;
	int maxParticles;
	bool isEnabled;

	void setup(int startNum, int maxPart);
	particle generateParticle();
	void deleteDeadParticles();
	void update();
	void draw();
	void applyForce(force& force);
	void enable();
	void disable();

	emitter();
	~emitter();
};

class rectEmitter : public emitter {
public:
	std::vector<snowParticle> particles;

	void setup(int x, int y, int startNum, int maxPart, std::vector<shared_ptr<obstacle>>& obstacles);
	void update(bool obstacleWorking);
	void draw();
	void deleteDeadParticles();
	snowParticle generateParticle();
	void applyForce(force& force);
private:
	int rectX, rectY;
};

class circleEmitter : public rectEmitter {
public:
	int circR;


	void setup(int r, int startNum, int maxPart, std::vector<shared_ptr<obstacle>>& obstacles);
	void update(bool obstacleWorking);
	snowParticle generateParticle();
	std::vector<float> generateCirclePos();
};

class pointEmitter : public emitter {
public:
	std::vector<fwParticle> particles;
	int posX, posY, posZ;
	ofColor fwColor;

	void setup(int x, int y, int z, int partNum);
	void update();
	void draw();
	bool getFinishedState();
	fwParticle generateParticle();
};