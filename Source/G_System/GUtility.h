#ifndef GUTILITY
#define GUTILITY

#include <locale>
#include <codecvt>

namespace INTERNAL
{
#if defined(__APPLE) || defined(__linux__)

#define G_WIDEN(value) value
#define G_NARROW(value) value

#define strcpy_s(...) strlcpy(__VA_ARGS__)

#elif defined(_WIN32)

#define G_WIDEN(value) stringConverter.from_bytes(value)
#define G_NARROW(value) INTERNAL::stringConverter.to_bytes(value)

#else

#error Gateware Libraries are not built for your current system

#endif

::std::wstring_convert < ::std::codecvt_utf8_utf16<wchar_t>, wchar_t > stringConverter;

unsigned int strlcpy(char* destination,  unsigned int strLen, const char* const source)
{
    return snprintf(destination, strLen, "%s", source);
}


}

#endif //GUTILITY
