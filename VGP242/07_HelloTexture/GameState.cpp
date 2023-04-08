#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace DubEngine::DEMath;

void GameState::Initialize()
{
	// NDC - Normalized Device Coordinate
	//
	//          +-----------------+
	//         /                 /|
	//   1.0  +-----------------+ |
	//	      |        ^        | |
	//	      |        |        | |
	//	      | <------+------> | |
	//	      |        |        | | 1.0
	//	      |        v        |/
	//	-1.0  +-----------------+ 0.0
	//      -1.0               1.0
	//

	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mSphere = MeshBuilder::CreateSpherePX(60, 60, 1);

	mConstantBuffer.Initialize(sizeof(Matrix4));
	mMeshBuffer.Initialize(mSphere);
	mEarthTextureId = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");
	mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VE_Position | VE_TexCoord);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");
}
void GameState::Terminate()
{
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
}

float rotationX = 0.0f;
float rotationY = 0.0f;
void GameState::Update(float deltaTime)
{
	if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::UP))
	{
		rotationY += Constants::HalfPi * deltaTime;
	}
	else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::DOWN))
	{
		rotationY -= Constants::HalfPi * deltaTime;
	}
	if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::RIGHT))
	{
		rotationX += Constants::HalfPi * deltaTime;
	}
	else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::LEFT))
	{
		rotationX -= Constants::HalfPi * deltaTime;
	}
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	Matrix4 cubeWorldRotY = Matrix4::RotationY(rotationX);
	Matrix4 cubeWorldRotX = Matrix4::RotationX(rotationY);
	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(cubeWorldRotX * cubeWorldRotY * view * proj);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);
	TextureManager::Get()->BindPS(mEarthTextureId, 0);

	mMeshBuffer.Render();
}

void GameState::DebugUI()
{

}