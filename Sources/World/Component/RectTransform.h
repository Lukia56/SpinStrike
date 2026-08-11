#pragma once

#include "Transform.h"
#include "Utility/Rect.h"

/// <summary>
/// UIで使用する矩形で表現したTransform
/// </summary>
class RectTransform : public Transform
{
public:

	/// <summary>
	/// アンカーのプリセット識別子
	/// </summary>
	enum class Anchor
	{
		LeftTop,		// (0, 0)
		CenterTop,		// (0.5, 0)
		RightTop,		// (1, 0)
		LeftMiddle,		// (0, 0.5)
		CenterMiddle,	// (0.5, 0.5)
		RightMiddle,	// (1, 0.5)
		LeftBottom,		// (0, 1)
		CenterBottom,	// (0.5, 1)
		RightBottom,	// (1, 1)
		LeftStretch,	// (0, 0) ~ (0, 1)
		CenterStretch,	// (0.5, 0) ~ (0.5, 1)
		RightStretch,	// (1, 0) ~ (1, 1)
		TopStretch,		// (0, 0) ~ (1, 0)
		MiddleStretch,	// (0, 0.5) ~ (1, 0.5)
		BottomStretch,	// (0, 1) ~ (1, 1)
		FullStretch,	// (0, 0) ~ (1, 1)
	};

	RectTransform(GameObject* owner);

	Rect CalculateRect();

public:

	// ==================================
	// 固定アンカー
	// ==================================

	/// <summary>
	/// サイズと基準点からの距離を固定化する方法で値を設定する
	/// </summary>
	void SetFullRectAsFixed(const Vector2& size);

	/// <summary>
	/// <para>矩形の幅を設定する</para>
	/// <para>アンカーを横を固定、縦をストレッチにする場合に使用</para>
	/// </summary>
	void SetRectWidthAsFixed(float width);
	/// <summary>
	/// <para>矩形の高さを設定する</para>
	/// <para>アンカーを横をストレッチ、縦を固定にする場合に使用</para>
	/// </summary>
	void SetRectHeightAsFixed(float height);

	// ==================================
	// ストレッチアンカー
	// ==================================

	/// <summary>
	/// 親のサイズに合わせて引き伸ばす方法で値を設定する
	/// </summary>
	void SetFullRectAsStretch(float left, float top, float right, float bottom);

	/// <summary>
	/// <para>矩形の左右のオフセットを設定する</para>
	/// <para>アンカーを横をストレッチ、縦を固定にする場合に使用</para>
	/// </summary>
	void SetRectXAsStretch(float left, float right);
	/// <summary>
	/// <para>矩形の上下のオフセットを設定する</para>
	/// <para>アンカーを横を固定、縦をストレッチにする場合に使用</para>
	/// </summary>
	void SetRectYAsStretch(float top, float bottom);

public:

	void SetAnchor(const Vector2& anchorMin, const Vector2& anchorMax);
	void SetAnchor(Anchor anchor);

	void SetPivot(const Vector2& pivot) { mPivot = pivot; }

private:

	/// <summary>
	/// 親が変更されたらRectTransformにアップキャストしたものを取得する
	/// </summary>
	void OnUpdateParent() override;

	void CalculateRectX(Rect& rectResult, const Rect& rectParent);
	void CalculateRectY(Rect& rectResult, const Rect& rectParent);

	bool IsXAxisStretch();
	bool IsYAxisStretch();

private:

	Vector2 mSizeDelta;

	Vector2 mOffsetMin;
	Vector2 mOffsetMax;

	Vector2 mAnchorMin;
	Vector2 mAnchorMax;

	Vector2 mPivot;

	/// <summary>
	/// <para>親のRectTransform</para>
	/// <para>nullptrなら親がいないか、親はRectTransformではない</para>
	/// </summary>
	RectTransform* mParentRect;
};
