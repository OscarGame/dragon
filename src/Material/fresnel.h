#pragma once
#include "defines.h"
#include "primitive.h"
#include "dragonMath.h"
#include "spectrum.h"
namespace dragon {
	Float FresnelDielectric(Float cosThetaI,Float etaI, Float etaT) {
		cosThetaI = Clamp(cosThetaI, -1.0, 1.0);
		// Potentially swap indices of refraction
		bool entering = cosThetaI > 0.f;
		if (!entering) {
			std::swap(etaI, etaT);
			cosThetaI = std::abs(cosThetaI);
		}

		// Compute _cosThetaT_ using Snell's law
		Float sinThetaI = std::sqrt(std::max((Float)0, 1 - cosThetaI * cosThetaI));
		Float sinThetaT = etaI / etaT * sinThetaI;

		// Handle total internal reflection
		if (sinThetaT >= 1) return 1;
		Float cosThetaT = std::sqrt(std::max((Float)0, 1 - sinThetaT * sinThetaT));
		Float Rparl = ((etaT * cosThetaI) - (etaI * cosThetaT)) /
			((etaT * cosThetaI) + (etaI * cosThetaT));
		Float Rperp = ((etaI * cosThetaI) - (etaT * cosThetaT)) /
			((etaI * cosThetaI) + (etaT * cosThetaT));
		return (Rparl * Rparl + Rperp * Rperp) / 2;
	}

	Spectrum FrConductor(Float cosThetaI, const Spectrum &etai,
		const Spectrum &etat, const Spectrum &k) {
		cosThetaI = Clamp(cosThetaI, -1.0, 1.0);
		Spectrum eta = etat / etai;
		Spectrum etak = k / etai;

		Float cosThetaI2 = cosThetaI * cosThetaI;
		Float sinThetaI2 = 1. - cosThetaI2;
		Spectrum eta2 = eta * eta;
		Spectrum etak2 = etak * etak;

		Spectrum t0 = eta2 - etak2 - sinThetaI2;
		Spectrum a2plusb2 = Sqrt(t0 * t0 + eta2 * etak2 * 4);
		Spectrum t1 = a2plusb2 + cosThetaI2;
		Spectrum a = Sqrt((a2plusb2 + t0) * 0.5f);
		Spectrum t2 = a * cosThetaI * 2.0;
		Spectrum Rs = (t1 - t2) / (t1 + t2);

		Spectrum t3 =  a2plusb2 * cosThetaI2 + sinThetaI2 * sinThetaI2;
		Spectrum t4 = t2 * sinThetaI2;
		Spectrum Rp = Rs * (t3 - t4) / (t3 + t4);

		return (Rp + Rs) * .5;
	}
}