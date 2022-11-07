#pragma once

#include <LIB_COMPILING.h>
#include <memory>

class Renderable;

struct LIB_API GraphicsComponent
{
	std::shared_ptr<Renderable> renderable;
};