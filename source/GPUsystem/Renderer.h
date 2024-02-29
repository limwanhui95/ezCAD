#pragma once
#include "Shader.h"
#include "../graphicObject/LayerManager.h"
#include "../ViewPort.h"

class Renderer
{
public:
	void draw(LayerManager* layerManager, ViewPort* myViewPort);
	void drawDemo(ViewPort* myViewPort);
	Shader* getShader();
	void init();
private:
	Shader shader;
	unsigned int VAO,VBO;
};

