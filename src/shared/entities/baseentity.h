#ifndef BASEENTITY_H
#define BASEENTITY_H

// Defined here, for several reasons, since it has to replace good ol' extentity.
namespace entities
{
    namespace classes {
        class BaseEntity : public dynent {
        public:
            BaseEntity();
            virtual ~BaseEntity();

            //
            // Base functions.
            //
            // Called every time a map is being loaded.
            virtual void preload();

            // Called each frame, to "think", AI logic should go here.
            virtual void think();

            // Called each frame to render.
            virtual void render();

            //
            // Attribute commands/events.
            //
            virtual void setAttribute(const std::string &key, const std::string &value, bool callAttrSet);
            virtual std::string getAttribute(const std::string &key);
            virtual void onAttributeSet(const std::string &key, const std::string &value);

            //
            // Trigger and touch commands.
            //
            // ent = the entity which has triggered you.
            virtual bool onTrigger(BaseEntity *otherEnt, const vec &dir);
            // ent = the entity which has touched you.
            virtual bool onTouch(BaseEntity *otherEnt, const vec &dir);


        public:
            //
            // Core BaseEntity data.
            //
            // Entity Name. (Used for trigger events.)
            std::string name;
            // Entity class name. (Used to spawn the proper inheritance class instance.)
            std::string classname;

            // Contains the json attributes.
            std::map<std::string, std::string> attributes;

        // Taken from what was called before, gameentity.
        public:
            int flags;
            BaseEntity *attached; // (this used to be extentity* attached;

            bool spawned() const { return (flags & EF_SPAWNED) != 0; }
            void setspawned(bool val) { if(val) flags |= EF_SPAWNED; else flags &= ~EF_SPAWNED; }
            void setspawned() { flags |= EF_SPAWNED; }
            void clearspawned() { flags &= ~EF_SPAWNED; }
        };
    } // classes
} // entities

#endif // BASEENTITY_H
