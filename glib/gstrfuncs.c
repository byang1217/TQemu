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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
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

/*
 * MT safe
 */

#include "config.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <locale.h>
#include <errno.h>
#include <ctype.h>              /* For tolower() */

#ifdef HAVE_XLOCALE_H
/* Needed on BSD/OS X for e.g. strtod_l */
#include <xlocale.h>
#endif

#ifdef G_OS_WIN32
#include <windows.h>
#endif

/* do not include <unistd.h> here, it may interfere with g_strsignal() */

#include "gstrfuncs.h"

#include "gprintf.h"
#include "gprintfint.h"
#include "glibintl.h"

static const guint16 ascii_table_data[256] = {
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x004, 0x104, 0x104, 0x004, 0x104, 0x104, 0x004, 0x004,
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x140, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459,
  0x459, 0x459, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x653, 0x653, 0x653, 0x653, 0x653, 0x653, 0x253,
  0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
  0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
  0x253, 0x253, 0x253, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x473, 0x473, 0x473, 0x473, 0x473, 0x473, 0x073,
  0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
  0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
  0x073, 0x073, 0x073, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x004
  /* the upper 128 are all zeroes */
};

const guint16 * const g_ascii_table = ascii_table_data;

/**
 * g_ascii_tolower:
 * @c: any character
 *
 * Convert a character to ASCII lower case.
 *
 * Unlike the standard C library tolower() function, this only
 * recognizes standard ASCII letters and ignores the locale, returning
 * all non-ASCII characters unchanged, even if they are lower case
 * letters in a particular character set. Also unlike the standard
 * library function, this takes and returns a char, not an int, so
 * don't call it on %EOF but no need to worry about casting to #guchar
 * before passing a possibly non-ASCII character in.
 *
 * Returns: the result of converting @c to lower case. If @c is
 *     not an ASCII upper case letter, @c is returned unchanged.
 */
gchar
g_ascii_tolower (gchar c)
{
  return g_ascii_isupper (c) ? c - 'A' + 'a' : c;
}

/**
 * g_ascii_toupper:
 * @c: any character
 *
 * Convert a character to ASCII upper case.
 *
 * Unlike the standard C library toupper() function, this only
 * recognizes standard ASCII letters and ignores the locale, returning
 * all non-ASCII characters unchanged, even if they are upper case
 * letters in a particular character set. Also unlike the standard
 * library function, this takes and returns a char, not an int, so
 * don't call it on %EOF but no need to worry about casting to #guchar
 * before passing a possibly non-ASCII character in.
 *
 * Returns: the result of converting @c to upper case. If @c is not
 *    an ASCII lower case letter, @c is returned unchanged.
 */
gchar
g_ascii_toupper (gchar c)
{
  return g_ascii_islower (c) ? c - 'a' + 'A' : c;
}

gint
g_vasprintf (gchar      **string,
             gchar const *format,
             va_list      args)
{
  gint len;
  g_return_val_if_fail (string != NULL, -1);

  char buf[512];
  len = vsnprintf(buf, sizeof(buf), format, args);
  *string = g_new (gchar, len + 1);
  strncpy(*string, buf, len + 1);
  return len;
}


/**
 * g_strdup:
 * @str: (nullable): the string to duplicate
 *
 * Duplicates a string. If @str is %NULL it returns %NULL.
 * The returned string should be freed with g_free()
 * when no longer needed.
 *
 * Returns: a newly-allocated copy of @str
 */
gchar*
g_strdup (const gchar *str)
{
  gchar *new_str;
  gsize length;

  if (str)
    {
      length = strlen (str) + 1;
      new_str = g_new (char, length);
      memcpy (new_str, str, length);
    }
  else
    new_str = NULL;

  return new_str;
}

/**
 * g_memdup:
 * @mem: the memory to copy.
 * @byte_size: the number of bytes to copy.
 *
 * Allocates @byte_size bytes of memory, and copies @byte_size bytes into it
 * from @mem. If @mem is %NULL it returns %NULL.
 *
 * Returns: a pointer to the newly-allocated copy of the memory, or %NULL if @mem
 *  is %NULL.
 */
