#include "GuiLogic.h"

LDDrift::GUI::DefaultWindowsData LDDrift::GuiLogic::PressEnterInSearchBarInProjectWatchTower(LDDrift::GUI* gui) {
    LDDrift::GUI::DefaultWindowsData window = gui->GetWindow("Project Watch Tower");
    if (ImGui::InputTextWithHint("##Project Watch Tower", "Enter Your File Name To Open", window.searchBuffer,
                                 sizeof(window.searchBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
        LDDrift::GUI::DefaultWindowsData result{
            .name = window.name, .canMoveWindow = window.canMoveWindow, .canResizeWindow = window.canResizeWindow,
            .textPrintInWindow = window.textPrintInWindow, .position = window.position,
            .size = window.size, .Show = window.Show, .searchBuffer = {}
        };
        for (std::size_t i = 0; i < 256; ++i) {
            result.searchBuffer[i] = window.searchBuffer[i];
        }
        return result;
    }
    return {
        .name = NULL_STR_VALUE, .canMoveWindow = false, .canResizeWindow = false, .textPrintInWindow = {},
        .position = {0, 0}, .size = {0, 0}
    };
}
