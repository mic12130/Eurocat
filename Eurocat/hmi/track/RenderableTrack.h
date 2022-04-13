#pragma once

#include "base/pch.h"

#include "hmi/track/FlightPlanDataProvider.h"
#include "hmi/track/RadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	struct RenderableTrack
	{
		enum class Type
		{
			Ground,
			Primary,
			Uncoupled,
			Coupled,
			FlightPlanTrack
		};

		CString id;
		Type type;
		std::shared_ptr<FlightPlanDataProvider> fp;
		std::shared_ptr<RadarTargetDataProvider> rt;

		RenderableTrack(
			CString id, Type type,
			std::shared_ptr<FlightPlanDataProvider> fp,
			std::shared_ptr<RadarTargetDataProvider> rt)
			: id(id), type(type), fp(fp), rt(rt) 
		{
		}

		bool operator<(const RenderableTrack& rhs) const
		{
			if (type != rhs.type)
			{
				return type < rhs.type;
			}

			if (type == Type::Coupled || type == Type::FlightPlanTrack)
			{
				auto leftState = fp->GetDisplayState();
				auto rightState = rhs.fp->GetDisplayState();

				if (leftState != rightState)
				{
					return leftState < rightState;
				}
			}

			return id < rhs.id;
		}
	};
}
