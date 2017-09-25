#include <stdint.h>
#if UINTPTR_MAX == UINT32_MAX
#include "glib/glibconfig_32.h"
#elif UINTPTR_MAX == UINT64_MAX
#include "glib/glibconfig_64.h"
#else
# error Unknown pointer size
#endif
