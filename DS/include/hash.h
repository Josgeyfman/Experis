#ifndef _HASH_H
#define _HASH_H
#include "adt_error.h" /*ERRCODE*/
#include <stddef.h> /*size_t*/

typedef enum HashSet_Result
{
	SET_SUCCESS = 0,

	SET_UNINITIALIZED,
	/** Uninitialized HasSeterror*/
	SET_KEY_DUPLICATE,
	/** Duplicate key error */

	SET_KEY_NOT_FOUND,
	/** Key not found */

	SET_OVERFLOW
	/**No more space in HashSe */ 

} HashSet_Result;

typedef struct Hash Hash;

/** 
 * @brief Hash function to preform operations on hash set
 *
 * @param _data : data to be hashed
 *
 * @return Hash value of data.
 */
typedef size_t (*hashFunction)(int);

/** 
 * @brief Create a Hash set
 * Creates an empty Hash set
 * Worst: time complexity O(sqrt(n)) (find next prime number)
 *
 * @param _hasF: A hash function  that returns Hash value of item in the set
 *				
 * @return a pointer to the newly created Hash set.
 * @retval NULL on failure due to allocation failure or NULL function pointer given
 */
Hash* HashCreate(size_t _size,hashFunction _hasF);

/** 
 * @brief Destroy Hash set
 * Destroys the Hash, freeing the memory.
 *  Worst: time complexity O(1)

 * @params _hash : A previously created Hash set by HashCreate
 */
void HashDestroy(Hash** _hash);

/** 
 * @brief Add an element to Hash set if it's not already there
 * Insert element to Hash set, using the Hash function
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * @param _data: An item to add to the hash
 * @return ERR_SUCCESS if succeeded
 *	   ERR_ILLEGAL_INPUT if wrong input
 *	   ERR_EXISTS if exists in list
 *	   ERR_FULL   if hash is full
 * @warning don't allow duplicates
 */
ERRCODE HashInsert(Hash* _hash, int _data);

/** 
 * @brief Remove an element from Hash set if it's already there
 * Iemove element from Hash set, using the Hash function
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * @param _data: An item to remove from the hash
 * @return ERR_SUCCESS if succeeded
 *	   ERR_ILLEGAL_INPUT if wrong input
 *	   ERR_NOT_EXISTS if not exists in hash
 *	   ERR_EMPTY  if hash is empty
 * @warning don't allow duplicates
 */
ERRCODE HashRemove(Hash* _hash, int _data);

/** 
 * @brief Check if element is in Hash set 
 * check if element is in  Hash set, using the Hash function
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * @param _data: An item to chaeck in the hash
 * @return 1 if is found 
 *	   0 if wrong input
 *	   0 if not exists in hash
 *	   0  if hash is empty
 */
int HashIsFound(const Hash* _hash, int _data);

/** 
 * @brief Check number of elements in Hash set 
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * @return num of elements if succeeded  
 *	   0 if wrong input
 */
size_t HashNumOfItems(const Hash* _hash);

/** 
 * @brief return maximum capacity of Hash set 
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * @return  maximum size if succeeded  
 *	   0 if wrong input
 */
size_t HashCapacity(const Hash* _hash);

/** 
 * @brief return average of rehashes of Hash set 
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * @return average of rehashes if succeeded  
 *	   0 if wrong input
 *         0 if no insertions were made
 */
double HashAverageRehashes(const Hash* _hash);

/** 
 * @brief return maximum number of rehashes of Hash set 
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * @return  maximum number of rehashes if succeeded  
 *	   0 if wrong input
 */
size_t HashMaxReHash(const Hash* _hash);

/** 
 * @brief Print current state  of Hash set 
 * Worst: time complexity O(1)
 *
 * @param _hash : A previously created Hash set by HashCreate
 * 
 */
void HashPrint(const Hash* _hash);


#endif /*_HASH_H*/
