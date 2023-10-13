#include <Windows.h>
#include "include/imgui_hook.h"
#include "include/imgui/imgui.h"
#include "vec.h"
#include "offsetse.h"
#include "draw.h"
bool esp = false;
bool teamesp = false;
float matrix[16];
bool show = true;
uintptr_t modulebase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

bool sped = false;
bool godmode = false; 
bool unliammo = false;
bool oneshot = false;

uintptr_t localplayer = *(uintptr_t*)(modulebase + localpl);



bool WorldToScreen(vec3 pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight) // public directx w2s
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.z * matrix[4] + pos.y * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.z * matrix[5] + pos.y * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.z * matrix[6] + pos.y * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.z * matrix[7] + pos.y * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}


void RenderMain() 
{
	int line = 1;
	
	ImGui::Begin("Assault Cube Internal");
	ImGui::Text("God knows how many times i attempted to create this");
	ImGui::Text("created by flod");
	if (esp)
	{
		
		ImGui::Checkbox("Team ESP", &teamesp);
			
			int* Players = (int*)(modulebase + CurrPlayers);

			vec2 vHead;
			vec2 vScreen;

			int screenY = GetSystemMetrics(SM_CYSCREEN);
			int screenX = GetSystemMetrics(SM_CXSCREEN);
			uintptr_t ent = *(uintptr_t*)(modulebase + EntityList);

			for (int i = 1; i < *Players; ++i)
			{
				int* screenX = (int*)(modulebase + 0x191ED8);
				int* screenY = (int*)(modulebase + 0x191EDC);
				uintptr_t entlist = *(uintptr_t*)(ent + (i * 0x4));

				float entPosX = *(float*)(entlist + feetposX);
				float entPosY = *(float*)(entlist + feetposY);
				float entPosZ = *(float*)(entlist + feetposZ);

				float entHeadPosX = *(float*)(entlist + headposX);
				float entHeadPosY = *(float*)(entlist + headposY);
				float entHeadPosZ = *(float*)(entlist + headposZ);


				vec3 pos = { entPosX, entPosY, entPosZ };
				vec3 Headpos = { entHeadPosX, entHeadPosY, entHeadPosZ };

				memcpy(&matrix, (PBYTE*)viewMatrix, sizeof(matrix));

				
				int* localHealth = (int*)(localplayer + hp);
				int* entHealth = (int*)(entlist + hp);
				int localteam = *(int*)(localplayer + 0x30C);
				int teamnum = *(int*)(entlist + 0x30C);
				 
				ImColor team = ImColor(0, 0, 255, 95);
				ImColor opps = ImColor(255, 0, 0, 60);

				if (*entHealth <= 0 || *localHealth <= 0)
				{
					continue;
				}

				if (teamnum == localteam)
					continue;


				if (WorldToScreen(pos, vScreen, matrix, *screenX, *screenY))
				{
					if (WorldToScreen(Headpos, vHead, matrix, *screenX, *screenY))
					{			

						
							ImGui::GetOverlayDrawList()->AddLine(ImVec2(*screenX / 2, *screenY / line), ImVec2(vScreen.x, vHead.y - 15.f), ImColor(255, 0, 0));
							DrawBoxFilled(vScreen.x - (((vScreen.y - vHead.y) * 0.5) / 2),
								vHead.y - 15.f,
								(vScreen.y - vHead.y) * 0.5f,
								vScreen.y - vHead.y + 10.f, opps);

						
														
					}
				}


			}
	}
	if (teamesp)
	{
		int* Players = (int*)(modulebase + CurrPlayers);

		vec2 vHead;
		vec2 vScreen;

		int screenY = GetSystemMetrics(SM_CYSCREEN);
		int screenX = GetSystemMetrics(SM_CXSCREEN);
		uintptr_t ent = *(uintptr_t*)(modulebase + EntityList);

		for (int i = 1; i < *Players; ++i)
		{
			int* screenX = (int*)(modulebase + 0x191ED8);
			int* screenY = (int*)(modulebase + 0x191EDC);
			uintptr_t entlist = *(uintptr_t*)(ent + (i * 0x4));

			float entPosX = *(float*)(entlist + feetposX);
			float entPosY = *(float*)(entlist + feetposY);
			float entPosZ = *(float*)(entlist + feetposZ);

			float entHeadPosX = *(float*)(entlist + headposX);
			float entHeadPosY = *(float*)(entlist + headposY);
			float entHeadPosZ = *(float*)(entlist + headposZ);


			vec3 pos = { entPosX, entPosY, entPosZ };
			vec3 Headpos = { entHeadPosX, entHeadPosY, entHeadPosZ };

			memcpy(&matrix, (PBYTE*)viewMatrix, sizeof(matrix));


			int* localHealth = (int*)(localplayer + hp);
			int* entHealth = (int*)(entlist + hp);
			int localteam = *(int*)(localplayer + 0x30C);
			int teamnum = *(int*)(entlist + 0x30C);

			ImColor team = ImColor(0, 255, 0, 95);
			ImColor opps = ImColor(255, 0, 0, 60);

			if (*entHealth <= 0 || *localHealth <= 0)
			{
				continue;
			}

			if (teamnum != localteam)
				continue;


			if (WorldToScreen(pos, vScreen, matrix, *screenX, *screenY))
			{
				if (WorldToScreen(Headpos, vHead, matrix, *screenX, *screenY))
				{


					ImGui::GetOverlayDrawList()->AddLine(ImVec2(*screenX / 2, *screenY / line), ImVec2(vScreen.x, vHead.y - 15.f), team);
					DrawBoxFilled(vScreen.x - (((vScreen.y - vHead.y) * 0.5) / 2),
						vHead.y - 15.f,
						(vScreen.y - vHead.y) * 0.5f,
						vScreen.y - vHead.y + 10.f, team);



				}
			}


		}
	}
	if (godmode)
	{
		*(int*)(localplayer + hp) = 1337;
	}
	if (unliammo)
	{
		int* pAmmo = (int*)(localplayer + ammo);
		*pAmmo = 1337;
	}

	if (oneshot)
	{
		uintptr_t ent = *(uintptr_t*)(modulebase + EntityList);
		int* Players = (int*)(modulebase + CurrPlayers);
		for (int i = 1; i < *Players; ++i)
		{
			uintptr_t entlist = *(uintptr_t*)(ent + (i * 0x4));
			int* localteam = (int*)(localplayer + 0x30C);
			int* teamnum = (int*)(entlist + 0x30C);

			int* entHealth = (int*)(entlist + hp);
												
			if (teamnum == localteam)
			{
				break;
			}
			else
			{
				*entHealth = 1;

			}
																
		}


	}
	if (sped)
	{
		int* pSpeed = (int*)(localplayer + speed);
		if (*pSpeed == 1)
		{
			*pSpeed = 3;
		}

		
	}
	ImGui::Checkbox("ESP", &esp);
	ImGui::Checkbox("Speed", &sped);
	ImGui::Checkbox("God Mode", &godmode);
	ImGui::Checkbox("Unlimited Ammo", &unliammo);
	ImGui::Checkbox("Oneshot", &oneshot);

	ImGui::End();
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		ImGuiHook::Load(RenderMain);
		break;
	case DLL_PROCESS_DETACH:
		ImGuiHook::Unload();
		break;
	}
	return TRUE;
}