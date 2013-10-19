#ifndef __has_feature         // Optional of course.
  #define __has_feature(x) 0  // Compatibility with non-clang compilers.
#endif
#ifndef __has_extension
  #define __has_extension __has_feature // Compatibility with pre-3.0 compilers.
#endif

/* Include required header */
#include "WolframLibrary.h"


/* Return the version of Library Link */
DLLEXPORT mint WolframLibrary_getVersion( ) {
	return WolframLibraryVersion;
}

/* Initialize Library */
DLLEXPORT int WolframLibrary_initialize( WolframLibraryData libData) {
	return LIBRARY_NO_ERROR;
}

/* Uninitialize Library */
DLLEXPORT void WolframLibrary_uninitialize( WolframLibraryData libData) {
	return;
}

/* Returns Sum[i*R0, {i, I0}] */
DLLEXPORT int Function01( WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	mreal R0;
	mint I0;
	mint i;
	mreal R1;
	I0 = MArgument_getInteger(Args[0]);
	R0 = MArgument_getReal(Args[1]);
	R1 = 0;
	for ( i = 0; i < I0; i++) {
		R1 = R1 + i*R0;
	}
	MArgument_setReal(Res, R1);
	return LIBRARY_NO_ERROR;
}

/*[> Takes two vectors of real, returns the dot product <]*/
/*DLLEXPORT int Function02( WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {*/
	/*MTensor t0;*/
	/*MTensor t1;*/
	/*mreal *u; */
	/*mreal *v; */
	/*int err=LIBRARY_NO_ERROR;*/
	/*t0 = MArgument_getMTensor(Args[0]);*/
	/*t1 = MArgument_getMTensor(Args[1]);*/


	/*return err; */
/*}*/

/*mreal dot_product(mreal *u, mreal *v, mint len){*/
	/*mreal sum=0.0;*/
	/*for (int i = 0; i < len; i++) {*/
		/*sum+=u[i]*v[i];*/
	/*}*/
	/*return sum;*/
/*}*/
