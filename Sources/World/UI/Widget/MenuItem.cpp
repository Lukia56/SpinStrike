#include "MenuItem.h"
#include <functional>

namespace UI
{
	MenuItem::MenuItem()
	{
	}

	void MenuItem::InvokeSelect()
	{
		if (!mOnSelect) return;

		mOnSelect();
	}

	void MenuItem::InvokeDeselect()
	{
		if (!mOnDeselect) return;

		mOnDeselect();
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
