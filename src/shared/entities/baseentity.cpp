#include "cube.h"
#include "game.h"
#include "baseentity.h"

namespace entities {
namespace classes {

void BaseEntity::preload() {}
void BaseEntity::think() {}
void BaseEntity::render() {}

void BaseEntity::reset() {
    // First reset core entity.
    CoreEntity::reset();
}

//
// Attributes set and get.
//
// Sets the key its value in the attributes list, also determines whether to automatically call onAttributeSet.
// Returns true in case it did not exist, returns false in case it already existed.
bool BaseEntity::setAttribute(const std::string &key, const std::string &value, bool callAttrSet) {
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

std::string BaseEntity::getAttribute(const std::string &key) {

    if (attributes.find(key) != attributes.end()) {
        return attributes[key];
    } else {
       return std::string();
    }
}

//
// OnEvent callbacks.
//
void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}
bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

} // classes
} // entities
