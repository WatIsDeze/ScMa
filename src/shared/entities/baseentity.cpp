#include "cube.h"
#include "game.h"
#include "ents.h"
#include "entityfactory.h"
#include "baseentity.h"
#include "coreentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() {
    // Reset.
    setName("base_entity");
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
bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

LINK_ENTITY_TO_CLASS(BaseEntity, base_entity);

} // classes
} // entities
