#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto span = 20;
	for (int x = -200; x <= 200; x += span) {

		for (int y = -200; y <= 200; y += span) {

			this->location_list.push_back(glm::vec3(x, y, 0));
		}
	}

	for (auto& location : this->location_list) {

		vector<int> next_index = vector<int>();
		int index = -1;
		for (auto& other : this->location_list) {

			index++;
			if (location == other) { continue; }

			float distance = glm::distance(location, other);
			if (distance <= span) {

				next_index.push_back(index);
			}
		}

		this->next_index_list.push_back(next_index);
	}
}


//--------------------------------------------------------------
void ofApp::update() {

	int frame_span = 15;
	int prev_index_size = 0;

	this->actor_list.push_back(make_unique<Actor>(this->location_list, this->next_index_list));

	for (auto& actor : this->actor_list) {

		actor->update(frame_span, this->location_list, this->next_index_list);
	}

	for (int i = this->actor_list.size() - 1; i >= 0; i--) {

		if (this->actor_list[i]->isDead()) {

			this->actor_list.erase(this->actor_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotate(90);
	ofRotateY(180);

	for (auto& actor : this->actor_list) {

		actor->draw();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}