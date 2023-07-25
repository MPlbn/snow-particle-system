#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include <memory>
#include "force.h"
#include <iostream>


class particle {
public:
	float size, gravityForce = 1.2; //temp
	float alpha; //This needs to be changed
	glm::vec3 forces, position, direction; //Making it 3d
	bool isTouched;

	void decreaseAlpha(float decreaser); //Will be used when touching something
	bool isDead();
	void applyForce(force& force);
	void draw();
	void update();



	particle();
	~particle();
};

class snowParticle : public particle {
public:
	void update();
	void draw();
	snowParticle(float x, float y);
};

class fwParticle : public particle {
public:
	float gravityForce = 0.09;
	void setColor(ofColor& newColor);
	void update();
	void draw();

	fwParticle(float x, float y, float z);

private:
	ofColor color;
};