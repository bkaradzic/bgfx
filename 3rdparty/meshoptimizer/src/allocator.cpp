#include "meshoptimizer.h"

void meshopt_setAllocator(void* (*allocate)(size_t), void (*deallocate)(void*))
{
	meshopt_Allocator::Storage::allocate = allocate;
	meshopt_Allocator::Storage::deallocate = deallocate;
}
