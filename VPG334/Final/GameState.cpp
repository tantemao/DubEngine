#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace DubEngine::DEMath;
using namespace DubEngine::Input;
using namespace DubEngine::Graphics;
bool mIsRollingForward = false;
bool mIsRollingBack = false;
bool mIsRollingLeft = false;
bool mIsRollingRight = false;
void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -10.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	
	mDirectionalLight.direction = DEMath::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };
	//ball
	Mesh ball = MeshBuilder::CreateSphere(30, 30, 1.0f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/basketball.jpg");
	mBall.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mBall.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mBall.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mBall.material.power = 10.0f;
	mBall.transform.position.y = 10.0f;
	mSphereCollisionShape.Initialize(1.0f);
	mBallRigidBody.Initialize(mBall.transform, mSphereCollisionShape,5.0f);
	//ground
	Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/concrete.jpg");
	mGround.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGround.material.power = 10.0f;
	mGroundCollisionShape.Initialize({10.0f,0.005f,10.0f});
	mGroundRigidBody.Initialize(mGround.transform, mGroundCollisionShape);




	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
}
void GameState::Terminate()
{
	mBallRigidBody.Terminate();
	mSphereCollisionShape.Terminate();
	mStandardEffect.Terminate();
	mBall.Terminate();
	mGround.Terminate();
	

}
int gAnimationIndex = 0;
void GameState::Update(float deltaTime)
{
	// movement
	auto input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;
	const float ballTurnSpeed = 1.0f;
	btRigidBody* ballBody = mBallRigidBody.GetRigidBody();


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


	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::P))
	{
		// Reset ball's position
		mBall.transform.position = { 0.0f, 10.0f, 0.0f };

		// Reset ball's velocity
		if (ballBody)
		{
			ballBody->setLinearVelocity(btVector3(0, 0, 0));
			ballBody->setAngularVelocity(btVector3(0, 0, 0));

			// Set transform
			btTransform newTransform;
			newTransform.setIdentity();
			newTransform.setOrigin(btVector3(mBall.transform.position.x, mBall.transform.position.y, mBall.transform.position.z));
			ballBody->setWorldTransform(newTransform);
		}
	}


	if (input->IsKeyDown(KeyCode::SPACE))
	{

		if (ballBody)
		{
			btVector3 impulse(0.0f, 2.0f, 0.0f);
			ballBody->applyCentralImpulse(impulse);
		}
	}
	if (input->IsKeyDown(KeyCode::J))
	{
		mIsRollingLeft = true;
		mIsRollingRight = false;
		if (ballBody)
		{
			btVector3 impulse(-2.0f, 0.0f, 0.0f);
			ballBody->applyCentralImpulse(impulse);
		}
	}
	else if (input->IsKeyDown(KeyCode::L))
	{
		mIsRollingRight = true;
		mIsRollingLeft = false;
		if (ballBody)
		{
			btVector3 impulse(2.0f, 0.0f, 0.0f);
			ballBody->applyCentralImpulse(impulse);
		}
	}
	if (input->IsKeyDown(KeyCode::I))
	{
		mIsRollingForward = true;
		mIsRollingBack = false;
		if (ballBody)
		{
			btVector3 impulse(0.0f, 0.0f, 2.0f);
			ballBody->applyCentralImpulse(impulse);
		}
	}
	else if (input->IsKeyDown(KeyCode::K))
	{
		mIsRollingBack = true;
		mIsRollingForward = false;
		if (ballBody)
		{
			btVector3 impulse(0.0f, 0.0f, -2.0f);
			ballBody->applyCentralImpulse(impulse);
		}
	}

	

	
	if (ballBody)
	{
		// Check the linear velocity magnitude
		float velocityMagnitude = ballBody->getLinearVelocity().length();
		const float velocityThreshold = 0.1f;

		if (velocityMagnitude < velocityThreshold)
		{
			// Reset the pitch and roll
			mPitch = 0.0f;
			mRoll = 0.0f;
		}
		else
		{
			// Apply pitch and roll based on the rolling direction
			if (mIsRollingLeft)
			{
				mRoll += ballTurnSpeed * deltaTime;
			}
			if (mIsRollingRight)
			{
				mRoll -= ballTurnSpeed * deltaTime;
			}

			if (mIsRollingForward)
			{
				mPitch += ballTurnSpeed * deltaTime;
			}
			if (mIsRollingBack)
			{
				mPitch -= ballTurnSpeed * deltaTime;
			}
		}

		// Update the ball's rotation
		mBall.transform.rotation = Quaternion::CreateFromYawPitchRoll(mYaw, mPitch, mRoll);

		// Update the rotation of the ball's rigid body
		auto quaternion = mBall.transform.rotation;
		btQuaternion btQuat(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
		btTransform trans = ballBody->getWorldTransform();
		trans.setRotation(btQuat);
		ballBody->setWorldTransform(trans);
	}


	
}

void GameState::Render()
{


	mStandardEffect.Begin();
		mStandardEffect.Render(mBall);
		mStandardEffect.Render(mGround);

	mStandardEffect.End();



	SimpleDraw::AddGroundPlane(20.0f, Colors::PaleVioletRed);
	SimpleDraw::Render(mCamera);
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


	mStandardEffect.DebugUI();

	PhysicsWorld::Get()->DebugUI();
	ImGui::End();
	SimpleDraw::Render(mCamera);
}