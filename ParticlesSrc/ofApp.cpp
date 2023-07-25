#include "ofApp.h"

void ofApp::setup(){
	ofSetBackgroundColor(0, 0, 0);
	cam.tilt(180);
	cam.pan(180);

	gui.setup();
	gui.add(randomWindToggle.setup("Losowy wiatr", false));
	gui.add(windToggle.setup("Wiatr", false));
	gui.add(windX.setup("Wiatr L-R", 0, -1, 1));
	gui.add(windZ.setup("Wiatr F-B", 0, -1, 1));
	gui.add(obstacleToggle.setup("Scene", false));
	gui.add(windForceSlider.setup("Sila wiatru", 1, 0, 2));
	gui.add(emitText.setup("label", "Types of snow emitters"));
	gui.add(rectEmitToggle.setup("Rectangle", true));
	gui.add(cEmitToggle.setup("Circle", false));
	
	ofEnableLighting();
	light.setPosition(0, 0, 0);
	ofSetSphereResolution(4);
	//Timer
	lastTime = ofGetElapsedTimef();
	frameRate = 30;
	timePerFrame = 1 / frameRate;
	tick = 0;
	direction = 1;
	randomTickNumber = (int)ofRandom(20, 40);

	//SETTING OBSTACLES
	//snowman
	Obstacles.emplace_back(std::make_shared<boxObstacle>(std::vector<float>({0,500,0})));
	Obstacles.emplace_back(std::make_shared<sphereObstacle>(std::vector<float>({ 35,500-30,100 }), 30.f));
	Obstacles.emplace_back(std::make_shared<sphereObstacle>(std::vector<float>({ 35, 445 - 15 ,100 }), 15.f));
	Obstacles.emplace_back(std::make_shared<sphereObstacle>(std::vector<float>({ 35, 435 - 15 - 10 ,100 }), 10.f));
	//roofing
	Obstacles.emplace_back(std::make_shared<boxObstacle>(std::vector<float>({ 0+200,500-100,0 }), std::vector<float>({ 20,200,20 }), ofColor(46, 30, 18)));
	Obstacles.emplace_back(std::make_shared<boxObstacle>(std::vector<float>({ 150+200,500-100,0 }), std::vector<float>({ 20,200,20 }), ofColor(46, 30, 18)));
	Obstacles.emplace_back(std::make_shared<boxObstacle>(std::vector<float>({ 0+200,500-100,150 }), std::vector<float>({ 20,200,20 }), ofColor(46, 30, 18)));
	Obstacles.emplace_back(std::make_shared<boxObstacle>(std::vector<float>({ 150+200,500-100,150 }), std::vector<float>({ 20,200,20 }), ofColor(46, 30, 18)));
	Obstacles.emplace_back(std::make_shared<boxObstacle>(std::vector<float>({ 275,300,75 }), std::vector<float>({ 2*95,10,2*95 }), ofColor(46, 30, 18)));
	//tree
	Obstacles.emplace_back(std::make_shared<boxObstacle>(std::vector<float>({ -200,500 - 150,-200 }), std::vector<float>({ 15,300,15 }), ofColor(46, 30, 18)));
	Obstacles.emplace_back(std::make_shared<sphereObstacle>(std::vector<float>({ -200,200,-200 }), 100, ofColor(11, 138, 11, 255)));


	rectangleEmitter.setup(800, 800, 20, 1500, Obstacles);
	circleEmitter.setup(500, 20, 1500, Obstacles);
}

//--------------------------------------------------------------
void ofApp::update(){
	deleteFinishedEmitters();
	float currentTime = ofGetElapsedTimef();

	if (!randomWindToggle && !windToggle) {
		currentForce.forceX = 0;
		currentForce.forceY = 0;
		currentForce.forceZ = 0;

	}

	if (randomWindToggle) {
		windToggle = false;
		//need to apply some sort of tick
		if (currentTime - lastTime > timePerFrame){
			currentForce.forceX += transitionForce.forceX / randomTickNumber;
			currentForce.forceZ += transitionForce.forceZ / randomTickNumber;

			tick++;
			lastTime = currentTime;
		}

		if (tick >= randomTickNumber) {
			
			direction *= -1;
			transitionForce.forceX = direction * ofRandom(0, 1);
			transitionForce.forceZ = direction * ofRandom(0,1);
			tick = 0;
			randomTickNumber = (int)ofRandom(20, 40);
		}

	}

	if (windToggle) {
		randomWindToggle = false;
		currentForce.forceX = windX * windForceSlider;
		currentForce.forceZ = windZ * windForceSlider;
	}


	if (rectEmitToggle) {
		cEmitToggle = false;
		circleEmitter.disable();
		rectangleEmitter.enable();
	}

	if (cEmitToggle) {
		rectEmitToggle = false;
		rectangleEmitter.disable();
		circleEmitter.enable();
	}

	if (rectangleEmitter.isEnabled) {
		rectangleEmitter.applyForce(currentForce);
		rectangleEmitter.update(obstacleToggle);
	}

	if (circleEmitter.isEnabled) {
		circleEmitter.applyForce(currentForce);
		circleEmitter.update(obstacleToggle);
	}

	for (int i = 0; i < pointEmitters.size(); i++) {
		pointEmitters[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	cam.begin();
	ofEnableDepthTest();
	for (int i = 0; i < pointEmitters.size(); i++)
		pointEmitters[i].draw();

	if (rectangleEmitter.isEnabled)
		rectangleEmitter.draw();
	if (circleEmitter.isEnabled)
		circleEmitter.draw();

	if(obstacleToggle)
		for (int i = 0; i < Obstacles.size(); i++) {
			Obstacles[i]->draw();
		}

	ofDisableDepthTest();
	cam.end();
}



void ofApp::deleteFinishedEmitters() {
	std::vector<int> finishedEmitterIndexes;
	for (int i = 0; i < pointEmitters.size(); i++) {
		if (pointEmitters[i].getFinishedState())
			finishedEmitterIndexes.push_back(i);
	}
	for (int index : finishedEmitterIndexes) {
		pointEmitters.erase(pointEmitters.begin() + index);
	}
}

void ofApp::keyPressed(int key) {
	if (key == ' ') {
		pointEmitter fwEmitter;
		fwEmitter.setup((int)ofRandom(-400, 400), (int)ofRandom(0, 200), (int)ofRandom(-400, 400), 150);
		pointEmitters.push_back(fwEmitter);
	}
}
