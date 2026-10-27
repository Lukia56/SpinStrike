#pragma once

#include "ObserverEvent.h"

namespace Observer
{
	/// <summary>
	/// Subjectから受け取った通知から処理を実行するインターフェース
	/// </summary>
	class IObserver
	{
	public:

		virtual ~IObserver() = default;

		/// <summary>
		/// 通知を受けたときに実行する関数
		/// </summary>
		/// <param name="event">イベントID</param>
		virtual void OnNotify(Event event) = 0;

		virtual void OnNotify(Event event, int value) {}
	};
}
