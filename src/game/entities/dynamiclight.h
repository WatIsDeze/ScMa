#ifndef DYNAMICLIGHTX_H
#define DYNAMICLIGHTX_H
#include "shared/entities/basephysicalentity.h"

namespace entities {
    namespace classes {
        class DynamicLight : public BasePhysicalEntity {
        public:
            DynamicLight();
            virtual ~DynamicLight();

            void preload();
            void think();
            void render();

            enum DYNAMIC_LIGHT_STATE {
                ON,
                OFF,
                FLICKERING,
                FADING
            };

            void setState(DynamicLight::DYNAMIC_LIGHT_STATE &state);

        public:
            //
            // Light states.
            //
            // Stores the current state of the dynamic light.
            DynamicLight::DYNAMIC_LIGHT_STATE lightState;

            // Obviously speaks for itself, the color.
            vec4 lightColor;
			
            //
            // Entity Factory functions.
            //
            static CoreEntity* factory();
        };
    } // classes
} // entities

#endif // DYNAMICLIGHT_H
