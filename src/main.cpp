#include <iostream>

#include "raylib.h"
#define IMGUI_DEFINE_MATH_OPERATORS 1
#include "imgui_internal.h"
#include "imgui.h"
#include "rlImGui/rlImGui.h"
#include "ImGuiFD.h"
#include "oneHeaderLibs/VectorOperators.h"

void setup();
void draw();
void destroy();

int frameCnt = 0;

Vector2 lastMousePos;
Vector2 mouseDelta;


void setup() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(1200, 800, "ABemu");

    SetWindowResizeDrawCallback(draw);
    SetTargetFPS(60);

    lastMousePos = GetMousePosition();
    mouseDelta = { 0,0 };

    //SetupRLImGui(true);
	InitRLGLImGui();
	AddRLImGuiIconFonts();
	FinishRLGLImguSetup();
	
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigWindowsResizeFromEdges = true;
    io.WantSaveIniSettings = false;
    io.ConfigWindowsMoveFromTitleBarOnly = true;
}
void draw() {
    BeginDrawing();

    mouseDelta = GetMousePosition() - lastMousePos;

    ClearBackground(DARKGRAY);

    BeginRLImGui();

    ImGui::ShowDemoWindow(NULL);

    

	if (ImGui::Begin("Hello World")) {
		ImGui::TextUnformatted("Hi! :)");
        if (ImGui::Button("Open Dialog")) {
            ImGuiFD::OpenDirDialog("Choose Dir", GetWorkingDirectory());
        }
	}
	ImGui::End();
	

	if (ImGuiFD::BeginDialog("Choose Dir")) {
        if (ImGuiFD::ActionDone()) {
            if (ImGuiFD::SelectionMade()) {
                printf("Selected path: %s\n", ImGuiFD::GetSelectionPathString(0));
            }
            ImGuiFD::CloseCurrentDialog();
        }

        ImGuiFD::EndDialog();
    }

    EndRLImGui();

    lastMousePos = GetMousePosition();

    DrawFPS(0,0);

    EndDrawing();

    frameCnt++;
}
void destroy() {
    ShutdownRLImGui();
    CloseWindow();
}


int main(void) {
    setup();

    while (!WindowShouldClose()) {
        draw();
    }

    destroy();

    return 0;
}