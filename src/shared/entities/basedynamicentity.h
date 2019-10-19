#pragma once
#include "animinfo.h"
#include "basephysicalentity.h"

struct occludequery;
struct ragdolldata;

namespace entities
{
    namespace classes {

        class BaseDynamicEntity : public BasePhysicalEntity
        {
        public:
            void stopmoving();
            vec abovehead();
            
            bool k_left = false;
            bool k_right = false;
            bool k_up = false;
            bool k_down = false;
            animinterpinfo animinterp[MAXANIMPARTS] { 0 };
            ragdolldata *ragdoll = nullptr;
            occludequery *query = nullptr;
            int lastrendered = -1;
        };
    } // classes
} // entities
