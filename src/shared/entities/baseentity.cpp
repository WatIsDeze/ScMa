#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() {

}
BaseEntity::~BaseEntity() {

}

void BaseEntity::preload() {}
void BaseEntity::think() {}
void BaseEntity::render() {}

void BaseEntity::reset() {
    // Reset CoreEntity data.
    CoreEntity::reset();

    // Set the name back to its original entity name.
    setName("BaseEntity");
}

//
// OnEvent callbacks.
//
void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}
bool BaseEntity::onTrigger(entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }
bool BaseEntity::onTouch(entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }


nlohmann::json BaseEntity::toJson()
{
	return nlohmann::json {};
}


} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(BaseEntity, "base_entity", CoreEntity);
