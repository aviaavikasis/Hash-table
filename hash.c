/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Ester                                   *
 * 20/07/2022                                        *
 * Description : imlementation of hash table         *
 *                                                   *
 *****************************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "hash.h"   /* hash functions */ 
#include "dlist.h" /* dlist functions */

typedef enum 
{
	SUCCESS,
	FAIL
} bst_params_ty;

struct hash_table {
    dlist_ty** lists_array;
    size_t hash_size;
    hash_function hash_func;
    is_match_func cmp_func;
};

/* static functions */
static void FreeListsArray(dlist_ty **lists_array , size_t arr_size);
static hash_function GetHashFunc(hash_table_ty *hash_table);
static dlist_ty **GetListsArr(const hash_table_ty *hash_table);
static is_match_func GetCmpFunc(hash_table_ty *hash_table);



hash_table_ty *HashTableCreate(hash_function hash_func,
						 is_match_func cmp_func, size_t hash_size)
{
	hash_table_ty *hash_table = NULL;
	size_t i = 0;
	assert(NULL != hash_func);
	assert(NULL != cmp_func);
	assert(0 != hash_size);
	
	hash_table = (hash_table_ty*)malloc(sizeof(hash_table_ty));
	if(NULL == hash_table)
	{
		return NULL;
	}
	
	hash_table->lists_array = (dlist_ty**)malloc(hash_size * sizeof(dlist_ty*));
	if(NULL == hash_table->lists_array)
	{
		free(hash_table);
		return NULL;
	}
	
	for(i = 0 ; i < hash_size ; ++i)
	{
		hash_table->lists_array[i] = DlistCreate();
	}
	
	hash_table->hash_size = hash_size;
	hash_table->hash_func = hash_func;
	hash_table->cmp_func = cmp_func;
	
	return hash_table;
}


static void FreeListsArray(dlist_ty **lists_array , size_t arr_size)
{
	size_t i = 0;
	assert(NULL != lists_array);
	for( ; i < arr_size ; ++i)
	{
		DlistDestroy(lists_array[i]);
	}
	free(lists_array);
}

size_t GetSize(hash_table_ty *hash_table)
{
	assert(NULL != hash_table);
	return hash_table->hash_size;
}

void HashTableDestroy(hash_table_ty *hash_table)
{
	FreeListsArray(GetListsArr(hash_table) , GetSize(hash_table));
	free(hash_table);
	hash_table = NULL;	
}

static hash_function GetHashFunc(hash_table_ty *hash_table)
{
	assert(NULL != hash_table);
	return hash_table->hash_func;
}

static dlist_ty **GetListsArr(const hash_table_ty *hash_table)
{
	assert(NULL != hash_table);
	return hash_table->lists_array;
}

int HashTableInsert(hash_table_ty *hash_table, void *data)
{
	size_t insert_index = 0;
	dlist_ty *insert_dlist = NULL;
	dlist_iterator_ty insert_test = NULL;
	
	assert(NULL != hash_table);
	assert(NULL != data);
	
	insert_index = GetHashFunc(hash_table)(data);
	insert_dlist = GetListsArr(hash_table)[insert_index];
	insert_test = DlistInsertBefore(DlistBegin(insert_dlist), (void*)data);
	
	return ((NULL == insert_test) ? FAIL : SUCCESS);
}


static is_match_func GetCmpFunc(hash_table_ty *hash_table)
{
	assert(NULL != hash_table);
	return hash_table->cmp_func;
}


void *HashTableFind(hash_table_ty *hash_table, void *data)
{
	size_t insert_index = 0;
	dlist_iterator_ty from = NULL;
	dlist_iterator_ty to = NULL;
	assert(NULL != hash_table);
	assert(NULL != data);

	insert_index = GetHashFunc(hash_table)(data);
	from = DlistBegin(GetListsArr(hash_table)[insert_index]);
	to = DlistEnd(GetListsArr(hash_table)[insert_index]);
	return (DlistGetData(DlistFind(from, to, GetCmpFunc(hash_table), (void*)data)));
}

size_t HashTableSize(const hash_table_ty *hash_table)
{
	size_t i = 0;
	size_t counter = 0;
	assert(NULL != hash_table);
	
	for( ; i < hash_table->hash_size ; ++i)
	{
		counter += DlistSize(GetListsArr(hash_table)[i]);
	}
	return counter;
}


int HashTableIsEmpty(const hash_table_ty *hash_table)
{
	assert(NULL != hash_table);
	return (0 == HashTableSize(hash_table));
}


int HashTableRemove(hash_table_ty *hash_table, void *data)
{
	size_t insert_index = 0;
	dlist_iterator_ty from = NULL;
	dlist_iterator_ty to = NULL;
	dlist_iterator_ty find_test = NULL;
	assert(NULL != hash_table);
	assert(NULL != data);
	
	insert_index = GetHashFunc(hash_table)(data);
	from = DlistBegin(GetListsArr(hash_table)[insert_index]);
	to = DlistEnd(GetListsArr(hash_table)[insert_index]);
	find_test = DlistFind(from, to, GetCmpFunc(hash_table), (void*)data);
	
	if (to == find_test)
	{
		return FAIL;
	} 
	DlistRemove(find_test);
	return SUCCESS;
}


int HashTableForEach(hash_table_ty *hash_table,
                      action_func action_func, void *param)
{
	dlist_iterator_ty from = NULL;
	dlist_iterator_ty to = NULL;
	size_t i = 0;
	int return_function = 0; 
	assert(NULL != hash_table);
	assert(NULL != action_func);
	
	for( ; i < GetSize(hash_table) ; ++i)
	{
		from = DlistBegin(GetListsArr(hash_table)[i]);
		to = DlistEnd(GetListsArr(hash_table)[i]);
		return_function = DlistForEach(from , to , action_func , param);
		if(0 != return_function)
		{
			return return_function;
		}
	}
	return return_function;
}

























