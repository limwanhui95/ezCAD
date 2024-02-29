#include "ViewPort.h"
glm::mat4 ViewPort::getProjection()
{
	return projection;
}

void ViewPort::setProjection(float x, float y)
{
	left += x;
	right += x;
	bottom += y;
	top += y;
	projection = glm::ortho(left * magnifier, right * magnifier, bottom * magnifier, top * magnifier);
}

void ViewPort::setMagnifier(float delta)
{
	magnifier += delta;
	projection = glm::ortho(left * magnifier, right * magnifier, bottom * magnifier, top * magnifier);
}