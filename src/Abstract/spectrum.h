#pragma once

#ifndef DRAGON_RADIOMETRY_SPECTRUM
#define DRAGON_RADIOMETRY_SPECTRUM
#include "types.h"
namespace dragon{
	/*
	
	
	*/
	template<uint32 N>
	class CoefficientSpectrum {
	private:
		Float samples[N];
	public:
		CoefficientSpectrum(Float v) {
			for (int i = 0; i < N; i++) {
				samples[i] = v;
			}
		}
	};

}

#endif