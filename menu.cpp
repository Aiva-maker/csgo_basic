#include "menu.hpp"

#include <Windows.h>
#include <chrono>

#include "valve_sdk/csgostructs.hpp"
#include "helper/input.hpp"
//#include "options.hpp"
//#include "ui.hpp"
//#include "config.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "imgui/impl/imgui_impl_win32.h"



void Menu::Initialize()
{
	CreateStyle();

	_visible = true;
}

void Menu::Shutdown()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Menu::OnDeviceReset()
{
	ImGui_ImplDX9_CreateDeviceObjects();
}

void Menu::OnDeviceLost()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}

void Menu::Render()
{
	ImGui::GetIO().MouseDrawCursor = _visible;

	if (!_visible)
		return;

	//const auto sidebar_size = get_sidebar_size();
	//static int active_sidebar_tab = 0;

	ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2{ 1000, 400 }, ImGuiSetCond_Once);

	if (ImGui::Begin("movrax CSGO",
		&_visible,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoTitleBar)) {

		
		ImGui::End();
	}
}

void Menu::Toggle()
{
	_visible = !_visible;
}

void Menu::CreateStyle()
{
	ImGui::StyleColorsDark();
}