#pragma once
#include "include/imgui/imgui.h"

void AddRect(const ImVec2& position, const ImVec2& size, const ImColor& color, float rounding);
void DrawBox(float x, float y, float w, float h, const ImColor& color);
void AddRectFilled(const ImVec2& position, const ImVec2& size, const ImColor& color, float rounding);
void DrawBoxFilled(float x, float y, float w, float h, const ImColor& color);