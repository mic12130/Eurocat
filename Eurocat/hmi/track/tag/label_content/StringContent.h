#pragma once

#include "hmi/track/tag/label_content/ITagLabelContent.h"

namespace Eurocat::Hmi::Track
{
	class StringContent : public ITagLabelContent
	{
	public:
		StringContent(CString str, CString objectIdSuffix = "");
		StringContent(
			CStringW str,
			CString objectIdSuffix = "",
			bool hasUnderline = false,
			std::optional<Gdiplus::Color> overridenColor = std::nullopt,
			std::optional<Gdiplus::Color> backgroundColor = std::nullopt
		);
		void Render(
			Gdiplus::PointF& point,
			Gdiplus::Color color,
			CString trackProfileId,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		) override;
		Gdiplus::SizeF GetSize(Screen::GraphicsWrapper& graphics) override;
		bool IsEmpty() override;

		const CStringW string;
		const CString objectIdSuffix;
		const bool hasUnderline;
		const std::optional<Gdiplus::Color> overridenColor;
		const std::optional<Gdiplus::Color> backgroundColor;

		// Tested using GraphicsWrapper::MeasureString(...)
		inline static const Gdiplus::REAL kCharWidth = float(7.22);
	};
}
