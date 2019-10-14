#include "cube.h"
#include "ents.h"
#include "game.h"
#include "ents.h"
#include "baseentity.h"
#include "coreentity.h"
#include "entityfactory.h"

const nlohmann::json json_utils::getSubobject(const nlohmann::json& document, const std::string& key)
{
	if (document.find(key) != document.end()){
		const auto& subObject = document.at(key);
		if (subObject.is_object())
		{
			return subObject;
		}
	}
	
	return NULL;
}

template<>
bool json_utils::tryQueryJsonVar(const nlohmann::json& document, const std::string& key, vec& value)
{
	if (document.find(key) != document.end()) {
		try {
			auto obj = document.at(key);
			
			if (obj.is_object())
			{
				json_utils::tryQueryJsonVar(obj, "x", value.x);
				json_utils::tryQueryJsonVar(obj, "y", value.y);
				json_utils::tryQueryJsonVar(obj, "z", value.z);
			}
			
			return true;
		}
		catch(nlohmann::json::type_error& e) {
		}
	}
	
	return false;
}

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

void CoreEntity::setName(const std::string &str) {
    name = str;
}


nlohmann::json CoreEntity::toJson()
{
	return {
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

void CoreEntity::saveToJsonImpl(nlohmann::json& document)
{
	document[classname] = toJson();
}


void CoreEntity::saveToJson(nlohmann::json& document)
{
	document = {
		{"class", currentClassname()},
		{"et_type", et_type},
		{"ent_type", ent_type},
		{"game_type", game_type}
	};
	
	saveToJsonImpl(document);
}

void CoreEntity::fromJson(const nlohmann::json& document)
{
	json_utils::tryQueryJsonVar(document, "name", name);
	json_utils::tryQueryJsonVar(document, "o", o);
	json_utils::tryQueryJsonVar(document, "attr1", attr1);
	json_utils::tryQueryJsonVar(document, "attr2", attr2);
	json_utils::tryQueryJsonVar(document, "attr3", attr3);
	json_utils::tryQueryJsonVar(document, "attr4", attr4);
	json_utils::tryQueryJsonVar(document, "attr5", attr5);
	json_utils::tryQueryJsonVar(document, "reserved", reserved);
	json_utils::tryQueryJsonVar(document, "model_idx", model_idx);
}

//NOTE: Only CoreEntity needs to implement this
void CoreEntity::fromJsonImpl(const nlohmann::json& document)
{
	auto subdoc = json_utils::getSubobject(document, classname);
	if (subdoc.is_object())
	{
		fromJson(subdoc);
	}
}

void CoreEntity::loadFromJson(const nlohmann::json& document) {
	if (!json_utils::tryQueryJsonVar(document, "et_type", et_type))
		conoutf(CON_ERROR, "Failed to load JSON element et_type in class %s and map %s", classname.c_str(), game::getclientmap());

	json_utils::tryQueryJsonVar(document, "ent_type", ent_type);
	json_utils::tryQueryJsonVar(document, "game_type", game_type);

	fromJsonImpl(document);
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY(CoreEntity, "core_entity");
