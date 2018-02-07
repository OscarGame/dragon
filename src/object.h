#pragma once
#ifndef DRAGON_CORE_OBJECT
#define DRAGON_CORE_OBJECT
#include <memory>
#include "primitive.h"
#include "math.h"
#include "transform.h"
#include"material.h"
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
		virtual bool Hit(const Ray&r, HitInfo* hitp) const = 0;
		virtual bool isHit(const Ray&r) const = 0;
		virtual bool in(const Point3f&p)const = 0;
		virtual Vec2f getTex(const Point3f&pos)const { return Vec2f(0, 0); }
	};
	class Sphere :public Object {
	private:
		Float radius;
	public:
		Sphere(const Point3f& p, Float r, const ::std::shared_ptr<Material>& mat)
			:radius(r),Object(p,mat) {};
		bool Hit(const Ray&r, HitInfo* hit)const override {
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
		bool isHit(const Ray&r)const override { 
			Vec3f oA = pos - r.o;
			Vec3f oD = r.d.GetNorm();
			Float oAs = oA.Length();
			Float oBs = oA.Dot(oD);
			if (::std::sqrt(oAs * oAs + oBs * oBs) > radius)
				return false;
			else return true;
		}
		bool in(const Point3f&p)const override {
			if (pos.Distance(p) < radius)return true;
			else return false;
		}
	};
	class Floor:public Object {
	private:
		Point3f p[4];//RT,LT,RB,LB
		Float width, height;
		Normal n;
	public:
		Floor(const Point3f&pos, Float width, Float height, const Vec3f&rot, const ::std::shared_ptr<Material>&mat) :
			width(width), height(height),Object(pos, mat) {
			p[0] = Point3f(pos.x - width / 2, pos.y + height / 2, pos.z);
			p[1] = Point3f(pos.x + width / 2, pos.y + height / 2, pos.z);
			p[2] = Point3f(pos.x - width / 2, pos.y - height / 2, pos.z);
			p[3] = Point3f(pos.x + width / 2, pos.y - height / 2, pos.z);
			n = ((p[2] - p[0]) * (p[1] - p[0])).GetNorm();
			Transform t;
			if (rot.x != 0)
				t *= RotateX(rot.x);
			if (rot.y != 0)
				t *= RotateY(rot.y);
			if (rot.z != 0)
				t *= RotateZ(rot.z);
			for (int i = 0; i < 4; i++) {
				t(p[i]);
			}
			Transform nt = NormalT(t);
			n = nt(n);
		};
		bool in(const Point3f&pp)const override {
			if (pp.x < p[0].x || pp.x < p[2].x)return false;
			if (pp.y < p[2].y || pp.y < p[3].y)return false;
			if (pp.y > p[0].y || pp.y > p[1].y)return false;
			if (pp.x > p[1].x || pp.x > p[3].x)return false;
			return true;
		}
		bool isHit(const Ray&r)const override {
			Float t;
			Float part1 = n.x * r.d.x + n.y * r.d.y + n.z * r.d.z;
			if (part1 < 1e-20 && part1 > -1e-20)return false;
			Float part2 = n.x * (pos.x - r.o.x) + n.y * (pos.y - r.o.y) + n.z * (pos.z - r.o.z);
			t = part2 / part1;
			if (t > r.t)return false;
			else return true;
		}
		bool Hit(const Ray&r, HitInfo*hit)const override {
			Float t;
			Float part1 = n.x * r.d.x + n.y * r.d.y + n.z * r.d.z;
			if (part1 < 1e-20 && part1 > -1e-20)return false;
			Float part2 = n.x * (pos.x - r.o.x) + n.y * (pos.y - r.o.y) + n.z * (pos.z - r.o.z);
			t = part2 / part1;
			if (t > r.t || t <= 0)return false;
			hit->hitp = r.o + r.d * t;
			if (!in(hit->hitp))return false;
			hit->mat = mat;
			hit->n = n;
			hit->uv = getTex(hit->hitp);
			return true;
		}
		Vec2f getTex(const Point3f&pos)const override {
			Vec3f pp0 = pos - p[0];
			Float u = pp0.Dot(p[1] - p[0]) / width;
			Float v = pp0.Dot(p[2] - p[0]) / height;
			return Vec2f(u / width, v / height);
		}
	};
	typedef ::std::shared_ptr<Sphere> PSphere;
	typedef ::std::shared_ptr<Floor> PFloor;
	typedef ::std::shared_ptr<Object>PObject;
}
#endif
