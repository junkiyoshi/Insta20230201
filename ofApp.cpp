#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 35, true, true, true);
	this->word = "0123456789";

	vector<glm::vec2> location_list;
	for (int i = 0; i < 300; i++) {

		this->radius_list.push_back(ofRandom(50, 300));
		this->speed_list.push_back(ofRandom(3, 7));
		this->rotation_list.push_back(glm::vec3(ofRandom(360), ofRandom(360), ofRandom(360)));
		this->index_list.push_back(ofRandom(this->word.size()));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->radius_list.size(); i++) {

		this->radius_list[i] = (int)(this->radius_list[i] + this->speed_list[i]) % 300;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.7);
	ofRotateX(ofGetFrameNum() * 1.2);

	for (int i = 0; i < this->radius_list.size(); i++) {

		ofRotateZ(this->rotation_list[i].z);
		ofRotateY(this->rotation_list[i].y);
		ofRotateX(this->rotation_list[i].x);

		ofPushMatrix();
		ofTranslate(-8, 15, this->radius_list[i] + 35);

		ofPath chara_path = this->font.getCharacterAsPoints(this->word[this->index_list[i]], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		auto alpha = this->radius_list[i] < 200 ? 100 : ofMap(this->radius_list[i], 200, 330, 100, 0);

		ofFill();
		ofSetColor(255, alpha);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getVertices();
			ofVertices(vertices);
		}
		ofEndShape(true);

		alpha = this->radius_list[i] < 200 ? 255 : ofMap(this->radius_list[i], 200, 330, 255, 0);

		ofNoFill();
		ofSetColor(255, alpha);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getVertices();
			ofVertices(vertices);
		}
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}