#ifndef BASEMONSTER_H
#define BASEMONSTER_H
#include "shared/entities/baseentity.h"

namespace entities {
    namespace classes {
        class BaseMonster : public BaseEntity {
        public:
            BaseMonster();
            virtual ~BaseMonster();

            void preload();
            void think();
            void render();

            //
            // Entity Factory functions.
            //
            static CoreEntity* factory();

        private:

        };
    } // classes
} // entities

#endif // BASEMONSTER_H
