#ifndef DYNAMICLIGHT_H
#define DYNAMICLIGHT_H

namespace entities {
    namespace classes {
        class DynamicLight : public BaseEntity {
        public:
            DynamicLight();
            virtual ~DynamicLight();

            void preload();
            void think();

        private:

        };
    } // classes
} // entities

#endif // DYNAMICLIGHT_H
