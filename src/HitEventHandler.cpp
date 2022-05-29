#include "HitEventHandler.h"
#include "AVManager.h"

void HitEventHandler::PreProcessHitEvent(RE::Actor* target, [[maybe_unused]] RE::HitData& hitData)
{
	if (target == hitData.aggressor.get().get())
		return;

	auto avManager = AVManager::GetSingleton();

	avManager->DamageActorValue("Poise", target, RecalculateStagger(target, hitData.aggressor.get().get(), hitData));


	hitData.stagger = static_cast<uint32_t>(0.00);
}

void HitEventHandler::PostProcessHitEvent(RE::Actor* target, RE::HitData& hitData)
{
	auto avManager = AVManager::GetSingleton();
	if (avManager->GetActorValue("Poise", target) == 0.0f) {
		TryStagger(target, 1.0f, hitData.aggressor.get().get());
		avManager->RestoreActorValue("Poise", target, FLT_MAX);
	}
}
