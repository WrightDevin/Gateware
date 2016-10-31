#ifndef GUTILITY
#define GUTILITY


#ifdef _WIN32

#define ConvertToUTF8(value)
#define ConvertToUTF16(value)

#elif __APPLE__

#elif __linux

#else

#error C++ compiler required.

#endif //_WIN32


#endif //GUTILITY