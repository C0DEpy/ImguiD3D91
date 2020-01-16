#include "stdafx.h"
#include "dx/dx9.h"
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_dx9.h"
#include "imgui/examples/imgui_impl_win32.h"
#include <stdio.h>
#include <time.h>


WNDPROC p_window_proc = nullptr;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wnd_proc(const HWND hwnd, const UINT u_msg, const WPARAM w_param, const LPARAM l_param)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, u_msg, w_param, l_param) && GetAsyncKeyState(VK_INSERT) & 1)
	{
		return 1l;
	}
	return CallWindowProc(p_window_proc, hwnd, u_msg, w_param, l_param);
}

bool do_ini = true;


bool show_demo_window = false;
bool Menu = true;
bool Outros = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
void __stdcall main_render(IDirect3DDevice9* p_device)
{
	//printf("zz\n");
	if (do_ini)
	{
		const auto window = GetForegroundWindow();
		DWORD pid;
		if (!window || !GetWindowThreadProcessId(window, &pid) || pid != GetCurrentProcessId())
			return;	
		do_ini = false;
		p_window_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, LONG_PTR(wnd_proc)));
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX9_Init(p_device);
		ImGui::StyleColorsDark();
	}
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);



	if (GetAsyncKeyState(VK_RSHIFT) & 1) Menu = !Menu;

	ImGuiIO & io = ImGui::GetIO();
	(void)io;
	io.IniFilename = NULL;

	if (GetAsyncKeyState(VK_DELETE) & 1) Menu = !Menu;

	static int e = 0;
	static int d = 0;
	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	if (Menu)
	{
		struct tm *data_hora_atual;
		time_t segundos;
		time(&segundos);
		data_hora_atual = localtime(&segundos);
		ImGui::SetNextWindowSize(ImVec2(227, 566));
		ImGui::StyleColorsClassic();
		ImGui::Begin("Cheat Legit Mafiagames.net", NULL, ImGuiWindowFlags_NoResize);
		if (ImGui::CollapsingHeader("Visual"))
		{
			ImGui::Checkbox("Esqueleto", &Menu);
			ImGui::Checkbox("Nome", &Menu);
			ImGui::Checkbox("Vida", &Menu);
			ImGui::Checkbox("Box", &Menu);
			ImGui::Checkbox("Distancia", &Menu);
		}
		if (ImGui::CollapsingHeader("Aimbot")) {
			ImGui::Text("Key");

			ImGui::RadioButton("SHIFT", &e, 0); ImGui::SameLine();
			ImGui::RadioButton("CTRL", &e, 1); ImGui::SameLine();
			ImGui::RadioButton("ALT", &e, 2);
			ImGui::Checkbox("Outros", &Outros);

			ImGui::Text("Local");

			ImGui::RadioButton("Cabeca", &d, 0); ImGui::SameLine();
			ImGui::RadioButton("Pescoco", &d, 1); ImGui::SameLine();
			ImGui::RadioButton("Peito", &d, 2);

			ImGui::Checkbox("Visivel", &Menu);
			ImGui::Checkbox("Modo", &Menu);
			ImGui::Checkbox("Atirar Auto", &Menu);
		}
		if (ImGui::CollapsingHeader("Misc")) {
			ImGui::Checkbox("Crosshair", &Menu);
			ImGui::Checkbox("Fly", &Menu);
			ImGui::Checkbox("Bag Hack", &Menu);
			ImGui::Checkbox("Spam Radio", &Menu);
			ImGui::Checkbox("Spam Spray", &Menu);
			ImGui::Checkbox("No Recoil", &Menu);
			ImGui::Checkbox("No Spread", &Menu);
		}

		ImGui::Text("FPS:%.1f Horas:%d:%d:%d", ImGui::GetIO().Framerate, data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec);
		ImGui::End();
	}

	if (Outros) {
		ImGui::SetNextWindowSize(ImVec2(91, 134));
		ImGui::Begin("Outros", NULL, ImGuiWindowFlags_NoResize);
		ImGui::Text("Outras Keys !");
		ImGui::RadioButton("LCLICK", &e, 3);
		ImGui::RadioButton("RCLICK", &e, 4);
		ImGui::Text("");
		if (ImGui::Button("Fechar"))
			Outros = false;
		ImGui::End();
	}
	// Rendering
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

auto gaks	= reinterpret_cast<void*>(&GetAsyncKeyState);
auto gks	= reinterpret_cast<void*>(&GetKeyState);
void xigncode3_un_hook()
{
	DWORD old;
	const size_t alloc_size = 100;
	const auto alloc_gaks	= malloc(alloc_size);
	const auto alloc_gks	= malloc(alloc_size);
	if (!alloc_gaks || !alloc_gks)
		return;

	memcpy(alloc_gaks,	gaks,	alloc_size);
	memcpy(alloc_gks,	gks,	alloc_size);
	VirtualProtect(gaks,	alloc_size, PAGE_EXECUTE_READWRITE, &old);
	VirtualProtect(gks,		alloc_size, PAGE_EXECUTE_READWRITE, &old);
	while (true)
	{
		if (memcmp(gaks, alloc_gaks, alloc_size) != 0 && memcmp(gks, alloc_gks, alloc_size) != 0)
		{
			memcpy(gaks,	alloc_gaks, alloc_size);
			memcpy(gks,		alloc_gks,	alloc_size);
			break;
		}
		Sleep(100);
	}
	free(alloc_gaks);
	free(alloc_gks);
}

void do_thread()
{
	printf("ini\n");
	dx9::set_frame_render(reinterpret_cast<void*>( main_render ));
	xigncode3_un_hook();
}

void open_console(const std::string title)
{
	AllocConsole();
	FILE* street;
	freopen_s(&street, "CONIN$", "r", stdin);
	freopen_s(&street, "CONOUT$", "w", stdout);
	freopen_s(&street, "CONOUT$", "w", stderr);
	SetConsoleTitle(title.c_str());
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		//open_console("");
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(do_thread), nullptr, 0, nullptr);
	}
	return TRUE;
}
