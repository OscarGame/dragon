#include "lambertianBRDF.h"
namespace dragon {
	Spectrum LambertianBRDF::DDReflectance(const Vec3f&wo, const Vec3f&wi) const{
		return R * InvPi;
	}
	Spectrum LambertianBRDF::HDReflectance(const Vec3f&wi)const{
		return R;
	}
}