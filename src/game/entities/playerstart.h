#ifndef PLAYERSTART_H
#define PLAYERSTART_H

namespace entities {
    namespace classes {
        class PlayerStart : public BasePhysicalEntity {
        public:
            PlayerStart();
            PlayerStart(const PlayerStart &) = default;
            virtual ~PlayerStart();

            void preload();
            void think();
            void render();

        private:

        };
    } // classes
} // entities

#endif // PLAYERSTART_H
