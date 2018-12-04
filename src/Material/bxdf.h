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
/*
Any computation of BxDF is under the tangent space.
And aware that any vector input into BxDF should 
transform into the tangent space before and be normalized.
*/
	class BxDF {
	public:
		virtual ~BxDF() {};
		BxDF(const BxDFType&t) :type(t) {};
		virtual Spectrum DDReflectance(const Vec3f&wo, const Vec3f&wi)const = 0;
		/*
		HD means Hemispherical-Directional Reflectance.
		PBRT:The hemispherical-directional reflectance is a 2D function 
		that gives the total reflection in a given direction 
		due to constant illumination over the hemisphere, or, equivalently, 
		total reflection over the hemisphere due to light from a given direction.
		It values the proportion of the exitance(incidence) and incoming(outgoing) energy of light.
		The equation is integral f(p,wo,wi)cos(theta in)d(wi) over hemisphere on the normal side.
		*/
		virtual Spectrum HDReflectance(const Vec3f&dir)const = 0;
		const BxDFType type;
	};
}
#endif