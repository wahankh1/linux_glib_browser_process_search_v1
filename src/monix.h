//
//  Copyright 2014 Wahankh <dev@wahankh.co.uk>
//
//  2014-12-7T19:12+0000

#ifndef MONIX_H
#define MONIX_H

#include <gio/gio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>

#include "common.h"
#include "debug.h"

struct _process_info
{
    gint pid;
};

void search_process_directory(struct _process_info *pinfo, const gchar *path);
gint extract_pid(gchar *data);

#endif
