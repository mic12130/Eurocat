#pragma once

#include "common/Coordinate.h"
#include "hmi/track/tag/ITagRenderer.h"

namespace Eurocat::Hmi::Track
{
	class TagRenderer : public ITagRenderer
	{
	public:
		void RenderTagLabels(
			ITagDataProvider& tagData,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		) override;

	private:
		auto GetLabelContents(TagLabelCollection labelCollection) -> std::vector<std::vector<std::shared_ptr<ITagLabelContent>>>;
		Gdiplus::REAL GetLabelWidth(
			const std::vector<std::vector<std::shared_ptr<ITagLabelContent>>>& labelContents, 
			Screen::GraphicsWrapper& graphics
		);
		Gdiplus::REAL GetLabelHeight(
			const std::vector<std::vector<std::shared_ptr<ITagLabelContent>>>& labelContents, 
			Screen::GraphicsWrapper& graphics
		);
		void RenderRepositioning(
			Common::Coordinate coord,
			ITagDataProvider& tagData,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		);
		
		const Gdiplus::REAL kLineSeparation = 13;
	};
}
