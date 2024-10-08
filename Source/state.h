#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#include "raymath.h"
#pragma warning(pop)

#include <memory>
#include <string>
#include "Utilities.h"


class State
{

public:
	virtual ~State() = default;
	virtual std::unique_ptr<State> update() = 0;
	virtual void draw()  const noexcept = 0;
};






