#pragma once

#include "Utility/Vector.h"

namespace Collision3D
{
	/// <summary>
	/// 衝突結果のデータ群
	/// </summary>
	struct Result
	{
		/// <summary>
		/// 当たったかどうか
		/// </summary>
		bool isHit = false;

		/// <summary>
		/// 衝突した面の法線ベクトル
		/// </summary>
		Vector3 normal = Vector3::Zero;

		/// <summary>
		/// めりこみ具合
		/// </summary>
		float penetration = 0.0f;
	};

	// ダブルディスパッチ用に前方宣言
	class Sphere3D;
	class AABB3D;
	class Capsule3D;

	/// <summary>
	/// 衝突判定の3Dコライダのインターフェース
	/// </summary>
	class ICollider3D
	{
	public:

		ICollider3D() = default;
		virtual ~ICollider3D() = default;

		/// <summary>
		/// 衝突しているか調べる
		/// </summary>
		/// <param name="other">衝突判定を調べるコライダー　コピーでなく、読み取り専用になっていたら参照でもポインタでもOK</param>
		/// <returns>衝突情報</returns>
		virtual Collision3D::Result CheckCollision(const ICollider3D* other) const = 0;

		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		virtual void DebugDraw() const = 0;

	public:

		virtual void SetPosition(const Vector3& pos) = 0;
		virtual const Vector3& GetPosition() const = 0;

	protected:

		friend Sphere3D;
		virtual Collision3D::Result Check(const Sphere3D* other) const = 0;
		friend AABB3D;
		virtual Collision3D::Result Check(const AABB3D* other) const = 0;
		friend Capsule3D;
		virtual Collision3D::Result Check(const Capsule3D* other) const = 0;
	};

	/// <summary>
	/// 衝突判定の球のコライダのクラス
	/// </summary>
	class Sphere3D : public ICollider3D
	{
	public:

		Sphere3D() = default;
		Sphere3D(const Vector3& pos, float radius) : mCenterPos(pos), mRadius(radius) {}
		~Sphere3D() = default;

		/// <summary>
		/// 衝突しているか調べる
		/// </summary>
		/// <param name="other">衝突判定を調べるコライダー</param>
		/// <returns>衝突情報</returns>
		Collision3D::Result CheckCollision(const ICollider3D* other) const override { return other->Check(this); }

		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw() const override;

	public:

		void SetPosition(const Vector3& pos) override { mCenterPos = pos; }
		const Vector3& GetPosition() const override { return mCenterPos; }

		float GetRadius() const { return mRadius; }

	protected:

		/// <summary>
		/// 球 vs 球の衝突判定
		/// </summary>
		Collision3D::Result Check(const Sphere3D* other) const override;

		/// <summary>
		/// 球 vs AABBの衝突判定
		/// </summary>
		Collision3D::Result Check(const AABB3D* other) const override;

		/// <summary>
		/// 球 vs カプセルの衝突判定
		/// </summary>
		Collision3D::Result Check(const Capsule3D* other) const override;

	private:
		
		Vector3 mCenterPos;

		float mRadius;
	};

	/// <summary>
	/// 衝突判定のAABBのコライダのクラス
	/// </summary>
	class AABB3D : public ICollider3D
	{
	public:

		AABB3D() = default;
		AABB3D(const Vector3& pos, const Vector3& size) : mCenterPos(pos), mHalfSize(size * 0.5f) {}
		~AABB3D() = default;

		/// <summary>
		/// 衝突しているか調べる
		/// </summary>
		/// <param name="other">衝突判定を調べるコライダー</param>
		/// <returns>衝突情報</returns>
		Collision3D::Result CheckCollision(const ICollider3D* other) const override { return other->Check(this); }

		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw() const override;

	public:

		void SetPosition(const Vector3& pos) override { mCenterPos = pos; }
		const Vector3& GetPosition() const override { return mCenterPos; }

		const Vector3& GetHalfSize() const { return mHalfSize; }

	protected:

		/// <summary>
		/// AABB vs 球の衝突判定
		/// </summary>
		Collision3D::Result Check(const Sphere3D* other) const override;

		/// <summary>
		/// AABB vs AABBの衝突判定
		/// </summary>
		Collision3D::Result Check(const AABB3D* other) const override;

		/// <summary>
		/// AABB vs カプセルの衝突判定
		/// </summary>
		Collision3D::Result Check(const Capsule3D* other) const override;

	private:

		Vector3 mCenterPos;

		Vector3 mHalfSize;
	};

	class Capsule3D : public ICollider3D
	{
	public:

		Capsule3D() = default;
		~Capsule3D() = default;

		/// <summary>
		/// 衝突しているか調べる
		/// </summary>
		/// <param name="other">衝突判定を調べるコライダー</param>
		/// <returns>衝突情報</returns>
		Collision3D::Result CheckCollision(const ICollider3D* other) const override { return other->Check(this); }

		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw() const override;

	protected:

		/// <summary>
		/// AABB vs 球の衝突判定
		/// </summary>
		Collision3D::Result Check(const Sphere3D* other) const override;

		/// <summary>
		/// AABB vs AABBの衝突判定
		/// </summary>
		Collision3D::Result Check(const AABB3D* other) const override;

		/// <summary>
		/// カプセル vs カプセルの衝突判定
		/// </summary>
		Collision3D::Result Check(const Capsule3D* other) const override;

	private:


	};
}
