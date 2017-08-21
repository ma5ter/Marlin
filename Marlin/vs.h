#if defined(__INTELLISENSE__)

#define __VISUAL_STUDIO_STUBS__

#define __inline__
#define __asm__(...)
#define __extension__
#define __inline__
#define __volatile__

#define volatile(...) 
#define _CONST
#define __builtin_va_start
#define __builtin_va_end
#define __attribute__(...)

#define constexpr
#define __ATTR_CONST__
#define __ATTR_NORETURN__
#define __ATTR_PURE__
#define __ATTR_PROGMEM__
#define __ATTR_MALLOC__

#define __LPM(x) ((uint16_t)(x))
#define __LPM_word(x) ((uint16_t)(x))
#define __LPM_dword(x) ((uint16_t)(x))
#define __LPM_float(x) ((uint16_t)(x))
#define __LPM_word(x) ((uint16_t)(x))

typedef void* __builtin_va_list

#endif
