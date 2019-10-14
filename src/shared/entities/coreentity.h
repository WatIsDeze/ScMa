#pragma once

#include "cube.h"
#include "ents.h"
#include "entityfactory.h"
#include <nlohmann/json.hpp>

namespace json_utils
{
	const nlohmann::json getSubobject(const nlohmann::json& document, const std::string& key);
	
	template<typename T>
	bool tryQueryJsonVar(const nlohmann::json& document, const std::string& key, T& value)
	{
		if (document.find(key) != document.end()) {
			try {
				auto jsonValue = document.at(key).get<T>();
				value = jsonValue;
				
				return true;
			}
			catch(nlohmann::json::type_error& e) {
			}
		}
		
		return false;
	}
	
	template<>
	bool tryQueryJsonVar(const nlohmann::json& document, const std::string& key, vec& value);
}


namespace entities {
    // Classes.
    namespace classes {
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
            ENTITY_FACTORY_IMPL(CoreEntity)
        public:
			//Serialization
			void saveToJson(nlohmann::json& document);
			void loadFromJson(const nlohmann::json& document);
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

            virtual void onAttributeSet(const std::string &key, const std::string &value) {}
            virtual std::string onAttributeGet(const std::string &key) { return ""; }
            virtual std::vector<std::string> onAttributeList() { return {}; }
        public:
            //
            // CoreEntity data.
            //
            // Entity Name. (Used for trigger events.)
            std::string name = "coreentity_unnamed";

        protected:
			void fromJson(const nlohmann::json& document);
			nlohmann::json toJson();

            //
            // CoreEntity utility functions.
            //
            // Sets the name of the entity.
            void setName(const std::string &str = "coreentity");
        };
    } // classes
} // entities
