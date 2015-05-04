#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>



typedef struct block_t	block_t;

struct block_t{

	size_t size; /*size including block_t*/
	block_t* next;	/*next block if exists, otherwise NULL*/
	bool free;
};


#define META_SIZE = sizeof(block_t);

static block_t* global_memory = NULL;
//static void* global_mem_ptr = NULL;


void split_block(block_t* block, size_t size)
{
	if(block->size > (size+META_SIZE))
	{
		block_t* new_block = ((void*)block)+size;
		new_block->free = true;
		new_block->next = block->next;
		new_block->size = block->size - size;

		block->size = size;
		block->next = new_block;
	}
}

block_t* exists_block(block_t** last,size_t size)
{
	block_t* block = global_memory;
	while(block)
	{
		if(block->free && block->size >= size)
		{
			block->free = false;
			return block;
		}
		*last = block;
		block = block->next;

	}
	return NULL;
}

block_t* extend_memory(block_t* last,size_t size)
{

	block_t* new_block = sbrk(size);

	if(new_block == (void*) -1)
		return NULL; //sbrk failed


	new_block->size = size;
	new_block->next = NULL;
	new_block->free = false;


	if(!last)	
		global_memory = new_block;
	else
		last->next = new_block;

	return new_block;
}



void* malloc(size_t size)
{

	if(!global_memory)
	{
		return (extend_memory(NULL,size+META_SIZE)+1);
	}
	else
	{
		block_t* last;
		block_t* block = exists_block(&last,size+META_SIZE);
		if(block)
		{
			split_block(block,size+META_SIZE);
			return block;
		}
		else
		{
			return (extend_memory(last,size+META_SIZE)+1)
		}
	}
}