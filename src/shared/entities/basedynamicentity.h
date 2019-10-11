#pragma once
#include "animinfo.h"
#include "basephysicalentity.h"

struct occludequery;
struct ragdolldata;

namespace entities
{
    namespace classes {

        // Animated Characters, which can possibly receive input
        class BaseDynamicEntity : public BasePhysicalEntity
        {
			ENTITY_FACTORY_IMPL(BaseDynamicEntity);
        public:
            //
            // Core dynent functions.
            //
            BaseDynamicEntity();
            BaseDynamicEntity(const BaseDynamicEntity&) = default;
            virtual ~BaseDynamicEntity();

            // Reset to basic state values.
            virtual void reset();

            // Stop moving.
            void stopmoving();

            // Returns above head fv
            vec abovehead();

            //
            // Key input states.
            //
            bool k_left, k_right, k_up, k_down;         // see input code - I think they meant, determine which key is pressed lolol.

            //
            // Rendering data.
            //
            animinterpinfo animinterp[MAXANIMPARTS];
            ragdolldata *ragdoll;
            occludequery *query;
            int lastrendered;
        };
    } // classes
} // entities
