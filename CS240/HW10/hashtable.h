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
    if (max_size <= 0) return NULL;
    hashtable_t* ht = (hashtable_t*)malloc(sizeof(hashtable_t));
    if (ht == NULL) return NULL;
    ht->table_len = max_size;
    ht->table = (hashtable_ent_t**)malloc(sizeof(hashtable_ent_t*) * max_size);
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }
    int i;
    for (i = 0; i < ht->table_len; i++) {
        ht->table[i] = NULL; /* Initialize as unused */
    }
    return ht;
}

void free_hashtable(hashtable_t *ht) {
    
}

int get(hashtable_t *ht, const char *key, double *value) {
    
}

int set(hashtable_t *ht, const char *key, double value) {
   
}

int key_exists(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) return -1;
    return locate(ht, key, 0) != NULL;
}

int remove_key(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) return -1;
    int h = hash(key) % ht->table_len;
    hashtable_ent_t* node = ht->table[h], *tmp;
    if (node != NULL) {
        /* Check if the first node is the target */
        if (!strcmp(key, node->key)) {
            ht->table[h] = node->next;
            free(node->key);
            free(node);
            return 0;
        }
        /* Search until we find a match or hit the end */
        while (node->next != NULL && strcmp(key, node->next->key)) node = node->next;
        if (!strcmp(key, node->next->key)) {
            tmp = node->next;
            node->next = tmp->next;
            free(tmp->key);
            free(tmp);
            return 0;
        }
    }
    return -1;
}
ode = locate(ht, key, 1);
    if (node == NULL) return -1;
    node->value = value;
    return 0;
}

int key_exists(hashtable_t *ht, const char *key) {

}

int remove_key(hashtable_t *ht, const char *key) {
}