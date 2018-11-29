#pragma once
#ifndef DRAGON_RADIOMETRY_SPATIALSPECTRUM
#define DRAGON_RADIOMETRT_SPATIALSPECTRUM
#include "spectrum.h"
namespace dragon {
	/*
	It is said that inline hints to the compiler that you think the function should be inlined. 
	That may have been true in 1998, but a decade later the compiler needs no such hints. 
	Not to mention humans are usually wrong when it comes to optimizing code, so most compilers flat out ignore the 'hint'.

	static - the variable/function name cannot be used in other translation units. 
	Linker needs to make sure it doesn't accidentally use a statically defined variable/function from another translation unit.

	extern - use this variable/function name in this translation unit but don't complain if it isn't defined. 
	The linker will sort it out and make sure all the code that tried to use some extern symbol has its address.

	inline - this function will be defined in multiple translation units, don't worry about it. 
	The linker needs to make sure all translation units use a single instance of the variable/function.
	The ¹guaranteed effect of inline as applied to a function, 
	is to allow the function to be defined identically, with external linkage, 
	in multiple translation units. For the in-practice that means defining the function in a header, 
	that can be included in multiple translation units. 
	The proposal extends this possibility to variables.

	So, in practical terms the (now accepted) proposal allows you to use the inline keyword to define an external linkage const namespace scope variable, 
	or any static class data member, in a header file, 
	so that the multiple definitions that result when that header is included in multiple translation units are OK with the linker – it just chooses one of them.
	*/
	static const uint32 nSpatialSamples = 60;
	static const uint32 lambdaStart = 400;
	static const uint32 lambdaEnd = 700;

	class SpatialSpectrum :public CoefficientSpectrum<nSpatialSamples> {

	};
}

#endif