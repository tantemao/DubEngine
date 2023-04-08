#pragma once

#include "Colors.h"
#include "Texture.h"

namespace DubEngine::Graphics
{
    class SimpleTexture final : public Texture
    {
    public:
        SimpleTexture() = default;
        ~SimpleTexture() override;

        void Initialize(const std::filesystem::path& fileName) override;
        void Initialize(uint32_t width, uint32_t height, Format format) override;

        int GetWidth() const { return mWidth; }
        int GetHeight() const { return mHeight; }
        void SetPixelColor(int x, int y, const Color& color);
        const Color& GetPixelColor(int x, int y) const;
        void ApplyColors();
    private:
        int mWidth = 0;
        int mHeight = 0;
        std::unique_ptr<Color[]> mPixelColors;
    };
}