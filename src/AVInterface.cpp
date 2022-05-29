#include "AVInterface.h"

float AVInterface::GetBaseActorValue([[maybe_unused]] RE::Actor* a_actor)
{
	return 0.0f;
}

float AVInterface::GetActorValueMax([[maybe_unused]] RE::Actor* a_actor)
{
	return 0.0f;
}

void AVInterface::DamageActorValue([[maybe_unused]] RE::Actor* a_actor, [[maybe_unused]] float afDamage)
{
}

void AVInterface::RestoreActorValue([[maybe_unused]] RE::Actor* a_actor, [[maybe_unused]] float afAmount)
{
}

void AVInterface::ModActorValue([[maybe_unused]] RE::Actor* a_actor, [[maybe_unused]] float afAmount)
{
}

float AVInterface::GetActorValue([[maybe_unused]] RE::Actor* a_actor)
{
	return 0.0f;
}
