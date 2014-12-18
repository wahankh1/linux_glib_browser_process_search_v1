//
//  Copyright 2014 Wahankh <dev@wahankh.co.uk>
//
//  2014-12-15T18:22+0000

#include "monix.h"

//
//
//
gint main(gint argc, gchar **argv)
{
    struct _process_info pinfo;
    
    g_type_init();
    pinfo.pid = 0;
    
    // get process
    monix_search_process_directory(&pinfo, "/proc");
    
    g_print("%d\n", pinfo.pid);
    
    return EXIT_SUCCESS;
}
