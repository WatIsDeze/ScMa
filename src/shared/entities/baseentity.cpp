#include "cube.h"
#include "game.h"
#include "ents.h"
#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() {
    // Reset.
    setName("baseentity");
    setClassName("BaseEntity");
}
BaseEntity::~BaseEntity() {

}

void BaseEntity::preload() {}
void BaseEntity::think() {}
void BaseEntity::render() {}

void BaseEntity::reset() {
    CoreEntity::reset();
    setName("baseentity");
    setClassName("BaseEntity");
}

//
// OnEvent callbacks.
//
void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}
bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

} // classes
} // entities
