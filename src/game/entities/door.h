#ifndef PLAYER_H
#define PLAYER_H

namespace entities {
    namespace classes {
        class Player : public BaseEntity {
        public:
            Player();
            virtual ~Player();

            void preload();
            void think();
            void render();

        private:

        };
    } // classes
} // entities

#endif // PLAYER_H
