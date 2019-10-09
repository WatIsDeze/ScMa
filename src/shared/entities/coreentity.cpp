#include "cube.h"
#include "ents.h"
#include "game.h"
#include "ents.h"
#include "baseentity.h"
#include "coreentity.h"
#include "entityfactory.h"

namespace entities {
namespace classes {

CoreEntity::CoreEntity() {
}
CoreEntity::CoreEntity(const std::string &strClassName) {
    classname = strClassName;
}
CoreEntity::~CoreEntity() {
}

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

    // To remove.
    if (clearClassname == true)
        classname.clear();
}

void CoreEntity::setName(const std::string &str) {
    name = str;
}

} // classes
} // entities

