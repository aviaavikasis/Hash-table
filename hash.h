/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Ester                                   *
 * 20/07/2022                                        *
 * Description : imlementation of hash table         *
 *                                                   *
 *****************************************************/
#ifndef __ILRD_OL_127_128_HASH_TABLE_H__
#define __ILRD_OL_127_128_HASH_TABLE_H__


typedef struct hash_table hash_table_ty;

typedef size_t (*hash_function)(const void *data);
typedef int (*is_match_func)(const void *hash_data, void *user_data);
typedef int(*action_func)(void *data, void *param);

/*
DESCRIPTION : create new hash table
PARAMETERS : hash function - create by user, compar
function for collision case , size of the table.
RETURN : pointer to new hash table. in fail - NULL.
COMPLEXITY : time - O(n) , space - O(n)
*/
hash_table_ty *HashTableCreate(hash_function  hash_func, is_match_func is_match, size_t hash_size);

/*
DESCRIPTION : free hash table
PARAMETERS : pointer to hash table
RETURN : void
COMPLEXITY : time - O(n) , space - O(1)
*/
void HashTableDestroy(hash_table_ty *hash_table);

/*
DESCRIPTION : insert new element into hash table
PARAMETERS : pointer to hash table , void pointer to data
RETURN : 0 in success , 1 otherwise
COMPLEXITY : time - O(1) , space - O(1)
*/
int HashTableInsert(hash_table_ty *hash_table, void *data);

/*
DESCRIPTION : remove element from hash table
PARAMETERS : pointer to hash table , void pointer to data
RETURN : 0 in success , 1 otherwise
COMPLEXITY : time - O(1) , space - O(1)
*/
int HashTableRemove(hash_table_ty *hash_table, void *data);

/*
DESCRIPTION : find element into hash table
PARAMETERS : pointer to hash table , void pointer
to identifier of data.
RETURN : void pointer to the find data
COMPLEXITY : time - O(1) , space - O(1)
*/
void *HashTableFind(hash_table_ty *hash_table, void *data);

/*
DESCRIPTION : return the num of elememts in hash table
PARAMETERS : pointer to hash table
RETURN : the num of elememts(size_t)
COMPLEXITY : time - O(n) , space - O(1)
*/
size_t HashTableSize(const hash_table_ty *hash_table);

/*
DESCRIPTION : check if hash table is empty
PARAMETERS : pointer to hash table
RETURN : 0 if true , else 1
COMPLEXITY : time - O(1) , space - O(1)
*/
int HashTableIsEmpty(const hash_table_ty *hash_table);

/*
DESCRIPTION : active given operation function on
each element in hash table.
PARAMETERS : pointer to hash table , pointer to action function
and void to pointers to action function params.
RETURN : 0 in success , something else in fail.
COMPLEXITY : time - O(n) , space - O(1)  
*/
int HashTableForEach(hash_table_ty *hash_table,
                      action_func action_func, void *param);

/* advanced */

double HasTableLoad(const hash_table_ty  *hash_table);

double HashTableSD(const hash_table_ty *hash_table);

#endif /* __ILRD_OL_127_128_HASH_TABLE_H__ */
