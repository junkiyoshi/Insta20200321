#pragma once
#include "ofMain.h"

class Actor {
public:
	Actor(vector<glm::vec3>& location_list, vector<vector<int>>& next_index_list);
	void update(int& frame_span, vector<glm::vec3>& location_list, vector<vector<int>>& next_index_list);
	void draw();

	bool isDead();

private:

	int select_index;
	int next_index;
	int life;

	glm::vec3 location;
	std::deque<glm::vec3> log;
};