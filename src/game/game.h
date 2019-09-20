#ifndef __GAME_H__
#define __GAME_H__

#include "cube.h"

enum { ETR_SPAWN = ET_GAMESPECIFIC, };

enum                              // static entity types
{
    NOTUSED = ET_EMPTY,           // entity slot not in use in map
    LIGHT = ET_LIGHT,             // lightsource, attr1 = radius, attr2 = intensity
    MAPMODEL = ET_MAPMODEL,       // modelfilename = attr1 index, attr2 = yaw, attr3 = pitch, attr4 = roll, attr5 = scale
    PLAYERSTART = ET_PLAYERSTART, // attr1 = angle, attr2 = team
    ENVMAP = ET_ENVMAP,           // attr1 = radius
    PARTICLES = ET_PARTICLES,
    MAPSOUND = ET_SOUND,
    SPOTLIGHT = ET_SPOTLIGHT,
    DECAL = ET_DECAL,
    TELEPORT,                     // attr1 = idx, attr2 = model, attr3 = tag
    TELEDEST,                     // attr1 = angle, attr2 = idx
    JUMPPAD,                      // attr1 = zpush, attr2 = ypush, attr3 = xpush
    FLAG,                         // attr1 = angle, attr2 = team
    GAMEENTITY,					  // classname = game entity class type, attributes list is what it is, and can be accessed in any derived BaseEntity class.
    MAXENTTYPES,

    I_FIRST = 0,
    I_LAST = -1
};

// hardcoded sounds, defined in sounds.cfg
enum
{
    S_JUMP = 0, S_LAND,
    S_SPLASHIN, S_SPLASHOUT, S_BURN,
    S_ITEMSPAWN, S_TELEPORT, S_JUMPPAD,
    S_MELEE, S_PULSE1, S_PULSE2, S_PULSEEXPLODE, S_RAIL1, S_RAIL2,
    S_WEAPLOAD, S_NOAMMO, S_HIT,
    S_PAIN1, S_PAIN2, S_DIE1, S_DIE2,

    S_FLAGPICKUP,
    S_FLAGDROP,
    S_FLAGRETURN,
    S_FLAGSCORE,
    S_FLAGRESET,
    S_FLAGFAIL
};

namespace entities
{
    namespace classes {
        class BaseEntity;
        class BaseMapModel;
        class DynamicLight;
        class Player;
    }

    // Entity arrays.
    extern vector<classes::BaseEntity *> g_ents;
    extern vector<classes::BaseEntity *> g_lightEnts;

    // Silly functions yup.
    extern void preloadentities();
    extern void startmap();
}

namespace game
{
    // Extern variablesy.
    extern entities::classes::BaseEntity *player;
    extern int maptime, maprealtime, maplimit;

    // Entities.
    extern void clearworld();

    // Update functions.
    extern void updateentities();

    // Render functions.
    extern void rendergame(bool mainpass);
    extern void renderobjects();

    // HUD functions.
    extern float clipconsole(float w, float h);

    // Physics.
    extern void physicstrigger(entities::classes::BaseEntity *d, bool local, int floorlevel, int waterlevel, int material);

    // Renderer.
    #define MAXTEAMS 2
    struct playermodelinfo
    {
        const char *model[1+MAXTEAMS], *hudguns[1+MAXTEAMS],
                   *icon[1+MAXTEAMS];
        bool ragdoll;
    };

    extern void saveragdoll(entities::classes::BaseEntity *d);
    extern void clearragdolls();
    extern void moveragdolls();
    extern const playermodelinfo &getplayermodelinfo(entities::classes::BaseEntity *d);
    extern int getplayercolor(entities::classes::BaseEntity *d, int team);
    extern int chooserandomplayermodel(int seed);
    extern void syncplayer();
    extern void swayhudgun(int curtime);
    extern vec hudgunorigin(int gun, const vec &from, const vec &to, entities::classes::BaseEntity *d);
};

#endif

