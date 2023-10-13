#include "include/imgui/imgui.h"
#include "draw.h"

void AddRect(const ImVec2& position, const ImVec2& size, const ImColor& color, float rounding)
{
    ImGui::GetBackgroundDrawList()->AddRect(position, size, ImGui::ColorConvertFloat4ToU32(color), rounding);
}

void AddRectFilled(const ImVec2& position, const ImVec2& size, const ImColor& color, float rounding)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(position, size, ImGui::ColorConvertFloat4ToU32(color), rounding);
}
void DrawBox(float x, float y, float w, float h, const ImColor& color)
{
    AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 5.f);
}

void DrawBoxFilled(float x, float y, float w, float h, const ImColor& color)
{
    AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.f);
}