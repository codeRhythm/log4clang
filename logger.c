#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util.h>
#include <lru.h>

#define MAX_LEN 256

const char *file_macro = __FILE__;

gint32 check_if_print(const char *filepath, guint32 fileline)
{
    if (filepath == NULL) {
        return TRUE;
    }

    node_data log_index_data = {0};
    log_index_data.timestamp = get_cur_timestamp();
    gint32 ret = get_string_hash(filepath, &(log_index_data.log_hash_id));
    if (ret != RET_OK) {
        printf("error for get hash \n");
        return TRUE;
    }
    log_index_data.log_hash_id += fileline;
    gint32 is_print = refresh_node(&log_index_data);
    return is_print;
}

