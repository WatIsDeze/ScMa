#include "cube.h"
#include "game.h"
#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() : CoreEntity()
{
    // Setup defaults.
    reset();
}

BaseEntity::BaseEntity(const CoreEntity &e) {
    //
    // Legacy Core Entity data.
    //
    o = e.o;                             // position
    attr1 = e.attr1;                     // Old integer attributes, still used for storing/loading certain attributes of ET_TYPES.
    attr2 = e.attr2;
    attr3 = e.attr3;
    attr4 = e.attr4;
    attr5 = e.attr5;
    et_type = e.et_type;                              // These are for the ET(Engine Type) values.
    ent_type = e.ent_type;                             // These are for ENT_(DynEnt/PhysEnt Type) values.
    game_type = e.game_type;                            // the internal game entity type values.
    reserved = e.reserved;

    // Legacy extent data.
    flags = e.flags;
    attached = e.attached;

    // SchizoMania data.
    name = e.name;
    classname = e.classname;
    attributes = e.attributes;
    model_idx = e.model_idx;
}

BaseEntity::BaseEntity(const BaseEntity &e) {
    //
    // Legacy Core Entity data.
    //
    o = e.o;                             // position
    attr1 = e.attr1;                     // Old integer attributes, still used for storing/loading certain attributes of ET_TYPES.
    attr2 = e.attr2;
    attr3 = e.attr3;
    attr4 = e.attr4;
    attr5 = e.attr5;
    et_type = e.et_type;                              // These are for the ET(Engine Type) values.
    ent_type = e.ent_type;                             // These are for ENT_(DynEnt/PhysEnt Type) values.
    game_type = e.game_type;                            // the internal game entity type values.
    reserved = e.reserved;

    // Legacy extent data.
    flags = e.flags;
    attached = e.attached;

    // SchizoMania data.
    name = e.name;
    classname = e.classname;
    attributes = e.attributes;
    model_idx = e.model_idx;
}

BaseEntity::BaseEntity(const BasePhysicalEntity &e) : BaseEntity() {
    //
    // Legacy Core Entity data.
    //
    o = e.o;                             // position
    attr1 = e.attr1;                     // Old integer attributes, still used for storing/loading certain attributes of ET_TYPES.
    attr2 = e.attr2;
    attr3 = e.attr3;
    attr4 = e.attr4;
    attr5 = e.attr5;
    et_type = e.et_type;                              // These are for the ET(Engine Type) values.
    ent_type = e.ent_type;                             // These are for ENT_(DynEnt/PhysEnt Type) values.
    game_type = e.game_type;                            // the internal game entity type values.
    reserved = e.reserved;

    // Legacy extent data.
    flags = e.flags;
    attached = e.attached;

    // SchizoMania data.
    name = e.name;
    classname = e.classname;
    attributes = e.attributes;
    model_idx = e.model_idx;
}

BaseEntity::BaseEntity(const BaseDynamicEntity & e) : BaseEntity() {
    //
    // Legacy Core Entity data.
    //
    o = e.o;                             // position
    attr1 = e.attr1;                     // Old integer attributes, still used for storing/loading certain attributes of ET_TYPES.
    attr2 = e.attr2;
    attr3 = e.attr3;
    attr4 = e.attr4;
    attr5 = e.attr5;
    et_type = e.et_type;                              // These are for the ET(Engine Type) values.
    ent_type = e.ent_type;                             // These are for ENT_(DynEnt/PhysEnt Type) values.
    game_type = e.game_type;                            // the internal game entity type values.
    reserved = e.reserved;

    // Legacy extent data.
    flags = e.flags;
    attached = e.attached;

    // SchizoMania data.
    name = e.name;
    classname = e.classname;
    attributes = e.attributes;
    model_idx = e.model_idx;
}

BaseEntity::~BaseEntity() {

}

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
    std::string retkey;

    if (attributes.find(key) != attributes.end()) {
        retkey = attributes[key];
    } else {
       retkey.clear();
    }

    return retkey;
}

//
// OnEvent callbacks.
//
void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}
bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

} // classes
} // entities
