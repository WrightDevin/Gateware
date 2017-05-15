#ifndef GDEFINES_H
#define GDEFINES_H

/*!
	File: GDefines.h
	Purpose: Lists the core #defines and MACROS used by the Gateware interfaces.
	Author: Lari H. Norri
	Contributors: N/A
	Last Modified: 12/12/2016
	Copyright: 7thGate Software LLC.
	License: MIT
*/

//! The core namespace to which all Gateware interfaces must belong.
namespace GW
{
// Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)

	//! Gateware Universally Unique Interface IDentifier.
	/*! 
	*	Each GUUIID defines a unique 128bit number identifying a particular version of an interface.
	*	This allows interfaces to be upgraded down the line safely without breaking legacy code.
	*/
	struct GUUIID // ALL GUUIID are stored little endian.
	{
		unsigned int	byte4;
		unsigned short  byte2a;
		unsigned short  byte2b;
		unsigned char	byte8[8];

		//For faster comparison.
		//union
		//{
		//	unsigned long long part1;
		//	unsigned long long part2;
		//};

		//! Comparison operator overload.
		bool operator==(const GUUIID& _cmp) const
		{
			const unsigned long long * part1a = reinterpret_cast<const unsigned long long *>(&byte4),
						             * part2a = reinterpret_cast<const unsigned long long *>(byte8),
				                     * part1b = reinterpret_cast<const unsigned long long *>(&_cmp.byte4),
				                     * part2b = reinterpret_cast<const unsigned long long *>(&_cmp.byte8);

			if (*part1a != *part1b || *part2a != *part2b)
				return false;

			return true;
			//if (part1 != _cmp.part1 || part2 != _cmp.part2)
			//	return false;
			//
			//return true;
		}
	}; // Gateware guuiid mimic microsoft GUID structure in byte pattern.
	   // Use built-in Visual Studio tools to generate unique ID for new interfaces.
#pragma pack(pop)

	//! Listing of common error codes returned by Gateware functions.
	enum GReturn
	{
		SUCCESS					= 0xFFFFFFFF, /*< The function succeded. */
		FAILURE					= 0, /*< The function failed (Check function documentation for possible reasons).*/
		INVALID_ARGUMENT		= 1, /*< An invalid argument was passed into the function.*/
		MEMORY_CORRUPTION		= 2, /*< A memory corruption occurred in the function.*/
		INTERFACE_UNSUPPORTED	= 3, /*< The requested interface is not supported by the object.*/
		FILE_NOT_FOUND			= 4, /*< A requested file is not found.*/
		REDUNDANT_OPERATION		= 5, /*< The requested operation will not do anything.*/
		FEATURE_UNSUPPORTED		= 6, /*< Attempted an operation that is currently not supported.*/
	};
};// end GW namespace

//! Macro used to determine if a function succeeded.
/*!
*	\param [in] _greturn_ The GReturn value to check.
*
*	\retval true GReturn value passed in was SUCCESS.
*	\retval false GReturn value passed in was a failure code.
*/
#define G_SUCCESS(_greturn_) ((~(_greturn_)) == 0x00000000)

//! Macro used to determine if a function has failed.
/*
*	\param [in] _greturn_ The GReturn value to check.
*
*	\retval true GReturn value passed in was a failure code.
*	\retval false GReturn value passed in was SUCCESS.
*/
#define G_FAIL(_greturn_) ((_greturn_) < 0xFFFFFFFF)

// If the following symbol is defined by the compiler then you must also define the following DLL export symbols.
// ADD NON SYMBOLS FOR STANDARD BUILDS TO BE OVERRIDEN PER-PROJECT COMPILER SETTINGS.
#ifndef GATEWARE_EXPORT_IMPLICIT
	#define GATEWARE_EXPORT_IMPLICIT
#endif
#ifndef GATEWARE_EXPORT_EXPLICIT
	#define GATEWARE_EXPORT_EXPLICIT extern "C"
#endif

#endif // end include guard