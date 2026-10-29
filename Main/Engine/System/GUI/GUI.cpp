#include "GUI.h"
#include "System/Core/Core.h"

static bool RemoveTextFromCurrentLine(
    TextEditor& editor,
    const std::string& target) {
    if (target.empty() || editor.IsReadOnly())
        return false;

    // Get the text of the current line.
    const std::string line = editor.GetCurrentLineText();

    // Find the first occurrence of the target.
    const std::size_t pos = line.find(target);

    if (pos == std::string::npos)
        return false;

    const auto cursor = editor.GetCursorPosition();

    // Convert a UTF-8 byte offset to a TextEditor column.
    const auto ToEditorColumn = [&](const std::size_t bytePos)
    {
        int column = 0;
        const int tabSize = editor.GetTabSize();

        for (std::size_t i = 0; i < bytePos;) {
            const auto ch =
                static_cast<unsigned char>(line[i]);

            if (ch == '\t') {
                if (tabSize > 0)
                    column += tabSize - column % tabSize;
                else
                    ++column;

                ++i;
            } else if ((ch & 0xC0) == 0x80) {
                ++i;
            } else {
                ++column;
                ++i;
            }
        }

        return column;
    };

    // Select the target text inside the editor.
    const TextEditor::Coordinates start(
        cursor.mLine,
        ToEditorColumn(pos));

    const TextEditor::Coordinates end(
        cursor.mLine,
        ToEditorColumn(pos + target.size()));

    editor.SetSelection(start, end);

    // Delete the selected text from the actual editor.
    editor.Delete();

    return true;
}

bool LDDrift::GUI::DrawCodeSuggestionPopup(
    bool& shouldOpen,
    const std::vector<std::string>& suggestions,
    std::string& selectedSuggestion,
    const ImVec2 position
) {
    auto& state = popupCompletionState;
    auto& editor = ImGuiEditorWindow.editorWindow;

    state.IsOpenInBeforeFrame = shouldOpen || state.WasOpen;

    if (!shouldOpen) {
        state.WasOpen = false;
        editor.SetCodeSuggestionPopupOpen(false);
        return false;
    }

    // Let TextEditor filter only the keys handled by the popup.
    editor.SetCodeSuggestionPopupOpen(true);

    if (!state.WasOpen) {
        state.WasOpen = true;
        state.SelectedIndex = 0;
    }
    if (position.x >= 0.0f && position.y >= 0.0f) {
        state.Position = position;
    }

    const int suggestionCount =
        static_cast<int>(suggestions.size());

    if (suggestionCount == 0) {
        state.SelectedIndex = 0;
    } else {
        state.SelectedIndex = std::clamp(
            state.SelectedIndex,
            0,
            suggestionCount - 1
        );
    }

    // ---------------------------------------------------------
    // Appearance
    // ---------------------------------------------------------

    ImGui::PushStyleColor(
        ImGuiCol_WindowBg,
        ImVec4(0.075f, 0.085f, 0.115f, 0.98f));

    ImGui::PushStyleColor(
        ImGuiCol_Border,
        ImVec4(0.25f, 0.30f, 0.42f, 1.0f));

    ImGui::PushStyleColor(
        ImGuiCol_Header,
        ImVec4(0.16f, 0.25f, 0.39f, 1.0f));

    ImGui::PushStyleColor(
        ImGuiCol_HeaderHovered,
        ImVec4(0.20f, 0.35f, 0.55f, 1.0f));

    ImGui::PushStyleColor(
        ImGuiCol_HeaderActive,
        ImVec4(0.24f, 0.42f, 0.67f, 1.0f));

    ImGui::PushStyleVar(
        ImGuiStyleVar_WindowRounding, 10.0f);

    ImGui::PushStyleVar(
        ImGuiStyleVar_WindowBorderSize, 1.0f);

    ImGui::PushStyleVar(
        ImGuiStyleVar_WindowPadding, ImVec2(12.0f, 12.0f));

    ImGui::PushStyleVar(
        ImGuiStyleVar_FrameRounding, 5.0f);

    ImGui::PushStyleVar(
        ImGuiStyleVar_ItemSpacing, ImVec2(6.0f, 7.0f));

    ImGui::SetNextWindowPos(
        state.Position, ImGuiCond_Always);

    ImGui::SetNextWindowSize(
        ImVec2(440.0f, 300.0f), ImGuiCond_Always);

    constexpr ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNavFocus;

    bool accepted = false;

    if (ImGui::Begin(
        "##LD_CodeSuggestionPopup",
        nullptr,
        flags)) {
        // -----------------------------------------------------
        // Header
        // -----------------------------------------------------

        ImGui::TextColored(
            ImVec4(0.40f, 0.72f, 1.0f, 1.0f),
            "Code Pathfinder");

        ImGui::SameLine();

        ImGui::TextDisabled(
            "%zu suggestions",
            suggestions.size());

        ImGui::Separator();
        ImGui::Spacing();

        // -----------------------------------------------------
        // Keyboard navigation
        // No popup focus is required.
        // TextEditor filters these keys while the popup is open.
        // -----------------------------------------------------

        if (suggestionCount > 0) {
            if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
                state.SelectedIndex =
                    (state.SelectedIndex + suggestionCount - 1)
                    % suggestionCount;
            }

            if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
                state.SelectedIndex =
                    (state.SelectedIndex + 1)
                    % suggestionCount;
            }
        }

        // -----------------------------------------------------
        // Enter: accept the suggestion
        // -----------------------------------------------------

        const bool enterPressed =
            ImGui::IsKeyPressed(ImGuiKey_Enter) ||
            ImGui::IsKeyPressed(ImGuiKey_KeypadEnter);

        if (enterPressed) {
            if (suggestionCount > 0) {
                selectedSuggestion =
                    suggestions[state.SelectedIndex];

                state.selectedSuggestion = selectedSuggestion;
                accepted = true;
            }

            shouldOpen = false;
            state.WasOpen = false;
        }

        // -----------------------------------------------------
        // Escape: close without accepting
        // -----------------------------------------------------

        if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
            shouldOpen = false;
            state.WasOpen = false;
        }

        // -----------------------------------------------------
        // Suggestion list
        // -----------------------------------------------------

        ImGui::BeginChild(
            "##LD_CodeSuggestionList",
            ImVec2(0.0f, 190.0f),
            false,
            ImGuiWindowFlags_None);

        if (suggestions.empty()) {
            ImGui::TextDisabled(
                "No suggestions available.");
        } else {
            for (int i = 0; i < suggestionCount; ++i) {
                ImGui::PushID(i);

                const bool isSelected =
                    state.SelectedIndex == i;

                if (ImGui::Selectable(
                    suggestions[i].c_str(),
                    isSelected,
                    ImGuiSelectableFlags_None,
                    ImVec2(0.0f, 27.0f))) {
                    state.SelectedIndex = i;

                    selectedSuggestion = suggestions[i];
                    state.selectedSuggestion = selectedSuggestion;

                    accepted = true;
                    shouldOpen = false;
                    state.WasOpen = false;
                }

                if (ImGui::IsItemHovered())
                    state.SelectedIndex = i;

                if (isSelected)
                    ImGui::SetScrollHereY(0.5f);

                ImGui::PopID();
            }
        }

        ImGui::EndChild();

        // -----------------------------------------------------
        // Footer
        // -----------------------------------------------------

        ImGui::Separator();

        ImGui::TextDisabled(
            "UP / DOWN  Navigate    ENTER  Select    ESC  Close");
    }

    ImGui::End();

    // Synchronize TextEditor with the final popup state.
    editor.SetCodeSuggestionPopupOpen(shouldOpen || state.IsOpenInBeforeFrame);

    ImGui::PopStyleVar(5);
    ImGui::PopStyleColor(5);

    return accepted;
}


LDDrift::GUI::GUI() = default;

