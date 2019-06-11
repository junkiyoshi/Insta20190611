#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto len = 25;
	vector<glm::vec2> outer, inner;
	for (int radius = 50; radius <= 300; radius += 50) {
		
		ofNoFill();
		ofDrawCircle(glm::vec2(), radius);

		auto out_radius = radius + len * 0.5;
		auto in_radius = radius - len * 0.5;
		for (int deg = 0; deg <= 360; deg++) {

			auto noise_source = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(noise_source.x * 0.005, noise_source.y * 0.005, ofGetFrameNum() * 0.005);
			if (noise_value < 0.55) {

				outer.push_back(glm::vec2(out_radius * cos(deg * DEG_TO_RAD), out_radius * sin(deg * DEG_TO_RAD)));
				inner.push_back(glm::vec2(in_radius  * cos(deg * DEG_TO_RAD), in_radius  * sin(deg * DEG_TO_RAD)));
			}
			else {

				this->draw_shape(outer, inner);
			}
		}

		this->draw_shape(outer, inner);
	}
}

//--------------------------------------------------------------
void ofApp::draw_shape(vector<glm::vec2>& param1, vector<glm::vec2>& param2) {

	if (param1.size() > 0 && param2.size() > 0) {

		std::reverse(param2.begin(), param2.end());

		ofFill();
		ofBeginShape();
		ofVertices(param1);
		ofVertices(param2);
		ofEndShape(true);
	}

	param1.clear();
	param2.clear();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}