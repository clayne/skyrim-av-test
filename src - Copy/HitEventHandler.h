#pragma once

class HitEventHandler
{
public:
	
	[[nodiscard]] static HitEventHandler* GetSingleton()
	{
		static HitEventHandler singleton;
		return std::addressof(singleton);
	}

	static void InstallHooks()
	{
		Hooks::Install();
	}


	void PreProcessHitEvent(RE::TESObjectREFR* target, RE::HitData& hitData);
	void PostProcessHitEvent(RE::TESObjectREFR* target, RE::HitData& hitData);


protected:

	static float GetStaminaPercentage(RE::Actor* actor)
	{
		auto currentValue = actor->GetActorValue(RE::ActorValue::kStamina);
		auto permanentValue = actor->GetPermanentActorValue(RE::ActorValue::kStamina);

		if (permanentValue == 0.0f || currentValue == 0.0f)
			return 0.0f;

		return currentValue / permanentValue;
	}

	static void TryStagger(RE::Character* target, float staggerMult, RE::Character* aggressor)
	{
		using func_t = decltype(&TryStagger);
		REL::Relocation<func_t> func{ REL::RelocationID(36700, 36700) };
		return func(target, staggerMult, aggressor);
	}

	static void CalculateWeaponStagger(RE::Character* actor_a, RE::Character* actor_b, RE::TESObjectWEAP* weapon, float& out, float unk)
	{
		using func_t = decltype(&CalculateWeaponStagger);
		REL::Relocation<func_t> func{ REL::RelocationID(42839, 42839) };  // 1.5.97 1407431D0
		return func(actor_a, actor_b, weapon, out, unk);
	}

	static void ApplyPerkEntryPoint(int entry, RE::Character* actor_a, RE::Character* actor_b, float& out)
	{
		using func_t = decltype(&ApplyPerkEntryPoint);
		REL::Relocation<func_t> func{ REL::RelocationID(23073, 23073) };  // 1.5.97 14032ECE0
		return func(entry, actor_a, actor_b, out);
	}

	static float RecalculateStagger(RE::Character* target, RE::Character* aggressor, RE::HitData& hitData)
	{
		float stagger = hitData.weapon->GetStagger() * (1.0f - hitData.percentBlocked);
		stagger += stagger * hitData.attackData.get()->data.staggerOffset;

		ApplyPerkEntryPoint(34, aggressor, target, stagger);
		ApplyPerkEntryPoint(33, target, aggressor, stagger);

		stagger *= 33;
		logger::info(FMT_STRING("calculated stagger last {}"), stagger);

		return stagger;
	}

	struct Hooks
	{
		struct ProcessHitEvent
		{
			static void thunk(RE::TESObjectREFR* target, RE::HitData& hitData)
			{
				logger::info(FMT_STRING("calculated stagger after after {}"), hitData.stagger);
				logger::info(FMT_STRING("calculated stagger after after {}"), static_cast<double>(hitData.attackData.get()->data.staggerOffset));
				auto manager = GetSingleton();
				manager->PreProcessHitEvent(target, hitData);
				func(target, hitData);
				manager->PostProcessHitEvent(target, hitData);
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct Nullify_ApplyPerkEntryPoint_Aggressor
		{
			static void thunk([[maybe_unused]] INT32 entry, [[maybe_unused]] RE::Character* actor_a, [[maybe_unused]] RE::Character* actor_b, [[maybe_unused]] INT64 out)
			{
				return;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct Nullify_ApplyPerkEntryPoint_Target
		{
			static void thunk([[maybe_unused]] INT32 entry, [[maybe_unused]] RE::Character* actor_a, [[maybe_unused]] RE::Character* actor_b, [[maybe_unused]] INT64 out)
			{
				return;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct CalculateHitData
		{
			static INT32 thunk(RE::TESObjectREFR* target, RE::HitData& hitData, RE::TESObjectREFR* aggressor, INT64 a4, float a5, char a6 )
			{

				logger::info(FMT_STRING("calculated stagger {}"), static_cast<double>(hitData.stagger));
				logger::info(FMT_STRING("calculated stagger {}"), static_cast<double>(hitData.attackData.get()->data.staggerOffset));
				INT32 toreturn = func(target, hitData, aggressor, a4, a5, a6);
				logger::info(FMT_STRING("calculated stagger after {}"), static_cast<double>(hitData.stagger));
				logger::info(FMT_STRING("calculated stagger after {}"), static_cast<double>(hitData.attackData.get()->data.staggerOffset));
				return toreturn;

			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct test
		{
			static INT64 thunk(RE::HitData &a1)
			{
				logger::info(FMT_STRING("calculated stagger test{}"), a1.stagger);
				INT64 toreturn = func(a1);
				logger::info(FMT_STRING("calculated stagger test after {}"), a1.stagger);
				return toreturn;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		static void Install()
		{
			stl::write_thunk_call<ProcessHitEvent>(REL::RelocationID(37673, 37673).address() + REL::Relocate(0x3C0, 0x3C0, 0x3C0));  // 1.5.97 140628C20
			stl::write_thunk_call<Nullify_ApplyPerkEntryPoint_Aggressor>(REL::RelocationID(36700, 36700).address() + REL::Relocate(0x9A, 0x90, 0x9A));  // 1.5.97 1405FA1B0
			stl::write_thunk_call<Nullify_ApplyPerkEntryPoint_Target>(REL::RelocationID(36700, 36700).address() + REL::Relocate(0xAE, 0xAE, 0xAE));    // 1.5.97 1405FA1B0
		
			//stl::write_thunk_call<CalculateHitData>(REL::RelocationID(37673, 37673).address() + REL::Relocate(0x1B7, 0x1B7, 0x1B7));  // 1.5.97 140628C20
			//stl::write_thunk_call<test>(REL::RelocationID(37673, 37673).address() + REL::Relocate(0x1EF, 0x1EF, 0x1EF));              // 1.5.97 140628C20

		}
	};


private:
	constexpr HitEventHandler() noexcept = default;
	HitEventHandler(const HitEventHandler&) = delete;
	HitEventHandler(HitEventHandler&&) = delete;

	~HitEventHandler() = default;

	HitEventHandler& operator=(const HitEventHandler&) = delete;
	HitEventHandler& operator=(HitEventHandler&&) = delete;


};
