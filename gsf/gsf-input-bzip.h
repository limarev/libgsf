/* vim: set sw=8: -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * gsf-input-bzip.h: wrapper to compress to bzipped output
 *
 * Copyright (C) 2003 Dom Lachowicz (cinamod@hotmail.com)
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

#ifndef GSF_INPUT_BZIP_H
#define GSF_INPUT_BZIP_H

#include <gsf-input-memory.h>

G_BEGIN_DECLS

GsfInputMemory *gsf_input_memory_new_from_bzip (GsfInput *source, GError **err);

G_END_DECLS

#endif /* GSF_INPUT_BZIP_H */
