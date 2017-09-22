#ifndef GLIB_CONFIGH_H
#define GLIB_CONFIGH_H

#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING

#if (SIZEOF_LONG == 8)
#include "config_64.h"
#else
#include "config_32.h"
#endif

// no thread and os
typedef int GMainContext;
typedef int GDir;
#define G_LOCK_DEFINE_STATIC(x) do{}while(0)
#define G_LOCK(x) do{}while(0)
#define G_UNLOCK(x) do{}while(0)

#undef HAVE_XLOCALE_H

#define GLIB_COMPILATION

#endif
