/* vim: set sw=8: -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * gsf-infile.h: 
 *
 * Copyright (C) 2002 Jody Goldberg (jody@gnome.org)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef GSF_INFILE_H
#define GSF_INFILE_H

#include <gsf/gsf.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define GSF_INFILE_TYPE        (gsf_infile_get_type ())
#define GSF_INFILE(o)          (G_TYPE_CHECK_INSTANCE_CAST ((o), GSF_INFILE_TYPE, GsfInfile))
#define IS_GSF_INFILE(o)       (G_TYPE_CHECK_INSTANCE_TYPE ((o), GSF_INFILE_TYPE))

GType gsf_infile_get_type (void);

int	    gsf_infile_num_children   (GsfInfile *infile);
char const *gsf_infile_name_by_index  (GsfInfile *infile, int i);
GsfInput   *gsf_infile_child_by_index (GsfInfile *infile, int i);
GsfInput   *gsf_infile_child_by_name  (GsfInfile *infile, char const *name);
GsfInput   *gsf_infile_child_by_vname  (GsfInfile *infile, char const *name, ...);

G_END_DECLS

#endif /* GSF_INFILE_H */