void LDDrift::GUI::Initialize(GLFWwindow* glfwWindow) {
    GLB_assert(glfwWindow != nullptr)
    ProjectWatchTower_PTR = nullptr;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init();
    this->CreateNewWindow(CIRCLE_CONFIGURE_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(POLYGON_CONFIGURE_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(LINE_CONFIGURE_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(SET_KEY_TARGET_WINDOW_NAME, true, false,
                          "", {10, 10}, {100, 40}, false);
    this->CreateNewWindow(EXIT_WARNING_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(GAME_SETTING_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(SEE_OBJECTS_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}

std::vector<std::string> LDDrift::GUI::ExtractTextFromString(const std::string& text) {
    std::vector<std::string> result;
    const std::size_t textSize = text.size();
    std::size_t startTextLine = 0;
    std::size_t endTextLine = 0;
    while (endTextLine < textSize) {
        while (endTextLine < textSize && text[endTextLine] != '\n') {
            ++endTextLine;
        }
        result.push_back(text.substr(startTextLine, (endTextLine - startTextLine)));
        if (endTextLine < textSize) {
            ++endTextLine;
        }
        startTextLine = endTextLine;
    }
    return result;
}

void LDDrift::GUI::CreateNewWindow(const std::string& name,
                                   const bool canMoveWindow,
                                   const bool canResizeWindow,
                                   const std::string& textPrintInWindow,
                                   const VecPos2D& position,
                                   const VecPos2D& size,
                                   const bool SHOW) {
    defaultWindows.push_back({
        .name = name, .canMoveWindow = canMoveWindow, .canResizeWindow = canResizeWindow,
        .textPrintInWindow = LDDrift::GUI::ExtractTextFromString(textPrintInWindow),
        .position = position, .size = size, .Show = SHOW,
    });
}

void LDDrift::GUI::BeginRenderGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

LDDrift::DefaultWindowsData LDDrift::GUI::GetWindow(const std::string& nameWindow) const {
    for (const auto& window : defaultWindows) {
        if (window.name == nameWindow) {
            return window;
        }
    }
    return {
        .name = NULL_STRING, .canMoveWindow = false, .canResizeWindow = false, .textPrintInWindow = {},
        .position = {0, 0}, .size = {0, 0}
    };
}


void LDDrift::GUI::SetCorePTR(LDDrift::Core* corePTR) {
    NPV_assert(corePTR)
    core = corePTR;
    consoleWindow.SetCorePTR(core);
    mainWindow.SetCorePTR(core);
    projectWatchTowerWindow.SetCorePTR(core);
    projectWatchTowerWindow.Initialize();
    mainWindow.Initialize();
    consoleWindow.Initialize();
}

LDDrift::DefaultWindowsData* LDDrift::GUI::GetWindowPTR(const std::string& nameWindow) {
    const std::size_t windowNumber = defaultWindows.size();
    for (std::size_t windowIndex = 0; windowIndex < windowNumber; ++windowIndex) {
        if (defaultWindows[windowIndex].name == nameWindow) {
            return &defaultWindows[windowIndex];
        }
    }
    return nullptr;
}

void LDDrift::GUI::SetCompilePTR(LDDrift::Compile* compilePTR) {
    CompilePTR = compilePTR;
}

void LDDrift::GUI::CircleConfigureWindowHandler(DefaultWindowsData* window) {
    if (window->name != CIRCLE_CONFIGURE_WINDOW_NAME) {
        return;
    }
    static int CheckBoxIsOn = 0;
    static int thick = 1;
    static int useThickForCircleShape = 0;
    static int circlePointCount = 45;
    static float redValueColor = 0;
    static float greenValueColor = 0;
    static float blueValueColor = 0;
    static float alphaValueColor = 1;
    static int circleRadius = 1;
    static int circleSpeed = 1;
    static int xPos = 0;
    static int yPos = 0;
    ImGui::RadioButton("##Create New Circle", &CheckBoxIsOn, 0);
    ImGui::SameLine();
    ImGui::RadioButton("##Configure Circle", &CheckBoxIsOn, 1);
    ImGui::SameLine();
    ImGui::RadioButton("##Delete Circle", &CheckBoxIsOn, 2);
    if (CheckBoxIsOn == 0) {
        ImGui::TextUnformatted("window: Create New Circle");
        ImGui::Separator();
        ImGui::SetNextItemWidth(400);
        ImGui::InputTextWithHint("##Circle Shape Name", "Enter Circle Name: ", window->searchBuffer,
                                 sizeof(window->searchBuffer));
        ImGui::Separator();
        ImGui::TextUnformatted("Circle Point Count: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(250);
        ImGui::InputInt("##Circle Point Count", &circlePointCount, 1, 1);
        if (circlePointCount < 45) {
            circlePointCount = 45;
        }
        ImGui::Separator();
        ImGui::TextUnformatted("Circle Radius: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(285);
        ImGui::InputInt("##Circle Radius", &circleRadius, 1, 1);
        if (circleRadius < 1) {
            circleRadius = 1;
        }
        ImGui::Separator();
        ImGui::TextUnformatted("Red: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(110);
        ImGui::InputFloat("##Red Circle Color", &redValueColor, 0.005, 0.005, "%.3f");
        if (redValueColor > 1) {
            redValueColor = 1;
        }
        if (redValueColor < 0) {
            redValueColor = 0;
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Green: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(110);
        ImGui::InputFloat("##Green Circle Color", &greenValueColor, 0.005, 0.005, "%.3f");
        if (greenValueColor > 1) {
            greenValueColor = 1;
        }
        if (greenValueColor < 0) {
            greenValueColor = 0;
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Blue: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(110);
        ImGui::InputFloat("##Blue Circle Color", &blueValueColor, 0.005, 0.005, "%.3f");
        if (blueValueColor > 1) {
            blueValueColor = 1;
        }
        if (blueValueColor < 0) {
            blueValueColor = 0;
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Alpha: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(110);
        ImGui::InputFloat("##Alpha Circle Color", &alphaValueColor, 0.005, 0.005, "%.3f");
        if (alphaValueColor > 1) {
            alphaValueColor = 1;
        }
        if (alphaValueColor < 0) {
            alphaValueColor = 0;
        }
        ImGui::Separator();
        ImGui::RadioButton("Without Thick## ignore Thickness for circle shape", &useThickForCircleShape, 0);
        ImGui::SameLine();
        ImGui::RadioButton("With Thick## set Thickness for circle shape", &useThickForCircleShape, 1);
        if (useThickForCircleShape == 0) {
            ImGui::Separator();
        }
        if (useThickForCircleShape == 1) {
            ImGui::TextUnformatted("Enter thickness: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(545);
            ImGui::InputInt("##Get Thick OF Circle Shape", &thick, 1, 1);
            if (thick < 1) {
                thick = 1;
            }
            ImGui::Separator();
        }
        ImGui::TextUnformatted("Circle Speed: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(110);
        ImGui::InputInt("##Circle Speed ", &circleSpeed, 1, 1);
        if (circleSpeed < 0) {
            circleSpeed = 0;
        }
        ImGui::Separator();
        ImGui::TextUnformatted("Circle Position");
        ImGui::TextUnformatted("X position: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("##X Position", &xPos, 1, 1);
        ImGui::SameLine();
        ImGui::TextUnformatted("Y position: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("##Y position", &yPos, 1, 1);
        ImGui::Separator();
        if (ImGui::Button("Create")) {
            if (useThickForCircleShape == 0)
                core->scene.CreateCircleShape(std::string(window->searchBuffer), circlePointCount, circleRadius,
                                              circleSpeed,
                                              {static_cast<float>(xPos), static_cast<float>(yPos)},
                                              {redValueColor, greenValueColor, blueValueColor, alphaValueColor}, -1);
            else if (useThickForCircleShape == 1)
                core->scene.CreateCircleShape(std::string(window->searchBuffer), circlePointCount, circleRadius,
                                              circleSpeed,
                                              {static_cast<float>(xPos), static_cast<float>(yPos)},
                                              {redValueColor, greenValueColor, blueValueColor, alphaValueColor},
                                              static_cast<float>(thick));
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
        }
        ImGui::SameLine();
        if (ImGui::Button("Close")) {
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
        }
    } else if (CheckBoxIsOn == 1) {
        static std::optional<bool> inThisBrace;
        ImGui::TextUnformatted("window: Circle Configuration");
        static std::optional<LDDrift::Actors::Circle*> circle;
        if ((ImGui::InputTextWithHint("##Configure circle", "Enter Circle Name: ", window->searchBuffer,
                                      sizeof(window->searchBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) &&
            !(circle.has_value())) {
            circle = core->scene.GetCircle(std::string(window->searchBuffer));
            if (circle.value() == nullptr) {
                this->SetTextForWindow(
                    CIRCLE_CONFIGURE_WINDOW_NAME,
                    std::string("not available circle actor with this name -> ") + window->searchBuffer, true);
                return;
            }
        }
        if (circle.has_value() && circle.value() != nullptr) {
            if (!inThisBrace.has_value()) {
                circlePointCount = static_cast<int>(circle.value()->GetPointCount());
                circleRadius = static_cast<int>(circle.value()->GetRadius());
                circleSpeed = static_cast<int>(circle.value()->GetSpeed());
                redValueColor = circle.value()->GetPointColor(0).R;
                greenValueColor = circle.value()->GetPointColor(0).G;
                blueValueColor = circle.value()->GetPointColor(0).B;
                alphaValueColor = circle.value()->GetPointColor(0).A;
                xPos = static_cast<int>(circle.value()->GetCirclePosition().X);
                yPos = static_cast<int>(circle.value()->GetCirclePosition().Y);
                inThisBrace = true;
            }
            ImGui::Separator();
            ImGui::TextUnformatted("Circle Point Count: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(250);
            ImGui::InputInt("##Circle Point Count", &circlePointCount, 1, 1);
            if (circlePointCount < 45) {
                circlePointCount = 45;
            }
            ImGui::Separator();
            ImGui::TextUnformatted("Circle Radius: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(285);
            ImGui::InputInt("##Circle Radius", &circleRadius, 1, 1);
            if (circleRadius < 1) {
                circleRadius = 1;
            }
            ImGui::Separator();
            ImGui::TextUnformatted("Red: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(110);
            ImGui::InputFloat("##Red Circle Color", &redValueColor, 0.005, 0.005, "%.3f");
            if (redValueColor > 1) {
                redValueColor = 1;
            }
            if (redValueColor < 0) {
                redValueColor = 0;
            }
            ImGui::SameLine();
            ImGui::TextUnformatted("Green: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(110);
            ImGui::InputFloat("##Green Circle Color", &greenValueColor, 0.005, 0.005, "%.3f");
            if (greenValueColor > 1) {
                greenValueColor = 1;
            }
            if (greenValueColor < 0) {
                greenValueColor = 0;
            }
            ImGui::SameLine();
            ImGui::TextUnformatted("Blue: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(110);
            ImGui::InputFloat("##Blue Circle Color", &blueValueColor, 0.005, 0.005, "%.3f");
            if (blueValueColor > 1) {
                blueValueColor = 1;
            }
            if (blueValueColor < 0) {
                blueValueColor = 0;
            }
            ImGui::SameLine();
            ImGui::TextUnformatted("Alpha: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(110);
            ImGui::InputFloat("##Alpha Circle Color", &alphaValueColor, 0.005, 0.005, "%.3f");
            if (alphaValueColor > 1) {
                alphaValueColor = 1;
            }
            if (alphaValueColor < 0) {
                alphaValueColor = 0;
            }
            ImGui::Separator();
            ImGui::TextUnformatted("Circle Speed: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(110);
            ImGui::InputInt("##Circle Speed ", &circleSpeed, 1, 1);
            if (circleSpeed < 0) {
                circleSpeed = 0;
            }
            ImGui::Separator();
            ImGui::TextUnformatted("Circle Position");
            ImGui::TextUnformatted("X position: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::InputInt("##X Position", &xPos, 1, 1);
            ImGui::SameLine();
            ImGui::TextUnformatted("Y position: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::InputInt("##Y position", &yPos, 1, 1);
            ImGui::Separator();
            static int withThick = 0;
            static int thickness = 1;
            ImGui::RadioButton("Without thick## config without thickness", &withThick, 0);
            ImGui::SameLine();
            ImGui::RadioButton("with thick## config with thickness", &withThick, 1);
            if (withThick == 1) {
                ImGui::TextUnformatted("Enter Thickness: ");
                ImGui::SameLine();
                ImGui::InputInt("##enter thick", &thickness, 1, 1);
            }
            if (ImGui::Button("Configure")) {
                if (withThick == 1) {
                    circle.value()->SetJoinLineAlgorithm(LDDrift::JoinLineType::Bevel);
                    circle.value()->SetThickness(static_cast<float>(thickness));
                }
                circle.value()->SetCirclePosition({static_cast<float>(xPos), static_cast<float>(yPos)});
                circle.value()->SetPointCount(circlePointCount);
                circle.value()->SetScreenSize(core->window.GetWindowSize());
                circle.value()->SetRadius(static_cast<float>(circleRadius));
                circle.value()->SetSpeed(static_cast<float>(circleSpeed));
                circle.value()->SetAllPointsColor({redValueColor, greenValueColor, blueValueColor, alphaValueColor});
                circle.value()->Rebuild();
                circle.value()->SetOriginalPositionToCenter();
                core->scene.MarkSendDataToGPU();
                this->core->scene.ReSendShapesToRender();
                window->Show = false;
                inThisBrace = false;
                std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            }
            ImGui::SameLine();
            if (ImGui::Button("Close")) {
                window->Show = false;
                inThisBrace = false;
                std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            }
        } else {
            if (ImGui::Button("Close")) {
                window->Show = false;
                std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            }
        }
    } else if (CheckBoxIsOn == 2) {
        ImGui::Separator();
        ImGui::TextUnformatted("window: Delete Circle");
        ImGui::InputTextWithHint("##Circle name", "Enter Circle name: ", window->searchBuffer,
                                 sizeof(window->searchBuffer));
        static std::optional<bool> foundCircle;
        if (ImGui::Button("Delete")) {
            foundCircle = core->scene.FindCircleWithName(std::string(window->searchBuffer));
        }
        ImGui::SameLine();
        if (ImGui::Button("Close")) {
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
        }
        if (foundCircle.has_value() && foundCircle.value() == false) {
            ImGui::TextUnformatted(("Can not find circle with name -> " + std::string(window->searchBuffer)).c_str());
        } else if (foundCircle.has_value() && foundCircle.value() == true) {
            core->scene.DeleteCircleShape(std::string(window->searchBuffer));
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
        }
    }
}

void LDDrift::GUI::LineConfigureWindowHandler(DefaultWindowsData* window) const {
    if (window->name != LINE_CONFIGURE_WINDOW_NAME) {
        return;
    }
    static int radioButton = 0;
    static int startPos[2] = {0, 0};
    static int endPos[2] = {0, 0};
    static float color[4] = {0, 0, 0, 1};
    static int thickness = 1;
    ImGui::RadioButton("##Create New Line", &radioButton, 0);
    ImGui::SameLine();
    ImGui::RadioButton("##Create New Polygon", &radioButton, 1);
    ImGui::SameLine();
    ImGui::RadioButton("##Delete Line", &radioButton, 2);
    if (radioButton == 0) {
        ImGui::TextUnformatted("Window: Create New Line");
        ImGui::Separator();
        ImGui::SetNextItemWidth(400);
        ImGui::InputTextWithHint("##Line Name", "Enter Line name:", window->searchBuffer, sizeof(window->searchBuffer));
        ImGui::Separator();
        ImGui::TextUnformatted("Start Pos");
        ImGui::TextUnformatted("X pos: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputInt("##X Start Pos", &startPos[0], 1, 1);
        ImGui::SameLine();
        ImGui::TextUnformatted("Y pos: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputInt("##Y Start Pos", &startPos[1], 1, 1);
        ImGui::Separator();
        ImGui::TextUnformatted("End Pos");
        ImGui::TextUnformatted("X pos: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputInt("##X End Pos", &endPos[0], 1, 1);
        ImGui::SameLine();
        ImGui::TextUnformatted("Y pos: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputInt("##Y End Pos", &endPos[1], 1, 1);
        ImGui::Separator();
        ImGui::TextUnformatted("Thickness: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(93);
        ImGui::InputInt("##Thickness Of Line", &thickness, 1, 1);
        if (thickness < 1) {
            thickness = 1;
        }
        ImGui::Separator();
        ImGui::TextUnformatted("Color Of Line");
        ImGui::TextUnformatted("Red: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputFloat("##Red Line Color", &color[0], 0.005, 0.005, "%.3f");
        if (color[0] > 1) {
            color[0] = 1;
        }
        if (color[0] < 0) {
            color[0] = 0;
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Green: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputFloat("##Green Line Color", &color[1], 0.005, 0.005, "%.3f");
        if (color[1] > 1) {
            color[1] = 1;
        }
        if (color[1] < 0) {
            color[1] = 0;
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Blue: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputFloat("##Blue Line Color", &color[2], 0.005, 0.005, "%.3f");
        if (color[2] > 1) {
            color[2] = 1;
        }
        if (color[2] < 0) {
            color[2] = 0;
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Alpha: ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120);
        ImGui::InputFloat("##Alpha Line Color", &color[3], 0.005, 0.005, "%.3f");
        if (color[3] > 1) {
            color[3] = 1;
        }
        if (color[3] < 0) {
            color[3] = 0;
        }
        ImGui::Separator();
        if (ImGui::Button("Create")) {
            core->scene.CreateLineActor(std::string(window->searchBuffer), thickness, startPos, endPos,
                                        {color[0], color[1], color[2], color[3]});
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
        }
        ImGui::SameLine();
        if (ImGui::Button("Close")) {
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
        }
    } else if (radioButton == 1) {
        static std::optional<LDDrift::Actors::Line*> line = std::nullopt;
        static std::optional<bool> initialized = false;
        static std::optional<bool> findLineWithName = std::nullopt;
        ImGui::TextUnformatted("Window: configure line");
        if ((findLineWithName.has_value() && findLineWithName.value() == true) || ImGui::InputTextWithHint(
            "##Line Configuration", "Enter Line Name: ", window->searchBuffer,
            sizeof(window->searchBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            if ((findLineWithName.has_value() && findLineWithName.value() == true) || core->scene.FindLineWithName(
                std::string(window->searchBuffer))) {
                findLineWithName = true;
                if (initialized.has_value() && initialized.value() == false) {
                    initialized = true;
                    line = core->scene.GetLine(std::string(window->searchBuffer));
                    startPos[0] = static_cast<int>(line.value()->GetFirstPoint().X);
                    startPos[1] = static_cast<int>(line.value()->GetFirstPoint().Y);
                    endPos[0] = static_cast<int>(line.value()->GetSecondPoint().X);
                    endPos[1] = static_cast<int>(line.value()->GetSecondPoint().Y);
                    color[0] = line.value()->GetColor().R;
                    color[1] = line.value()->GetColor().G;
                    color[2] = line.value()->GetColor().B;
                    color[3] = line.value()->GetColor().A;
                    thickness = static_cast<int>(line.value()->GetThickness());
                }
                ImGui::Separator();
                ImGui::SetNextItemWidth(400);
                ImGui::InputTextWithHint("##Line Name", "Enter Line name:", window->searchBuffer,
                                         sizeof(window->searchBuffer));
                ImGui::Separator();
                ImGui::TextUnformatted("Start Pos");
                ImGui::TextUnformatted("X pos: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputInt("##X Start Pos", &startPos[0], 1, 1);
                ImGui::SameLine();
                ImGui::TextUnformatted("Y pos: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputInt("##Y Start Pos", &startPos[1], 1, 1);
                ImGui::Separator();
                ImGui::TextUnformatted("End Pos");
                ImGui::TextUnformatted("X pos: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputInt("##X End Pos", &endPos[0], 1, 1);
                ImGui::SameLine();
                ImGui::TextUnformatted("Y pos: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputInt("##Y End Pos", &endPos[1], 1, 1);
                ImGui::Separator();
                ImGui::TextUnformatted("Thickness: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(93);
                ImGui::InputInt("##Thickness Of Line", &thickness, 1, 1);
                if (thickness < 1) {
                    thickness = 1;
                }
                ImGui::Separator();
                ImGui::TextUnformatted("Color Of Line");
                ImGui::TextUnformatted("Red: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Red Line Color", &color[0], 0.005, 0.005, "%.3f");
                if (color[0] > 1) {
                    color[0] = 1;
                }
                if (color[0] < 0) {
                    color[0] = 0;
                }
                ImGui::SameLine();
                ImGui::TextUnformatted("Green: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Green Line Color", &color[1], 0.005, 0.005, "%.3f");
                if (color[1] > 1) {
                    color[1] = 1;
                }
                if (color[1] < 0) {
                    color[1] = 0;
                }
                ImGui::SameLine();
                ImGui::TextUnformatted("Blue: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Blue Line Color", &color[2], 0.005, 0.005, "%.3f");
                if (color[2] > 1) {
                    color[2] = 1;
                }
                if (color[2] < 0) {
                    color[2] = 0;
                }
                ImGui::SameLine();
                ImGui::TextUnformatted("Alpha: ");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Alpha Line Color", &color[3], 0.005, 0.005, "%.3f");
                if (color[3] > 1) {
                    color[3] = 1;
                }
                if (color[3] < 0) {
                    color[3] = 0;
                }
                ImGui::Separator();
                if (ImGui::Button("Configuration")) {
                    line.value()->SetFirstPoint({static_cast<float>(startPos[0]), static_cast<float>(startPos[1])});
                    line.value()->SetSecondPoint({static_cast<float>(endPos[0]), static_cast<float>(endPos[1])});
                    line.value()->SetScreenSize(core->window.GetViewportSize());
                    line.value()->SetThickness(static_cast<float>(thickness));
                    line.value()->SetLineColor({color[0], color[1], color[2], color[3]});
                    line.value()->CreateTriangles();
                    core->scene.MarkSendDataToGPU();
                    core->scene.ReSendShapesToRender();
                    window->Show = false;
                    std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
                }
                if (ImGui::Button("Close")) {
                    window->Show = false;
                    std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
                }
            } else {
                findLineWithName = false;
            }
        }
        if (!findLineWithName.has_value() || findLineWithName.value() == false) {
            if (ImGui::Button("Close")) {
                window->Show = false;
            }
        }
        if (findLineWithName.has_value() && findLineWithName.value() == false) {
            ImGui::TextUnformatted(("Can not find polygon wit name -> " + std::string(window->searchBuffer)).c_str());
        }
    } else if (radioButton == 2) {
        ImGui::Separator();
        ImGui::TextUnformatted("window: Delete Line");
        ImGui::InputTextWithHint("##Line Name", "Enter Line name: ", window->searchBuffer,
                                 sizeof(window->searchBuffer));
        static std::optional<bool> foundLine;
        if (ImGui::Button("Delete")) {
            foundLine = core->scene.FindLineWithName(std::string(window->searchBuffer));
        }
        ImGui::SameLine();
        if (ImGui::Button("Close")) {
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            foundLine = std::nullopt;
        }
        if (foundLine.has_value() && foundLine.value() == false) {
            ImGui::TextUnformatted(("can not find line with name -> " + std::string(window->searchBuffer)).c_str());
        } else if (foundLine.has_value() && foundLine.value() == true) {
            core->scene.DeleteLineShape(std::string(window->searchBuffer));
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            foundLine = std::nullopt;
        }
    }
}

void LDDrift::GUI::PolygonConfigureWindowHandler(DefaultWindowsData* window) const {
    if (window->name != POLYGON_CONFIGURE_WINDOW_NAME) {
        return;
    }
    // 0 = fill color with one color value
    // for example: filled shape with ( red color ) or ( blue color ) or ...
    // 1 = Each vertex has its own color value.
    /*
     *  for example:
     *      point shape of number 0 -> is red
     *      point shape of number 1 -> is blue
     *      and ...
     */
    static int fillColorWithOneColorOrEachVertexHaveAColor = 0;
    static int if_withThick = 0;
    static int drawThicknessRadioButton = 0;
    static int thickness = 1;
    static int radioButton = 0;
    static int polygonActorPointCount = 3;
    static float polygonActorRedColor = 0;
    static float polygonActorGreenColor = 0;
    static float polygonActorBlueColor = 0;
    static float polygonActorAlpha = 1;
    static int polygonActorSpeed = 1;
    static std::vector<LDDrift::VecCol> pointColors;
    const auto initPointColor = []()
    {
        if (pointColors.empty() || pointColors.size() != polygonActorPointCount) {
            pointColors.clear();
            for (std::size_t i = 0; i < polygonActorPointCount; ++i) {
                pointColors.emplace_back(0.0f, 0.0f, 0.0f, 1.0f);
            }
            std::cout << polygonActorPointCount << " - " << pointColors.size() << std::endl;
        }
    };
    ImGui::RadioButton("Create##Create New Polygon", &radioButton, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Configure##Configure Polygon", &radioButton, 1);
    ImGui::SameLine();
    ImGui::RadioButton("Delete##Delete polygon", &radioButton, 2);

    if (radioButton == 0) {
        ImGui::TextUnformatted("window: create new polygon");
        ImGui::SetNextItemWidth(300);
        ImGui::InputTextWithHint("##Polygone Name (00)", "Enter Polygon Actor Name:", window->searchBuffer,
                                 sizeof(window->searchBuffer));
        ImGui::TextUnformatted("Polygon Point Count: "); // START --- point count of Polygon
        ImGui::SameLine();
        ImGui::SetNextItemWidth(145);
        ImGui::InputInt("##Polygon Point Count (00)", &polygonActorPointCount, 1, 1);
        if (polygonActorPointCount < 3) {
            polygonActorPointCount = 3;
        }
        polygonActorPointCount = std::clamp(polygonActorPointCount, 3, 100);
        ImGui::Separator(); // END --- point count of polygon
        ImGui::RadioButton("without Thickness## not use thickness for polygon shapes", &if_withThick, 0);
        ImGui::SameLine();
        ImGui::RadioButton("With thickness## use thickness for polygon shapes", &if_withThick, 1);
        if (if_withThick == 0) {
            ImGui::Separator();
        } else if (if_withThick == 1) {
            ImGui::TextUnformatted("Enter Thickness: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(580);
            ImGui::InputInt("##Thickness for shape", &thickness, 1, 1);
            if (thickness < 1) {
                thickness = 1;
            }
            ImGui::RadioButton("Mitter## Miter join line algorithm", &drawThicknessRadioButton, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Round## round join line algorithm", &drawThicknessRadioButton, 1);
            ImGui::SameLine();
            ImGui::RadioButton("Bevel## bevel join line algorithm", &drawThicknessRadioButton, 2);
            ImGui::Separator();
        }
        ImGui::RadioButton("fill shape with##fill shape (00)", &fillColorWithOneColorOrEachVertexHaveAColor, 0);
        ImGui::SameLine();
        ImGui::RadioButton("set color for any vertexes##each vertex have a color (00)",
                           &fillColorWithOneColorOrEachVertexHaveAColor, 1);
        if (if_withThick == 1) {
            fillColorWithOneColorOrEachVertexHaveAColor = 0;
        }
        if (fillColorWithOneColorOrEachVertexHaveAColor == 0) {
            ImGui::TextUnformatted("Red: "); // START --- Red Color Of Polygon
            ImGui::SameLine();
            ImGui::SetNextItemWidth(120);
            ImGui::InputFloat("##polygon Red Color value (00)", &polygonActorRedColor, 0.005, 0.005, "%.3f");
            if (polygonActorRedColor > 1) {
                polygonActorRedColor = 1;
            }
            if (polygonActorRedColor < 0) {
                polygonActorRedColor = 0;
            }
            ImGui::SameLine(); // END --- Red Color Of Polygon
            ImGui::TextUnformatted("Green: "); // START --- Green Color Of Polygon
            ImGui::SameLine();
            ImGui::SetNextItemWidth(120);
            ImGui::InputFloat("##Polygon Green Color Value", &polygonActorGreenColor, 0.005, 0.005, "%.3f");
            if (polygonActorGreenColor > 1) {
                polygonActorGreenColor = 1;
            }
            if (polygonActorGreenColor < 0) {
                polygonActorGreenColor = 0;
            }
            ImGui::SameLine(); // END --- Green Color Of Polygon
            ImGui::TextUnformatted("Blue: "); // START --- Blue Color Of Polygon
            ImGui::SameLine();
            ImGui::SetNextItemWidth(120);
            ImGui::InputFloat("##Polygon Blue Color Value (00)", &polygonActorBlueColor, 0.005, 0.005, "%.3f");
            if (polygonActorBlueColor > 1) {
                polygonActorBlueColor = 1;
            }
            if (polygonActorBlueColor < 0) {
                polygonActorBlueColor = 0;
            }
            ImGui::SameLine(); // END --- Blue Color Of Polygon
            ImGui::TextUnformatted("Alpha: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(120);
            ImGui::InputFloat("##Polygon Alpha Color Value (00)", &polygonActorAlpha, 0.005, 0.005, "%.3f");
            if (polygonActorAlpha > 1) {
                polygonActorAlpha = 1;
            }
            if (polygonActorAlpha < 0) {
                polygonActorAlpha = 0;
            }
            ImGui::Separator();
        }
        if (fillColorWithOneColorOrEachVertexHaveAColor == 1) {
            initPointColor();
            for (std::size_t pointIndex = 0; pointIndex < polygonActorPointCount; ++pointIndex) {
                ImGui::PushID(static_cast<int>(pointIndex));
                ImGui::Text("point %s ( RED ): ", std::to_string(pointIndex).c_str());
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Polygon red Color Value %s (001)", &pointColors[pointIndex].R, 0.005, 0.005,
                                  "%.3f");
                if (pointColors[pointIndex].R > 1) {
                    pointColors[pointIndex].R = 1;
                }
                if (pointColors[pointIndex].R < 0) {
                    pointColors[pointIndex].R = 0;
                }
                ImGui::SameLine();
                ImGui::Text("point %s ( BLUE ): ", std::to_string(pointIndex).c_str());
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Polygon blue Color Value (001)", &pointColors[pointIndex].B, 0.005, 0.005,
                                  "%.3f");
                if (pointColors[pointIndex].B > 1) {
                    pointColors[pointIndex].B = 1;
                }
                if (pointColors[pointIndex].B < 0) {
                    pointColors[pointIndex].B = 0;
                }
                ImGui::SameLine();
                ImGui::Text("point %s ( GREEN ): ", std::to_string(pointIndex).c_str());
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Polygon green Color Value (001)", &pointColors[pointIndex].G, 0.005, 0.005,
                                  "%.3f");
                if (pointColors[pointIndex].G > 1) {
                    pointColors[pointIndex].G = 1;
                }
                if (pointColors[pointIndex].G < 0) {
                    pointColors[pointIndex].G = 0;
                }
                ImGui::SameLine();
                ImGui::Text("point %s ( ALPHA ): ", std::to_string(pointIndex).c_str());
                ImGui::SameLine();
                ImGui::SetNextItemWidth(120);
                ImGui::InputFloat("##Polygon alpha Color Value (001)", &pointColors[pointIndex].A, 0.005, 0.005,
                                  "%.3f");
                if (pointColors[pointIndex].A > 1) {
                    pointColors[pointIndex].A = 1;
                }
                if (pointColors[pointIndex].A < 0) {
                    pointColors[pointIndex].A = 0;
                }
                ImGui::Separator();
                ImGui::PopID();
            }
        }
        ImGui::TextUnformatted("Polygon Speed Value: "); // START --- speed of polygon
        ImGui::SameLine();
        ImGui::SetNextItemWidth(555);
        ImGui::InputInt("##Polygon Speed Value", &polygonActorSpeed, 1, 1);
        if (polygonActorSpeed < 0) {
            polygonActorSpeed = 0;
        }
        ImGui::Separator(); // END --- speed of polygon
        ImGui::TextUnformatted("Set Point Position");
        static std::vector<int> pointPositions(polygonActorPointCount * 2);
        pointPositions.resize(polygonActorPointCount * 2);
        for (int pointIndex = 0; pointIndex < polygonActorPointCount; ++pointIndex) {
            ImGui::TextUnformatted("X Position: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::InputInt((std::string("##X Position Of point ") + std::to_string(pointIndex)).c_str(),
                            &pointPositions[pointIndex * 2], 1, 1);
            ImGui::SameLine();
            ImGui::TextUnformatted("Y Position: ");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::InputInt((std::string("##Y Position Of point ") + std::to_string(pointIndex)).c_str(),
                            &pointPositions[pointIndex * 2 + 1], 1, 1);
            ImGui::Separator();
        }

        if (ImGui::Button("Create")) {
            if (fillColorWithOneColorOrEachVertexHaveAColor == 0) {
                if (if_withThick == 0) {
                    core->scene.CreatePolygonShape(std::string(window->searchBuffer), polygonActorPointCount,
                                                   polygonActorSpeed,
                                                   pointPositions.data(), {
                                                       polygonActorRedColor, polygonActorGreenColor,
                                                       polygonActorBlueColor,
                                                       polygonActorAlpha
                                                   }, -1, -1);
                } else if (if_withThick == 1) {
                    core->scene.CreatePolygonShape(std::string(window->searchBuffer), polygonActorPointCount,
                                                   polygonActorSpeed,
                                                   pointPositions.data(), {
                                                       polygonActorRedColor, polygonActorGreenColor,
                                                       polygonActorBlueColor,
                                                       polygonActorAlpha
                                                   }, static_cast<float>(thickness), drawThicknessRadioButton);
                }
                window->Show = false;
                std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            } else if (fillColorWithOneColorOrEachVertexHaveAColor == 1) {
                if (if_withThick == 0) {
                    core->scene.CreatePolygonShape(std::string(window->searchBuffer), polygonActorPointCount,
                                                   polygonActorSpeed,
                                                   pointPositions.data(), pointColors, -1, -1);
                } else if (if_withThick == 1) {
                    core->scene.CreatePolygonShape(std::string(window->searchBuffer), polygonActorPointCount,
                                                   polygonActorSpeed,
                                                   pointPositions.data(), pointColors, static_cast<float>(thickness),
                                                   drawThicknessRadioButton);
                }
                window->Show = false;
                std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Close")) {
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
        }
    } else if (radioButton == 1) {
        static std::optional<LDDrift::Actors::Polygon*> polygonActor = std::nullopt;
        static std::optional<bool> variablesInitialized = false;
        static std::optional<bool> findShapeWithName = std::nullopt;
        static std::vector<int> pointPositions(polygonActorPointCount * 2);
        pointPositions.resize(polygonActorPointCount * 2);
        ImGui::TextUnformatted("window: polygon configuration");
        if ((findShapeWithName.has_value() && findShapeWithName.value() == true) || ImGui::InputTextWithHint(
            "##Polygon Name", "Enter Polygon Name: ", window->searchBuffer,
            sizeof(window->searchBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            if ((findShapeWithName.has_value() && findShapeWithName.value() == true) || core->scene.
                FindPolygonWithName(std::string(window->searchBuffer))) {
                findShapeWithName.operator=(true);
                if (variablesInitialized.has_value() && variablesInitialized.value() == false) {
                    variablesInitialized = true;
                    polygonActorPointCount = std::clamp(polygonActorPointCount, 3, 100);

                    pointColors.assign(static_cast<std::size_t>(polygonActorPointCount),
                                       LDDrift::VecCol(0.0f, 0.0f, 0.0f, 1.0f));
                    polygonActor = core->scene.GetPolygon(std::string(window->searchBuffer));
                    polygonActorPointCount = static_cast<int>(polygonActor.value()->GetPointCount());
                    polygonActorRedColor = polygonActor.value()->GetPointColor(0).R;
                    polygonActorGreenColor = polygonActor.value()->GetPointColor(0).G;
                    polygonActorBlueColor = polygonActor.value()->GetPointColor(0).B;
                    polygonActorAlpha = polygonActor.value()->GetPointColor(0).A;
                    polygonActorSpeed = static_cast<int>(polygonActor.value()->GetSpeed());
                    for (std::size_t point = 0; point < polygonActorPointCount; ++point) {
                        const LDDrift::VecPos2D& pointPos = polygonActor.value()->GetGlobalPoint(point);
                        pointPositions[point * 2] = static_cast<int>(pointPos.X);
                        pointPositions[point * 2 + 1] = static_cast<int>(pointPos.Y);
                    }
                    if_withThick = 0;
                    thickness = 1;
                    drawThicknessRadioButton = 0;
                    fillColorWithOneColorOrEachVertexHaveAColor = 0;
                }
                ImGui::SetNextItemWidth(300);
                ImGui::InputTextWithHint("##Polygone Name", "Enter Polygon Actor Name:", window->searchBuffer,
                                         sizeof(window->searchBuffer));
                ImGui::TextUnformatted("Polygon Point Count: "); // START --- point count of Polygon
                ImGui::SameLine();
                ImGui::SetNextItemWidth(145);
                if (ImGui::InputInt("##Polygon Point Count", &polygonActorPointCount, 1, 1)) {
                    polygonActorPointCount = std::clamp(polygonActorPointCount, 3, 100);

                    pointPositions.resize(static_cast<std::size_t>(polygonActorPointCount) * 2);

                    pointColors.assign(static_cast<std::size_t>(polygonActorPointCount),
                                       LDDrift::VecCol(0.0f, 0.0f, 0.0f, 1.0f));
                }
                polygonActorPointCount = std::clamp(polygonActorPointCount, 3, 100);
                ImGui::Separator(); // END --- point count of polygon
                ImGui::RadioButton("without thickness", &if_withThick, 0);
                ImGui::SameLine();
                ImGui::RadioButton("with thickness", &if_withThick, 1);
                if (if_withThick == 1) {
                    ImGui::TextUnformatted("enter thick: ");
                    ImGui::SameLine();
                    ImGui::InputInt("##enter thickness input int", &thickness, 1, 1);
                    ImGui::RadioButton("Miter##miter line join alg", &drawThicknessRadioButton, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Round##round line join alg", &drawThicknessRadioButton, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("Bevel##bevel line join alg", &drawThicknessRadioButton, 2);
                }
                ImGui::Separator();
                ImGui::RadioButton("fill shape with a color##_FILL_", &fillColorWithOneColorOrEachVertexHaveAColor, 0);
                ImGui::SameLine();
                ImGui::RadioButton("set color for any vertices##_SET_COLOR_FOR_ANY_VERTICES",
                                   &fillColorWithOneColorOrEachVertexHaveAColor, 1);
                if (if_withThick == 1) {
                    fillColorWithOneColorOrEachVertexHaveAColor = 0;
                }
                if (fillColorWithOneColorOrEachVertexHaveAColor == 0) {
                    ImGui::TextUnformatted("Red: "); // START --- Red Color Of Polygon
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(120);
                    ImGui::InputFloat("##polygon Red Color value", &polygonActorRedColor, 0.005, 0.005, "%.3f");
                    if (polygonActorRedColor > 1) {
                        polygonActorRedColor = 1;
                    }
                    if (polygonActorRedColor < 0) {
                        polygonActorRedColor = 0;
                    }
                    ImGui::SameLine(); // END --- Red Color Of Polygon
                    ImGui::TextUnformatted("Green: "); // START --- Green Color Of Polygon
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(120);
                    ImGui::InputFloat("##Polygon Green Color Value", &polygonActorGreenColor, 0.005, 0.005, "%.3f");
                    if (polygonActorGreenColor > 1) {
                        polygonActorGreenColor = 1;
                    }
                    if (polygonActorGreenColor < 0) {
                        polygonActorGreenColor = 0;
                    }
                    ImGui::SameLine(); // END --- Green Color Of Polygon
                    ImGui::TextUnformatted("Blue: "); // START --- Blue Color Of Polygon
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(120);
                    ImGui::InputFloat("##Polygon Blue Color Value", &polygonActorBlueColor, 0.005, 0.005, "%.3f");
                    if (polygonActorBlueColor > 1) {
                        polygonActorBlueColor = 1;
                    }
                    if (polygonActorBlueColor < 0) {
                        polygonActorBlueColor = 0;
                    }
                    ImGui::SameLine(); // END --- Blue Color Of Polygon
                    ImGui::TextUnformatted("Alpha: ");
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(120);
                    ImGui::InputFloat("##Polygon Alpha Color Value", &polygonActorAlpha, 0.005, 0.005, "%.3f");
                    if (polygonActorAlpha > 1) {
                        polygonActorAlpha = 1;
                    }
                    if (polygonActorAlpha < 0) {
                        polygonActorAlpha = 0;
                    }
                } else if (fillColorWithOneColorOrEachVertexHaveAColor == 1) {
                    for (std::size_t pointIndex = 0; pointIndex < polygonActorPointCount; ++pointIndex) {
                        ImGui::PushID(static_cast<int>(pointIndex));
                        ImGui::TextUnformatted("RED: ");
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(120);
                        ImGui::InputFloat("##RED_COLOR_VALUE", &pointColors[pointIndex].R, 0.005, 0.005, "%.3f");
                        ImGui::SameLine();
                        ImGui::TextUnformatted("GREEN: ");
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(120);
                        ImGui::InputFloat("##GREEN_COLOR_VALUE", &pointColors[pointIndex].G, 0.005, 0.005, "%.3f");
                        ImGui::SameLine();
                        ImGui::TextUnformatted("BLUE: ");
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(120);
                        ImGui::InputFloat("##BLUE_COLOR_VALUE", &pointColors[pointIndex].B, 0.005, 0.005, "%.3f");
                        ImGui::SameLine();
                        ImGui::TextUnformatted("ALPHA: ");
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(120);
                        ImGui::InputFloat("##ALPHA_COLOR_VALUE", &pointColors[pointIndex].A, 0.005, 0.005, "%.3f");
                        ImGui::Separator();
                        ImGui::PopID();
                    }
                }
                ImGui::Separator();
                ImGui::TextUnformatted("Polygon Speed Value: "); // START --- speed of polygon
                ImGui::SameLine();
                ImGui::SetNextItemWidth(555);
                ImGui::InputInt("##Polygon Speed Value", &polygonActorSpeed, 1, 1);
                if (polygonActorSpeed < 0) {
                    polygonActorSpeed = 0;
                }
                ImGui::Separator(); // END --- speed of polygon
                ImGui::TextUnformatted("Set Point Position");
                for (int pointIndex = 0; pointIndex < polygonActorPointCount; ++pointIndex) {
                    ImGui::TextUnformatted("X Position: ");
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt((std::string("##X Position Of point ") + std::to_string(pointIndex)).c_str(),
                                    &pointPositions[pointIndex * 2], 1, 1);
                    ImGui::SameLine();
                    ImGui::TextUnformatted("Y Position: ");
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt((std::string("##Y Position Of point ") + std::to_string(pointIndex)).c_str(),
                                    &pointPositions[pointIndex * 2 + 1], 1, 1);
                    ImGui::Separator();
                }
                if (ImGui::Button("Configure")) {
                    if (if_withThick == 1) {
                        if (drawThicknessRadioButton == 0) {
                            polygonActor.value()->SetJoinLineAlgorithm(LDDrift::JoinLineType::Miter);
                        } else if (drawThicknessRadioButton == 1) {
                            polygonActor.value()->SetJoinLineAlgorithm(LDDrift::JoinLineType::Round);
                        } else if (drawThicknessRadioButton == 2) {
                            polygonActor.value()->SetJoinLineAlgorithm(LDDrift::JoinLineType::Bevel);
                        }
                        polygonActor.value()->SetThickness(static_cast<float>(thickness));
                    }
                    polygonActor.value()->SetPointCount(polygonActorPointCount);
                    polygonActor.value()->SetScreenSize(core->window.GetViewportSize());
                    polygonActor.value()->SetSpeed(static_cast<float>(polygonActorSpeed));
                    if (fillColorWithOneColorOrEachVertexHaveAColor == 0) {
                        polygonActor.value()->SetAllPointsColor({
                            polygonActorRedColor, polygonActorGreenColor, polygonActorBlueColor, polygonActorAlpha
                        });
                    } else if (fillColorWithOneColorOrEachVertexHaveAColor == 1) {
                        std::size_t counter = 0;
                        for (const LDDrift::VecCol& color : pointColors) {
                            polygonActor.value()->SetPointColor(counter++, color);
                        }
                    }
                    for (int pointIndex = 0; pointIndex < polygonActorPointCount; ++pointIndex) {
                        polygonActor.value()->SetPoint(pointIndex, {
                                                           static_cast<float>(pointPositions[pointIndex * 2]),
                                                           static_cast<float>(pointPositions[pointIndex * 2 + 1])
                                                       });
                    }
                    core->scene.MarkSendDataToGPU();
                    core->scene.ReSendShapesToRender();
                    window->Show = false;
                }
                if (ImGui::Button("Close")) {
                    window->Show = false;
                }
            } else {
                findShapeWithName.operator=(false);
            }
        }
        if (!findShapeWithName.has_value() || findShapeWithName.value() == false) {
            if (ImGui::Button("Close")) {
                window->Show = false;
            }
        }
        if (findShapeWithName.has_value() && findShapeWithName.value() == false) {
            ImGui::TextUnformatted(("Can not find polygon wit name -> " + std::string(window->searchBuffer)).c_str());
        }
    } else if (radioButton == 2) {
        ImGui::Separator();
        ImGui::TextUnformatted("window: Delete Polygon");
        ImGui::InputTextWithHint("##polygon name", "Enter polygon Name: ", window->searchBuffer,
                                 sizeof(window->searchBuffer));
        static std::optional<bool> foundPolygon;
        if (ImGui::Button("Delete")) {
            foundPolygon = core->scene.FindPolygonWithName(std::string(window->searchBuffer));
        }
        ImGui::SameLine();
        if (ImGui::Button("Close")) {
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            foundPolygon = std::nullopt;
        }
        if (foundPolygon.has_value() && foundPolygon.value() == false) {
            ImGui::TextUnformatted(("can not find polygon with name -> " + std::string(window->searchBuffer)).c_str());
        } else if (foundPolygon.has_value() && foundPolygon.value() == true) {
            core->scene.DeletePolygonShape(std::string(window->searchBuffer));
            window->Show = false;
            std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
            foundPolygon = std::nullopt;
        }
    }
}

bool LDDrift::GUI::SearchableCombo(char* buffer, const std::vector<std::string>& options) {
    bool selected = false;
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputTextWithHint("##Set Keys of Target", "Search...", buffer, 256);
    const std::string searchText = buffer;
    if (ImGui::IsItemActivated() || ImGui::IsItemActive()) { ImGui::OpenPopup("##Set Keys of Target"); }
    if (ImGui::BeginPopup("##Set Keys of Target")) {
        for (const std::string& option : options) {
            if (!searchText.empty()) { if (option.find(searchText) == std::string::npos) continue; }
            if (ImGui::Selectable(option.c_str())) {
                const size_t length = std::min(option.size(), static_cast<std::size_t>(255));
                std::copy_n(option.data(), length, buffer);
                buffer[length] = '\0';
                selected = true;
            }
        }
        ImGui::EndPopup();
    }
    return selected;
}

void LDDrift::GUI::SetKeyTargetWindowHandler(DefaultWindowsData* window) const {
    if (window->name != SET_KEY_TARGET_WINDOW_NAME) {
        return;
    }
    this->SearchableCombo(window->searchBuffer,
                          LDDrift::KeyBoardKeyName);
    ImGui::Separator();
    if (ImGui::Button("Set")) {
        LDDrift::input::Keyboard::SetKeyTarget(std::string(window->searchBuffer));
        window->Show = false;
        std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
    }
    ImGui::SameLine();
    if (ImGui::Button("Close")) {
        window->Show = false;
        std::memset(window->searchBuffer, '\0', sizeof(window->searchBuffer));
    }
}

void LDDrift::GUI::TransformString(std::string& text) {
    std::size_t pos = 0;

    while ((pos = text.find('\t', pos)) != std::string::npos) {
        text.replace(pos, 1, "    ");
        pos += 4;
    }
}

bool LDDrift::GUI::ValidChar(const char c) {
    return (c >= 65 && c <= 90) ||
        (c >= 97 && c <= 122) ||
        (c >= '0' && c <= '9') ||
        c == ':' || c == '_';
}

void LDDrift::GUI::PopupCompletionLogic() {
    TextEditor& editor = ImGuiEditorWindow.editorWindow;
    if (!popupCompletionState.ShowPopup) {
        popupCompletionState.WasOpen = false;
        editor.SetCodeSuggestionPopupOpen(false);
        return;
    }
    std::string line = editor.GetCurrentLineText();
    TransformString(line);
    const TextEditor::Coordinates cursorPos = editor.GetCursorPosition();
    int startPos = cursorPos.mColumn - 1;
    while (startPos > LOWER_BOUND_WHILE_LOOP && ValidChar(line[startPos])) {
        --startPos;
    }
    ++startPos;

    const std::string text = line.substr(startPos, cursorPos.mColumn - startPos);


    if (const std::vector<std::string> suggestions = core->codePathfinder.GetSuggestions(text);
        DrawCodeSuggestionPopup(popupCompletionState.ShowPopup, suggestions,
                                popupCompletionState.selectedSuggestion, {
                                    editor.GetCursorScreenPosition().x + 20,
                                    editor.GetCursorScreenPosition().y
                                })) {
        RemoveTextFromCurrentLine(editor, text);
        editor.InsertText(popupCompletionState.selectedSuggestion);
        popupCompletionState.selectedSuggestion.clear();
    }
}

void LDDrift::GUI::EndRenderGUI() {
    constexpr ImGuiWindowFlags FLAGS = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    ImGui::SetNextWindowPos({mainWindow.GetPosition().X, mainWindow.GetPosition().Y});
    ImGui::SetNextWindowSize({mainWindow.GetSize().X, mainWindow.GetSize().Y});
    ImGui::Begin(MAIN_WINDOW_NAME, nullptr, FLAGS);
    mainWindow.Render();
    ImGui::End();
    ImGui::SetNextWindowPos({projectWatchTowerWindow.GetPosition().X, projectWatchTowerWindow.GetPosition().Y});
    ImGui::SetNextWindowSize({projectWatchTowerWindow.GetSize().X, projectWatchTowerWindow.GetSize().Y});
    ImGui::Begin(PROJECT_WATCH_TOWER_WINDOW_NAME, nullptr, FLAGS);
    projectWatchTowerWindow.Render();
    ImGui::End();
    ImGui::SetNextWindowPos({consoleWindow.GetPosition().X, consoleWindow.GetPosition().Y});
    ImGui::SetNextWindowSize({consoleWindow.GetSize().X, consoleWindow.GetSize().Y});
    ImGui::Begin(CONSOLE_WINDOW_NAME, nullptr, FLAGS);
    consoleWindow.Render();
    ImGui::End();
    for (DefaultWindowsData& window : defaultWindows) {
        if (!window.Show || window.name.empty()) {
            continue;
        }
        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoCollapse;
        if (!window.canResizeWindow) {
            flags |= ImGuiWindowFlags_NoResize;
        }
        if (!window.canMoveWindow) {
            flags |= ImGuiWindowFlags_NoMove;
        }
        if ((window.name != CIRCLE_CONFIGURE_WINDOW_NAME) && (window.name != POLYGON_CONFIGURE_WINDOW_NAME) &&
            (window.name != LINE_CONFIGURE_WINDOW_NAME) && (window.name != SET_KEY_TARGET_WINDOW_NAME) &&
            (window.name != EXIT_WARNING_WINDOW_NAME) && (window.name != GAME_SETTING_WINDOW_NAME) &&
            (window.name != SEE_OBJECTS_WINDOW_NAME)) {
            ImGui::SetNextWindowSize(ImVec2(window.size.X, window.size.Y));
            ImGui::SetNextWindowPos(ImVec2(window.position.X, window.position.Y));
        }

        ImGui::Begin(window.name.c_str(), nullptr, flags);
        // مدیریت صفحه ساخت دایره
        CircleConfigureWindowHandler(&window);
        // مدیریت صفحه ساخت خط
        LineConfigureWindowHandler(&window);
        // مدیریت صفحه ساخت چند ضلعی
        PolygonConfigureWindowHandler(&window);
        // مدیریت صفحه تنظیمات بازی
        this->GameSettingWindowHandler(&window);
        // مدیریت رویداده های کلید های مورد نظر کاربر
        this->SetKeyTargetWindowHandler(&window);
        this->SeeObjectsWindowHandler(&window);
        if (!window.textPrintInWindow.empty())
            for (const std::string& text : window.textPrintInWindow) {
                ImGui::TextUnformatted(text.c_str());
            }
        ImGui::End();
    }
    // میدیریت ادیتور موتور بازی
    // Code editor
    if (ImGuiEditorWindow.Show && !ImGuiEditorWindow.name.empty()) {
        ImGui::Begin(ImGuiEditorWindow.name.c_str());

        if (ImGui::Button("Save")) {
            NPV_assert(ProjectWatchTower_PTR);

            const std::string sourceCode =
                ImGuiEditorWindow.editorWindow.GetText();

            ProjectWatchTower_PTR->WriteCodeToFile(
                ImGuiEditorWindow.name,
                sourceCode.c_str()
            );
        }

        ImGui::SameLine();

        if (ImGui::Button("Exit")) {
            ImGuiEditorWindow.Show = false;
        }

        ImGui::Separator();

        auto& editor = ImGuiEditorWindow.editorWindow;


        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
            LDDrift::input::Keyboard::IsKeyPressed(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_T)) {
            popupCompletionState.ShowPopup = true;
        }

        ImGui::Text(
            "Popup state: %s",
            popupCompletionState.ShowPopup ? "OPEN" : "CLOSED"
        );

        PopupCompletionLogic();

        editor.SetCodeSuggestionPopupOpen(popupCompletionState.IsOpenInBeforeFrame);


        editor.Render(
            "##Code",
            ImVec2(-1.0f, -1.0f),
            true
        );

        popupCompletionState.IsOpenInBeforeFrame = false;

        editor.SetCodeSuggestionPopupOpen(popupCompletionState.ShowPopup);


        ImGui::End();
    }
    if (popupCompletionState.ShowPopup) {
        if (ImGuiWindow* popupWindow =
            ImGui::FindWindowByName("##LD_CodeSuggestionPopup")) {
            ImGui::BringWindowToDisplayFront(popupWindow);
        }
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void LDDrift::GUI::UpdateWindow(const std::string& windowName) {
    for (auto& window : defaultWindows) {
        if (window.name == windowName) {
            window.textPrintInWindow.clear();
            break;
        }
    }
}

std::string LDDrift::GUI::GetCodeBuffer() const {
    return ImGuiEditorWindow.editorWindow.GetText();
}

void LDDrift::GUI::SetProjectWatchTower_PTR(LDDrift::ProjectWatchTower* projectWatchTower) {
    ProjectWatchTower_PTR = projectWatchTower;
}

void LDDrift::GUI::CreateNewEditor(const std::string& name, const bool canShowWindow) {
    ImGuiEditorWindow.name = name;
    ImGuiEditorWindow.Show = canShowWindow;
}

void LDDrift::GUI::SetTextForWindow(const std::string& windowName, const std::string& text,
                                    const bool deletePreviousMessages) {
    for (DefaultWindowsData& window : defaultWindows) {
        if (window.name == windowName) {
            if (deletePreviousMessages) {
                window.textPrintInWindow.clear();
            }
            for (const std::string& line : LDDrift::GUI::ExtractTextFromString(text)) {
                window.textPrintInWindow.push_back(line);
            }
            break;
        }
    }
}

void LDDrift::GUI::RenameEditorWindow(const std::string& newWindowName) {
    ImGuiEditorWindow.name = newWindowName;
}

void LDDrift::GUI::SetShowEditorWindow(const bool show) {
    ImGuiEditorWindow.Show = show;
}

int LDDrift::GUI::CodeEditorCallback(ImGuiInputTextCallbackData* data) {
    if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion &&
        data->EventKey == ImGuiKey_Tab) {
        constexpr const char* Indentation = "    ";

        if (data->HasSelection()) {
            const int SelectionStart = data->SelectionStart;
            const int SelectionSize =
                data->SelectionEnd - data->SelectionStart;

            data->DeleteChars(SelectionStart, SelectionSize);
            data->InsertChars(SelectionStart, Indentation);
        } else {
            data->InsertChars(data->CursorPos, Indentation);
        }
    }

    return 0;
}

void LDDrift::GUI::GameSettingWindowHandler(DefaultWindowsData* window) {
    if (window->name != GAME_SETTING_WINDOW_NAME) {
        return;
    }
    static bool checkbox = false;
    ImGui::Separator();
    ImGui::TextUnformatted("actors");
    if (ImGui::Button("Circle")) {
        DefaultWindowsData* circleWindow = GetWindowPTR(CIRCLE_CONFIGURE_WINDOW_NAME);
        NPV_assert(circleWindow)
        circleWindow->Show = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Polygon")) {
        DefaultWindowsData* polygonWindow = GetWindowPTR(POLYGON_CONFIGURE_WINDOW_NAME);
        NPV_assert(polygonWindow)
        polygonWindow->Show = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Line")) {
        DefaultWindowsData* lineWindow = GetWindowPTR(LINE_CONFIGURE_WINDOW_NAME);
        NPV_assert(lineWindow)
        lineWindow->Show = true;
    }
    ImGui::Separator();
    ImGui::TextUnformatted("Camera");

    ImGui::Text("Camera Speed: %s", std::to_string(core->camera.GetSpeed()).c_str());
    ImGui::SameLine();
    if (ImGui::Button("-##Sub Speed")) {
        core->camera.SubSpeedCamera(5);
    }
    ImGui::SameLine();
    if (ImGui::Button("+##Add Speed")) {
        core->camera.AddSpeedCamera(5);
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset##Reset Speed Camera Value")) {
        core->camera.SetSpeedCamera(1);
    }
    ImGui::Text("Camera Zoom: %s", std::to_string(core->camera.GetZoom()).c_str());
    ImGui::SameLine();
    if (ImGui::Button("-##Sub Zoom")) {
        core->camera.SubZoomCamera(1.0f);
        core->render.UpdateViewMatrix();
    }
    ImGui::SameLine();
    if (ImGui::Button("+##Add Zoom")) {
        core->camera.AddZoomCamera(1.0f);
        core->render.UpdateViewMatrix();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset##Reset Zoom Camera Value")) {
        core->camera.SetZoomCamera(1);
        core->render.UpdateViewMatrix();
    }
    ImGui::Separator();
    ImGui::Checkbox("See Objects## se objects window", &checkbox);
    if (checkbox) {
        GetWindowPTR(SEE_OBJECTS_WINDOW_NAME)->Show = true;
    } else {
        GetWindowPTR(SEE_OBJECTS_WINDOW_NAME)->Show = false;
    }
    if (ImGui::Button("Close")) {
        window->Show = false;
    }
}

void LDDrift::GUI::OpenWindow(const std::string& name) {
    for (auto& window : defaultWindows) {
        if (window.name == name) {
            window.Show = true;
        }
    }
}

void LDDrift::GUI::SeeObjectsWindowHandler(const DefaultWindowsData* window) const {
    if (window->name != SEE_OBJECTS_WINDOW_NAME) {
        return;
    }
    const auto init = [](std::vector<bool>& arr, const std::size_t sz) -> void
    {
        for (std::size_t i = 0; i < sz; ++i) {
            arr.push_back(false);
        }
    };
    const auto ConvertLineJoiningAlgorithmToString = [](const LDDrift::JoinLineType& jlt) -> const char*
    {
        if (jlt == LDDrift::JoinLineType::Miter) {
            return "Miter";
        } else if (jlt == LDDrift::JoinLineType::Round) {
            return "Round";
        } else if (jlt == LDDrift::JoinLineType::Bevel) {
            return "Bevel";
        } else {
            return NULL_STRING;
        }
    };
    // start - circle
    const std::vector<std::string> circles_name = core->scene.GetCircleNames();
    const std::vector<LDDrift::Actors::Circle*> circles = core->scene.GetCircles_ptr();
    static std::vector<bool> checkBoxState_circle;
    // end - circle
    //-------------//
    // start - line
    const std::vector<std::string> polygons_name = core->scene.GetPolygonNames();
    const std::vector<LDDrift::Actors::Line*> lines = core->scene.GetLines_ptr();
    static std::vector<bool> checkBoxState_line;
    // end - line
    //-------------//
    // start - polygon
    const std::vector<std::string> lines_name = core->scene.GetLineNames();
    const std::vector<LDDrift::Actors::Polygon*> polygons = core->scene.GetPolygons_ptr();
    static std::vector<bool> checkBoxState_polygon;
    // end - polygon

    // circle objects
    const std::size_t circleCount = circles.size();
    init(checkBoxState_circle, circleCount);
    for (std::size_t circleNumber = 0; circleNumber < circleCount; ++circleNumber) {
        ImGui::PushID(static_cast<int>(circleNumber));
        const LDDrift::Actors::Circle* c_ptr = circles[circleNumber];
        bool state = checkBoxState_circle[circleNumber];
        ImGui::Checkbox("##show", &state);
        ImGui::SameLine();
        ImGui::TextUnformatted(circles_name[circleNumber].c_str());
        checkBoxState_circle[circleNumber] = state;
        if (state) {
            ImGui::Text("Point Count: %zu", c_ptr->GetPointCount());
            ImGui::SameLine();
            ImGui::Text("radius: %.0f", c_ptr->GetRadius());
            ImGui::SameLine();
            if (c_ptr->IsHaveThickness()) {
                ImGui::Text("thick: %.0f", c_ptr->GetThickness());
                ImGui::SameLine();
            }
            ImGui::Text("position: {x: %.1f, y: %.1f}", c_ptr->GetCirclePosition().X, c_ptr->GetCirclePosition().Y);
            const LDDrift::VecCol col = c_ptr->GetPointColor(0);
            ImGui::Text("red: %.3f - green: %.3f - blue: %.3f - alpha: %.3f", col.R, col.G, col.B, col.A);
            ImGui::Separator();
        }
        ImGui::PopID();
    }
    // line objects
    const std::size_t lineCount = lines.size();
    init(checkBoxState_line, lineCount);
    for (std::size_t lineNumber = 0; lineNumber < lineCount; ++lineNumber) {
        ImGui::PushID(static_cast<int>(lineNumber));
        bool state = checkBoxState_line[lineNumber];
        ImGui::Checkbox("##show", &state);
        ImGui::SameLine();
        ImGui::TextUnformatted(lines_name[lineNumber].c_str());
        checkBoxState_line[lineNumber] = state;
        if (state) {
            const LDDrift::Actors::Line* l_ptr = lines[lineNumber];
            ImGui::Text("start pos: {x: %.1f, y: %.1f}", l_ptr->GetFirstPoint().X, l_ptr->GetFirstPoint().Y);
            ImGui::SameLine();
            ImGui::Text("end pod: {x: %.1f, y: %.1f}", l_ptr->GetSecondPoint().X, l_ptr->GetSecondPoint().Y);
            ImGui::SameLine();
            const LDDrift::VecCol col = l_ptr->GetColor();
            ImGui::Text("red: %.3f - green: %.3f - blue: %.3f - alpha: %.3f", col.R, col.G, col.B, col.A);
            ImGui::SameLine();
            ImGui::Text("thick: %.0f", l_ptr->GetThickness());
        }
        ImGui::PopID();
    }

    // polygon objects
    const std::size_t polygonCount = polygons.size();
    init(checkBoxState_polygon, polygonCount);
    for (std::size_t polygonNumber = 0; polygonNumber < polygonCount; ++polygonNumber) {
        ImGui::PushID(static_cast<int>(polygonNumber));
        bool state = checkBoxState_polygon[polygonNumber];
        ImGui::Checkbox("##show", &state);
        ImGui::SameLine();
        ImGui::TextUnformatted(polygons_name[polygonNumber].c_str());
        checkBoxState_polygon[polygonNumber] = state;
        if (state) {
            const LDDrift::Actors::Polygon* p_ptr = polygons[polygonNumber];
            ImGui::Text("point count: %zu", p_ptr->GetPointCount());
            ImGui::SameLine();
            ImGui::Text("speed: %.0f", p_ptr->GetSpeed());
            ImGui::SameLine();
            if (p_ptr->IsHaveThickness()) {
                ImGui::Text("thickness: %.0f", p_ptr->GetThickness());
                ImGui::SameLine();
                ImGui::Text("join line alg: %s",
                            ConvertLineJoiningAlgorithmToString(p_ptr->GetJoinLineAlgorithm().value()));
                const LDDrift::VecCol col = p_ptr->GetPointColor(0);
                ImGui::Text("red: %.3f - green: %.3f - blue: %.3f - alpha: %.3f", col.R, col.G, col.B, col.A);
            } else {
                for (std::size_t pointNumber = 0; pointNumber < p_ptr->GetPointCount(); ++pointNumber) {
                    const LDDrift::VecCol col = p_ptr->GetPointColor(pointNumber);
                    ImGui::Text("point %zu: red: %.3f - green: %.3f - blue: %.3f - alpha: %.3f", pointNumber, col.R,
                                col.G, col.B, col.A);
                }
            }
            for (std::size_t pointNumber = 0; pointNumber < p_ptr->GetPointCount(); ++pointNumber) {
                ImGui::Text("point %zu: {x: %0.0f, y: %0.0f}", pointNumber, p_ptr->GetGlobalPoint(pointNumber).X,
                            p_ptr->GetGlobalPoint(pointNumber).Y);
                if (pointNumber % 3 != 0) ImGui::SameLine();
            }
        }
        ImGui::PopID();
    }
}

LDDrift::GUI::~GUI() {
    if (reloadCmakeFileThread.joinable()) {
        reloadCmakeFileThread.join();
    }
}
