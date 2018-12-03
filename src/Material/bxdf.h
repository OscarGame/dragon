#pragma once
#ifndef DRAGON_MATERIAL_BXDF
#define DRAGON_MATERIAL_BXDF
#include "Spectrum.h"
#include "primitive.h"
namespace dragon {
	enum BxDFType {
		BSDF_REFLECTION = 1 << 0,
		BSDF_TRANSMISSION = 1 << 1,
		BSDF_DIFFUSE = 1 << 2,
		BSDF_GLOSSY = 1 << 3,
		BSDF_SPECULAR = 1 << 4,
		BSDF_ALL = BSDF_REFLECTION | BSDF_TRANSMISSION | BSDF_DIFFUSE | BSDF_GLOSSY | BSDF_SPECULAR,
	};
	class BxDF {
	public:
		BxDF(const BxDFType&t) :type(t) {};
		virtual Spectrum Evaluate(const Vec3f&wo, const Vec3f&wi)const = 0;
		/*
		HD means Hemispherical-Directional Reflectance.
		It values the proportion of the exitance and incoming energy of light.
		The equation is integral f(p,wo,wi)cos(theta in)d(wi) over hemisphere on the normal side.
		*/
		virtual Spectrum HDReflectance(const Vec3f&wi)const = 0;
		const BxDFType type;
	};
}
#endif