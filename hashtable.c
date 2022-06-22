#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define capacity 5000

// hash function
unsigned long hash_function(char* str) {

    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
    {
        i += str[j];
    }

    return i % capacity;
}

typedef struct Ht_item Ht_item;
typedef struct Hashtable Hashtable;

struct Ht_item
{
    char* key;
    char* value;
};

struct Hashtable
{
    Ht_item** items;
    int size;
    int count;
};


// creating the item 

Ht_item* create_item(char* key, char* value)
{
    // create a pointer to a new hash table item 
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item-> key = (char*) malloc (strlen(key) + 1);
    item-> value = (char*) malloc (strlen(value) + 1);

    strcpy(item -> key, key);
    strcpy(item -> value, value);
    return item;
}

Hashtable* create_table(int size){

    Hashtable* table = (Hashtable*) malloc (sizeof(Hashtable));
    table -> size = size;
    table -> count = 0;
    table -> items = (Ht_item**) calloc (table-> size, sizeof(Ht_item*));

    for (int i = 0; i< table->size; i++){
        table -> items[i] = NULL;
    }

    return table;
}


void free_item(Ht_item* item){
    free(item ->key);
    free(item ->value);
    free(item);
}

void free_table(Hashtable* table){
    for (int i = 0; i< table->size ; i++){
        Ht_item* item  = table -> items[i];
        if (item != NULL){
            free_item(item);
        }
    }
}

void collisionHandling(Hashtable* table,unsigned long index, Ht_item* item){
}

void insert(Hashtable* table, char* key, char* value){
    Ht_item* item = create_item(key, value);
    unsigned long index = hash_function(key);
    Ht_item* current_item = table->items[index];

    if (current_item == NULL)
    {
        if (table-> count == table-> size)
        {
            printf("Error: HashTable is FULL \n");
            free_item(item);
            return;
        }
        table->items[index] = item; 
        table->count++;
    } 
    else 
    {
        if (strcmp(current_item -> key, key) == 0)
        {
            strcpy(table->items[index]-> value, value);
            return;
        } 
        else 
        {
            collisionHandling(table, index, item);
            return;
        }
    }
}


char* search(Hashtable* table, char* key){
    int index = hash_function(key);
    Ht_item* item = table-> items[index];


    if (item != NULL){
        if (strcmp(item -> key, key) == 0)
        return item-> value;
    }
    return NULL;
}
void print_search(Hashtable* table, char* key){
    char* val;
    if ((val = search(table, key)) == NULL) {
        printf("Key: %s does not exist \n", key);
    }
    else {
        printf("Key: %s , Value: %s\n", key, val);
    }
}

void print_table(Hashtable* table){
    printf("\nHash Table\n-----------------------------------------------------------------------\n");

    for (int i = 0; i < table-> size; i++){
        if (table -> items[i]){
            printf("Index: %d, Key: %s, Value: %s\n", i,  table->items[i]->key, table->items[i]->value);        
        }
    }
    printf("-----------------------------------------------------------------------\n\n");
}


int main() {
    Hashtable* ht = create_table(capacity);
    insert(ht, "1", "First Address");
    insert(ht, "2", "Second Address");
    insert(ht, "3", "3rd address");    print_search(ht, "1");
    print_search(ht, "2");
    print_search(ht, "3");
    print_table(ht);
    free_table(ht);
    return 0;
}
