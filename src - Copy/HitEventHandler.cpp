#include "HitEventHandler.h"

void HitEventHandler::PreProcessHitEvent(RE::TESObjectREFR* target, [[maybe_unused]] RE::HitData& hitData)
{
	if (auto actor = target->As<RE::Actor>()) {
		if (actor == hitData.aggressor.get().get())
			return;
		//auto  staggerAmount = std::bit_cast<float>(hitData.stagger);
		//float modifier = -30;
		actor->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, -1 * RecalculateStagger(actor->As<RE::Character>(), hitData.aggressor.get().get()->As<RE::Character>(), hitData));
	//	logger::info(FMT_STRING("stagger {}"), hitData.stagger);
	//	logger::info(FMT_STRING("stagger {}"), std::bit_cast<float>(hitData.stagger));
	//	logger::info(FMT_STRING("stagger {}"), static_cast<float>(hitData.stagger));

		hitData.stagger = static_cast<uint32_t>(0.00);
	}
}

void HitEventHandler::PostProcessHitEvent(RE::TESObjectREFR* target, RE::HitData& hitData)
{
	if (auto actor = target->As<RE::Actor>()) {
		if (actor->GetActorValue(RE::ActorValue::kStamina) == 0.0f) {
			TryStagger(actor->As<RE::Character>(), 1.0f - GetStaminaPercentage(actor), hitData.aggressor.get().get()->As<RE::Character>());
			actor->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, 99999);
		}
		//if (actor->GetActorValue(RE::ActorValue::kStamina) < 1.0) {
		//	TryStagger(actor->As<RE::Character>(), GetStaminaPercentage(actor), hitData.aggressor.get().get()->As<RE::Character>());
		//}
	}
}
