#ifndef COREENTITY_H
#define COREENTITY_H

#include "cube.h"

namespace entities {
    // Classes.
    namespace classes {
        class BaseEntity;
    //        // Entity
    //        o(0, 0, 0), attr1(0), attr2(0), attr3(0), attr4(0), attr5(0), et_type(ET_EMPTY), ent_type(ENT_INANIMATE), game_type(GAMEENTITY), reserved(0), model_idx(0),

    //        // Dynent.
    //        blocked(false), ragdoll(NULL), query(NULL), lastrendered(0),

    //        // Physent.
    //        deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(25),
    //                   radius(2.4), eyeheight(7), maxheight(8), aboveeye(2), xradius(1.67), yradius(1.67), zmargin(0),
    //                   state(CS_ALIVE), editstate(CS_ALIVE),
    //                   collidetype(COLLIDE_ELLIPSE)

        // Core legacy entity class.
        class CoreEntity
        {
        public:
            CoreEntity();
            virtual ~CoreEntity();

            //
            // Legacy Core Entity data.
            //
            vec o {0.0f, 0.0f, 0.0f};       // position
            short attr1 = 0;
            short attr2 = 0;
            short attr3 = 0;
            short attr4 = 0;
            short attr5 = 0;
            uchar et_type = ET_EMPTY;       // These are for the ET(Engine Type) values.
            uchar ent_type = ENT_INANIMATE; // These are for ENT_(DynEnt/PhysEnt Type) values.
            uchar game_type = GAMEENTITY;   // the internal game entity type values.
            uchar reserved = 0;
            short model_idx = 0;

            //
            // Legacy Core ExtEntity data and functions.
            //
            int flags = EntityFlags::EF_NOFLAG;
            BaseEntity *attached = nullptr;

            bool spawned() const;
            void setspawned(bool val);
            void setspawned();
            void clearspawned();

            //
            // onEvent functions.
            //
            // Can be overloaded to execute certain actions when the key/value of an attribute is changed.
            virtual void onAttributeSet(const std::string &key, const std::string &value) {}

            //
            // Attributes set and get.
            //
            // Sets the key its value in the attributes list, also determines whether to automatically call onAttributeSet.
            bool setAttribute(const std::string &key, const std::string &value, bool callOnAttrSet);
            // Returns the value of the attribute key.
            std::string getAttribute(const std::string &key);

            //
            // CoreEntity virtual functions.
            //
            virtual void reset();
            virtual void resetExt(bool clearName = true, bool clearClassname = true, bool clearAttributes = true);

        public:
            //
            // CoreEntity data.
            //
            // Entity Name. (Used for trigger events.)
            std::string name = "coreentity_unnamed";
            // Entity class name. (Used to spawn the proper inheritance class instance.)
            std::string classname = "CoreEntity";
            // Contains the json attributes.
            std::map<std::string, std::string> attributes = {};

        protected:
            //
            // CoreEntity utility functions.
            //
            void setName(const std::string &str = "coreentity") {
                name = str + "_" + std::to_string(entities::getents().length());

				// Do not forget to store it in our attributes list, so it can be saved to disk.
				setAttribute("name", name, false);
			}
            void setClassName(const std::string &str = "CoreEntity") {
				// Store classname.
				classname = str;

				// Do not forget to store it in our attributes list, so it can be saved to disk.
				setAttribute("classname", classname, false);
            }
        };
    } // classes
} // entities

#endif
