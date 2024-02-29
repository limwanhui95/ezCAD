#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <typeinfo>

class ViewPort
{
public:
	glm::mat4 getProjection();
	void setProjection(float x, float y);
	void setMagnifier(float delta);
private:
	float magnifier = 1.0f;
	float left = 0.0f;
	float right = 800.0f;
	float bottom = 600.0f;
	float top = 0.0f;
	glm::mat4 projection = glm::ortho(left * magnifier, right * magnifier, bottom * magnifier, top * magnifier);
};

