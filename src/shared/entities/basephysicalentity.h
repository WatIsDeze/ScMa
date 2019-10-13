#pragma once
#include "baseentity.h"

namespace entities
{
    namespace classes {
        // PhysicalEntity: Used for objects such as crates, etc.
        class BasePhysicalEntity : public BaseEntity
        {
			ENTITY_FACTORY_IMPL(BasePhysicalEntity);
        public:
            //
            // Core physent functions.
            //
            BasePhysicalEntity();
            ~BasePhysicalEntity();


            //
            // Core BasePhysicalEntity functions.
            //
            // Resets the interpolation of the physical entity. (Ensures it is at the proper position in the next frame.)
            void resetinterp();

            // Reset the entity to its basic states. Keep in mind that BaseEntity::reset or CoreEntity::reset
            // need to be called by yourself if you wish to reset their state variables as well.
            virtual void reset();

            // Returns a feet position vector of the feet, with an offset.
            vec feetpos(float offset) const;
            // Returns a head position vector of the feet, with an offset.
            vec headpos(float offset) const;

            // Returns true while crouched, false if not.
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

