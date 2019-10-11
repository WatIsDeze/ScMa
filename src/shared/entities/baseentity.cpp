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
    CoreEntity::reset();
    //setName("base_entity");
}

//
// OnEvent callbacks.
//
void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}
bool BaseEntity::onTrigger(entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }
bool BaseEntity::onTouch(entities::classes::CoreEntity *otherEnt, const vec &dir) { return false; }


} // classes
} // entities

ADD_ENTITY_TO_FACTORY(BaseEntity, "base_entity");
