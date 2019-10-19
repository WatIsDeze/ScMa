#ifndef BASEMODEL_H
#define BASEMODEL_H

namespace entities {
    namespace classes {

        // The base entity class for any model. (This could be a tree, or even doors and other interactive items.)
        // NOTE: Never change its type, it is MAPMODEL for a reason.
        class BaseModel : public BaseEntity {
            ENTITY_FACTORY_IMPL(BaseMapModel);
        public:
            BaseModel();
            BaseModel(const std::string &filename);
            virtual ~BaseModel();

            virtual void preload();
            virtual void think();
            virtual void render();

            //
            // onSet/Get/Function functions.
            //
            virtual void onAttributeSet(const std::string &key, const std::string &value);
            virtual void onAnimate(int &anim, int &basetime);

            int model_flags;

        private:
            void loadModelAttributes();

        public:
            void preloadMapModel(const std::string &filename);
        };
    } // classes
} // entities

#endif // BASEMODEL_H
