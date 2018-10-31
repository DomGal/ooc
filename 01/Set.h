#ifndef	SET_H
#define	SET_H

extern const void * Set;

/*
 * How can we encode exit status with void * - return NULL when fails
 */
void * add (void * set, const void * element);
void * find (const void * set, const void * element);
void * drop (void * set, const void * element);
int contains (const void * set, const void * element);
unsigned count (const void * set);

#endif
