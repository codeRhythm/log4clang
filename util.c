#include <datastruct.h>
#include <util.h>
#include <sys/time.h>

// BKDR Hash Function
gint32 get_string_hash(const char *str, guint32 *hash_result)
{
    if (str == NULL) {
        return RET_ERROR;
    }
    guint32 seed = 131; // 31 131 1313 13131 131313 etc..
    guint32 hash = 0;
 
    while (*str) {
        hash = hash * seed + (*str++);
    }
 
    *hash_result =  (hash & 0x7FFFFFFF);
    return RET_OK;
}

gint64 get_cur_timestamp()
{
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    gint64 milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}