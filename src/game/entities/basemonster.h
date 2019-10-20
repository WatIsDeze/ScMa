#pragma once
#include "shared/entities/baseentity.h"

namespace entities {
    namespace classes {
        class BaseMonster : public BaseEntity {
			ENTITY_FACTORY_IMPL(BaseMonster);
        public:
            BaseMonster();

            void preload();
            void think();
            void render();

        private:

        };
    } // classes
} // entities

