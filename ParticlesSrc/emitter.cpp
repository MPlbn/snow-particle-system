#include "emitter.h"

// ------------ EMITTER ------------- //
emitter::emitter() {}

emitter::~emitter() {}

void emitter::setup(int startNum, int mP) {
	maxParticles = mP;
	for (int i = 0; i < startNum; i++) {
		particles.emplace_back(generateParticle());
	}
}

 particle emitter::generateParticle() { 
	return particle::particle();
} 


void emitter::deleteDeadParticles() {
	std::vector<int> deadParticleIndexes;
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isDead())
			deadParticleIndexes.push_back(i);
	}
	for (int index : deadParticleIndexes) {
		particles.erase(particles.begin() + index);
	}
}

void emitter::update() {
	deleteDeadParticles();

	if (particles.size() < maxParticles)
		for (int i = 0; i < 3; i++)
			particles.emplace_back(generateParticle());

	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();
	}
}
void emitter::draw() {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}

void emitter::applyForce(force& force) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].applyForce(force);
	}
}

void emitter::enable() { isEnabled = true; }
void emitter::disable() { isEnabled = false; }

// --------- RECTANGLE EMITTER ---------- //
void rectEmitter::setup(int x, int y, int startingNum, int maxPart, std::vector<shared_ptr<obstacle>>& obstacles) { //Smart pointery i std::vector<obstacle>
	maxParticles = maxPart;
	rectX = x / 2;
	rectY = y / 2;
	allObstacles = obstacles;
	for (int i = 0; i < startingNum; i++) {
		particles.emplace_back(generateParticle());
	}
}

void rectEmitter::draw() {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}

void rectEmitter::update(bool obstacleWorking) {
	deleteDeadParticles();

	if (particles.size() < maxParticles)
		for (int i = 0; i < 3; i++)
			particles.emplace_back(generateParticle());

	for (int i = 0; i < particles.size(); i++) {
		if (obstacleWorking) {
			for (int k = 0; k < allObstacles.size(); k++) {
				if (allObstacles[k]->collide(particles[i])) {
					particles[i].isTouched = true;
					//maybe break???
				}
			}
		}
		else
			particles[i].isTouched = false;
			
		particles[i].update();
	}
}

void rectEmitter::deleteDeadParticles() {
	std::vector<int> deadParticleIndexes;
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].isDead())
			deadParticleIndexes.push_back(i);
	}
	for (int index : deadParticleIndexes) {
		particles.erase(particles.begin() + index);
	}
}

snowParticle rectEmitter::generateParticle() {
	return snowParticle(ofRandom(-rectX, rectX), ofRandom(-rectY, rectY));
}

void rectEmitter::applyForce(force& force) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].applyForce(force);
	}
}

// --------- CIRCLE EMITTER ---------- //
void circleEmitter::setup(int r, int startingNum, int maxPart, std::vector<shared_ptr<obstacle>>& obstacles) {
	maxParticles = maxPart;
	circR = r;
	allObstacles = obstacles;
	for (int i = 0; i < startingNum; i++) {
		particles.emplace_back(generateParticle());
	}
}


//If obstacles working then do all obstacles stuff, probably need to setup all obstacles inside emitter
void circleEmitter::update(bool obstacleWorking) {
	deleteDeadParticles();

	if (particles.size() < maxParticles)
		for (int i = 0; i < 3; i++)
			particles.emplace_back(generateParticle());

	for (int i = 0; i < particles.size(); i++) {
		if (obstacleWorking) {
			for (int k = 0; k < allObstacles.size(); k++) {
				if (allObstacles[k]->collide(particles[i])) {
					particles[i].isTouched = true;
				}
			}
		}
		else
			particles[i].isTouched = false;

		particles[i].update();
	}
}

snowParticle circleEmitter::generateParticle() {
	std::vector<float> posV = generateCirclePos();
	return snowParticle(posV[0], posV[1]);
}

std::vector<float> circleEmitter::generateCirclePos() {
	float r = circR * sqrt(ofRandomf());
	float theta = ofRandomf() * 2 * PI;
	float x = r * std::cos(theta);
	float y = r * std::sin(theta);
	std::vector<float> retV;
	retV.push_back(x);
	retV.push_back(y);

	return retV;
}

// --------------- POINT EMITTER (FIREWORKS) ---------- //

void pointEmitter::setup(int x, int y, int z, int partNum) {
	maxParticles = partNum;
	posX = x;
	posY = y;
	posZ = z;
	fwColor = ofColor((int)ofRandom(0, 255), (int)ofRandom(0, 255), (int)ofRandom(0, 255), 255);

	for (int i = 0; i < partNum; i++) {
		particles.emplace_back(generateParticle());
	}
	for (int i = 0; i < partNum; i++) {
		particles[i].setColor(fwColor);
	}
}

void pointEmitter::update(){
	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();
	}
}

void pointEmitter::draw() {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}

bool pointEmitter::getFinishedState() {
	if (particles[0].alpha <= 0)
		return true;
	return false;
}

fwParticle pointEmitter::generateParticle() {
	return fwParticle(posX, posY, posZ);
}