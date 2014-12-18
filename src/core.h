//
//  Copyright 2014 Wahankh <dev@wahankh.co.uk>
//
//  2014-12-18T20:33+0000

#ifndef CORE_H
#define CORE_H

#include "monix.h"

struct _process_info
{
    gint pid;
};

void monix_search_process_directory(struct _process_info *pinfo, const gchar *path);
gint monix_extract_pid(gchar *data);


#endif
