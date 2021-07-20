#pragma once

#include "public/libexport.h"

namespace HDMapStandalone {
	enum class ERoadMarkType
	{
		none,
		solid,
		broken,
		solid_solid,
		solid_broken,
		broken_solid,
		broken_broken,
		botts_dots,
		grass,
		curb
	};

	enum class ERoadMarkColor
	{
		standard,
		blue,
		green,
		red,
		white,
		yellow
	};

	struct LIBEXPORT MRoadMark
	{
		//@brief road mark's sOffset
		double sOffset;

		//@brief road mark's length
		double length;

		//@brief road mark's type.
		ERoadMarkType type = ERoadMarkType::none;

		//@brief road mark's color.
		ERoadMarkColor color = ERoadMarkColor::white;

		//@brief road mark's width.
		double width;
	};
}
