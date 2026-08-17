#pragma once

#include "../GameObject.h"
#include <stack>
#include <typeindex>
#include <unordered_map>
#include "Command.h"
#include "../Other/RootObject.h"

namespace Input
{
	struct UIInputState;
}

namespace UI
{
	class Screen;

	/// <summary>
	/// UIの画面を管理するクラス
	/// </summary>
	class UIManager : public GameObject
	{
	public:

		UIManager();
		~UIManager() = default;

		void Init() override {}
		void Update() override {}

		void ProcessInput(const Input::UIInputState& input);

		/// <summary>
		/// プールから画面をプッシュする
		/// 画面を事前にプールに追加する必要がある
		/// </summary>
		template <class T>
		requires std::derived_from<T, Screen>
		void PushScreen();

		/// <summary>
		/// 画面をプールに戻す
		/// </summary>
		void PopScreen();

		template <class T>
		requires std::derived_from<T, Screen>
		void AddScreenToPool(std::unique_ptr<T> screen);

		/// <summary>
		/// プールにある画面を削除する
		/// 表示中のものは削除できない
		/// </summary>
		template <class T>
		requires std::derived_from<T, Screen>
		void DeleteScreenFromPool();

		Command ConsumeCommand();

	private:

		RootObject* mActiveScreenRoot;
		RootObject* mPoolScreenRoot;

		std::stack<Screen*> mActiveScreens;

		/// <summary>
		/// プッシュできるように型で値を識別する
		/// </summary>
		std::unordered_map<std::type_index, Screen*> mPoolScreen;
	};

	template<class T>
	requires std::derived_from<T, Screen>
	inline void UIManager::PushScreen()
	{
		std::type_index type = typeid(T);

		if (!mPoolScreen.contains(type)) return;

		// 画面をプールから取り出しアクティブにする
		Screen* screen = mPoolScreen.at(type);
		mPoolScreen.erase(type);

		screen->Setup();
		screen->GetTransform()->ChangeParent(mActiveScreenRoot->GetTransform());
		mActiveScreens.emplace(screen);
	}

	template<class T>
	requires std::derived_from<T, Screen>
	inline void UIManager::AddScreenToPool(std::unique_ptr<T> screen)
	{
		mPoolScreen.try_emplace(typeid(T), screen.get());

		mPoolScreenRoot->AddToChild(std::move(screen));
	}

	template<class T>
	requires std::derived_from<T, Screen>
	inline void UIManager::DeleteScreenFromPool()
	{
		std::type_index type = typeid(T);

		if (!mPoolScreen.contains(type)) return;

		Screen* screen = mPoolScreen.at(type);
		Destroy(screen);

		mPoolScreen.erase(type);
	}
}
