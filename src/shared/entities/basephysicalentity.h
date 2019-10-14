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

            void resetinterp();

            vec feetpos(float offset) const;
            vec headpos(float offset) const;

            bool crouched() const;

            vec deltapos = vec(0, 0, 0);
            vec newpos = vec(0, 0, 0);
            float yaw = 0.0f;
            float pitch = 0.0f;
            float roll = 0.0f;
            float maxspeed = 25.0f;
            float radius = 2.4;
            float eyeheight = 7.0f;
            float maxheight = 8.0f;
            float aboveeye = 2.0f;
            float xradius = 1.67;
            float yradius = 1.67;
            float zmargin = 0;
            
			int inwater = 0;
			int timeinair = 0;
			bool jumping = false;
			char strafe = 0;
			char move = 0;
			char crouching = 0;
			uchar physstate = PHYS_FALL;
			vec vel = vec(0, 0, 0);
			vec falling = vec(0, 0, 0);
			vec floor = vec(0, 0, 1);
            uchar state = CS_ALIVE;
            uchar editstate = CS_ALIVE;
            uchar collidetype = COLLIDE_ELLIPSE;

            bool blocked = false;
        };
    } // classes
} // entities

