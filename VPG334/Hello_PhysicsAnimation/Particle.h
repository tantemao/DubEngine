#pragma once
#include <DubEngine/Inc/DubEngine.h>
struct ParticleInfo
{
	float lifetime;
	DubEngine::Color startColor = DubEngine::Colors::White;
	DubEngine::Color endColor = DubEngine::Colors::White;
	DubEngine::DEMath::Vector3 startPosition = DubEngine::DEMath::Vector3::Zero;
	DubEngine::DEMath::Vector3 startVelocity = DubEngine::DEMath::Vector3::Zero;

};
class Particle
{
public:
	Particle() = default;
	~Particle();

	void Initialize(const ParticleInfo& info);
private:
	float mLifeTime = 0.0f;
	DubEngine::Color mStartColor = DubEngine::Colors::White;
};
