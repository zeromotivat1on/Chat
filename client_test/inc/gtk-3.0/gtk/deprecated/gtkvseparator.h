/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
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
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __GTK_VSEPARATOR_H__
#define __GTK_VSEPARATOR_H__

#if !defined (__GTK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gtk/gtk.h" can be included directly."
#endif

#include "../../gtk/gtkseparator.h"

G_BEGIN_DECLS

#define GTK_TYPE_VSEPARATOR                  (gtk_vseparator_get_type ())
#define GTK_VSEPARATOR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_VSEPARATOR, GtkVSeparator))
#define GTK_VSEPARATOR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_VSEPARATOR, GtkVSeparatorClass))
#define GTK_IS_VSEPARATOR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VSEPARATOR))
#define GTK_IS_VSEPARATOR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_VSEPARATOR))
#define GTK_VSEPARATOR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_VSEPARATOR, GtkVSeparatorClass))


typedef struct _GtkVSeparator       GtkVSeparator;
typedef struct _GtkVSeparatorClass  GtkVSeparatorClass;

/**
 * GtkVSeparator:
 *
 * The #GtkVSeparator struct contains private data only, and
 * should be accessed using the functions below.
 */
struct _GtkVSeparator
{
  GtkSeparator separator;
};

struct _GtkVSeparatorClass
{
  GtkSeparatorClass parent_class;
};


GDK_DEPRECATED_IN_3_2
GType      gtk_vseparator_get_type (void) G_GNUC_CONST;
GDK_DEPRECATED_IN_3_2_FOR(gtk_separator_new)
GtkWidget* gtk_vseparator_new      (void);

G_END_DECLS

#endif /* __GTK_VSEPARATOR_H__ */
