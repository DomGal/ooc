#include <assert.h>
#include <stdio.h>

#include "new.h"
#include "Set.h"
#include "Object.h"

const void * Set;
const void * Object;

#if ! defined MANY || MANY < 1
#define	MANY	10
#endif

/*
 * heap is static, so we extend it's lifetime and make chain it to Set.c
 * 
 * both set end element are containd on heap
 */
static int heap [MANY];

void * new (const void * type, ...)
{	int * p;							/* & heap[1..] */

/*
 * when new object is created, before it's added to a set we set it's
 * "value" to MANY (that adress held 0 previously indicating it's
 * free)
 * 
 * if newly created object is a set, it holds "value" MANY indicating
 * it's not free (!= 0), also not holding an adress (> heap
 * && < MANY)
 * 
 * we exclued index 0 (using addresses between (heap + 1) and (heap + MANY - 1)) because if it were a set than all free elements
 * would belong to it
 */
	for (p = heap + 1; p < heap + MANY; ++ p)
		if (! * p)
			break;
	assert(p < heap + MANY);
	* p = MANY;
	return p;
}

void delete (void * _item)
{	int * item = _item;

	if (item)		// so if item is not a NULL
	{	assert(item > heap && item < heap + MANY);
		* item = 0;
	}
}

void * add (void * _set, const void * _element)
{	int * set = _set;
	const int * element = _element;

	assert(set > heap && set < heap + MANY);
	assert(* set == MANY);
	assert(element > heap && element < heap + MANY);

	if (* element == MANY)
		* (int *) element = set - heap;
	else
		assert(* element == set - heap);

	return (void *) element;
}

void * find (const void * _set, const void * _element)
{	const int * set = _set;
	const int * element = _element;

	assert(set > heap && set < heap + MANY);
	assert(* set == MANY);	// set must contain "value" MANY
	assert(element > heap && element < heap + MANY);
	assert(* element);
/*
 * Element has value equal to the difference between location of
 * the set it belongs to and the base address of the heap,
 * so we can get address of the set by
 * heap + element
 * */
	return * element == set - heap ? (void *) element : 0;
}

int contains (const void * _set, const void * _element)
{
	return find(_set, _element) != 0;
}

void * drop (void * _set, const void * _element)
{	int * element = find(_set, _element);

	if (element)
		* element = MANY;
	return element;
}

int differ (const void * a, const void * b)
{
	return a != b;
}
