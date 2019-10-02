#ifndef PLAYER_H
#define PLAYER_H

namespace entities {
    namespace classes {
        class Player : public entities::classes::BaseDynamicEntity {
        public:
            Player();
            virtual ~Player();

            void preload();
            void think();
            void render();

            void reset();
            void respawn();

            bool onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir);
            bool onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir);

            entities::classes::BasePhysicalEntity *camera;
        private:

        };
    } // classes
} // entities

#endif // PLAYER_H
