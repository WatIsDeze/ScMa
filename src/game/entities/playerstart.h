#ifndef PLAYERSTART_H
#define PLAYERSTART_H

namespace entities {
    namespace classes {
        class PlayerStart : public BaseEntity {
        public:
            PlayerStart();
            ~PlayerStart();

            void preload();
            void think();

        private:

        };
    } // classes
} // entities

#endif // PLAYERSTART_H
