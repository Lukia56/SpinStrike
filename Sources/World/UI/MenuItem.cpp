#include "MenuItem.h"
#include <functional>

namespace UI
{
	MenuItem::MenuItem(const std::function<bool(void)>& onSubmit, const std::function<bool(void)>& onCancel) :
		mOnSubmit(onSubmit),
		mOnCancel(onCancel)
	{
	}

	bool MenuItem::InvokeSubmit()
	{
		if (!mOnSubmit)
		{
			return true;
		}

		return mOnSubmit();
	}

	bool MenuItem::InvokeCancel()
	{
		if (!mOnCancel)
		{
			return true;
		}

		return mOnCancel();
	}
}
