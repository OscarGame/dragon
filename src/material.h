#pragma once
#ifndef DRAGON_CORE_MATERIAL
#define DRAGON_CORE_MATERIAL
#include"primitive.h"
namespace dragon {
	class Texture {
		virtual RGB getColor(const Vec2f&uv) const = 0;
	};
	class CheckTex:public Texture {
	private:
		Vec2f res;
	public:
		CheckTex(const Vec2f&res):res(res){}
		RGB getColor(const Vec2f&uv) const override {
			int index = (int)(uv.x / res.x) + (int)(uv.y / res.y);
			if (index > 10) {
				int i = 1;
			}
			if ( index % 2) {
				return WHITE;
			}
			else return BLACK;
		}
	};
	class Material {
	public:
		Float eta;
		Material(Float eta):eta(eta) {};
		virtual bool isReflect()const = 0;
		virtual bool isRefract()const = 0;
		virtual ~Material() {};
		virtual RGB ComputeColor(const Vec3f&view, const Vec3f&ray,const Normal&n,
			const RGB&light,const Vec2f&uv)const = 0;
	};
	class MatteMat :public Material {
	private:
		Float shininess;
		Vec3f Kd;
		Vec3f Ks;
	public:
		MatteMat(const Vec3f&Kd, const Vec3f&Ks, Float shininess) 
			:Kd(Kd), Ks(Ks), shininess(shininess),Material(0) {}
		RGB ComputeColor(const Vec3f&view, const Vec3f&ray,const Normal&n,
			const RGB&lightSDF,const Vec2f&uv)const override {
			Float diffratio = (-ray).Dot(n);
			if (diffratio <= 0.f)return BLACK;
			RGB t = lightSDF * Kd * diffratio;	
			Float sradio = Reflect(ray, n).Dot(view);
			if (sradio > 0) {
				Float spratio = ::std::powf(sradio, shininess);
				t += lightSDF * Ks * spratio;
			}
			return t;
		}
		bool isRefract()const override {
			return false;
		}
		bool isReflect()const override {
			return false;
		}
	};
	class GlassMat :public Material{
	private:
		Float shininess;
		Float glossiness;
		Vec3f Kd;
		Vec3f Ks;
	public:
		GlassMat(const Vec3f&Kd, const Vec3f&Ks, Float shininess, Float eta)
			:Kd(Kd), Ks(Ks), shininess(shininess),Material(eta) {}
		RGB ComputeColor(const Vec3f&view, const Vec3f&ray, const Normal&n, 
			const RGB&lightSDF,const Vec2f&uv)const override{
			Float diffratio = (-ray).Dot(n);
			if (diffratio <= 0.f)return BLACK;
			RGB t = BLACK;// lightSDF * Kd * diffratio;
			Float sradio = Reflect(ray, n).Dot(view);
			if (sradio > 0) {
				Float spratio = ::std::powf(sradio, shininess);
				t += lightSDF * Ks * spratio;
			}
			return BLACK;
		}
		bool isReflect()const override {
			return true;
		}
		bool isRefract()const override {
			return true;
		}
	};
	class CheckMat:public Material {
	private:
		Float shininess;
		Vec3f Kd;
		Vec3f Ks;
		CheckTex tex;
	public:
		CheckMat(const Vec3f&Kd, const Vec3f&Ks, const Vec2f&grid, Float shininess)
			:Kd(Kd), Ks(Ks), shininess(shininess),tex(grid), Material(0) {}
		RGB ComputeColor(const Vec3f&view, const Vec3f&ray, const Normal&n, 
			const RGB&lightSDF, const Vec2f&uv)const override {
			Float diffratio = (-ray).Dot(n);
			if (diffratio <= 0.f)return BLACK;
			RGB t = lightSDF * Kd * diffratio;
			Float sradio = Reflect(ray, n).Dot(view);
			if (sradio > 0) {
				Float spratio = ::std::powf(sradio, shininess);
				t += lightSDF * Ks * spratio;
			}
			t += tex.getColor(uv);
			return t;
		}
		bool isRefract()const override {
			return false;
		}
		bool isReflect()const override {
			return false;
		}
	};
	typedef ::std::shared_ptr<MatteMat> PMatteMat;
	typedef ::std::shared_ptr<GlassMat> PGlassMat;
	typedef ::std::shared_ptr<Material> PMaterial;
}
#endif
