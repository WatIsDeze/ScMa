#include "cube.h"
#include "game.h"
#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() : dynent(), flags(EF_RENDER), attached(NULL) {
    // Setup defaults.
    et_type = ET_EMPTY;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
}

BaseEntity::~BaseEntity() {

}

void BaseEntity::preload() {}
void BaseEntity::think() {}
void BaseEntity::render() {}

void BaseEntity::setAttribute(const std::string &key, const std::string &value, bool callAttrSet) {
    // Set the value.
    attributes[key] = value;

    // Call onAttributeSet?
    if (callAttrSet == true)
        onAttributeSet(key, value);
}

std::string BaseEntity::getAttribute(const std::string &key) {
    if (attributes.find(key) != attributes.end()) {
        return attributes[key];
    } else {
        return "";
    }
}

void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}

bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

} // classes
} // entities
