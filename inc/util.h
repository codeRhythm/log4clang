#ifndef UTIL_H
#define UTIL_H

#include <semaphore.h>

#define RET_OK 0
#define RET_ERROR (-1)
#define NULL ((void *)0)

#define TRUE 1
#define FALSE 0
#define LOG_INTERVAL 3000


typedef char            gint8;
typedef short           gint16;
typedef int             gint32;
typedef long            gint64;

typedef unsigned char   guint8;
typedef unsigned short  guint16;
typedef unsigned int    guint32;
typedef unsigned long   guint64;

typedef struct tag_node_data {
    guint32 log_hash_id;
    guint8 count;
    gint64 timestamp;
}node_data;

typedef struct tag_lru_node{
    struct tag_lru_node *prev;
    struct tag_lru_node *next;
    node_data data;
}lru_node;

gint64 get_cur_timestamp();
gint32 get_string_hash(const char *str, guint32 *hash_result);

#endif //UTIL_H