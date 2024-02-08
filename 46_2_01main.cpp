#include <iostream>
#include "os_mem.h"

using namespace std;

int main()
{
	memory_manager_t mm;
	setup_memory_manager(&mm);
	mm.create(150, 1); //expected: 1, passed
	mm.alloc(1); //expected: mem_handle_t(0, 32), passed
	mm.alloc(1); //expected: mem_handle_t(32, 32), passed
	mm.alloc(1); //expected: mem_handle_t(64, 32), passed
	mm.print_blocks();
	mm.alloc(1); //expected: mem_handle_t(96, 32), passed
	mm.alloc(1); //expected: mem_handle_t(0, 0), passed
	mm.free(mem_handle_t(0, 1));// expected: 1, passed
	mm.free(mem_handle_t(0, 1));// expected: 1, passed
	mm.free(mem_handle_t(0, 1)); //expected: 1, passed
	mm.alloc(1);// expected: mem_handle_t(32, 32), passed
	mm.alloc(1);// expected: mem_handle_t(64, 32), passed
	mm.alloc(1);// expected: mem_handle_t(96, 32), passed
	mm.alloc(1);// expected: mem_handle_t(0, 0), passed

	cout << "get_max_block_size: " << mm.get_max_block_size() << endl;// expected: 0, failed
	mm.print_blocks();
	mm.destroy();
	return 0;
}