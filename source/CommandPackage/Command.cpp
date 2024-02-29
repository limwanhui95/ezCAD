#include "Command.h"

void MoveCommand::undo()
{
	Objpointer->move(increment * -1.0f);
}

void MoveCommand::redo()
{
	Objpointer->move(increment);
}

LineCommand::LineCommand(Point a, Point b, IDManager* _IDManager, LayerManager* _LayerManager)
{	
	unsigned int newID = _IDManager->registerNewID();  // get new ID from IDmanager
	//std::cout << "NewID: " << newID << std::endl;
	this->ID = newID; // store the new obj id in command
	Objpointer = new Line(a,b, newID);  // create new line object
	_IDManager->bindID(newID, Objpointer); // store the id & objPointer in hash map
	_LayerManager->getCurrentActiveLayer()->insertObj(Objpointer);
}

RecCommand::RecCommand(Point a, Point b, Point c, Point d, IDManager* _IDManager, LayerManager* _LayerManager)
{
	unsigned int newID = _IDManager->registerNewID();
	this->ID = newID;
	Objpointer = new Rectangular(a, b, c, d, newID);
	_IDManager->bindID(newID, Objpointer);
	_LayerManager->getCurrentActiveLayer()->insertObj(Objpointer);
}

void LineCommand::undo()
{
}

void LineCommand::redo()
{
}

void RecCommand::undo()
{
}

void RecCommand::redo()
{
}
