#include "FurShader.h"
#include "Graphics/Inc/Colors.h"

void FurShaderEffect::Initialize()
{
	mGravity = { -1.0f, 0.0f, 0.0f };
	mForces = { 0.0f, 0.0f, 0.0f };
	mBlend = 0.0f;
	mMaxLayers = 0.0f;
	mMaxLayers = 0;
	mDensity = 0.0f;

	std::filesystem::path shaderFile = L"../../Assets/Shaders/FurShader.fx";
	mVertexShader.Initialize<Vertex>(shaderFile);
	mPixelShader.Initialize(shaderFile);
	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mFurBuffer.Initialize();
	mBlendState.Initialize(BlendState::Mode::AlphaBlend);

	Model character;
	ModelIO::LoadModel("../../Assets/Models/mutant/Mutant.model", character);
	mFurRenderObject.meshBuffer.Initialize(character.meshData[0].mesh);

	mDiffuseTexture = TextureManager::Get()->LoadTexture(L"Models/mutant/Mutant_diffuse_0.png");
	mFurTexture = TextureManager::Get()->LoadTexture(L"Models/mutant/Mutant_fur_0.png");

	const Texture* furTexture = TextureManager::Get()->GetTexture(mFurTexture);
	ID3D11ShaderResourceView* textureData = (ID3D11ShaderResourceView*)furTexture->GetRawData();
	ID3D11Resource* textureRes = nullptr;
	textureData->GetResource(&textureRes);
	ID3D11Texture2D* pTextureInterface = nullptr;
	textureRes->QueryInterface<ID3D11Texture2D>(&pTextureInterface);
	D3D11_TEXTURE2D_DESC desc;
	pTextureInterface->GetDesc(&desc);

	mFurData.width = static_cast<int>(desc.Width);
	mFurData.height = static_cast<int>(desc.Height);
}
void FurShaderEffect::Terminate()
{
	mBlendState.Terminate();
	mFurBuffer.Terminate();
	mLightBuffer.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mTransformBuffer.Terminate();
	mFurRenderObject.Terminate();
}
void FurShaderEffect::Render(const Camera& camera)
{
	const auto& matWorld = mFurRenderObject.transform.GetMatrix4();
	const auto& matView = camera.GetViewMatrix();
	const auto& matProj = camera.GetProjectionMatrix();

	TransformData transformData;
	transformData.world = Transpose(matWorld);
	transformData.vp = Transpose(matView * matProj);
	transformData.maxLength = mMaxLength;
	transformData.viewPosition = camera.GetPosition();
	transformData.forces = mGravity + mForces;

	auto tm = TextureManager::Get();

	float maxLayers = static_cast<float>(mMaxLayers);
	for (int i = 0; i < mMaxLayers; ++i)
	{
		mVertexShader.Bind();
		mPixelShader.Bind();
		mBlendState.Set();
		mTransformBuffer.BindVS(0);
		mTransformBuffer.BindPS(0);
		mLightBuffer.BindVS(1);
		mLightBuffer.BindPS(1);
		mFurBuffer.BindPS(2);

		tm->BindPS(mDiffuseTexture, 0);
		tm->BindPS(mFurTexture, 1);

		mLightBuffer.Update(*mDirectionalLight);
		mFurBuffer.Update(mFurData);
		transformData.currentLayer = static_cast<float>(i) / maxLayers;
		mTransformBuffer.Update(transformData);

		mFurRenderObject.meshBuffer.Render();
		Texture::UnbindPS(0);
		Texture::UnbindPS(1);
		mBlendState.ClearState();
	}

}
void FurShaderEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}
void FurShaderEffect::UpdateFurTexture(float density, float maxLength, int maxLayers)
{
	if (density != mDensity || mMaxLength != maxLength || mMaxLayers != maxLayers)
	{
		mDensity = density;
		mMaxLength = maxLength;
		mMaxLayers = maxLayers;

		//create number of strands and max strands per layer
		int width = (int)mFurData.width;
		int height = (int)mFurData.height;
		int size = width * height;

		int numstrands = std::min(static_cast<int>(density * size), 64);
		int maxstrperlay = numstrands / mMaxLayers;

		Color color = Colors::Black;
		for (int i = 0; i < numstrands; ++i)
		{
			int x = rand() % width;
			int y = rand() % height;

			int maxlayer = i / maxstrperlay;
			float maxlayern = (static_cast<float>(maxlayer) / static_cast<float>(mMaxLayers));
			maxlayern = sqrt(maxlayern);

			int index = (x + (y * width)) % 64;
			mFurData.furLength[index] = maxlayern;
		}
	}
}
void FurShaderEffect::Update(float deltaTime)
{
	mBlend += deltaTime;
	mForces.y = std::sin(mBlend) * 0.5f;
}
void FurShaderEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("FurShaderEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Gravity", &mGravity.y, 0.5f, -20.0f, 20.0f);
		float density = mDensity;
		ImGui::DragFloat("Density", &density, 0.01f, 0.0f, 1.0f);
		float maxLength = mMaxLength;
		ImGui::DragFloat("MaxLength", &maxLength, 0.5f, 0.0f, 20.0f);
		int maxLayers = mMaxLayers;
		ImGui::DragInt("Layers", &maxLayers, 1, 0, 50);

		UpdateFurTexture(density, maxLength, maxLayers);
	}
}