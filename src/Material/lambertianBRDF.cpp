#include "lambertianBRDF.h"
namespace dragon {
	Spectrum LambertianBRDF::Evaluate(const Vec3f&wo, const Vec3f&wi) const{
		return R * InvPi;
	}
	Spectrum LambertianBRDF::HDReflectance(const Vec3f&wi)const{
		return R;
	}
}