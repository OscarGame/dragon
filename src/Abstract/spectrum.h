#pragma once

#ifndef DRAGON_RADIOMETRY_SPECTRUM
#define DRAGON_RADIOMETRY_SPECTRUM
#include "defines.h"

namespace dragon{
	/*
	
	
	*/
	template<uint32 N>
	class CoefficientSpectrum {
	private:
		Float samples[N];
	public:
		virtual ~CoefficientSpectrum() {};
		CoefficientSpectrum(Float v = 0.f) {
			for (int i = 0; i < N; i++) {
				samples[i] = v;
			}
		}
		Float operator[](uint32 i) {
			return samples[i];
		}
		CoefficientSpectrum operator *(Float v) const{
			CoefficientSpectrum t = *this;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] *= v;
			}
			return t;
		}
		CoefficientSpectrum operator *(const CoefficientSpectrum&v)const {
			CoefficientSpectrum t = *this;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] *= v.samples[i];
			}
			return t;
		}
		CoefficientSpectrum &operator *=(const CoefficientSpectrum&v){
			for (uint32 i = 0; i < N; i++) {
				samples[i] *= v.samples[i];
			}
			return *this;
		}
		CoefficientSpectrum operator -(Float v)const {
			CoefficientSpectrum t;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] -= v;
			}
			return t;
		}
		CoefficientSpectrum operator +(const CoefficientSpectrum&v)const {
			CoefficientSpectrum t;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] += v.samples[i];
			}
			return t;
		}
		CoefficientSpectrum operator +(Float v)const {
			CoefficientSpectrum t;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] += v;
			}
			return t;
		}
		CoefficientSpectrum operator -(const CoefficientSpectrum&v)const {
			CoefficientSpectrum t;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] -= v.samples[i];
			}
			return t;
		}
		CoefficientSpectrum operator /(const CoefficientSpectrum&v)const {
			CoefficientSpectrum t;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] /= v.samples[i];
			}
			return t;
		}
		friend CoefficientSpectrum Sqrt(const CoefficientSpectrum&v)const {
			CoefficientSpectrum t = *this;
			for (uint32 i = 0; i < N; i++) {
				t.samples[i] = std::sqrt(v.samples[i]);
			}
			return t;
		}
	};

	class RGBSpectrum :public CoefficientSpectrum<3> {
	public:
		RGBSpectrum(Float v = 0.f) :CoefficientSpectrum(v) {};
		RGBSpectrum(const CoefficientSpectrum&t) :CoefficientSpectrum(t) {};
	};

	static const uint32 nSpatialSamples = 60;
	static const uint32 lambdaStart = 400;
	static const uint32 lambdaEnd = 700;

	class SpatialSpectrum :public CoefficientSpectrum<nSpatialSamples> {
	public:
		SpatialSpectrum(Float v = 0.f) :CoefficientSpectrum(v) {};
		SpatialSpectrum(const CoefficientSpectrum&t) :CoefficientSpectrum(t) {};

	};

	typedef RGBSpectrum Spectrum;
}

#endif