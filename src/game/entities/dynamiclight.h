#ifndef DYNAMICLIGHTX_H
#define DYNAMICLIGHTX_H

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

            void setState(const DynamicLight::DYNAMIC_LIGHT_STATE &state);

        public:
            // Stores the current state of the dynamic light.
            DynamicLight::DYNAMIC_LIGHT_STATE lightState;

            // Obviously speaks for itself, the color.
            vec4 lightColor;
        };
    } // classes
} // entities

#endif // DYNAMICLIGHT_H
