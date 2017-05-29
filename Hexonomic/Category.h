#pragma once

namespace Category
{
	enum Type
	{
		None			= 0,
		LowerMap		= 1 << 0,
		UpperMap		= 1 << 1,
		Borders			= 1 << 2,
		Units			= 1 << 3,
		SelectedUnit	= 1 << 4
	};
}