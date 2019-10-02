#ifndef PLAYERSTART_H
#define PLAYERSTART_H

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

        private:

        };
    } // classes
} // entities

#endif // PLAYERSTART_H
