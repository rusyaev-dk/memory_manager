#include <stdio.h>
#include "os_mem.h"

int GL_MEMORY_SIZE = 0;
int GL_FREE_MEMORY = 0;
int GL_CUR_BLOCKS_COUNT = 0;
mem_handle_t** GL_STACK_ARR = NULL;


int my_create(int size, int num_pages)
{
	if (GL_MEMORY_SIZE != 0)
	{
		return 0;
	}
	mem_handle_t** buffer = (mem_handle_t**)malloc(sizeof(mem_handle_t*) * (size / 32));
	if (!buffer)
	{
		return 0;
	}
	GL_STACK_ARR = buffer;

	GL_MEMORY_SIZE = size;
	GL_FREE_MEMORY = size;
	return 1;
}

int my_destroy()
{
	if (!GL_STACK_ARR || !GL_MEMORY_SIZE)
	{
		return 0;
	}
	for (int i = 0; i < GL_CUR_BLOCKS_COUNT; i++)
	{
		free(GL_STACK_ARR[i]);
	}
	GL_MEMORY_SIZE = 0;
	GL_FREE_MEMORY = 0;
	GL_CUR_BLOCKS_COUNT = 0;
	free(GL_STACK_ARR);
	GL_STACK_ARR = NULL;
	return 1;
}

mem_handle_t my_alloc(int block_size)
{
	if (GL_FREE_MEMORY < 32)
	{
		return { 0, 0 };
	}
	mem_handle_t* buffer = (mem_handle_t*)malloc(sizeof(mem_handle_t));
	if (!buffer)
	{
		return { 0, 0 };
	}
	mem_handle_t* new_mem_block = buffer;
	new_mem_block->addr = GL_CUR_BLOCKS_COUNT * 32;
	new_mem_block->size = 32;

	GL_STACK_ARR[GL_CUR_BLOCKS_COUNT] = new_mem_block;
	GL_CUR_BLOCKS_COUNT += 1;

	GL_FREE_MEMORY -= 32;

	return *new_mem_block;
}

int my_free(mem_handle_t h)
{
	if (GL_CUR_BLOCKS_COUNT == 0)
	{
		return 0;
	}
	free(GL_STACK_ARR[GL_CUR_BLOCKS_COUNT - 1]);
	GL_CUR_BLOCKS_COUNT -= 1;
	GL_FREE_MEMORY += 32;
	return 1;
}

int my_get_max_block_size()
{
	if (GL_FREE_MEMORY / 32 >= 1)
	{
		return 32;
	}
	return 0;
}

int my_get_free_space()
{
	return GL_FREE_MEMORY;
}

void my_print_blocks()
{
	for (int i = 0; i < GL_CUR_BLOCKS_COUNT; i++)
	{
		printf("%d %d\n", GL_STACK_ARR[i]->addr, GL_STACK_ARR[i]->size);
	}
}

void setup_memory_manager(memory_manager_t* mm)
{
	mm->create = my_create;
	mm->destroy = my_destroy;
	mm->alloc = my_alloc;
	mm->free = my_free;
	mm->get_max_block_size = my_get_max_block_size;
	mm->get_free_space = my_get_free_space;
	mm->print_blocks = my_print_blocks;
}