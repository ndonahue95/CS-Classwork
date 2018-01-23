#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hashtable.h"

static hashtable_ent_t* add_new(hashtable_ent_t** entry, const char* key) {
    if (entry == NULL || key == NULL) return NULL;
    *entry = (hashtable_ent_t*)malloc(sizeof(hashtable_ent_t));
    if (*entry == NULL) return NULL;
    (*entry)->key = malloc(strlen(key) + 1);
    strcpy((*entry)->key, key);
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
    if (max_size <= 0)
        return NULL;
    
    hashtable_t * hashPointer = (hashtable_t *) malloc(sizeof(hashtable_t));
    
    hashPointer->table = (hashtable_ent_t **) malloc(max_size * sizeof(hashtable_ent_t*));
    hashPointer->table_len = max_size;
    
    int i;
    for (i = 0; i < max_size; i++) {
        hashPointer->table[i] = NULL;
        //hashPointer->table[i]->next = NULL;
    }
    
    // REMOVE!!! this is to silence warning. FOR NOW noob.
    //locate(NULL, "NULL", 0);
    
    return hashPointer;
}

void free_hashtable(hashtable_t *ht) {
    int i;
    
    for (i = 0; i < ht->table_len; i++) {
        
        //free(ht->table[i]->key);
        
        hashtable_ent_t * head = ht->table[i];
        hashtable_ent_t * node = head;
        while ((node = head) != NULL) {
            head = head->next;
            free(node->key);
            free(node);
        }
        
    }
    
    free(ht->table);
    free(ht);
}

int get(hashtable_t *ht, const char *key, double *value) {
    if (ht == NULL || key == NULL)
        return -1;
    
    int index = hash(key) % ht->table_len;
    
    if (ht->table[index] == NULL) {
        // nothin here, boss.
        return -1;
        
    } else {
        
        if (strcmp(key, ht->table[index]->key) == 0) {
            
            
            // success #1
            *value = ht->table[index]->value;
            return 0;
            
        } else {
            
            hashtable_ent_t * node = ht->table[index];
            
            while (node->next != NULL) {
                node = node->next;
                
                if (strcmp(key, node->key) == 0) {
                    
                    // success #2
                    *value = node->value;
                    return 0;
                    
                }
                
            }
            
        }
        
    }
    
    return -1;
}

int set(hashtable_t *ht, const char *key, double value) {
    if (ht == NULL || key == NULL)
        return -1;
    
    int index = hash(key) % ht->table_len;
    
    hashtable_ent_t * located = locate(ht, key, 0);
    
    if (ht->table[index] == NULL) {
        located = locate(ht, key, 1);
        
        located->value = value;
        
        ht->table[index] = located;
    } else {
        
        // LINKED LIST WORK
        
        hashtable_ent_t * node = ht->table[index];
        
        while (node->next != NULL)
            node = node->next;
        
        hashtable_ent_t * toAdd = (hashtable_ent_t*) malloc(sizeof(hashtable_ent_t));
        toAdd->key = malloc(strlen(key) + 1);
        strcpy(toAdd->key, key);
        toAdd->next = NULL;
        toAdd->value = value;
        
        node->next = toAdd;
        
    }
    
    return 0;
}


int key_exists(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL)
        return -1;
    
    hashtable_ent_t * located = locate(ht, key, 0);
    
    if (located == NULL)
        return 0;
    
    return 1;
}

int remove_key(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL)
        return -1;
    
    hashtable_ent_t * located = locate(ht, key, 0);
    
    if (located == NULL)
        return -1;
    
    // can be deleted anywhere from chain
    // noob.
    
    int index = hash(key) % ht->table_len;
    
    hashtable_ent_t * node = ht->table[index];
    hashtable_ent_t * temp = node;
    
    while (node != NULL) {
        if (strcmp(key, node->key) == 0) {
            if (node == ht->table[index])
                ht->table[index] = node->next;
            else
                temp->next = node->next;
            
            free(node);
            break;
        }
        temp = node;
        node = node->next;
        
    }
    
    return 0;
}
