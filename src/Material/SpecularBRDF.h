#pragma once
#ifndef DRAGON_MATERIAL_SPECULARBRDF
#define DRAGON_MATERIAL_SPECULARBRDF
#include "spectrum.h"
#include "bxdf.h"
#include "primitive.h"
#include "fresnel.h"
#include <memory>
namespace dragon {
	class SpecularBRDF :public BxDF {
	public:
		SpecularBRDF(const Spectrum&r, FresnelUptr f) :
			R(r), BxDF(BxDFType(BSDF_REFLECTION | BSDF_SPECULAR)), fresnel(std::move(f)) {};
		Spectrum DDReflectance(const Vec3f&wo, const Vec3f&wi)const override final;
		Spectrum HDReflectance(const Vec3f&dir)const override final;
	private:
		FresnelUptr fresnel;
		const Spectrum R;
	};

}
#endif