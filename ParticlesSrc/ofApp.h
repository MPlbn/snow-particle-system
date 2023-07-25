#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>
#include <iostream>
#include "emitter.h"
#include "particle.h"
#include "force.h"
#include <memory>

class ofApp : public ofBaseApp{

	public:
		
		void setup();
		void update();
		void draw();
		void deleteFinishedEmitters();

		void keyPressed(int key);

		int tick, direction, randomTickNumber;
		float frameRate, lastTime, timePerFrame;

		rectEmitter rectangleEmitter;
		circleEmitter circleEmitter;
		std::vector<pointEmitter> pointEmitters;

		//SMARTPOINTERS
		std::vector<std::shared_ptr<obstacle>> Obstacles;

		ofLight light;
		force currentForce = force::force(0, 0, 0), transitionForce = force::force(0,0,0);

		//gui
		ofxPanel gui;

		ofxLabel emitText;
		ofxToggle windToggle, randomWindToggle, cEmitToggle, rectEmitToggle, obstacleToggle;
		ofxIntSlider windX, windZ;
		ofxFloatSlider windForceSlider;

		//camera
		ofEasyCam cam;
};
