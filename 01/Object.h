#ifndef	OBJECT_H
#define	OBJECT_H

/*
 * Why do we describe it as extern?
 */
extern const void * Object;		/* new(Object); */

int differ (const void * a, const void * b);

#endif
