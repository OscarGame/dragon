#pragma once
#ifndef DRAGON_OBJECT_FLOOR
#define DRAGON_OBJECT_FLOOR
#include "object.h"

namespace dragon{
		class Floor :public Object {
		private:
			Point3f p[4];//RT,LT,RB,LB
			Float width, height;
			Normal n;
		public:
			Floor(const Point3f&pos, Float width, Float height, const Vec3f&rot, const ::std::shared_ptr<Material>&mat) :
				width(width), height(height), Object(pos, mat) {
				p[0] = Point3f(- width / 2, height / 2, 0);
				p[1] = Point3f(width / 2, height / 2, 0);
				p[2] = Point3f(- width / 2, - height / 2, 0);
				p[3] = Point3f(width / 2, - height / 2, 0);
				n = ((p[2] - p[0]) * (p[1] - p[0])).GetNorm();
				Transform t;
				if (rot.x != 0)
					t *= RotateX(rot.x);
				if (rot.y != 0)
					t *= RotateY(rot.y);
				if (rot.z != 0)
					t *= RotateZ(rot.z);
				for (int i = 0; i < 4; i++) {
					p[i] = t(p[i]) + Vec3f(pos.x,pos.y,pos.z);
				}
				Transform nt = NormalT(t);
				n = nt(n).GetNorm();
			};
			bool OnSurface(const Point3f&pp)const override {
				Float minx1 = std::min(p[0].x, p[1].x);
				Float minx2 = std::min(p[2].x, p[3].x);
				Float minx = minx1 < minx2 ? minx1 : minx2;
				Float miny1 = std::min(p[0].y, p[1].y);
				Float miny2 = std::min(p[2].y, p[3].y);
				Float miny = miny1 < miny2 ? miny1 : miny2;
				if (pp.x < minx || pp.y < miny)return false;
				Float maxx1 = std::max(p[0].x, p[1].x);
				Float maxx2 = std::max(p[2].x, p[3].x);
				Float maxx = maxx1 < maxx2 ? maxx1 : maxx2;
				Float maxy1 = std::max(p[0].y, p[1].y);
				Float maxy2 = std::max(p[2].y, p[3].y);
				Float maxy = maxy1 > maxy2 ? maxy1 : maxy2;
				if (pp.x > maxx || pp.y > maxy)return false;
				return true;
			}
			bool IsHit(const Ray&r)const override {
				Float t;
				Float part1 = n.x * r.d.x + n.y * r.d.y + n.z * r.d.z;
				if (part1 < 1e-20 && part1 > -1e-20)return false;
				Float part2 = n.x * (pos.x - r.o.x) + n.y * (pos.y - r.o.y) + n.z * (pos.z - r.o.z);
				t = part2 / part1;
				if (t > r.t)return false;
				else return true;
			}
			bool Hit(const Ray&r, Float t,HitInfo*hit)const override {
				Float t;
				Float part1 = n.x * r.d.x + n.y * r.d.y + n.z * r.d.z;
				if (part1 < 1e-20 && part1 > -1e-20)return false;
				Float part2 = n.x * (pos.x - r.o.x) + n.y * (pos.y - r.o.y) + n.z * (pos.z - r.o.z);
				t = part2 / part1;
				if (t > r.t || t <= 0)return false;
				hit->hitp = r.o + r.d * t;
				if (!on(hit->hitp))return false;
				hit->mat = mat;
				hit->n = n;
				hit->uv = getTex(hit->hitp);
				return true;
			}
			Vec2f GetTexByPos(const Point3f&pos)const override {
				Vec3f pp0 = pos - p[0];
				Float u = pp0.Dot(p[1] - p[0]) / width;
				Float v = pp0.Dot(p[2] - p[0]) / height;
				return Vec2f(u / width, v / height);
			}
		};
		typedef ::std::shared_ptr<Floor> FloorPtr;
}
#endif