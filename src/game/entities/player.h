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

            void respawn();

            bool onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir);
            bool onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir);

        private:

        };
    } // classes
} // entities

#endif // PLAYER_H
