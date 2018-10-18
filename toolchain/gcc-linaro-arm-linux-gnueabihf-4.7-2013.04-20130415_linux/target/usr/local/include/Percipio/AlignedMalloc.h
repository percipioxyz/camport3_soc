#ifndef Foundation_AlignedMalloc_INCLUDED
#define Foundation_AlignedMalloc_INCLUDED

#include <stdlib.h>
#include "Percipio/Foundation.h"


namespace Percipio {


/***************************************************************************** 
* AlignedMalloc 
* 
* This function allocates 'size' bytes (usable by the user) on the heap and 
* takes care of the requested 'alignment'. 
* In order to align the allocated memory block, the xvid_malloc allocates 
* 'size' bytes + 'alignment' bytes. So try to keep alignment very small 
* when allocating small pieces of memory. 
* 
* NB : a block allocated by xvid_malloc _must_ be freed with xvid_free 
*      (the libc free will return an error) 
* 
* Returned value : - NULL on error 
*                  - Pointer to the allocated aligned block 
* 
****************************************************************************/  
void* AlignedMalloc(unsigned int size, unsigned int alignment);

/***************************************************************************** 
* AlignedFree 
* 
* Free a previously 'xvid_malloc' allocated block. Does not free NULL 
* references. 
* 
* Returned value : None. 
* 
****************************************************************************/  
void AlignedFree(void *mem_ptr);

}


#endif
