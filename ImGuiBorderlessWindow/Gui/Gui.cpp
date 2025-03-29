// Copyright (C) 2023 Avnish Kirnalli.

#include "Font.h"
#include "Gui.h"

#include "imgui.h"
#include "Platform/Platform.h"

void Gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	Platform::Get()->InitImguiImpl();
	ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = static_cast<float>(Gui::WIDTH);
    io.DisplaySize.y = static_cast<float>(Gui::HEIGHT);

	io.IniFilename = NULL;

	ImGui::StyleColorsDark();
}

void Gui::DestroyImGui() noexcept
{
	Platform::Get()->ShutdownImguiImpl();
	ImGui::DestroyContext();
}

void Gui::BeginRender() noexcept
{
	// Start the Dear ImGui frame
	ImGui::NewFrame();
}

void Gui::EndRender() noexcept
{
	ImGui::EndFrame();
}

void Gui::BeginImGuiRender() noexcept
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)));
	ImGui::Begin(
		Gui::windowName,
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove
	);
}

void Gui::EndImGuiRender() noexcept
{
	ImGui::End();
}

void Gui::PushFont(const GuiFont& inFont) noexcept
{
	if (inFont.GetImGuiFont() && inFont.GetImGuiFont()->IsLoaded())
		ImGui::PushFont(inFont.GetImGuiFont());
}

void Gui::PopFont()
{
	ImGui::PopFont();
}
