#pragma once

#include "AVInterfaceImpl.h"
#include "AVManager.h"

class PoiseAV : public AVInterfaceImpl
{

public:

	inline  static const char* avName = "Poise";

	float GetBaseActorValue(RE::Actor* a_actor);

	float GetActorValueMax(RE::Actor* a_actor);

	float GetActorValue(RE::Actor* a_actor);




private:


};
