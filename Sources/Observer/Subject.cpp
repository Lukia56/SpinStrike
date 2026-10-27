#include "Subject.h"
#include "IObserver.h"

namespace Observer
{
	void Subject::RegisterObserver(IObserver* observer)
	{
		mObservers.emplace_back(observer);
	}

	void Subject::UnregisterObserver(IObserver* observer)
	{
		auto iter = std::find(mObservers.begin(), mObservers.end(), observer);
		mObservers.erase(iter);
	}

	void Subject::Notify(Event event)
	{
		for (const auto& observer : mObservers)
		{
			observer->OnNotify(event);
		}
	}

	void Subject::Notify(Event event, int value)
	{
		Notify(event);

		for (const auto& observer : mObservers)
		{
			observer->OnNotify(event, value);
		}
	}
}
