#include "basephysicalentity.h"
#include "cube.h"
#include "game.h"
#include "ents.h"
#include "shared/entities/entityfactory.h"

namespace entities
{
namespace classes {
// ORIGINAL SETTINGS.
//physent() : deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(20),
//           radius(4.1f), eyeheight(18), maxheight(18), aboveeye(2), xradius(4.1f), yradius(4.1f), zmargin(0),

// ATTEMPT #1.
//physent::physent() : deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(30),
//           radius(3.15), eyeheight(7), maxheight(8), aboveeye(2), xradius(1.6768999999999998), yradius(1.6768999999999998), zmargin(0),

// FINAL ATTEMPT FOR NOW.
BasePhysicalEntity::BasePhysicalEntity() : BaseEntity(), deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(25),
           radius(2.4), eyeheight(7), maxheight(8), aboveeye(2), xradius(1.67), yradius(1.67), zmargin(0),
           state(CS_ALIVE), editstate(CS_ALIVE),
           collidetype(COLLIDE_ELLIPSE),
           blocked(false)
{
    ent_type = ENT_INANIMATE;
}

BasePhysicalEntity::~BasePhysicalEntity() {

}

void BasePhysicalEntity::resetinterp() {
    newpos = o;
    deltapos = vec(0, 0, 0);
}

void BasePhysicalEntity::reset() {
    inwater = 0;
    timeinair = 0;
    eyeheight = maxheight;
    jumping = false;
    strafe = move = crouching = 0;
    physstate = PHYS_FALL;
    vel = falling = vec(0, 0, 0);
    floor = vec(0, 0, 1);
}

vec BasePhysicalEntity::feetpos(float offset = 0) const {
    return vec(o).addz(offset - eyeheight);
}
vec BasePhysicalEntity::headpos(float offset = 0) const {
    return vec(o).addz(offset);
}

bool BasePhysicalEntity::crouched() const {
    return fabs(eyeheight - maxheight*CROUCHHEIGHT) < 1e-4f;
}

LINK_ENTITY_TO_CLASS(BasePhysicalEntity, base_physical_entity);

} // classes
} // entities
