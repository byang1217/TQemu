/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_LIB_H__
#define __G_LIB_H__

#define __GLIB_H_INSIDE__
#include <glib/gatomic.h>
#include <glib/gbase64.h>
#include <glib/gstrfuncs.h>
#include <glib/ghash.h>
#include <glib/glist.h>
#include <glib/gqueue.h>
#include <glib/gslist.h>
#include <glib/gtypes.h>
#include <glib/gunicode.h>
#include <glib/gutils.h>
#include <glib/gtestutils.h>
#include <glib/gslice.h>
#include <glib/gversion.h>
#include <glib/gversionmacros.h>
#undef __GLIB_H_INSIDE__

/////////////////////////////////////////////////////////
//hack glib
typedef int GPollFD;
typedef int GSource;
typedef int GWakeup;
typedef int GIOCondition;
typedef void * GIOFunc;

void g_usleep (unsigned long microseconds);
void g_get_current_time (GTimeVal *result);


#endif /* __G_LIB_H__ */
