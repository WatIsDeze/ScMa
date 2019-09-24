#ifndef PHYSENT_H
#define PHYSENT_H

class physent : public entity
{
public:
    //vec o, vel, falling;                          // origin, velocity
    vec vel, falling;                               // origin, velocity
    vec deltapos, newpos;                           // movement interpolation
    float yaw, pitch, roll;
    float maxspeed;                                 // cubes per second, 100 for player
    int timeinair;
    float radius, eyeheight, maxheight, aboveeye;   // bounding box size
    float xradius, yradius, zmargin;
    vec floor;                                      // the normal of floor the dynent is on

    int inwater;
    bool jumping;
    char move, strafe, crouching;

    uchar physstate;            // one of PHYS_* above
    uchar state, editstate;     // one of CS_* above
    //uchar type;               // one of ENT_* above NOTE: This one is now located in entity structure.
    uchar collidetype;          // one of COLLIDE_* above

    bool blocked;               // used by physics to signal ai

    physent();

    void resetinterp();

    void reset();

    vec feetpos(float offset) const;
    vec headpos(float offset) const;

    bool crouched() const;
};

#endif // PHYSENT_H
