# **Custom Memory Manager**  

## 📌 **Description**  
This project implements a **simple stack-based memory manager** that manages memory in fixed-size **32-byte blocks**. The manager provides efficient allocation and deallocation functions, keeping track of free and used memory.  

The memory manager is designed as a **replacement for standard memory allocation functions (`malloc/free`)**, offering controlled memory usage through **a predefined memory pool**.  

---

## **🔧 Core Features**  

✔️ **Fixed Block Size Allocation (32 bytes)** – Ensures efficient memory usage  
✔️ **Stack-Based Memory Management** – LIFO (Last In, First Out) allocation strategy  
✔️ **Memory Fragmentation Handling** – Prevents excessive fragmentation  
✔️ **Simple API for Integration** – Easily integrates into existing projects  

---

## **📜 Function Overview**  

| **Function**                          | **Description** |
|----------------------------------------|----------------|
| `my_create(int size, int num_pages)`   | Initializes the memory manager with a given size |
| `my_destroy()`                         | Frees all allocated memory and resets the manager |
| `my_alloc(int block_size)`             | Allocates a 32-byte memory block |
| `my_free(mem_handle_t h)`              | Frees the last allocated memory block |
| `my_get_max_block_size()`              | Returns the maximum block size that can be allocated (always 32 bytes) |
| `my_get_free_space()`                  | Returns the amount of free memory available |
| `my_print_blocks()`                    | Prints the currently allocated memory blocks |
| `setup_memory_manager(memory_manager_t* mm)` | Configures the memory manager in the given structure |

---

## **🚀 How It Works**  

1️⃣ **Initialization (`my_create`)**  
   - Allocates an array (`GL_STACK_ARR`) to track allocated memory blocks.  
   - Initializes global variables for memory size and free space.  

2️⃣ **Memory Allocation (`my_alloc`)**  
   - Allocates a **fixed-size 32-byte block**.  
   - Updates the stack tracker and reduces free memory.  

3️⃣ **Memory Deallocation (`my_free`)**  
   - Frees the **last allocated block** (LIFO order).  
   - Updates the memory counter and restores free space.  

4️⃣ **Destruction (`my_destroy`)**  
   - Frees all allocated memory and resets tracking variables.  
