#include "GuiLogic.h"

LDDrift::GUI::DefaultWindowsData LDDrift::GuiLogic::PressEnterInSearchBarInProjectWatchTower(
    LDDrift::GUI::DefaultWindowsData* window) {
    if (window->name != PROJECT_WATCH_TOWER_WINDOW_NAME) {
        return {
            .name = NULL_STR_VALUE, .canMoveWindow = false, .canResizeWindow = false, .textPrintInWindow = {},
            .position = {0, 0}, .size = {0, 0}
        };
    }
    if (ImGui::InputTextWithHint("##Project Watch Tower", "Enter Your File Name To Open", window->searchBuffer,
                                 sizeof(window->searchBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
        LDDrift::GUI::DefaultWindowsData result{
            .name = window->name, .canMoveWindow = window->canMoveWindow, .canResizeWindow = window->canResizeWindow,
            .textPrintInWindow = window->textPrintInWindow, .position = window->position,
            .size = window->size, .Show = window->Show, .searchBuffer = {}
        };
        for (std::size_t i = 0; i < 256; ++i) {
            result.searchBuffer[i] = window->searchBuffer[i];
        }
        return result;
    }
    return {
        .name = NULL_STR_VALUE, .canMoveWindow = false, .canResizeWindow = false, .textPrintInWindow = {},
        .position = {0, 0}, .size = {0, 0}
    };
}

void LDDrift::GuiLogic::SetProjectWatchTowerPtr(ProjectWatchTower* projectWatchTowerPtr) {
    LDDrift::Anonymous::projectWatchTowerPTR = projectWatchTowerPtr;
}

void LDDrift::GuiLogic::ProjectManagerHandling(LDDrift::GUI::DefaultWindowsData* window) {
    if (window->name != PROJECT_MANAGER_WINDOW_NAME) {
        return;
    }
    if (ImGui::InputTextWithHint("##Project Manager", "Enter dir with file (test1/test2/test3.cpp):",
                                 window->searchBuffer, sizeof(window->searchBuffer),
                                 ImGuiInputTextFlags_EnterReturnsTrue)) {}
    if (Anonymous::projectWatchTowerPTR->FindFile(std::filesystem::path(window->searchBuffer))) {
        std::cout << "Cannot create the file because a file with the same name already exists in the project.";
        return;
    }
    if (ImGui::Button("Create New File")) {
        Anonymous::projectWatchTowerPTR->WriteCodeToFile(std::filesystem::path(window->searchBuffer), "");
    }
}
