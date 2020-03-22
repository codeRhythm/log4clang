#include <lru.h>
#include <util.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define NODE_CNT_MAX    8
static lru_node *glru_head = NULL;
static lru_node *glru_tail = NULL;

static gnode_count = 0;

void remove_node(lru_node *node_to_remove);

void destroy_list() {
    lru_node *node_to_del = glru_head;
    while (node_to_del != NULL) {
        node_to_del = node_to_del->next;
    }
}

gint32 init_list() {
    gnode_count = 0;
    if (glru_head == NULL) {
        glru_head = malloc(sizeof(lru_node));
    }
    if (glru_tail == NULL) {
        glru_tail = malloc(sizeof(lru_node));
    }
    if (glru_head != NULL && glru_tail != NULL) {
        memset(glru_head, 0, sizeof(lru_node));
        memset(glru_tail, 0, sizeof(lru_node));
        glru_head->next = glru_tail;
        glru_tail->prev = glru_head;
        gnode_count += 2;
    } else {
        free(glru_head);
        free(glru_tail);
    }
}

//TODO:
void move_node_tail(lru_node *node_to_move)
{
    node_to_move->prev->next = node_to_move->next;
    node_to_move->next->prev = node_to_move->prev;

    node_to_move->prev = glru_tail->prev;
    node_to_move->next = glru_tail;
    node_to_move->prev->next = node_to_move;
    glru_tail->prev = node_to_move;
    return;
}

lru_node *add_node(node_data *new_data)
{
    if (new_data == NULL) {
        printf("error");
        return NULL;
    }
    if (glru_head == NULL) {
        printf("error");
        return NULL;
    }

    lru_node *new_node =  malloc(sizeof(lru_node));
    if (new_node == NULL) {
        printf("error");
        return NULL;
    }
    new_node->data = *new_data;

    new_node->prev = glru_tail->prev;
    new_node->next = glru_tail;
    new_node->prev->next = new_node;
    glru_tail->prev = new_node;
    gnode_count++;
    printf("add node %p %x %u\n", new_node, new_node->data.log_hash_id, gnode_count);
    return new_node;
}

void remove_node(lru_node *node_to_remove)
{
    if (node_to_remove == NULL) {
        printf("error");
        return;
    }
    printf("remove node %p %x %u\n", node_to_remove, node_to_remove->data.log_hash_id, gnode_count);
    node_to_remove->prev->next = node_to_remove->next;
    node_to_remove->next->prev = node_to_remove->prev;
    free(node_to_remove);
    gnode_count--;
    return;
}

//根据
// 0:  打印日志
// 1：不打印日志
gint32 refresh_node(node_data *new_data)
{
    gint32 ret = TRUE;
    if (glru_head == NULL) {
        init_list();
    }
    //search for node
    lru_node *temp_node = glru_head->next;
    while(temp_node != NULL) {
        if (temp_node->data.log_hash_id == new_data->log_hash_id) {
            if (temp_node->data.timestamp + LOG_INTERVAL >= new_data->timestamp) { //log时间间隔大
                ret = FALSE;
            }
            temp_node->data.timestamp = new_data->timestamp;
            temp_node->data.count++;
            move_node_tail(temp_node);
            return ret;
        }
        temp_node = temp_node->next;
    }

    if (gnode_count == NODE_CNT_MAX) {
        remove_node(glru_head->next);
    }
    //add node.
    add_node(new_data);
    return TRUE;
}