#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <util.h>

gint32 check_if_print(const gint8 *filepath, guint32 fileline);

#define DEBUG(fmt, args...) printf("CK File[%s:%s(%d)]:" fmt "\n", __FILE__,__FUNCTION__, __LINE__, ##args)
#define log(fmt, args...) \
do { \
    if (check_if_print(__FILE__, __LINE__)) { \
        printf("[%s:%u] "fmt"\n",__FILE__, __LINE__, ##args); \
    } \
} while (0)

#endif //LOGGER_H