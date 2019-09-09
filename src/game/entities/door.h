#ifndef DOOR_H
#define DOOR_H

namespace entities {
    namespace classes {
        class Door : public BaseEntity {
        public:
            Door();
            virtual ~Door();

            void preload();
            void think();
            void render();

        private:

        };
    } // classes
} // entities

#endif // DOOR_H
