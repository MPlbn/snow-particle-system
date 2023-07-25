#include "obstacle.h"
obstacle::obstacle(){}

obstacle::~obstacle(){}

//BOX
void boxObstacle::draw() {
	ofSetColor(Color);
	ofDrawBox(Position[0], Position[1], Position[2], Size[0], Size[1], Size[2]);
}

bool boxObstacle::collide(snowParticle& particle) {
	int check = 0;
	for (int i = 0; i < 3; i++) {
		if (particle.position[i] > bounds[0][i] && particle.position[i] < bounds[1][i])
			check++;
	}
	if (check == 3) {
		return true;
	}

	return false;
}

boxObstacle::boxObstacle(std::vector<float> position, std::vector<float> size, ofColor color) {
	Position = position;
	Color = color;
	Size = size;
	bounds = { {Position[0] - Size[0] / 2, Position[1] - Size[1] / 2 , Position[2] - Size[2] / 2 },
		{ Position[0] + Size[0] / 2, Position[1] + Size[1] / 2 , Position[2] + Size[2] / 2 } };
}

boxObstacle::~boxObstacle() {}

//SPHERE

void sphereObstacle::draw() {
	ofSetSphereResolution(10);
	ofSetColor(Color);
	ofDrawSphere(Position[0], Position[1], Position[2], R);
	ofSetSphereResolution(4);
}

bool sphereObstacle::collide(snowParticle& particle) {
	std::vector<float> v;
	for (int i = 0; i < 3; i++) {
		v.push_back(particle.position[i] - Position[i]);
	}
	float sum = 0;
	for (int i = 0; i < 3; i++) {
		sum += v[i] * v[i];
	}
	if (sum <= R * R) {
		return true;
	}
	return false;
}

sphereObstacle::sphereObstacle(std::vector<float> position, float r, ofColor color) {
	Position = position;
	R = r;
	Color = color;
}

sphereObstacle::~sphereObstacle(){}