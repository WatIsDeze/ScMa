#include "cube.h"

//physent() : deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(20),
//           radius(4.1f), eyeheight(18), maxheight(18), aboveeye(2), xradius(4.1f), yradius(4.1f), zmargin(0),
physent::physent() : deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(30),
           radius(3.5), eyeheight(7), maxheight(8), aboveeye(2), xradius(1.6768999999999998), yradius(1.6768999999999998), zmargin(0),
           state(CS_ALIVE), editstate(CS_ALIVE),
           collidetype(COLLIDE_ELLIPSE),
           blocked(false)
{
    type = ENT_PLAYER; reset();
}

void physent::resetinterp() {
    newpos = o;
    deltapos = vec(0, 0, 0);
}

void physent::reset() {
    inwater = 0;
    timeinair = 0;
    eyeheight = maxheight;
    jumping = false;
    strafe = move = crouching = 0;
    physstate = PHYS_FALL;
    vel = falling = vec(0, 0, 0);
    floor = vec(0, 0, 1);
}

vec physent::feetpos(float offset = 0) const {
    return vec(o).addz(offset - eyeheight);
}
vec physent::headpos(float offset = 0) const {
    return vec(o).addz(offset);
}

bool physent::crouched() const {
    return fabs(eyeheight - maxheight*CROUCHHEIGHT) < 1e-4f;
}

