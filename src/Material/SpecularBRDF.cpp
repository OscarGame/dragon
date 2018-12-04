#include "SpecularBRDF.h"
namespace dragon {
	Spectrum SpecularBRDF::DDReflectance(const Vec3f&wo, const Vec3f&wi)const {
		Spectrum t = R;
		//(0,0,1) * wo = wo.z = cosThetao 
		t *= fresnel.get()->Reflectance(wo.z);
		return t;
	}
}