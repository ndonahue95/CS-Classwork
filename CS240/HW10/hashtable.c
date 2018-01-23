#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

static hashtable_ent_t* add_new(hashtable_ent_t** entry, const char* key) {
    if (entry == NULL || key == NULL) return NULL;
    *entry = (hashtable_ent_t*)malloc(sizeof(hashtable_ent_t));
    if (*entry == NULL) return NULL;
    (*entry)->key = strdup(key);
    if ((*entry)->key == NULL) {
        free(*entry);
        return NULL;
    }
    (*entry)->next = NULL;
    return *entry;
}

/*
 * Helper function that does most of the implemention work
 */
static hashtable_ent_t* locate(hashtable_t* ht, const char* key, int create_if_missing) {
    if (ht == NULL || key == NULL) return NULL;
    int h = hash(key) % ht->table_len;
    hashtable_ent_t* node = ht->table[h];
    if (node != NULL) {
        /* Search until we find a match or hit the end */
        while (node->next != NULL && strcmp(key, node->key)) node = node->next;
        if (!strcmp(key, node->key)) {
            return node;
        } else if (node->next == NULL && create_if_missing) {
            /* If we failed to find the key, we can create an entry in place */
            return add_new(&node->next, key);
        }
    } else if (create_if_missing) {
        return add_new(&ht->table[h], key);
    }
    return NULL;
}

hashtable_t *create_hashtable(int max_size) {
   //TODO
}

void free_hashtable(hashtable_t *ht) {
    //TODO
}

int get(hashtable_t *ht, const char *key, double *value) {
    //TODO
}

int set(hashtable_t *ht, const char *key, double value) {
   //TODO
}


int key_exists(hashtable_t *ht, const char *key) {
//TODO
}

int remove_key(hashtable_t *ht, const char *key) {
//TODO
}