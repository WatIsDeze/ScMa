#ifndef __GAME_H__
#define __GAME_H__

#include "cube.h"
#include "ents.h"

namespace entities
{
	namespace classes
	{
		class Player;
		class BaseEntity;
	}
}

namespace game
{
    // Extern variables.
    extern entities::classes::Player *player1;  // Main player entity in the game code.
    extern int maptime, maprealtime;            // Times.
    extern cubestr clientmap;                   // The map the client is currently running or loading.

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
    extern void physicstrigger(entities::classes::BaseDynamicEntity *d, bool local, int floorlevel, int waterlevel, int material);

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
}

#endif

