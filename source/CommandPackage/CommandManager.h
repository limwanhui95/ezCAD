#pragma once
#include "Command.h"
#include <vector>
class CommandManager {
public:
	CommandManager();
	void insertNewCommand(Command& command);
	void undo();
	void redo();
private:
	std::vector<Command> commandHistory;
	std::vector<Command>::iterator currentCommand;
};