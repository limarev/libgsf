/* vim: set sw=8: -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * gsf-input-file.h: interface for used by the ole layer to read raw data
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

#ifndef GSF_INPUT_MEMORY_H
#define GSF_INPUT_MEMORY_H

#include "gsf-input.h"

G_BEGIN_DECLS

#define GSF_INPUT_MEMORY_TYPE	(gsf_input_memory_get_type ())
#define GSF_INPUT_MEMORY(o)	(G_TYPE_CHECK_INSTANCE_CAST ((o), GSF_INPUT_MEMORY_TYPE, GsfInputMemory))
#define IS_GSF_INPUT_MEMORY(o)	(G_TYPE_CHECK_INSTANCE_TYPE ((o), GSF_INPUT_MEMORY_TYPE))

typedef struct _GsfInputMemory GsfInputMemory;

GType     gsf_input_memory_get_type (void);
GsfInput *gsf_input_memory_new      (guint8 const *buf, size_t length,
				     gboolean needs_free);

#define GSF_INPUT_MMAP_TYPE	(gsf_input_mmap_get_type ())
#define GSF_INPUT_MMAP(o)	(G_TYPE_CHECK_INSTANCE_CAST ((o), GSF_INPUT_MMAP_TYPE, GsfInputMMap))
#define IS_GSF_INPUT_MMAP(o)	(G_TYPE_CHECK_INSTANCE_TYPE ((o), GSF_INPUT_MMAP_TYPE))

typedef struct _GsfInputMMap GsfInputMMap;

GType     gsf_input_mmap_get_type (void);
GsfInput *gsf_input_mmap_new	  (char const *filename, GError **err);

G_END_DECLS

#endif /* GSF_INPUT_MEMORY_H */
