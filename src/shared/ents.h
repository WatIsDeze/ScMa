#ifndef ENTS_H
#define ENTS_H

// This file defines static map entities ("entity") and includes the basic entities:
// (dynamic entities (players/monsters, "dynent"), and static(No AI, or Input) entities(barrels, etc, "physent")
// the gamecode extends from the BaseEntity class type.

// ET_*: The internal engine entity type.
// (ent->et_type = ..)

enum {
    ET_EMPTY=0,         // Empty entities. Not in use. (No functionality, usually removed, or yet to be replaced.)
    ET_LIGHT,           // Light entities, can be dynamic lights(flickering, moving, on/off)
    ET_MAPMODEL,        // MapModel entities, can be benches, boxes, doors, anything alike.
    ET_PLAYERSTART,     // Playerstart entities, where players can spawn.
    ET_ENVMAP,          // Environment Map entity.
    ET_PARTICLES,       // Particle Effect entities.
    ET_SOUND,           // Sound Effect entities.
    ET_SPOTLIGHT,       // Spotlight entity, has to be attached to an ET_LIGHT entity.
    ET_DECAL,           // Decal entities, speak for itself.s
    ET_GAMESPECIFIC
};

#define MAXENTS 10000

//extern vector<entities::classes::BaseEntity *> ents;                // map entities


// Client/Server entity states. (ent->state, ent->editstate).
enum { CS_ALIVE = 0, CS_DEAD, CS_SPAWNING, CS_LAGGED, CS_EDITING, CS_SPECTATOR };

// Physics entity states. (ent->physstate)
enum { PHYS_FLOAT = 0, PHYS_FALL, PHYS_SLIDE, PHYS_SLOPE, PHYS_FLOOR, PHYS_STEP_UP, PHYS_STEP_DOWN, PHYS_BOUNCE };

// Game entity type, is it a player, AI, Inanimate, camera, or bounces.. (ent->ent_type)
enum { ENT_PLAYER = 0, ENT_AI, ENT_INANIMATE, ENT_CAMERA, ENT_BOUNCE };

// Physics collision types. (ent->collidetype)
enum { COLLIDE_NONE = 0, COLLIDE_ELLIPSE, COLLIDE_OBB, COLLIDE_TRI };

// Crouche Time, and Crouch Height. TODO: Place in Physics or player settings?
#define CROUCHTIME 200
#define CROUCHHEIGHT 0.75f

// Core entity class.
class entity
{
public:
    entity() : o(0, 0, 0), attr1(0), attr2(0), attr3(0), attr4(0), attr5(0), et_type(0), ent_type(0), game_type(0), reserved(0), model_idx(0) {}
    virtual ~entity() {}

    vec o;                                      // position
    short attr1, attr2, attr3, attr4, attr5;
    uchar et_type;                              // These are for the ET(Engine Type) values.
    uchar ent_type;                             // These are for ENT_(DynEnt/PhysEnt Type) values.
    uchar game_type;                            // the internal game entity type values.
    uchar reserved;

    // Variables used for classes who inherit from this original entity class.. (Model_idx == -1 by default.)
    int model_idx;
};

// Core entity flags.
enum
{
    EF_NOVIS      = 1<<0,
    EF_NOSHADOW   = 1<<1,
    EF_NOCOLLIDE  = 1<<2,
    EF_ANIM       = 1<<3,
    EF_SHADOWMESH = 1<<4,
    EF_OCTA       = 1<<5,
    EF_RENDER     = 1<<6,
    EF_SOUND      = 1<<7,
    EF_SPAWNED    = 1<<8
};

#include "entities/animinfo.h"
#include "entities/physent.h"
#include "entities/dynent.h"
#include "entities/baseentity.h"

#endif // ENTS_H
