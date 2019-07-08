#ifndef BASEMONSTER_H
#define BASEMONSTER_H

namespace entities {
    namespace classes {
        class BaseMonster : public BaseEntity {
        public:
            BaseMonster();
            virtual ~BaseMonster();

            void preload();
            void think();
            void render();

        private:

        };
    } // classes
} // entities

#endif // BASEMONSTER_H
