#include "Precompiled.h"
#include "SimpleTexture.h"

#include "GraphicsSystem.h"

using namespace DubEngine;
using namespace DubEngine::Graphics;

SimpleTexture::~SimpleTexture()
{
}

void SimpleTexture::Initialize(const std::filesystem::path& fileName)
{
    ASSERT(false, "SimpleTexture -- cannot initialize render from file");
}
void SimpleTexture::Initialize(uint32_t width, uint32_t height, Format format)
{
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = GetDXGIFormat(format);
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    auto device = GraphicsSystem::Get()->GetDevice();
    ID3D11Texture2D* texture = nullptr;
    HRESULT hr = device->CreateTexture2D(&desc, nullptr, &texture);
    ASSERT(SUCCEEDED(hr), "RenderTarget -- failed to create render texture");

    hr = device->CreateShaderResourceView(texture, nullptr, &mShaderResourceView);
    ASSERT(SUCCEEDED(hr), "RenderTarget -- failed to create shader resource view");

    int pixCount = desc.Width * desc.Height;
    mPixelColors = std::make_unique<Color[]>(pixCount);
    for (int i = 0; i < pixCount; ++i)
    {
        mPixelColors[i] = Colors::Black;
    }
}
void SimpleTexture::SetPixelColor(int x, int y, const Color& color)
{
    int index = x + (y * mWidth);
    mPixelColors[index] = color;
}

const Color& SimpleTexture::GetPixelColor(int x, int y) const
{
    int index = x + (y * mWidth);
    return mPixelColors[index];
}
void SimpleTexture::ApplyColors()
{

}