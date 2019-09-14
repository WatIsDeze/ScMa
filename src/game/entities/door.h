#ifndef DOOR_H
#define DOOR_H

#include "basemapmodelentity.h"

namespace entities {
    namespace classes {
        class Door : public BaseMapModelEntity {
        public:
            Door();
            virtual ~Door();

            void preload();
            void think();
            void render();

            bool onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir);
            bool onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir);

        private:

        };
    } // classes
} // entities

#endif // DOOR_H
