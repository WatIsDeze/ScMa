#include "cube.h"
#include "game.h"
#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() : CoreEntity(), flags(0), attached(NULL),
    // Entity
    o(0, 0, 0), attr1(0), attr2(0), attr3(0), attr4(0), attr5(0), et_type(ET_EMPTY), ent_type(ENT_INANIMATE), game_type(GAMEENTITY), reserved(0), model_idx(0),

    // Dynent.
    blocked(false), ragdoll(NULL), query(NULL), lastrendered(0),

    // Physent.
    deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(25),
               radius(2.4), eyeheight(7), maxheight(8), aboveeye(2), xradius(1.67), yradius(1.67), zmargin(0),
               state(CS_ALIVE), editstate(CS_ALIVE),
               collidetype(COLLIDE_ELLIPSE)

{
    // Setup defaults.
    reset();
}

BaseEntity(const BasePhysicalEntity& e) : CoreEntity() {
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
    attributes = attributes;
    flags = flags;
}

BaseEntity(const BaseDynamicEntity& e) : CoreEntity() {
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
    attributes = attributes;
    flags = flags;
}



BaseEntity::~BaseEntity() {
#ifndef STANDALONE
    extern void cleanragdoll(dynent *d);
    if(ragdoll) cleanragdoll(this);
#endif
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

const std::string BaseEntity::getAttribute(const std::string &key) const &{
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


void BaseEntity::stopmoving()
{
    k_left = k_right = k_up = k_down = jumping = false;
    move = strafe = crouching = 0;
}


vec BaseEntity::abovehead() {
    // WatIsDeze: Seems to determine to which lengths the camera and the character are allowed to go when jumping or crouching through a tunnel etc.
    return vec(o).addz(aboveeye+4);
}

void BaseEntity::resetinterp() {
    newpos = o;
    deltapos = vec(0, 0, 0);
}

void BaseEntity::reset() {
    // Physentity
    inwater = 0;
    timeinair = 0;
    eyeheight = maxheight;
    jumping = false;
    strafe = move = crouching = 0;
    physstate = PHYS_FALL;
    vel = falling = vec(0, 0, 0);
    floor = vec(0, 0, 1);

    // Dynentity.
    stopmoving();
    loopi(MAXANIMPARTS) animinterp[i].reset();
}

vec BaseEntity::feetpos(float offset = 0) const {
    return vec(o).addz(offset - eyeheight);
}
vec BaseEntity::headpos(float offset = 0) const {
    return vec(o).addz(offset);
}

bool BaseEntity::crouched() const {
    return fabs(eyeheight - maxheight*CROUCHHEIGHT) < 1e-4f;
}

} // classes
} // entities
