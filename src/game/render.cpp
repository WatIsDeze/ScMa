#include "game.h"
#include "entities.h"
#include "entities/player.h"

namespace game
{
    __attribute__((optimize("O0"))) void RenderGameEntities()
    {
        loopv(entities::g_ents) {
            entities::classes::BaseEntity *ent = entities::g_ents[i];
            //if (ent->et_type != ET_PLAYERSTART && ent->et_type != ET_EMPTY && ent->et_type != ET_LIGHT && ent->et_type != ET_SPOTLIGHT && ent->et_type != ET_SOUND)

            // Ensure we only render player entities if it isn't our own player 1 entity. (Otherwise we'd render it double.)
            if (ent != nullptr && (ent != game::player1))
                ent->render();
        }

        // Render our client player.
        if (game::player1 != nullptr)
            game::player1->render();
    }

    VARP(hudgun, 0, 1, 1);
    VARP(hudgunsway, 0, 1, 1);

    FVAR(swaystep, 1, 35.0f, 100);
    FVAR(swayside, 0, 0.10f, 1);
    FVAR(swayup, -1, 0.15f, 1);

    float swayfade = 0, swayspeed = 0, swaydist = 0;
    vec swaydir(0, 0, 0);

    void swayhudgun(int curtime) {

    }


    void drawhudmodel(entities::classes::BaseEntity *d, int anim, int basetime) {

    }

    void drawhudgun() {

    }

    void renderplayerpreview(int model, int color, int team, int weap) {

    }

    vec hudgunorigin(int gun, const vec &from, const vec &to, entities::classes::BaseEntity *d) {
        vec offset(from);

        return offset;
    }

    int numanims() {
        return 0;
    }

    __attribute__((used)) void findanims(const char *pattern, vector<int> &anims)
    {
        //loopi(sizeof(animnames)/sizeof(animnames[0])) if(matchanim(animnames[i], pattern)) anims.add(i);
    }

    void preloadweapons() {

    }

    void preloadsounds()
    {

    }
}

