#include "PoiseAV.h"

float PoiseAV::GetBaseActorValue([[maybe_unused]] RE::Actor* a_actor)
{
	return a_actor->GetActorValue(RE::ActorValue::kMass);
}

float PoiseAV::GetActorValueMax([[maybe_unused]] RE::Actor* a_actor)
{
	return a_actor->GetActorValue(RE::ActorValue::kMass);
}

float PoiseAV::GetActorValue(RE::Actor* a_actor)
{
	float value = GetBaseActorValue(a_actor);

	auto manager = AVManager::GetSingleton();
	value += manager->avStorage[a_actor->formID][0];
	value += manager->avStorage[a_actor->formID][1];
	value -= manager->avStorage[a_actor->formID][2];

	return value;
}
