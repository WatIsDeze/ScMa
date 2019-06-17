#ifndef BASEENTITY_H
#define BASEENTITY_H

namespace entities {
    namespace classes {
        class BaseEntity : public gameentity {
        public:
            BaseEntity();
            virtual ~BaseEntity();

            virtual void preload();
            virtual void think();

        private:

        };
    } // classes
} // entities

#endif // BASEENTITY_H
