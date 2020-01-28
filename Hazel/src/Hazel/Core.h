#pragma once

// These Preprocessor definitions are set at Project's Properties: 
// As Configurations is All Configurations & Platform is Active(x64)
// definitions are set at C/C++ > Preprocessor Definitions.
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL // in Hazel Project, we need export
		#define HAZEL_API __declspec(dllexport)
	#else							  // in Sandbox Project, we need import
		#define HAZEL_API __declspec(dllimport)
	#endif // HZ_BUILD_DLL
	#else
		#error Hazel only supports Windows !
#endif // HZ_PLATFORM_WINDOWS
