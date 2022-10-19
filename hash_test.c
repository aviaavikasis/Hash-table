#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc , free */
#include <string.h> /* strlen */
#include "hash.h"

#define DICT_SIZE 102401
#define MAX_SIZE_WORD 45

void HashTableCreateTest(void);
void HashTableInsertTest(void);
void HashTableRemoveTest(void);
void HashTableFindTest(void);
void HashTableSizeTest(void);
void HashTableIsEmptyTest(void);
void HasTableLoadTest(void);
void HashTableSDTest(void);
void HashTableForEachTest(void);
void CpyDictinaryTest(void);

/* help functions */
size_t ModuleIndex(const void *data);
int IdCmp(const void *hash_id, void *user_id);
int AddThirty(void *data , void *null);
size_t DictHash(const void *data);
int DictCmp(const void *hash_word, void *user_word);



int main(void)
{
	HashTableCreateTest();
	HashTableInsertTest();
	HashTableRemoveTest();
	HashTableFindTest();
	HashTableSizeTest();
	HashTableIsEmptyTest();
	HashTableForEachTest();
	HasTableLoadTest();
	HashTableSDTest();
	CpyDictinaryTest();
	printf("\n\n->->->->->->->->-> success!!! <-<-<-<-<-<-<-<-<-<\n\n\n");
	
	return 0;
}


void HashTableCreateTest(void)
{
	hash_function hash_func = &ModuleIndex;
	is_match_func cmp_func = &IdCmp;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 30);
	HashTableDestroy(hash_table);
}

void HashTableInsertTest(void)
{
	hash_function hash_func = &ModuleIndex;
	is_match_func cmp_func = &IdCmp;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 30);
	int i = 0;
	int ids_arr[20] = {0};
	
	for( ; i < 20 ; ++i)
	{
		ids_arr[i] = i * 5 * i * 7 + 5000;
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		HashTableInsert(hash_table, ids_arr + i);
	}
	HashTableDestroy(hash_table);
}


void HashTableFindTest(void)
{
	hash_function hash_func = &ModuleIndex;
	is_match_func cmp_func = &IdCmp;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 30);
	int i = 0;
	int ids_arr[20] = {0};
	
	for( ; i < 20 ; ++i)
	{
		ids_arr[i] = i * 5 * i * 7 + 5000;
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		HashTableInsert(hash_table, ids_arr + i);
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		assert(i * 5 * i * 7 + 5000 == *(int*)HashTableFind(hash_table, ids_arr + i));	
	}
	
	HashTableDestroy(hash_table);	
}


void HashTableSizeTest(void)
{
	hash_function hash_func = &ModuleIndex;
	is_match_func cmp_func = &IdCmp;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 30);
	int i = 0;
	int ids_arr[20] = {0};
	assert(0 == HashTableSize(hash_table));
	for( ; i < 20 ; ++i)
	{
		ids_arr[i] = i * 5 * i * 7 + 5000;
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		HashTableInsert(hash_table, ids_arr + i);
	}
	
	assert(20 == HashTableSize(hash_table));
	
	HashTableDestroy(hash_table);	
}


void HashTableIsEmptyTest(void)
{
	hash_function hash_func = &ModuleIndex;
	is_match_func cmp_func = &IdCmp;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 30);
	int i = 0;
	int ids_arr[20] = {0};
	assert(1 == HashTableIsEmpty(hash_table));
	for( ; i < 20 ; ++i)
	{
		ids_arr[i] = i * 5 * i * 7 + 5000;
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		HashTableInsert(hash_table, ids_arr + i);
	}
	
	assert(0 == HashTableIsEmpty(hash_table));
	
	HashTableDestroy(hash_table);
}


void HashTableRemoveTest(void)
{
	hash_function hash_func = &ModuleIndex;
	is_match_func cmp_func = &IdCmp;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 30);
	int i = 0;
	int ids_arr[20] = {0};

	for( ; i < 20 ; ++i)
	{
		ids_arr[i] = i * 5 * i * 7 + 5000;
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		HashTableInsert(hash_table, ids_arr + i);
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		assert((size_t)(20 - i) == HashTableSize(hash_table));
		HashTableRemove(hash_table , ids_arr + i);
	}

	HashTableDestroy(hash_table);
}


