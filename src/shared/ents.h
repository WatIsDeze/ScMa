#ifndef ENTS_H
#define ENTS_H

// this file defines static map entities ("entity") and dynamic entities (players/monsters, "dynent")
// the gamecode extends these types to add game specific functionality

// ET_*: the only static entity types dictated by the engine... rest are gamecode dependent

enum { ET_EMPTY=0, ET_LIGHT, ET_MAPMODEL, ET_PLAYERSTART, ET_ENVMAP, ET_PARTICLES, ET_SOUND, ET_SPOTLIGHT, ET_DECAL, ET_GAMESPECIFIC };

class entity                                   // persistent map entity
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

    // Only used for BaseMapModelEntities.
    int model_idx;
};

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




#define MAXENTS 10000

//extern vector<entities::classes::BaseEntity *> ents;                // map entities

enum { CS_ALIVE = 0, CS_DEAD, CS_SPAWNING, CS_LAGGED, CS_EDITING, CS_SPECTATOR };

enum { PHYS_FLOAT = 0, PHYS_FALL, PHYS_SLIDE, PHYS_SLOPE, PHYS_FLOOR, PHYS_STEP_UP, PHYS_STEP_DOWN, PHYS_BOUNCE };

enum { ENT_PLAYER = 0, ENT_AI, ENT_INANIMATE, ENT_CAMERA, ENT_BOUNCE };

enum { COLLIDE_NONE = 0, COLLIDE_ELLIPSE, COLLIDE_OBB, COLLIDE_TRI };

#define CROUCHTIME 200
#define CROUCHHEIGHT 0.75f

// Base Entity type, can be affected by physics
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

enum
{
    ANIM_MAPMODEL = 0,
    ANIM_GAMESPECIFIC
};

#define ANIM_ALL         0x1FF
#define ANIM_INDEX       0x1FF
#define ANIM_LOOP        (1<<9)
#define ANIM_CLAMP       (1<<10)
#define ANIM_REVERSE     (1<<11)
#define ANIM_START       (ANIM_LOOP|ANIM_CLAMP)
#define ANIM_END         (ANIM_LOOP|ANIM_CLAMP|ANIM_REVERSE)
#define ANIM_DIR         0xE00
#define ANIM_SECONDARY   12
#define ANIM_REUSE       0xFFFFFF
#define ANIM_NOSKIN      (1<<24)
#define ANIM_SETTIME     (1<<25)
#define ANIM_FULLBRIGHT  (1<<26)
#define ANIM_NORENDER    (1<<27)
#define ANIM_RAGDOLL     (1<<28)
#define ANIM_SETSPEED    (1<<29)
#define ANIM_NOPITCH     (1<<30)
#define ANIM_FLAGS       0xFF000000

struct animinfo // description of a character's animation
{
    int anim, frame, range, basetime;
    float speed;
    uint varseed;

    animinfo() : anim(0), frame(0), range(0), basetime(0), speed(100.0f), varseed(0) { }

    bool operator==(const animinfo &o) const { return frame==o.frame && range==o.range && (anim&(ANIM_SETTIME|ANIM_DIR))==(o.anim&(ANIM_SETTIME|ANIM_DIR)) && (anim&ANIM_SETTIME || basetime==o.basetime) && speed==o.speed; }
    bool operator!=(const animinfo &o) const { return frame!=o.frame || range!=o.range || (anim&(ANIM_SETTIME|ANIM_DIR))!=(o.anim&(ANIM_SETTIME|ANIM_DIR)) || (!(anim&ANIM_SETTIME) && basetime!=o.basetime) || speed!=o.speed; }
};

struct animinterpinfo // used for animation blending of animated characters
{
    animinfo prev, cur;
    int lastswitch;
    void *lastmodel;

    animinterpinfo() : lastswitch(-1), lastmodel(NULL) {}

    void reset() { lastswitch = -1; }
};

#define MAXANIMPARTS 3

struct occludequery;
struct ragdolldata;

// Animated Characters, or Characters that can receive input
struct dynent : physent
{
    bool k_left, k_right, k_up, k_down;         // see input code - I think they meant, determine which key is pressed lolol.

    animinterpinfo animinterp[MAXANIMPARTS];
    ragdolldata *ragdoll;
    occludequery *query;
    int lastrendered;

    dynent();

    ~dynent();

    void stopmoving();

    void reset();

    vec abovehead();
};


// Defined here, for several reasons, since it has to replace good ol' extentity.
namespace entities
{
    namespace classes {
        class BaseEntity : public dynent {
        public:
            BaseEntity();
            virtual ~BaseEntity();

            //
            // Base functions.
            //
            // Called every time a map is being loaded.
            virtual void preload();

            // Called each frame, to "think", AI logic should go here.
            virtual void think();

            // Called each frame to render.
            virtual void render();

            //
            // Attribute events.
            //
            virtual void onAttributeSet(const std::string &key, const std::string &value);

            //
            // Trigger and touch commands.
            //
            // ent = the entity which has triggered you.
            virtual bool onTrigger(BaseEntity *otherEnt, const vec &dir);
            // ent = the entity which has touched you.
            virtual bool onTouch(BaseEntity *otherEnt, const vec &dir);

        // Taken from what was, gameentity.
        public:
            std::string classname;

            // Contains the json attributes.
            std::map<std::string, std::string> attributes;

        public:
            int flags;
            BaseEntity *attached;

            bool spawned() const { return (flags&EF_SPAWNED) != 0; }
            void setspawned(bool val) { if(val) flags |= EF_SPAWNED; else flags &= ~EF_SPAWNED; }
            void setspawned() { flags |= EF_SPAWNED; }
            void clearspawned() { flags &= ~EF_SPAWNED; }
        };
    } // classes
} // entities

#endif // ENTS_H
