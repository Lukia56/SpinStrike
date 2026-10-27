#pragma once

#include <vector>
#include "ObserverEvent.h"

namespace Observer
{
	class IObserver;

	/// <summary>
	/// 登録したオブザーバに通知を送る
	/// </summary>
	class Subject
	{
	public:

		Subject() = default;
		virtual ~Subject() = default;

		void RegisterObserver(IObserver* observer);

		void UnregisterObserver(IObserver* observer);

		/// <summary>
		/// 登録されたオブザーバに通知を送る
		/// </summary>
		/// <param name="event">イベントID</param>
		void Notify(Event event);
		void Notify(Event event, int value);

	private:

		std::vector<IObserver*> mObservers;
	};
}