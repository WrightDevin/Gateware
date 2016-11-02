#ifndef GUTILITY
#define GUTILITY

#include <locale>
#include <codecvt>

namespace INTERNAL
{

	::std::wstring_convert < ::std::codecvt_utf8_utf16<wchar_t>, wchar_t > stringConverter;

#ifdef _WIN32

#define G_WIDEN(value) stringConverter.from_bytes(value)
#define G_NARROW(value) INTERNAL::stringConverter.to_bytes(value)

#elif __APPLE || __linux__

#define G_WIDEN(value) value
#define G_NARROW(value) value

#else

#error Gateware Libraries are not built for your current system

#endif // _WIN32



}

#endif //GUTILITY
