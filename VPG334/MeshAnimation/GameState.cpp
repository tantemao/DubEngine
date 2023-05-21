#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace DubEngine::DEMath;
using namespace DubEngine::Input;
using namespace DubEngine::Graphics;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	
	mDirectionalLight.direction = DEMath::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");
	mGround.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGround.material.power = 10.0f;

	auto mm = ModelManager::Get();
	mCharacterModelId = mm->LoadModel(L"../../Assets/Models/Jones/character.model");
	mm->AddAnimation(mCharacterModelId, L"../../Assets/Models/Jones/animations/Dancing.animset");
	mm->AddAnimation(mCharacterModelId, L"../../Assets/Models/Jones/animations/Dancing2.animset");


	//mCharacterModelId = ModelManager::Get()->LoadModel("../../Assets/Models/Jones/Dancing.model");
	mCharacterAnimator.Initialize(mCharacterModelId);
	mCharacter = CreateRenderGroup(mCharacterModelId,&mCharacterAnimator);
	mCharacterAnimator.PlayAnimation(0, true);

	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
}
void GameState::Terminate()
{
	CleanupRenderGroup(mCharacter);

	mStandardEffect.Terminate();
	mGround.Terminate();
	

}
int gAnimationIndex = 0;
void GameState::Update(float deltaTime)
{
	mCharacterAnimator.Update(deltaTime);
	// movement
	auto input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input -> IsKeyPressed(KeyCode::UP))
	{
		int animCount=mCharacterAnimator.GetAnimationCount();
		gAnimationIndex = (gAnimationIndex + 1) % animCount;
		mCharacterAnimator.PlayAnimation(gAnimationIndex, true,2.0f);
	}
	if (input->IsKeyPressed(KeyCode::DOWN))
	{
		int animCount = mCharacterAnimator.GetAnimationCount();
		gAnimationIndex = (gAnimationIndex - 1);
		if (gAnimationIndex < 0)
		{
			gAnimationIndex = animCount - 1;
		}
		mCharacterAnimator.PlayAnimation(gAnimationIndex, true);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	
	
}

void GameState::Render()
{


	mStandardEffect.Begin();
		mStandardEffect.Render(mGround);
		
		if (mDrawSkeleton)
		{
			AnimationUtil::Bonetransforms boneTransforms;
			AnimationUtil::ComputeBoneTransform(mCharacterModelId, boneTransforms,&mCharacterAnimator);
			AnimationUtil::DrawSkeleton(mCharacterModelId, boneTransforms);

			SimpleDraw::Render(mCamera);
		}
		else
		{
			DrawRenderGroup(mStandardEffect, mCharacter);
		}
		
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	ImGui::Checkbox("Draw##Skeleton", &mDrawSkeleton);

	mStandardEffect.DebugUI();


	ImGui::End();
}