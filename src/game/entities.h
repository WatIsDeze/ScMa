#ifndef __ENTITIES_H__
#define __ENTITIES_H__

namespace entities
{
    namespace classes {
        class CoreEntity;
        class BaseEntity;
        class BasePhysicalEntity;
        class BaseDynamicEntity;
        class BaseMapModel;
        class DynamicLight;
        class Player;
    }

    // Entity arrays.
    extern vector<classes::BaseEntity *> g_ents;
    extern vector<classes::BaseEntity *> g_lightEnts;

    //
    // Entity core functions.
    //
    // Preloads the entities.
    extern void preloadentities();

    // Renders all the entities.
    extern void renderentities();

    // Sets the spawn state on a given entity index.
    extern void setspawn(int i, bool on);

    // Resets all the spawns.
    extern void resetspawns();
}

#endif // __ENTITIES_H__
