#ifndef BASEMAPMODELENTITY_H
#define BASEMAPMODELENTITY_H

namespace entities {
    namespace classes {

        // The base entity class for any model. (This could be a tree, or even doors and other interactive items.)
        // NOTE: Never change its type, it is MAPMODEL for a reason.
        class BaseMapModelEntity : public BaseEntity {
        public:
            BaseMapModelEntity(const std::string &filename);
            virtual ~BaseMapModelEntity();

            virtual void preload();
            virtual void think();
            virtual void render();

        public:
            void preloadMapModel(const std::string &filename);
        };
    } // classes
} // entities

#endif // BASEMAPMODELENTITY_H
