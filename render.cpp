#include "render.hpp"

#include <mutex>

//#include "features/visuals.hpp"
#include "valve_sdk/csgostructs.hpp"
#include "Helpers/input.hpp"
#include "menu.hpp"
//#include "options.hpp"
//#include "fonts/fonts.hpp"
//#include "Helpers/math.hpp"

ImFont* g_pDefaultFont;
ImFont* g_pSecondFont;

ImDrawListSharedData _data;

std::mutex render_mutex;

void Render::Initialize()
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(InputSys::Get().GetMainWindow());
	ImGui_ImplDX9_Init(g_D3DDevice9);

	draw_list = new ImDrawList(ImGui::GetDrawListSharedData());
	draw_list_act = new ImDrawList(ImGui::GetDrawListSharedData());
	draw_list_rendering = new ImDrawList(ImGui::GetDrawListSharedData());

	//GetFonts();
}

/*void Render::GetFonts() {

	// menu font
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Droid_compressed_data,
		Fonts::Droid_compressed_size,
		14.f);

	// esp font
	g_pDefaultFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Droid_compressed_data,
		Fonts::Droid_compressed_size,
		18.f);


	// font for watermark; just example
	g_pSecondFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Cousine_compressed_data,
		Fonts::Cousine_compressed_size,
		18.f);
}*/

void Render::ClearDrawList() {
	render_mutex.lock();
	draw_list_act->Clear();
	render_mutex.unlock();
}

void Render::BeginScene() {
	draw_list->Clear();
	draw_list->PushClipRectFullScreen();

	//if (g_Options.misc_watermark)
	//	Render::Get().RenderText("movrax CSGO", 10, 5, 18.f, g_Options.color_watermark, false, true, g_pSecondFont);

	//if (g_EngineClient->IsInGame() && g_LocalPlayer && g_Options.esp_enabled)
	//	Visuals::Get().AddToDrawList();

	render_mutex.lock();
	*draw_list_act = *draw_list;
	render_mutex.unlock();
}

