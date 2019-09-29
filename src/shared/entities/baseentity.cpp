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
    name = e.name;
    attributes = e.attributes;
    classname = e.classname;
    flags = e.flags;
    attached = e.attached;
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
    name = e.name;
    classname = e.classname;
    attributes = e.attributes;
    flags = e.flags;
    attached = e.attached;
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

//
// onEvents.
//
void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}
bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

} // classes
} // entities
