#include "Renderer.h"



void Renderer::draw(LayerManager* layerManager, ViewPort* myViewPort)
{
	std::unordered_map<std::string, Layer*>::iterator it, _end;
	it = layerManager->getBegin();
	_end = layerManager->getEnd();
	// get Projection mat4
	shader.Use();
	shader.SetMatrix4("projection", myViewPort->getProjection());
	// for every layer
	for (; it != _end; ++it) {
		std::vector<float> myvert;
		if (*it->second->getVisibility()) {
			// get uniform "linecolor"
			shader.SetVector4f("lineColor", it->second->getColor()->x, it->second->getColor()->y, it->second->getColor()->z, it->second->getColor()->w);
			//shader.SetVector4f("lineColor", 0.0f, 0.0f, 0.0f, 1.0f);
			// get line width
			glLineWidth(*(it->second->getWidth()));
			std::vector<lineObject*>::iterator obj_it, obj_end;
			// for every object
			for (obj_it = it->second->begin(); obj_it != it->second->end(); ++obj_it) {
				(*obj_it)->setVert(&myvert);				
			}
			if (myvert.size() != 0) {
				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * myvert.size(), &myvert[0], GL_DYNAMIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				glDrawArrays(GL_LINES, 0, myvert.size() / 3); // draw
			}
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		// setLinewidth back to default
		glLineWidth(1.0f);
	}
}

void Renderer::drawDemo(ViewPort* myViewPort)
{
	shader.Use();
	shader.SetMatrix4("projection", myViewPort->getProjection());
	shader.SetVector4f("lineColor", 0.0f, 0.0f, 0.0f, 1.0f);
	float vertices[] =
	{
		 50.0f,  50.0f,  0.0f, // bottom left
		350.0f,  65.0f,  0.0f, // bottom right
	};
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINE_LOOP, 0, 2);
	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Shader* Renderer::getShader()
{
	return &shader;
}

void Renderer::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

