#ifndef PLAYER_H
#define PLAYER_H
#include "shared/entities/basedynamicentity.h"

struct vec;

namespace entities {
    namespace classes {
        class Player : public BaseDynamicEntity {
        public:
			//
			// Constructors/Destructor.
			//
            Player();
            virtual ~Player();

			//
			// Base/Core entity functions.
			//
            void preload();
            void think();
            void render();

			//
			// Entity functions.
			//
            void reset();
            void respawn();

			//
			// onEvent functions.
			//
            bool onTrigger(entities::classes::CoreEntity *otherEnt, const vec &dir);
            bool onTouch(entities::classes::CoreEntity *otherEnt, const vec &dir);

			//
			// Entity member variables.
			//
            entities::classes::BasePhysicalEntity *camera;
			
            //
            // Entity Factory functions.
            //
            static CoreEntity* factory();

        private:

        };
    } // classes
} // entities

#endif // PLAYER_H
