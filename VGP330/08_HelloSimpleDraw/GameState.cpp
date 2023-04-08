#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace DubEngine::DEMath;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}
void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
}

void GameState::Render()
{
    if (mIsLine)
    {
        SimpleDraw::AddLine(mLinePos1, mLinePos2, mLineColor);
    }
    else
    {
        SimpleDraw::AddSphere(mSlices, mRings, mCircleRadius, mCircleColor);
    }

    SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug Draw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Checkbox("IsLine", &mIsLine);
    if (mIsLine)
    {
        ImGui::Begin("Line Data", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::DragFloat3("Pos1", &mLinePos1.x, 0.01f);
        ImGui::DragFloat3("Pos2", &mLinePos2.x, 0.01f);
        ImGui::ColorEdit4("Color", &mLineColor.r);
        ImGui::End();
    }
    else
    {
        ImGui::Begin("Sphere Data", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::DragInt("Slices", &mSlices, 0.01f);
        ImGui::DragInt("Rings", &mRings, 0.01f);
        ImGui::DragFloat("Radius", &mCircleRadius, 0.01f);
        ImGui::ColorEdit4("Color", &mCircleColor.r);
        ImGui::End();
    }
    ImGui::End();
}