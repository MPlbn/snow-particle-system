#pragma once
#include "particle.h"
#include "ofMain.h"
#include <vector>
#include <memory>

class obstacle { // obstacle
public:
	std::vector<float> Position;
	virtual bool collide(snowParticle& particle) = 0;
	virtual void draw() = 0;

	obstacle();
	~obstacle();
};

class boxObstacle : public obstacle {
public:
	std::vector<float> Size;
	std::vector<std::vector<float>> bounds;
	ofColor Color;

	bool collide(snowParticle& particle);
	void draw();

	boxObstacle(std::vector<float> position, std::vector<float> size = std::vector<float>({ 850,10,850 }), ofColor Color = ofColor(11, 138, 11, 255));
	~boxObstacle();

	using obstacle::collide;
};

class sphereObstacle : public obstacle {
public:
	float R;
	ofColor Color;

	void draw();
	bool collide(snowParticle& particle);

	sphereObstacle(std::vector<float> position, float r = 300, ofColor color = ofColor(86,90,99,255));
	~sphereObstacle();

	using obstacle::collide;
};
