#pragma once
#ifndef DRAGON_CORE_OBJECT
#define DRAGON_CORE_OBJECT
#include <memory>
#include "primitive.h"
#include "math.h"
#include "transform.h"
#include "material.h"
namespace dragon {
	struct HitInfo {
		Point3f hitp;
		Normal n;
		Vec2f uv;
		::std::shared_ptr<Material>mat;
	};
	class Object {
	public:
		::std::shared_ptr<Material>mat;
		Point3f pos;
		Object(const Point3f& pos, const ::std::shared_ptr<Material>& mat)
			:pos(pos), mat(mat) {};
		virtual ~Object() {};
		virtual AABB3f GetAABB() = 0;
		virtual bool Hit(const Ray&r,Float t,HitInfo* hitp) const = 0;
		virtual bool IsHit(const Ray&r) const = 0;
		virtual bool OnSurface(const Point3f&p)const = 0;
		Virtual bool InVolumn(const Point3f&p)const = 0;
		virtual Float Volumn()const = 0;
		virtual Float Area()const = 0;
		virtual Vec2f GetTexByPos(const Point3f&pos)const { return Vec2f(0, 0); }
		virtual Vec3f GetPosByTex(const Point2f&pos)const { return Vec3f(0, 0, 0); }
	};

	typedef ::std::shared_ptr<Object>ObjectPtr;
}
#endif
