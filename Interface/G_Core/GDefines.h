#ifndef GDEFINES
#define GDEFINES

/*!
	File: GDefines.h
	Purpose: Lists the core #defines and MACROS used by the Gateware interfaces.
	Author: Lari H. Norri
	Contributors: N/A
	Last Modified: 12/12/2016
	Copyright: 7thGate Software LLC.
	License: MIT
*/

//! The core namespace to which all Gateware interfaces must belong
namespace GW
{
// ensure identical binary padding for structures on all platforms
#pragma pack(push, 1)
	//! Gateware Universaly Unique Interface IDentifier
	//! Each GIID defines a unique 128bit number identifying a particular version of an interface
	//! This allows interfaces to be upgraded down the line safely without breaking legacy code
	struct GUUIID // ALL GUUIID are stored little endian
	{
		unsigned int	byte4;
		unsigned short  byte2a;
		unsigned short  byte2b;
		unsigned char	byte8[8];

		//For faster comparison
		union
		{
			unsigned long long part1;
			unsigned long long part2;
		};

		bool operator==(const GUUIID& _cmp) const
		{
			if (part1 != _cmp.part1 || part2 != _cmp.part2)
				return false;

			return true;
		}
	}; // gateware guuiid mimic microsoft GUID structure in byte pattern 
	   // use built-in Visual Studio tools to generate unique ID for new interfaces
#pragma pack(pop)

	//! Listing of common error codes returned by Gateware functions
	enum GRETURN
	{
		SUCCESS					= 0xFFFFFFFF, // Any other code indicates some type of failure
		FAILURE					= 0,
		INVALID_ARGUMENT		= 1,
		MEMORY_CORRUPTION		= 2,
		INTERFACE_UNSUPPORTED	= 3,
		FILE_NOT_FOUND			= 4,
		REDUNDENT_OPERATION		= 5,
		FEATURE_UNSUPPORTED		= 6,
	};
};// end GW namespace

//! Macro used to determine if a function succeeded 
#define G_SUCCESS(_greturn_) ((~(_greturn_)) == 0x00000000)

//! Macro used to determine if a function has failed 
#define G_FAIL(_greturn_) ((_greturn_) < 0xFFFFFFFF)

//! If the following symbol is defined by the complier then you must also define the following DLL export symbols.
// ADD NON SYMBOLS FOR STANDARD BUILDS TO BE OVERRIDEN PER-PROJECT COMPILER SETTINGS
#ifndef GATEWARE_EXPORT_IMPLICIT
	#define GATEWARE_EXPORT_IMPLICIT
#endif
#ifndef GATEWARE_EXPORT_EXPLICIT
	#define GATEWARE_EXPORT_EXPLICIT extern "C"
#endif

#endif // end include guard