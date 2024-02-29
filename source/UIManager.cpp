#include "UIManager.h"

UIManager::UIManager()
{
	_UIState.clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
}

UIState UIManager::getUIState()
{
	return _UIState;
}

void UIManager::render()
{
	showMainMenuBar();
	if (_UIState.isBackGroundColorWindowOpen) {
		showBackGroundColorWindow(&_UIState.isBackGroundColorWindowOpen);
	}
	if (_UIState.isToolWindowOpen) {
		showToolWindow();
	}
	if (_UIState.isLayerManagerWindowOpen) {
		showLayerManagerWindow(&_UIState.isLayerManagerWindowOpen);
	}
	if (_UIState.showObjExplorer) {
		showObjExplorer();
	}
}

void UIManager::setCommandManager(CommandManager* pt)
{
	_commandManager = pt;
}

void UIManager::setIDManager(IDManager* pt)
{
	_IDManager = pt;
}

void UIManager::setLayerManager(LayerManager* pt)
{
	_LayerManager = pt;
}

void UIManager::showMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
				// do your command here
			}
			if (ImGui::MenuItem("Open"))
			{
				// do your command here
			}
			if (ImGui::MenuItem("Save as"))
			{
				// do your command here
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo")) {

			}
			if (ImGui::MenuItem("Redo")) {

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Background Color")) {
				// pop up background color picker window
				_UIState.isBackGroundColorWindowOpen = true;
			}
			if (ImGui::MenuItem("Tool Box")) {
				_UIState.isToolWindowOpen = !_UIState.isToolWindowOpen;
			}
			if (ImGui::MenuItem("Layer Explorer")) {
				_UIState.isLayerManagerWindowOpen = true;
			}
			if (ImGui::MenuItem("Object Explorer##menuitem")) {
				_UIState.showObjExplorer = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Style")) {
			if (ImGui::MenuItem("Dark")) {
				ImGui::StyleColorsDark();
			}
			if (ImGui::MenuItem("Light")) {
				ImGui::StyleColorsLight();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void UIManager::showToolWindow()
{
	ImGui::Begin("ToolsBox");
	if (ImGui::Button("Line")) {
		_UIState.showLineCreationWindow = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Rectangular")) {
		// execute rectangular command
		_UIState.showRecCreationWindow = true;
	}
	if (ImGui::Button("Triangle")) {
		// execute triangle command
	}
	ImGui::SameLine();
	if (ImGui::Button("Circle")) {

	}
	if (ImGui::Button("Copy")) {

	}
	ImGui::SameLine();
	if (ImGui::Button("Move")) {

	}
	ImGui::End();

	if (_UIState.showLineCreationWindow) {
		// create window to get point a & b
		ImGui::Begin("Create Line", &_UIState.showLineCreationWindow, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Point A: ");
		ImGui::SameLine();
		ImGui::InputFloat("x##line_pointAx", &_UIState._a[0]);
		ImGui::SameLine();
		ImGui::InputFloat("y##line_pointAy", &_UIState._a[1]);
		ImGui::Text("Point B: ");
		ImGui::SameLine();
		ImGui::InputFloat("x##line_pointBx", &_UIState._b[0]);
		ImGui::SameLine();
		ImGui::InputFloat("y##line_pointBy", &_UIState._b[1]);
		ImGui::Separator();
		if (ImGui::Button("Confirm##Line_confirm")) {
			// execute line command
			// transfer float to point
			Point pointA(_UIState._a[0], _UIState._a[1]);
			Point pointB(_UIState._b[0], _UIState._b[1]);
			LineCommand newCommand = LineCommand(pointA, pointB, _IDManager, _LayerManager);
			_commandManager->insertNewCommand(newCommand);
			// reset a and b
			_UIState._a[0] = 0.0f;	_UIState._a[1] = 0.0f; _UIState._b[0] = 0.0f; _UIState._b[1] = 0.0f;
			_UIState.showLineCreationWindow = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel##line_cancel")) {
			_UIState._a[0] = 0.0f;	_UIState._a[1] = 0.0f; _UIState._b[0] = 0.0f; _UIState._b[1] = 0.0f;
			_UIState.showLineCreationWindow = false;
		}
		ImGui::End();
	}

	if (_UIState.showRecCreationWindow) {
		static float width, height;
		ImGui::Begin("Create Rectangular", &_UIState.showRecCreationWindow, ImGuiWindowFlags_AlwaysAutoResize);
		// point a
		ImGui::Text("Starting Point");
		ImGui::InputFloat("x##rectangular_startingpoint", &_UIState._a[0]);
		ImGui::SameLine();
		ImGui::InputFloat("y##rectangular_startingpoint", &_UIState._a[1]);
		// height & width
		ImGui::Text("Width: ");
		ImGui::SameLine();
		ImGui::InputFloat("##rectangular_width", &width);
		ImGui::Text("Height:");
		ImGui::SameLine();
		ImGui::InputFloat("##rectangular_height", &height);
		ImGui::Separator();
		if (ImGui::Button("Confirm##Rectangular_confirm")) {
			Point pointA(_UIState._a[0], _UIState._a[1]);
			Point pointB(_UIState._a[0] + width, _UIState._a[1]);
			Point pointC(_UIState._a[0] + width, _UIState._a[1] + height);
			Point pointD(_UIState._a[0], _UIState._a[1] + height);
			RecCommand newCommand = RecCommand(pointA, pointB, pointC, pointD, _IDManager, _LayerManager);
			_commandManager->insertNewCommand(newCommand);
			// reset a,b,c,d
			_UIState._a[0] = 0.0f;	_UIState._a[1] = 0.0f; width = 0.0f; height = 0.0f;
			_UIState.showRecCreationWindow = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel##Rectangular_cancel")) {
			_UIState._a[0] = 0.0f;	_UIState._a[1] = 0.0f; ; width = 0.0f; height = 0.0f;
			_UIState.showRecCreationWindow = false;
		}
		ImGui::End();
	}
}

void UIManager::showBackGroundColorWindow(bool* is_open)
{
	// window flag
	ImGuiWindowFlags window_flags = 0;
	//window_flags |= ImGuiWindowFlags_NoResize;
	//window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	ImGui::Begin("Background Color Picker", is_open, window_flags);
	ImGui::ColorEdit3("BackgroundColor", (float*)&_UIState.clearColor);
	ImGui::End();
}

void UIManager::showLayerManagerWindow(bool* is_open)
{
	ImGui::Begin("Layer Explorer", is_open);
	if (ImGui::Button("Create New Layer")) {
		_LayerManager->newLayer();
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete Layer")) {
		_UIState.showDeleteLayerWindow = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Rename Layer")) {
		_UIState.showRenameWindow = true;		
	}
	if (ImGui::Button("Set All Layer To Be Visible")) {
		for (std::unordered_map<std::string, Layer*>::iterator it = _LayerManager->getBegin(); it != _LayerManager->getEnd(); ++it) {
			it->second->setVisiblity(true);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Set All Layer To Be Invisible")) {
		for (std::unordered_map<std::string, Layer*>::iterator it = _LayerManager->getBegin(); it != _LayerManager->getEnd(); ++it) {
			it->second->setVisiblity(false);
			std::cout << _LayerManager->getCurrentActiveLayer()->getName();
		}
	}
	// combo widget to select current active layer
	static int selected_index_to_active = 0;
	if (ImGui::BeginCombo("Select Current Active Layer", _LayerManager->getName(selected_index_to_active).c_str())) {
		for (int n = 0; n < _LayerManager->getNumberOfLayer(); n++) {
			const bool is_selected = (selected_index_to_active == n);
			if (ImGui::Selectable(_LayerManager->getName(n).c_str(), is_selected))
				selected_index_to_active = n;
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	_LayerManager->setCurrentActiveLayer(_LayerManager->getName(selected_index_to_active));
	ImGui::Separator();
	// create table
	ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable;
	if (ImGui::BeginTable("Layer",4,flags)) {
		// display header
		ImGui::TableSetupColumn("Layer Name");
		//ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 50.0f);
		ImGui::TableSetupColumn("Color");
		ImGui::TableSetupColumn("Visibility");
		ImGui::TableSetupColumn("Line Width");
		ImGui::TableHeadersRow();
		// item
		auto it = _LayerManager->getBegin();
		for (int row = 0; row < _LayerManager->getNumberOfLayer(); row++)
		{
			ImGui::TableNextRow();
			// first column : Name
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(it->second->getName().c_str());
			// second colmn : color
			ImGui::TableSetColumnIndex(1);
			std::string s = "##Color of Layer: ";
			s = s + _LayerManager->getName(row);
			ImGui::ColorEdit3(s.c_str(), (float*)_LayerManager->getLayer(_LayerManager->getName(row))->getColor());
			// third column : visibility
			ImGui::TableSetColumnIndex(2);
			std::string s2 = "##Visibility of Layer: ";
			s2 = s2 + _LayerManager->getName(row);
			ImGui::Checkbox(s2.c_str(), _LayerManager->getLayer(_LayerManager->getName(row))->getVisibility());
			// fourth column : line width
			ImGui::TableSetColumnIndex(3);
			std::string s3 = "##Line width of Layer: ";
			s3 = s3 + _LayerManager->getName(row);
			ImGui::SliderFloat(s3.c_str(), _LayerManager->getLayer(_LayerManager->getName(row))->getWidth(), 1.0f, 9.0f);
			++it;
		}
		ImGui::EndTable();
	}	
	ImGui::End();

	// Rename Window
	if (_UIState.showRenameWindow) {
		ImGui::Begin("Rename Layer", &_UIState.showRenameWindow, ImGuiWindowFlags_AlwaysAutoResize);
		static int selected_index_to_rename = 0;
		if (ImGui::BeginCombo("Select Layer to Rename", _LayerManager->getName(selected_index_to_rename).c_str())) {
			for (int n = 0; n < _LayerManager->getNumberOfLayer(); n++) {
				const bool is_selected = (selected_index_to_rename == n);
				if (ImGui::Selectable(_LayerManager->getName(n).c_str(), is_selected))
					selected_index_to_rename = n;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
ImGui::EndCombo();
		}
		// input new name
		static char NewGivenName_renameWindow[256] = "";
		ImGui::InputText("Input New Name For The Selected Layer", NewGivenName_renameWindow, IM_ARRAYSIZE(NewGivenName_renameWindow));
		ImGui::Text("Note: Length of Name < 256!");
		ImGui::Separator();
		if (ImGui::Button("Confirm to Rename!")) {
			std::string s;
			s = NewGivenName_renameWindow;
			if (_LayerManager->getName(selected_index_to_rename) == "default") {
				_UIState.failedToRename_DefaultLayer = true;
			}
			else {
				if (!_LayerManager->setName(selected_index_to_rename, s)) {
					_UIState.failedToRename_RepeatedName = true;
				}
			}
			strcpy_s(NewGivenName_renameWindow, ""); // clear char array
			_UIState.showRenameWindow = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel. Forfeit to Rename!")) {
			strcpy_s(NewGivenName_renameWindow, "");
			_UIState.showRenameWindow = false;
		}
		ImGui::End();
	}
	if (_UIState.failedToRename_RepeatedName) {
		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Warning: Failed To Rename Due To Repeated Name", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::Button("Confirm. Note: Previous Attempt To Rename Is Forfeit!")) {
			_UIState.failedToRename_RepeatedName = false;
		}
		ImGui::End();
	}
	if (_UIState.failedToRename_DefaultLayer) {
		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Error!##Can't Rename Default Layer!", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Can't Rename Default Layer!!!");
		if (ImGui::Button("Confirm.##Error:RenameDefaultLayer")) {
			_UIState.failedToRename_DefaultLayer = false;
		}
		ImGui::End();
	}

	// Delete layer window
	if (_UIState.showDeleteLayerWindow) {
		ImGui::Begin("Delete Layer", &_UIState.showDeleteLayerWindow, ImGuiWindowFlags_AlwaysAutoResize);
		static int selected_layer_to_delete = 0;
		if (ImGui::BeginCombo("Select Layer to Delete", _LayerManager->getName(selected_layer_to_delete).c_str())) {
			for (int n = 0; n < _LayerManager->getNumberOfLayer(); n++) {
				const bool is_selected = (selected_layer_to_delete == n);
				if (ImGui::Selectable(_LayerManager->getName(n).c_str(), is_selected))
					selected_layer_to_delete = n;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::Text("Note: Object In Deleted Layer Will Trasnfer To Default Layer !");
		ImGui::Separator();
		if (ImGui::Button("Confirm to delete!")) {
			if (_LayerManager->getName(selected_layer_to_delete) != "default") {
				//std::cout << "delete layer" << std::endl;
				if (_LayerManager->getCurrentActiveLayer()->getName() != _LayerManager->getName(selected_layer_to_delete)) {
					_LayerManager->deleteLayer(_LayerManager->getName(selected_layer_to_delete));
				}
				else {
					_UIState.failedToDelete_DeletedLayerIsCurrentActive = true;
				}
			}
			else if (_LayerManager->getName(selected_layer_to_delete) == "default") {
				//std::cout << "failed to delete layer" << std::endl;
				_UIState.failedToDelete_DefaultLayer = true;
			}
			_UIState.showDeleteLayerWindow = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel. Forfeit to Delete!")) {
			_UIState.showDeleteLayerWindow = false;
		}
		ImGui::End();
	}

	if (_UIState.failedToDelete_DefaultLayer) {
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Error!##Cant delete default layer", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Can't Delete Default Layer!!!");
		if (ImGui::Button("Confirm.##Error:DeleteDefaultLayer")) {
			_UIState.failedToDelete_DefaultLayer = false;
		}
		ImGui::End();
	}

	if (_UIState.failedToDelete_DeletedLayerIsCurrentActive) {
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Error!##Cant delete layer due to current active layer", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Can't Delete Current Active Layer!!!");
		if (ImGui::Button("Confirm.##Error:DeleteCurrentActiveLayer")) {
			_UIState.failedToDelete_DeletedLayerIsCurrentActive = false;
		}
		ImGui::End();
	}
}

void UIManager::showObjExplorer()
{
	static int selected_layer_to_explore;
	ImGui::Begin("Object Explorer", &_UIState.showObjExplorer);
	if (ImGui::BeginCombo("Layer##objExplorer", _LayerManager->getName(selected_layer_to_explore).c_str())) {
		for (int n = 0; n < _LayerManager->getNumberOfLayer(); n++) {
			const bool is_selected = (selected_layer_to_explore == n);
			if (ImGui::Selectable(_LayerManager->getName(n).c_str(), is_selected))
				selected_layer_to_explore = n;
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::Separator();
	// a table to show all object
	ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable;
	if (ImGui::BeginTable("##objectlist_objectexplorer", 3, flags)) {
		ImGui::TableSetupColumn("ID");
		ImGui::TableSetupColumn("Type");
		ImGui::TableSetupColumn("INFO");
		ImGui::TableHeadersRow();
		std::vector<lineObject*>::iterator it = _LayerManager->getLayer(_LayerManager->getName(selected_layer_to_explore))->begin();
		std::stringstream stream;
		std::string string_ID;
		for (; it != _LayerManager->getLayer(_LayerManager->getName(selected_layer_to_explore))->end(); ++it) {
			ImGui::TableNextRow();
			// first column : id
			ImGui::TableSetColumnIndex(0);
			stream << (*it)->getID();
			stream >> string_ID;
			stream.clear();
			ImGui::Text(string_ID.c_str());
			// second column : type
			ImGui::TableSetColumnIndex(1);
			ImGui::Text((*it)->printType().c_str());
			// third column : info
			ImGui::TableSetColumnIndex(2);
			ImGui::Text((*it)->printInfo().c_str());
		}
		ImGui::EndTable();
	}
	ImGui::End();
}
