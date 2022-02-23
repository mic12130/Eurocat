#pragma once

#include "pch.h"

#include "screen/GraphicsWrapper.h"

namespace Eurocat::Screen
{
	class TestGraphics : public GraphicsWrapper
	{
	public:
		TestGraphics() : GraphicsWrapper(CreateDummy())
		{
		}
	};
}
