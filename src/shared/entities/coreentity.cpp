#include "cube.h"
#include "ents.h"
#include "game.h"
#include "ents.h"
#include "baseentity.h"
#include "coreentity.h"
#include "entityfactory.h"

namespace entities {
namespace classes {

//
// Spawned set get clear functions.
//
bool CoreEntity::spawned() const {
    return (flags&entities::EntityFlags::EF_SPAWNED) != 0;
}
void CoreEntity::setspawned(bool val) {
    if(val)
        flags |= entities::EntityFlags::EF_SPAWNED;
    else
        flags &= ~entities::EntityFlags::EF_SPAWNED;
}
void CoreEntity::setspawned() {
    flags |= entities::EntityFlags::EF_SPAWNED;
}
void CoreEntity::clearspawned() {
    flags &= ~entities::EntityFlags::EF_SPAWNED;
}

//
// Attributes set and get.
//
// Sets the key its value in the attributes list, also determines whether to automatically call onAttributeSet.
// Returns true in case it did not exist, returns false in case it already existed.
bool CoreEntity::setAttribute(const std::string &key, const std::string &value, bool callAttrSet) {
    bool retval = true;

    // Determine if it exists.
    if (attributes.find(key) != attributes.end())
        retval = false;

    // Set the value even if it did not exist.
    attributes[key] = value;

    // Call onAttributeSet event if demanded for.
    if (callAttrSet == true)
        onAttributeSet(key, value);

    return retval;
}

std::string CoreEntity::getAttribute(const std::string &key) {
    if (attributes.find(key) != attributes.end()) {
        return attributes[key];
    } else {
       return std::string();
    }
}

void CoreEntity::reset() {
    o = vec(0, 0, 0);
    attr1 = attr2 = attr3 = attr4 = attr5 = 0;
    et_type = ET_EMPTY;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
    reserved = 0;
    model_idx = 0;
    flags = EntityFlags::EF_NOFLAG;
    attached = nullptr;
    //resetExt(false, false, false);
}

void CoreEntity::resetExt(bool clearName, bool clearClassname, bool clearAttributes) {
    o = vec(0, 0, 0);
    attr1 = attr2 = attr3 = attr4 = attr5 = 0;
    et_type = ET_EMPTY;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
    reserved = 0;
    model_idx = 0;
    flags = EntityFlags::EF_NOFLAG;
    attached = nullptr;

    if (clearAttributes == true)
        attributes.clear();
    if (clearName == true)
        name.clear();
}

void CoreEntity::setName(const std::string &str) {
    name = str;
}

void CoreEntity::toJson(nlohmann::json& document)
{
	document = {
		{"class", currentClassname()},
		{"et_type", et_type},
		{"ent_type", ent_type},
		{"game_type", game_type}
	};
	document[classname] = {
		{"name", name},
		{"o", {
			{"x", o.x},
			{"y", o.y},
			{"z", o.z},
		}},
		{"attr1", attr1},
		{"attr2", attr2},
		{"attr3", attr3},
		{"attr4", attr4},
		{"attr5", attr5},
		{"reserved", reserved},
		{"model_idx", model_idx}
	};
}

void CoreEntity::fromJson(const nlohmann::json& document) {
	try {
        if (document.contains("et_type"))
            et_type = document["et_type"];
        else
            conoutf(CON_ERROR, "Failed to load JSON element et_type in class %s and map %s", classname.c_str(), game::getclientmap());

		ent_type = document["ent_type"];
		game_type = document["game_type"];
		
        if (document.contains(classname) && document[classname].is_string())
		{
            std::string json_name = "-- unset --";

            // Fetch our sub document for this specific classname.
            auto &subDoc = document[classname];

            // Determine whether it contains a name value, if so, assign it.
            if (subDoc.contains("name")) {
                name = subDoc["name"];
            } else {
                conoutf(CON_WARN, "Entity %s : %s in map %s is lacking member 'name", classname.c_str(), name.c_str(), game::getclientmap());
            }

            // Load in the origin.
            if (subDoc.contains("o")) {
                auto &oDoc = subDoc["o"];
                o.x = oDoc["x"];
                o.y = oDoc["y"];
                o.z = oDoc["z"];
            } else {
                conoutf(CON_WARN, "Entity %s : %s in map %s is lacking member 'o'", classname.c_str(), name.c_str(), game::getclientmap());
            }
			
            // Load in the attributes.
			attr1 = subDoc["attr1"];
			attr2 = subDoc["attr2"];
			attr3 = subDoc["attr3"];
			attr4 = subDoc["attr4"];
			attr5 = subDoc["attr5"];
			
			reserved = subDoc["reserved"];
			model_idx = subDoc["model_idx"];
		}
	}
	catch(nlohmann::json::type_error& e)
	{
		conoutf(CON_ERROR, "Unable to parse json into CoreEntity: %s", e.what());
	}
	catch(nlohmann::json::out_of_range& e)
	{
		conoutf(CON_ERROR, "Unable to parse json into CoreEntity: %s", e.what());
	}
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY(CoreEntity, "core_entity");
