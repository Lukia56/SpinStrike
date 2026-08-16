#pragma once

namespace Input
{
	/// <summary>
	/// UI‚Å“ü—ÍŒŸ’m‚ğ‚¹‚¸‚Éˆ—‚ğs‚¤‚½‚ß‚Ì\‘¢‘Ì
	/// </summary>
	struct UIInputState
	{
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;

		bool submit = false;
		bool cancel = false;
	};
}