gpointer
g_memdup (gconstpointer mem,
          guint         byte_size)
{
  gpointer new_mem;

  if (mem)
    {
      new_mem = g_malloc (byte_size);
      memcpy (new_mem, mem, byte_size);
    }
  else
    new_mem = NULL;

  return new_mem;
}

/**
 * g_strndup:
 * @str: the string to duplicate
 * @n: the maximum number of bytes to copy from @str
 *
 * Duplicates the first @n bytes of a string, returning a newly-allocated
 * buffer @n + 1 bytes long which will always be nul-terminated. If @str
 * is less than @n bytes long the buffer is padded with nuls. If @str is
 * %NULL it returns %NULL. The returned value should be freed when no longer
 * needed.
 *
 * To copy a number of characters from a UTF-8 encoded string,
 * use g_utf8_strncpy() instead.
 *
 * Returns: a newly-allocated buffer containing the first @n bytes
 *     of @str, nul-terminated
 */
gchar*
g_strndup (const gchar *str,
           gsize        n)
{
  gchar *new_str;

  if (str)
    {
      new_str = g_new (gchar, n + 1);
      strncpy (new_str, str, n);
      new_str[n] = '\0';
    }
  else
    new_str = NULL;

  return new_str;
}

/**
 * g_strnfill:
 * @length: the length of the new string
 * @fill_char: the byte to fill the string with
 *
 * Creates a new string @length bytes long filled with @fill_char.
 * The returned string should be freed when no longer needed.
 *
 * Returns: a newly-allocated string filled the @fill_char
 */
gchar*
g_strnfill (gsize length,
            gchar fill_char)
{
  gchar *str;

  str = g_new (gchar, length + 1);
  memset (str, (guchar)fill_char, length);
  str[length] = '\0';

  return str;
}

/**
 * g_stpcpy:
 * @dest: destination buffer.
 * @src: source string.
 *
 * Copies a nul-terminated string into the dest buffer, include the
 * trailing nul, and return a pointer to the trailing nul byte.
 * This is useful for concatenating multiple strings together
 * without having to repeatedly scan for the end.
 *
 * Returns: a pointer to trailing nul byte.
 **/
gchar *
g_stpcpy (gchar       *dest,
          const gchar *src)
{
#ifdef HAVE_STPCPY
  g_return_val_if_fail (dest != NULL, NULL);
  g_return_val_if_fail (src != NULL, NULL);
  return stpcpy (dest, src);
#else
  gchar *d = dest;
  const gchar *s = src;

  g_return_val_if_fail (dest != NULL, NULL);
  g_return_val_if_fail (src != NULL, NULL);
  do
    *d++ = *s;
  while (*s++ != '\0');

  return d - 1;
#endif
}

/**
 * g_strdup_vprintf:
 * @format: a standard printf() format string, but notice
 *     [string precision pitfalls][string-precision]
 * @args: the list of parameters to insert into the format string
 *
 * Similar to the standard C vsprintf() function but safer, since it
 * calculates the maximum space required and allocates memory to hold
 * the result. The returned string should be freed with g_free() when
 * no longer needed.
 *
 * See also g_vasprintf(), which offers the same functionality, but
 * additionally returns the length of the allocated string.
 *
 * Returns: a newly-allocated string holding the result
 */
gchar*
g_strdup_vprintf (const gchar *format,
                  va_list      args)
{
  gchar *string = NULL;

  g_vasprintf (&string, format, args);

  return string;
}

/**
 * g_strdup_printf:
 * @format: a standard printf() format string, but notice
 *     [string precision pitfalls][string-precision]
 * @...: the parameters to insert into the format string
 *
 * Similar to the standard C sprintf() function but safer, since it
 * calculates the maximum space required and allocates memory to hold
 * the result. The returned string should be freed with g_free() when no
 * longer needed.
 *
 * Returns: a newly-allocated string holding the result
 */
