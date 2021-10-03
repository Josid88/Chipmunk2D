// INCLUDE IN: cpShape.h:51
// Replace cpShapeFilterInit in function cpShapeInit in cpShapeInit.c:46
#ifndef CHIPMUNK_SHAPE_FILTER_H
#define CHIPMUNK_SHAPE_FILTER_H

#include "../chipmunk.h"


typedef struct ccpLayerFilter {
    cpBool isActive;
    cpBitmask currentLayers;
    cpBitmask ignoreLayers;
    cpBool checkAllEquals;
    cpBool isLayerChanger;
    cpBool isOnLayerChanger;
    cpBitmask layerChangerKey;
} ccpLayerFilter;

#ifndef CCP_LAYER_FILTER_DEFAULT_MACRO
#define CCP_LAYER_FILTER_DEFAULT_MACRO {cpFalse, 0, 0, cpFalse, cpFalse, cpFalse, 0}
#endif
static const ccpLayerFilter CCP_LAYER_FILTER_DEFAULT = CCP_LAYER_FILTER_DEFAULT_MACRO;

/// Fast collision filtering type that is used to determine if two objects collide before calling collision or query callbacks.
typedef struct cpShapeFilter {
    /// Two objects with the same non-zero group value do not collide.
    /// This is generally used to group objects in a composite object together to disable self collisions.
    cpGroup group;
    /// A bitmask of user definable categories that this object belongs to.
    /// The category/mask combinations of both objects in a collision must agree for a collision to occur.
    cpBitmask categories;
    /// A bitmask of user definable category types that this object object collides with.
    /// The category/mask combinations of both objects in a collision must agree for a collision to occur.
    cpBitmask mask;
	/// Layer Filter
    ccpLayerFilter layerFilter;
} cpShapeFilter;

/// Collision filter value for a shape that will collide with anything except CP_SHAPE_FILTER_NONE.
static const cpShapeFilter CP_SHAPE_FILTER_ALL = {CP_NO_GROUP, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES, CCP_LAYER_FILTER_DEFAULT_MACRO};
/// Collision filter value for a shape that does not collide with anything.
static const cpShapeFilter CP_SHAPE_FILTER_NONE = {CP_NO_GROUP, ~CP_ALL_CATEGORIES, ~CP_ALL_CATEGORIES, CCP_LAYER_FILTER_DEFAULT_MACRO};

/// Create a new collision filter.
static inline cpShapeFilter
cpShapeFilterNew(cpGroup group, cpBitmask categories, cpBitmask mask)
{
    cpShapeFilter filter = {group, categories, mask, CCP_LAYER_FILTER_DEFAULT};	
	return filter;
}

static inline void
cpShapeFilterInit(cpShapeFilter* filter)
{
    filter->group = CP_NO_GROUP;
    filter->categories = CP_ALL_CATEGORIES;
    filter->mask = CP_ALL_CATEGORIES;
    filter->layerFilter = CCP_LAYER_FILTER_DEFAULT;
}


#endif
