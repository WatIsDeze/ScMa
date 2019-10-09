#ifndef BASEPHYSICALENTITY_H
#define BASEPHYSICALENTITY_H

#include "baseentity.h"

namespace entities
{
    namespace classes {
        // PhysicalEntity: Used for objects such as crates, etc.
        class BasePhysicalEntity : public BaseEntity
        {
        public:
            //
            // Core physent functions.
            //
            BasePhysicalEntity();
            ~BasePhysicalEntity();

            void resetinterp();
            void reset();

            vec feetpos(float offset) const;
            vec headpos(float offset) const;

            bool crouched() const;

            //
            // Physics variables.
            //
            vec vel, falling;                               // velocity, falling
            vec deltapos, newpos;                           // movement interpolation
            float yaw, pitch, roll;
            float maxspeed;                                 // cubes per second, 100 for player
            int timeinair;
            float radius, eyeheight, maxheight, aboveeye;   // bounding box size
            float xradius, yradius, zmargin;
            vec floor;                                      // the normal of floor the dynent is on

            //
            // Physical state values.
            //
            int inwater;
            bool jumping;
            char move, strafe, crouching;

            uchar physstate;            // one of PHYS_* above
            uchar state, editstate;     // one of CS_* above
            uchar collidetype;          // one of COLLIDE_* above

            bool blocked;               // used by physics to signal ai
        };
    } // classes
} // entities

#endif // BASEPHYSICALENTITY_H
