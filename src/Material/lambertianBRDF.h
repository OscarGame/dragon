#pragma once
#ifndef DRAGON_MATERIAL_LAMBERTIAN
#define DRAGON_MATERIAL_LAMBERTIAN
#include "bxdf.h"
namespace dragon {
	class LambertianBRDF :BxDF {
	public:
		LambertianBRDF(const Spectrum&r) :BxDF(BxDFType(BSDF_REFLECTION | BSDF_DIFFUSE)), R{r} {};
		Spectrum Evaluate(const Vec3f&wo, const Vec3f&wi)const override final;
		Spectrum HDReflectance(const Vec3f&wo)const override final;
	private:
		const Spectrum R;
	};
}
#endif // !DRAGON_MATERIAL_LAMBERTIAN
