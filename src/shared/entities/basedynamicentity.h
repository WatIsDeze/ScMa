#ifndef BASEDYNAMICENTITY_H
#define BASEDYNAMICENTITY_H

struct occludequery;
struct ragdolldata;

namespace entities
{
    namespace classes {
        // Predefined.
        class BasePhysicalEntity;
        // Animated Characters, which can possibly receive input
        class BaseDynamicEntity : public BasePhysicalEntity
        {
        public:
            //
            // Core dynent functions.
            //
            BaseDynamicEntity();
            BaseDynamicEntity(const BaseDynamicEntity&) = default;
            virtual ~BaseDynamicEntity();

            // Reset to basic state values.
            void reset();

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

#endif // BASEDYNAMICENTITY_H
