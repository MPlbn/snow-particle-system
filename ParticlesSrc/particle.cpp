#include "particle.h"

particle::particle() {
	size = 2;
	//starting position
	position = glm::vec3(0, 0, 0); //changed to 3d
	//force
	forces = glm::vec3(0, 0, 0); //starting force
	//direction
	direction = glm::vec3(0, 0, 0); //changed to 3d x,y,z
	alpha = 255;
	isTouched = false;
}

particle::~particle() {}

void particle::decreaseAlpha(float decreaser) {
	alpha -= decreaser;
}

bool particle::isDead() {
	if (alpha <= 0)
		return true;
	return false;
}


void particle::applyForce(force& force) {
	forces[0] = force.forceX;
	forces[1] = force.forceY;
	forces[2] = force.forceZ;
}

void particle::draw() {
	ofDrawSphere(position, size);
}

void particle::update() {
	//lifespan
	decreaseAlpha(0.5);

	//updating location
	if (!isTouched) {
		for (int i = 0; i < 3; i++) {
			position[i] += direction[i] + forces[i];
		}
	}
}


// ------------- SNOW PARTICLE ------------- //

void snowParticle::update() {
	//lifespan
	decreaseAlpha(0.5);

	//updating location
	if (!isTouched) {
		for (int i = 0; i < 3; i++) {
			position[i] += direction[i] + forces[i];
		}
	}
}

void snowParticle::draw() {
	ofSetColor(255, 255, 255, 255);
	ofDrawSphere(position, size);
}

snowParticle::snowParticle(float x, float z) {
	size = 4;
	//starting position
	position = glm::vec3(x, 0, z); //changed to 3d
	//force
	forces = glm::vec3(0, 0, 0); //starting force
	//direction
	direction = glm::vec3(0, gravityForce, 0); //changed to 3d x,y,z
	alpha = 255;
	isTouched = false;
}


// ------------- FW PARTICLE -------------- //

void fwParticle::setColor(ofColor& newColor) {
	color = newColor;
}

void fwParticle::update() {
	decreaseAlpha(3);
	forces[1] += gravityForce;
	//updating location
	if (!isTouched) {
		for (int i = 0; i < 3; i++) {
			position[i] += direction[i] + forces[i];
		}
	}
}

void fwParticle::draw() {
	ofSetColor(color,alpha);
	ofDrawSphere(position, size);
}

fwParticle::fwParticle(float x, float y, float z) {
	size = 5;
	position = glm::vec3(x, y, z);
	forces = glm::vec3(0, 0, 0);
	direction = glm::vec3(ofRandom(-5, 5), ofRandom(-5.5, -1), ofRandom(-5, 5));
	alpha = 255;
	isTouched = false;
}