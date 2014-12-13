//
//  Copyright 2014 Wahankh <dev@wahankh.co.uk>
//
//  2014-12-7T19:12+0000

#include "monix.h"

gint main(gint argc, gchar **argv)
{
    g_type_init();
    
    search_process_directory("/proc");
    
    return EXIT_SUCCESS;
}

void search_process_directory(const gchar *path)
{
    GError *error = NULL;
    GFile *dir;
    GFileInfo *info;
    GFileEnumerator *enumerator;
    gchar *dir_path;
    
    dir = g_file_new_for_path(path);
    enumerator = g_file_enumerate_children(dir, NULL, 0, NULL, &error);
    
    if(enumerator == NULL)
    {
        #ifdef DEBUG 
            //debug(error->message); 
        #endif
        
        g_error_free(error);
        g_object_unref(dir);
        
        return;
    }
    
    dir_path = g_file_get_path(dir);
    
    while((info = g_file_enumerator_next_file(enumerator, NULL, &error)) != NULL)
    {
        GFileType type;
        const gchar *name;
        
        type = g_file_info_get_file_type(info);
        name = g_file_info_get_name(info);
        
        if(type == G_FILE_TYPE_REGULAR ||
            !g_file_info_has_attribute(info, G_FILE_ATTRIBUTE_ACCESS_CAN_READ) ||
            g_file_info_get_attribute_boolean(info, G_FILE_ATTRIBUTE_ACCESS_CAN_READ))
        {
            // found status file
            if(g_strcmp0(name, "status") == 0)
            {
                GIOChannel *gio;
                GIOStatus status;
                gchar *buffer;
                gchar *status_file;
                gboolean found = FALSE;
                
                status_file = g_strdup_printf("%s/%s", dir_path, name);
                
                if((gio = g_io_channel_new_file(status_file, "r", &error)) == NULL)
                {
                    #ifdef DEBUG 
                        //debug(error->message); 
                    #endif
                    
                    g_error_free(error);
                    break;
                }
                
                while((status = g_io_channel_read_line(gio, &buffer, NULL,NULL, &error)))
                {
                    if(status == G_IO_STATUS_NORMAL)
                    {                        
                        // contains string
                        if(g_strstr_len(buffer, -1, "iceweasel") != NULL)
                        {
                            #ifdef DEBUG 
                                debug(g_strdup_printf("Found Iceweasel -> %s", status_file)); 
                            #endif
                            
                            found = TRUE;                            
                        }
                        
                        if(g_strstr_len(buffer, -1, "Pid") != NULL && found)
                        {
                            #ifdef DEBUG 
                                debug(g_strdup_printf("%s", buffer)); 
                            #endif
                            
                            break;
                        }
                    }
                    else
                    {
                        g_io_channel_shutdown(gio, FALSE, &error);
                        g_io_channel_unref(gio);
                        
                        if(error != NULL)
                        {
                            #ifdef DEBUG
                                debug(error->message);
                            #endif
                            
                            g_error_free(error);
                        }
                        
                        break;
                    }
                }
                
                g_free(buffer);
            }
        }
        
        if(type == G_FILE_TYPE_DIRECTORY)
        {
            gchar *next_dir;
            
            next_dir = g_strdup_printf("%s/%s", dir_path, name);
            search_process_directory(next_dir);
            
            g_free(next_dir);
        }
    }
    
    if((g_file_enumerator_close(enumerator, NULL, &error)) == FALSE)
    {
        g_error_free(error);
    }
    
    g_object_unref(enumerator);
    g_free(dir_path);
}
