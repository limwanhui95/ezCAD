#pragma once
#include "../graphicObject/graphicObject.h"
#include "../graphicObject/Point.h"
#include "../graphicObject/IDManager.h"
#include "../graphicObject/Line.h"
#include "../graphicObject/Rectangular.h"
#include "../graphicObject/LayerManager.h"

class Command {
public:
	virtual void undo() {}
	virtual void redo() {}
protected:
	lineObject* Objpointer = nullptr;
};

class MoveCommand : public Command {
public:
	MoveCommand(lineObject* _pointer, Point increment) : increment(increment) { Objpointer = _pointer; }
	virtual void undo();
	virtual void redo();
private:
	Point increment;
};

class LineCommand : public Command {
public:
	LineCommand(Point a, Point b, IDManager* _IDManager, LayerManager* _LayerManager);
	virtual void undo();
	virtual void redo();
private:
	int ID;
};

class RecCommand : public Command {
public:
	RecCommand(Point a, Point b, Point c, Point d, IDManager* _IDManager, LayerManager* _LayerManager);
	virtual void undo();
	virtual void redo();
private:
	int ID;
};