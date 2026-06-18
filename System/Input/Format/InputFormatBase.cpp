#include "InputFormatBase.h"
#include <unordered_map>
#include "../Literal/KeyCodes.h"

void InputFormatBase::RegisterKeyCode(const KeyCode::Button myKeyCode, const unsigned int keyCode)
{
	mLinkToKeyCode.emplace(myKeyCode, keyCode);
}
