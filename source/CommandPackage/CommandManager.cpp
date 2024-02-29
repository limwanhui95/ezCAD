#include "CommandManager.h"

CommandManager::CommandManager()
{
	currentCommand = commandHistory.end();
}

void CommandManager::insertNewCommand(Command& command)
{
	// delete the undo-command
	commandHistory.erase(currentCommand, commandHistory.end());
	// push back the new command and set the pointer to the end
	commandHistory.push_back(command);
	currentCommand = commandHistory.end();
}

void CommandManager::undo()
{
	--currentCommand;
	currentCommand->undo();
}

void CommandManager::redo()
{
	if (currentCommand != commandHistory.end()) {
		++currentCommand;
		currentCommand->redo();
	}
}