gchar*
g_strdup_printf (const gchar *format,
                 ...)
{
  gchar *buffer;
  va_list args;

  va_start (args, format);
  buffer = g_strdup_vprintf (format, args);
  va_end (args);

  return buffer;
}

/**
 * g_strsplit:
 * @string: a string to split
 * @delimiter: a string which specifies the places at which to split
 *     the string. The delimiter is not included in any of the resulting
 *     strings, unless @max_tokens is reached.
 * @max_tokens: the maximum number of pieces to split @string into.
 *     If this is less than 1, the string is split completely.
 *
 * Splits a string into a maximum of @max_tokens pieces, using the given
 * @delimiter. If @max_tokens is reached, the remainder of @string is
 * appended to the last token.
 *
 * As an example, the result of g_strsplit (":a:bc::d:", ":", -1) is a
 * %NULL-terminated vector containing the six strings "", "a", "bc", "", "d"
 * and "".
 *
 * As a special case, the result of splitting the empty string "" is an empty
 * vector, not a vector containing a single string. The reason for this
 * special case is that being able to represent a empty vector is typically
 * more useful than consistent handling of empty elements. If you do need
 * to represent empty elements, you'll need to check for the empty string
 * before calling g_strsplit().
 *
 * Returns: a newly-allocated %NULL-terminated array of strings. Use
 *    g_strfreev() to free it.
 */
gchar**
g_strsplit (const gchar *string,
            const gchar *delimiter,
            gint         max_tokens)
{
  GSList *string_list = NULL, *slist;
  gchar **str_array, *s;
  guint n = 0;
  const gchar *remainder;

  g_return_val_if_fail (string != NULL, NULL);
  g_return_val_if_fail (delimiter != NULL, NULL);
  g_return_val_if_fail (delimiter[0] != '\0', NULL);

  if (max_tokens < 1)
    max_tokens = G_MAXINT;

  remainder = string;
  s = strstr (remainder, delimiter);
  if (s)
    {
      gsize delimiter_len = strlen (delimiter);

      while (--max_tokens && s)
        {
          gsize len;

          len = s - remainder;
          string_list = g_slist_prepend (string_list,
                                         g_strndup (remainder, len));
          n++;
          remainder = s + delimiter_len;
          s = strstr (remainder, delimiter);
        }
    }
  if (*string)
    {
      n++;
      string_list = g_slist_prepend (string_list, g_strdup (remainder));
    }

  str_array = g_new (gchar*, n + 1);

  str_array[n--] = NULL;
  for (slist = string_list; slist; slist = slist->next)
    str_array[n--] = slist->data;

  g_slist_free (string_list);

  return str_array;
}

/**
 * g_strfreev:
 * @str_array: (nullable): a %NULL-terminated array of strings to free
 *
 * Frees a %NULL-terminated array of strings, as well as each
 * string it contains.
 *
 * If @str_array is %NULL, this function simply returns.
 */
void
g_strfreev (gchar **str_array)
{
  if (str_array)
    {
      int i;

      for (i = 0; str_array[i] != NULL; i++)
        g_free (str_array[i]);

      g_free (str_array);
    }
}

/**
 * g_str_has_suffix:
 * @str: a nul-terminated string
 * @suffix: the nul-terminated suffix to look for
 *
 * Looks whether the string @str ends with @suffix.
 *
 * Returns: %TRUE if @str end with @suffix, %FALSE otherwise.
 *
 * Since: 2.2
 */
gboolean
g_str_has_suffix (const gchar *str,
                  const gchar *suffix)
{
  int str_len;
  int suffix_len;

  g_return_val_if_fail (str != NULL, FALSE);
  g_return_val_if_fail (suffix != NULL, FALSE);

  str_len = strlen (str);
  suffix_len = strlen (suffix);

  if (str_len < suffix_len)
    return FALSE;

  return strcmp (str + str_len - suffix_len, suffix) == 0;
}

