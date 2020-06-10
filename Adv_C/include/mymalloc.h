#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__
#include <stddef.h> /*size_t*/

typedef unsigned char BYTE;

/**	
 * @brief init memory before allocation
 * @input _memory - pointer to allocated memory
 * @input _memorySize - initial memory size
 * After initializiation only _memorySize-12 bytes are available for client usage
 **/
void MyMallocInit(void* _memory, size_t _memorySize);

/**
 *@brief allocate memory of given size
 * @input _memory - pointer to allocated memory
 * @input _requiredBlockSize - requested memory size
 * @return Every allocation returns _requiredBlockSize bytes to the client,
 * but reserves _requiredBlockSize+4 bytes from _memory .
*/
void* MyMalloc(void* _memory, size_t _requiredBlockSize);

/**
 *@brief free allocated memory of given pointer
 * @input _myBlock - pointer to allocated memory
 * @warning double free might happen
*/
void MyFree(void* _myBlock);

#endif /* __MYMALLOC_H__ */
