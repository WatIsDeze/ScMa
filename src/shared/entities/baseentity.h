#ifndef BASEENTITY_H
#define BASEENTITY_H
#include "coreentity.h"

// Defined here, for several reasons, since it has to replace good ol' extentity.
namespace entities
{
    namespace classes {
        // Predefined.
        class BasePhysicalEntity;
        class BaseDynamicEntity;

        class BaseEntity : public CoreEntity
        {
        public:
            //
            // Base functions.
            //
            BaseEntity();
            virtual ~BaseEntity();
//            BaseEntity(const CoreEntity& e);
//            BaseEntity(const BaseEntity& e);
//            BaseEntity(const BasePhysicalEntity *e);
//            BaseEntity(const BaseDynamicEntity *e);
//            virtual ~BaseEntity();

            // Called every time a map is being loaded.
            virtual void preload();
            // Called each frame, to "think", AI logic should go here.
            virtual void think();
            // Called each frame to render.
            virtual void render();
            // Reset the entity to its basic states.
            virtual void reset();

            //
            // OnEvent callbacks.
            //
            // Can be used to call functions given on which key changed into what value.
            virtual void onAttributeSet(const std::string &key, const std::string &value);
            // otherEnt = the entity which has triggered you.
            virtual bool onTrigger(BaseEntity *otherEnt, const vec &dir);
            // otherEnt = the entity which has touched you.
            virtual bool onTouch(BaseEntity *otherEnt, const vec &dir);
			
            static CoreEntity* factory();
        };
    } // classes
} // entities

#endif // BASEENTITY_H
