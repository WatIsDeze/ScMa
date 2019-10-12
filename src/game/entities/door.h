#pragma once
#include "basemapmodel.h"

namespace entities {
    namespace classes {
        class Door : public BaseMapModel {
			ENTITY_FACTORY_IMPL(Door);
        public:
            Door();
            virtual ~Door();

            void preload();
            void think();
            void render();

            bool onTrigger(entities::classes::CoreEntity *otherEnt, const vec &dir);
            bool onTouch(entities::classes::CoreEntity *otherEnt, const vec &dir);

            void onAttributeSet(const std::string &key, const std::string &value);
            void onAnimate(int &anim, int &basetime);

        private:

        };
    } // classes
} // entities
