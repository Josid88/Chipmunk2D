// INCLUDE IN: chipmunk_private.h:144
#ifndef CHIPMUNK_SHAPE_FILTER_REJECT_H
#define CHIPMUNK_SHAPE_FILTER_REJECT_H


#include "../chipmunk.h"

static inline cpBool
cpShapeFilterReject(cpShapeFilter a, cpShapeFilter b)
{
	// Reject the collision if:
	return (
		// They are in the same non-zero group.
		(a.group != 0 && a.group == b.group) ||
		// One of the category/mask combinations fails.
		(a.categories & b.mask) == 0 ||
		(b.categories & a.mask) == 0
	);
}


#endif
