#pragma once

#include "AVInterface.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class AVAPI
{

public:

	bool RegisterActorValue(std::string avName, AVInterface* avInterface);


};
