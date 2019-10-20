#include "baseentity.h"

namespace entities {
namespace classes {

void BaseEntity::preload() {}
void BaseEntity::think() {}
void BaseEntity::render() {}

//
// OnEvent callbacks.
//
void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}
bool BaseEntity::onTrigger(const entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }
bool BaseEntity::onTouch(const entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }
bool BaseEntity::onUse(CoreEntity *otherEnt, const vec &dir) { return false; }

nlohmann::json BaseEntity::toJson()
{
	return nlohmann::json {};
}


} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseEntity, "base_entity", CoreEntity);
