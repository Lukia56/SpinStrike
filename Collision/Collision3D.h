#pragma once

#include "CollisionResult.h"
#include "Utility/Vector.h"
#include "Param/Param.h"

namespace Collision
{
	// ダブルディスパッチ用に前方宣言
	class Sphere3D;
	class AABB3D;
	class Capsule3D;

	/// <summary>
	/// 衝突判定の3D形状のインターフェース
	/// </summary>
	class IShape3D
	{
	public:

		IShape3D() = default;
		virtual ~IShape3D() = default;

		/// <summary>
		/// 衝突しているか調べる
		/// </summary>
		/// <param name="other">衝突判定を調べる形状</param>
		/// <returns>衝突情報</returns>
		virtual Collision::Result CheckCollision(const IShape3D* other) const = 0;

		virtual void DebugDraw() const = 0;

	public:

		virtual void SetPosition(const Vector3& pos) = 0;
		virtual Vector3 GetPosition() const = 0;

		virtual void SetOffset(const Vector3& offset) = 0;
		virtual const Vector3& GetOffset() const = 0;

	protected:

		friend Sphere3D;
		virtual Collision::Result Check(const Sphere3D* other) const = 0;
		friend AABB3D;
		virtual Collision::Result Check(const AABB3D* other) const = 0;
		friend Capsule3D;
		virtual Collision::Result Check(const Capsule3D* other) const = 0;
	};

	/// <summary>
	/// 衝突判定の球の形状のクラス
	/// </summary>
	class Sphere3D : public IShape3D
	{
	public:

		Sphere3D() = default;
		Sphere3D(const Vector3& pos, float radius, const Vector3& offset = Vector3::Zero) : mCenterPos(pos), mOffsetPos(offset), mRadius(radius) {}
		~Sphere3D() = default;

		Collision::Result CheckCollision(const IShape3D* other) const override { return other->Check(this); }

		void DebugDraw() const override;

	public:

		void SetPosition(const Vector3& pos) override { mCenterPos = pos; }
		/// <summary>
		/// オフセット込みの座標を取得
		/// </summary>
		Vector3 GetPosition() const override { return mCenterPos + mOffsetPos; }

		void SetOffset(const Vector3& offset) override { mOffsetPos = offset; }
		const Vector3& GetOffset() const override { return mOffsetPos; }

		float GetRadius() const { return mRadius; }

	protected:

		/// <summary>
		/// 球 vs 球の衝突判定
		/// </summary>
		Collision::Result Check(const Sphere3D* other) const override;

		/// <summary>
		/// 球 vs AABBの衝突判定
		/// </summary>
		Collision::Result Check(const AABB3D* other) const override;

		/// <summary>
		/// 球 vs カプセルの衝突判定
		/// </summary>
		Collision::Result Check(const Capsule3D* other) const override;

	private:
		
		Vector3 mCenterPos;

		Vector3 mOffsetPos;

		float mRadius;
	};

	/// <summary>
	/// 衝突判定のAABBの形状のクラス
	/// </summary>
	class AABB3D : public IShape3D
	{
	public:

		AABB3D() = default;
		AABB3D(const Vector3& pos, const Vector3& size, const Vector3& offset = Vector3::Zero) : mCenterPos(pos), mOffsetPos(offset), mHalfSize(size * 0.5f) {}
		AABB3D(const Vector3& pos, const AABBColliderParam& param) : mCenterPos(pos), mOffsetPos(param.offsetPos), mHalfSize(param.size * 0.5f) {}
		~AABB3D() = default;

		Collision::Result CheckCollision(const IShape3D* other) const override { return other->Check(this); }

		void DebugDraw() const override;

	public:

		void SetPosition(const Vector3& pos) override { mCenterPos = pos; }
		/// <summary>
		/// オフセット込みの座標を取得
		/// </summary>
		Vector3 GetPosition() const override { return mCenterPos + mOffsetPos; }

		void SetOffset(const Vector3& offset) override { mOffsetPos = offset; }
		const Vector3& GetOffset() const override { return mOffsetPos; }

		const Vector3& GetHalfSize() const { return mHalfSize; }

	protected:

		/// <summary>
		/// AABB vs 球の衝突判定
		/// </summary>
		Collision::Result Check(const Sphere3D* other) const override;

		/// <summary>
		/// AABB vs AABBの衝突判定
		/// </summary>
		Collision::Result Check(const AABB3D* other) const override;

		/// <summary>
		/// AABB vs カプセルの衝突判定
		/// </summary>
		Collision::Result Check(const Capsule3D* other) const override;

	private:

		Vector3 mCenterPos;

		Vector3 mOffsetPos;

		Vector3 mHalfSize;
	};

	/// <summary>
	/// 衝突判定のカプセルの形状のクラス
	/// </summary>
	class Capsule3D : public IShape3D
	{
	public:

		Capsule3D() = default;
		~Capsule3D() = default;

		Collision::Result CheckCollision(const IShape3D* other) const override { return other->Check(this); }

		void DebugDraw() const override;

	protected:

		/// <summary>
		/// AABB vs 球の衝突判定
		/// </summary>
		Collision::Result Check(const Sphere3D* other) const override;

		/// <summary>
		/// AABB vs AABBの衝突判定
		/// </summary>
		Collision::Result Check(const AABB3D* other) const override;

		/// <summary>
		/// カプセル vs カプセルの衝突判定
		/// </summary>
		Collision::Result Check(const Capsule3D* other) const override;

	private:


	};
}
