#ifndef PLAYERSTART_H
#define PLAYERSTART_H
#include "shared/entities/baseentity.h"

namespace entities {
    namespace classes {
        class PlayerStart : public BaseEntity {
        public:
            PlayerStart();
            virtual ~PlayerStart();

            void preload();
            void think();
            void render();

            void reset();

			static CoreEntity* factory();
        private:

        };
    } // classes
} // entities

#endif // PLAYERSTART_H
