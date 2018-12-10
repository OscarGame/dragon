#pragma once
#ifndef DRAGON_OBJECT_FLOOR
#define DRAGON_OBJECT_FLOOR
#include "object.h"

namespace dragon{
	class Sphere :public Object {
	private:
		Float radius;
	public:
		Sphere(const Point3f& p, Float r, const ::std::shared_ptr<Material>& mat)
			:radius(r),Object(p,mat) {};
		bool Hit(const Ray&r,Float t, HitInfo* hit)const override {
			Float ox = r.o.x,oy = r.o.y,oz = r.o.z,
				dx = r.d.x,dy = r.d.y,dz = r.d.z,
				cx = pos.x,cy = pos.y,cz = pos.z;
			Float a = 1.f;
			Float b = 2 * (dx * (ox - cx) + dy * (oy - cy) + dz * (oz - cz));
			Float c = (ox - cx) * (ox - cx) + (oy - cy) * (oy - cy) + (oz - cz) * (oz - cz) - radius * radius;
			Float r1, r2;
			if (!Quadratic(a, b, c, r1, r2))return false;
			Float t;
			if (r1 > INFINITE_SMALL)t = r1;
			else if (r2 > INFINITE_SMALL) t = r2;
			else return false;
			hit->hitp = (r.o + r.d * t);
			hit->n = (hit->hitp - pos).GetNorm();
			hit->mat = mat;
			return true;
		}
		bool IsHit(const Ray&r)const override {
			Vec3f oA = pos - r.o;
			Vec3f oD = r.d.GetNorm();
			Float oAs = oA.Length();
			Float oBs = oA.Dot(oD);
			if (::std::sqrt(oAs * oAs + oBs * oBs) > radius)
				return false;
			else return true;
		}
		bool OnSurface(const Point3f&p)const override {
			if (pos.Distance(p) < radius)return true;
			else return false;
		}
	};
	typedef ::std::shared_ptr<Sphere> SpherePtr;
}
#endif