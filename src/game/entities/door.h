#ifndef DOOR_H
#define DOOR_H

#include "basemapmodel.h"

namespace entities {
    namespace classes {
        class Door : public BaseMapModel {
        public:
            Door();
            virtual ~Door();

            void preload();
            void think();
            void render();

            bool onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir);
            bool onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir);

            void onAttributeSet(const std::string &key, const std::string &value);
            void onAnimate(int &anim, int &basetime);

        private:

        };
    } // classes
} // entities

#endif // DOOR_H
