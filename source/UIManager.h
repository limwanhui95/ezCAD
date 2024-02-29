#pragma once
#include "imGui/imgui.h"
#include "imGui/imgui_stdlib.h"
#include "graphicObject/LayerManager.h"
#include "CommandPackage/CommandManager.h"

#include <iostream>
#include <sstream>
struct UIState
{
	ImVec4 clearColor;
	bool isToolWindowOpen = true;
	bool isBackGroundColorWindowOpen = false;
	bool isLayerManagerWindowOpen = false;
	bool showRenameWindow = false;
	bool failedToRename_RepeatedName = false;
	bool failedToRename_DefaultLayer = false;
	bool showDeleteLayerWindow = false;
	bool failedToDelete_DefaultLayer = false;
	bool failedToDelete_DeletedLayerIsCurrentActive = false;
	// object creation
	bool showLineCreationWindow = false;
	bool showRecCreationWindow = false;
	float _a[2] = { 0.0f,0.0f };
	float _b[2] = { 0.0f,0.0f };
	float _c[2] = { 0.0f,0.0f };
	float _d[2] = { 0.0f,0.0f };
	// obj explorer
	bool showObjExplorer = false;
	// other state
};


class UIManager
{
public:
	UIManager();
	UIState getUIState();
	void render();
	void setCommandManager(CommandManager* pt);
	void setIDManager(IDManager* pt);
	void setLayerManager(LayerManager* pt);
private:
	UIState _UIState;
	void showMainMenuBar();
	void showToolWindow();
	void showBackGroundColorWindow(bool* is_open);
	void showLayerManagerWindow(bool* is_open);
	void showObjExplorer();
	CommandManager* _commandManager = nullptr;
	IDManager* _IDManager = nullptr;
	LayerManager* _LayerManager = nullptr;
};