void HashTableForEachTest(void)
{
	hash_function hash_func = &ModuleIndex;
	is_match_func cmp_func = &IdCmp;
	action_func action_function = &AddThirty;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 30);
	int i = 0;
	int ids_arr[20] = {0};
	int test_arr[20] = {0};

	for( ; i < 20 ; ++i)
	{
		ids_arr[i] = i * 5 * i * 7 + 5000;
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		HashTableInsert(hash_table, ids_arr + i);
	}
	
	HashTableForEach(hash_table , action_function , NULL);
	
	for(i = 0 ; i < 20 ; ++i)
	{
		test_arr[i] = i * 5 * i * 7 + 5000 + 30;
	}
	
	for(i = 0 ; i < 20 ; ++i)
	{
		assert(i * 5 * i * 7 + 5000 + 30 == *(int*)HashTableFind(hash_table, test_arr + i));
	}
	HashTableDestroy(hash_table);

}

void FreeDict(char **dict_buff , const size_t size)
{
	size_t i = 0;
	for( ; i < size ; ++i)
	{
		free(dict_buff[i]);
	}	
	free(dict_buff);
}


void SpellChecker(hash_table_ty *hash_table)
{

	char *result = NULL;
	char *input = (char*)calloc(MAX_SIZE_WORD , sizeof(char));
	if(NULL == input)
	{
		return;
	}
	
	printf("enter word to find in hash table : \n\n");
	scanf("%s" , input);
	
	result = HashTableFind(hash_table , input);
	if(NULL != result)
	{
		printf("the word is find : %s\n\n" , result);
		free(input);
		return;
	}
	printf("the word not find\n\n");
	free(input);

}


void CpyDictinaryTest(void)
{
	hash_function hash_func = &DictHash;
	is_match_func cmp_func = &DictCmp;
	hash_table_ty *hash_table = HashTableCreate(hash_func, cmp_func, 500);	
	
	const size_t dict_len = DICT_SIZE ;
	char **dict_buff = (char**)calloc(dict_len + 1 , sizeof(char*));
	char *dict_word = (char*)calloc(MAX_SIZE_WORD , sizeof(char));
	size_t i = 0;
	FILE *dict = fopen("/usr/share/dict/words" , "r");
	
	for( ; i < dict_len ; ++i) 
	{
		fgets(dict_word, MAX_SIZE_WORD, dict);
		dict_buff[i] = (char*)calloc(strlen(dict_word) , sizeof(char));
		strncpy(dict_buff[i] , dict_word , strlen(dict_word) - 1);
	}
	fclose(dict);
	
	for(i = 0 ; i < dict_len ; ++i)
	{
		HashTableInsert(hash_table , dict_buff[i]);
	}
	assert(DICT_SIZE == HashTableSize(hash_table));
	SpellChecker(hash_table);
	
	FreeDict(dict_buff , dict_len);
	free(dict_word);
	HashTableDestroy(hash_table);
}





void HasTableLoadTest(void){}
void HashTableSDTest(void){}


size_t ModuleIndex(const void *data)
{
	assert(NULL != data);
	return (*(int*)data % 30);
}

size_t DictHash(const void *data)
{ 
	unsigned int hash_key= 0;
	int counter = 0;
	/*printf("%s\n" , (char*)data);*/
    for ( ; ((char*)data)[counter]!= '\0'; counter++)
    {
        hash_key = (hash_key * ((char*)data)[counter] + ((char*)data)[counter] + counter) % 500;
    }
    return hash_key;
}

int DictCmp(const void *hash_word, void *user_word)
{
	assert(NULL != hash_word);
	assert(NULL != user_word);
	return (0 == strcmp((char*)hash_word , (char*)user_word));	
}

int IdCmp(const void *hash_id, void *user_id)
{
	assert(NULL != hash_id);
	assert(NULL != user_id);	
	return *(int*)hash_id == *(int*)user_id;
}


int AddThirty(void *data , void *null)
{
	(void)null;
	assert(NULL != data);
	*(int*)data += 30;
	return 0;
}


















