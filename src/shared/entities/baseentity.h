#ifndef BASEENTITY_H
#define BASEENTITY_H

// Defined here, for several reasons, since it has to replace good ol' extentity.
namespace entities
{
    namespace classes {
        // Predefined.
        class CoreEntity;
        class BasePhysicalEntity;
        class BaseDynamicEntity;

        class BaseEntity : public CoreEntity {
        public:
            //
            // Base functions.
            //
            BaseEntity();
//            BaseEntity(const CoreEntity& e);
//            BaseEntity(const BaseEntity& e);
//            BaseEntity(const BasePhysicalEntity *e);
//            BaseEntity(const BaseDynamicEntity *e);
//            virtual ~BaseEntity();

            // Called every time a map is being loaded.
            virtual void preload();
            // Called each frame, to "think", AI logic should go here.
            virtual void think();
            // Called each frame to render.
            virtual void render();
            // Reset the entity to its basic states.
            virtual void reset();

            //
            // OnEvent callbacks.
            //
            // otherEnt = the entity which has triggered you.
            virtual bool onTrigger(BaseEntity *otherEnt, const vec &dir);
            // otherEnt = the entity which has touched you.
            virtual bool onTouch(BaseEntity *otherEnt, const vec &dir);
            // Can be overloaded to execute certain actions when the key/value of an attribute is changed.
            virtual void onAttributeSet(const std::string &key, const std::string &value);

            //
            // Attributes set and get.
            //
            // Sets the key its value in the attributes list, also determines whether to automatically call onAttributeSet.
            bool setAttribute(const std::string &key, const std::string &value, bool callOnAttrSet);
            // Returns the value of the attribute key.
            std::string getAttribute(const std::string &key);
        };
    } // classes
} // entities

#endif // BASEENTITY_H
