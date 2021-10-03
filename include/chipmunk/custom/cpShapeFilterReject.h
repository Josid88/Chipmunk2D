// INCLUDE IN: chipmunk_private.h:144
#ifndef CHIPMUNK_SHAPE_FILTER_REJECT_H
#define CHIPMUNK_SHAPE_FILTER_REJECT_H

#include "../chipmunk.h"


static inline cpBool
cpShapeFilterReject(const cpShapeFilter a, const cpShapeFilter b)
{
    // Reject the collision if:
    return (cpBool) (
               (
                   // They are in the same non-zero group OR...
                   (a.group != 0 && a.group == b.group)
                   // One of the category/mask combinations fails.
                   || ((a.categories & b.mask) == 0 || (b.categories & a.mask) == 0)
               ) || (
                   // Contains layer filter and...
                   (a.layerFilter.isActive && b.layerFilter.isActive)
                   // Current layers are not equals and ...
                   && (a.layerFilter.currentLayers != b.layerFilter.currentLayers)
                   && (
                       // check layer equality
                       (a.layerFilter.checkAllEquals || b.layerFilter.checkAllEquals)
                       // or not in the same layer
                       || ((a.layerFilter.currentLayers & b.layerFilter.currentLayers) == 0)
                       // or
                       || (
                           // A ignores B
                           ((a.layerFilter.ignoreLayers & b.layerFilter.currentLayers) != 0)
                           // And if NOT (B is layer changer and A is on layer changer and both have same keys)
                           && !(b.layerFilter.isLayerChanger && a.layerFilter.isOnLayerChanger && ((a.layerFilter.layerChangerKey & b.layerFilter.layerChangerKey) != 0))
                       )
                       // or
                       || (
                           // B ignores A
                           ((b.layerFilter.ignoreLayers & a.layerFilter.currentLayers) != 0)
                           // And if NOT (A is layer changer and B is on layer changer and both have same keys
                           && !(a.layerFilter.isLayerChanger && b.layerFilter.isOnLayerChanger && ((a.layerFilter.layerChangerKey & b.layerFilter.layerChangerKey) != 0))
                       )
                   )
               )
           );
}


#endif
