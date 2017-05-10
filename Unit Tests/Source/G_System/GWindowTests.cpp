#include "Common.h"


///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE 
//CRASHES, FALSE FAILURES, or FALSE PASSES

//Global variables needed for all Test Cases
GW::SYSTEM::GWindow* appWindow = nullptr; //Our buffered input object
GW::CORE::GListener* windowListener = nullptr; //Our listener object