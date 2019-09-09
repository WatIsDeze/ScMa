#include "game.h"

// Base entities.
#include "entities/basemonster.h"

// Game entities.
#include "entities/door.h"
#include "entities/dynamiclight.h"
#include "entities/playerstart.h"
#include "entities/player.h"

namespace entities
{
    using namespace game;

#ifndef STANDALONE
    vector<classes::BaseEntity *> g_ents;
    vector<classes::BaseEntity *> g_lightEnts;

    vector<classes::BaseEntity *> &getents() { return g_ents; }

    bool mayattach(classes::BaseEntity &e) { return false; }
    bool attachent(classes::BaseEntity &e, classes::BaseEntity &a) { return false; }

    const char *itemname(int i)
    {
        return NULL;
#if 0
        int t = ents[i]->type;
        if(!validitem(t)) return NULL;
        return itemstats[t-I_FIRST].name;
#endif
    }

    int itemicon(int i)
    {
        return -1;
#if 0
        int t = ents[i]->type;
        if(!validitem(t)) return -1;
        return itemstats[t-I_FIRST].icon;
#endif
    }

    const char *entmdlname(int type)
    {
        static const char * const entmdlnames[MAXENTTYPES] =
        {
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "game/teleport", NULL, NULL,
            NULL, NULL
        };
        return entmdlnames[type];
    }

    const char *entmodel(const entity &e)
    {
        if(e.type == TELEPORT)
        {
            if(e.attr2 > 0) return mapmodelname(e.attr2);
            if(e.attr2 < 0) return NULL;
        }
        return e.type < MAXENTTYPES ? entmdlname(e.type) : NULL;
    }

    void preloadentities()
    {
        // Execute preload actions for entities.
        loopv(g_ents)
        {
            // Let's go at it!
            entities::classes::BaseEntity *e = g_ents[i];
            e->preload();
        }

        // Specifically load in the client player model.
        game::player1->preload();

        // TODO: If stuff suddenly starts failing it is likely cuz of this being commented.
/*
        loopi(MAXENTTYPES)
        {
            const char *mdl = entmdlname(i);
            if(!mdl) continue;
            preloadmodel(mdl);
        }*/
//        loopv(ents)
//        {
//            switch(e.type)
//            {
//                case TELEPORT:
//                    if(e.attr2 > 0) preloadmodel(mapmodelname(e.attr2));
//                case JUMPPAD:
//                    if(e.attr4 > 0) preloadmapsound(e.attr4);
//                    break;
//                //case ET_GAMESPECIFIC:
//                //	conoutf("%s", "Found a gamespecific entity");
//            }
//        }
    }

// TODO: Wonder what this function was for anyway, we don't need it.
//    void renderentities()
//    {
//        loopv(g_ents)
//        {
//            entities::classes::BaseEntity &e = *g_ents[i];
//            int revs = 10;

//            switch(e.type)
//            {
//                case TELEPORT:
//                    if(e.attr2 < 0) continue;
//                    break;
//                case ENT_PLAYER:

//                default:
//                    if(!e.spawned()) continue;
//                    break;
//            }

//            // This code seems to render the default models.
//            const char *mdlname = entmodel(e);
//            if(mdlname)
//            {
//                vec p = e.o;
//                p.z += 1+sinf(lastmillis/100.0+e.o.x+e.o.y)/20;
//                rendermodel(mdlname, ANIM_MAPMODEL|ANIM_LOOP, p, lastmillis/(float)revs, 0, 0, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED);
//            }
//        }
//    }

    void resetspawns() {
        loopv(g_ents)
                g_ents[i]->clearspawned();
    }

    void setspawn(int i, bool on) { if(g_ents.inrange(i)) g_ents[i]->setspawned(on); }

    // Returns the entity class respectively according to its registered name.
    entities::classes::BaseEntity *newgameentity(char *strclass) {
        if (strclass != NULL && strcmp(strclass, "playerstart") == 0) {
            // TODO: Remove this one after we are further into development.
            conoutf("%s", "Found Playerstart");
            return new entities::classes::PlayerStart();
        } else {
            if (strclass != NULL && strcmp(strclass, "basemonster") == 0) { return new entities::classes::BaseMonster(); }
            if (strclass != NULL && strcmp(strclass, "dynamiclight") == 0) { return new entities::classes::DynamicLight(); }
            if (strclass != NULL && strcmp(strclass, "door") == 0) { return new entities::classes::Door(); }

            // No entity was found, so we'll return base entity for now.
            // TODO: Should we do this at all? I guess returning NULL is fine too and warning our user instead.
            return new entities::classes::BaseEntity();
        }
    }
    // Deletes the entity class in specific.
    void deletegameentity(entities::classes::BaseEntity *e) {
        delete (entities::classes::BaseEntity *)e;
    }

    // Deletes all game entities in the stack.
    void clearents()
    {
        while(g_ents.length()) deletegameentity(g_ents.pop());
    }

    void animatemapmodel(const entities::classes::BaseEntity &e, int &anim, int &basetime)
    {
    }

    // Fixes entities, which mainly just mangles the attributes. I see little reason to keep this around...
    // TODO: Do we need this? Remove it?
    void fixentity(entities::classes::BaseEntity &e)
    {
        switch(e.type)
        {
            case FLAG:
                e.attr5 = e.attr4;
                e.attr4 = e.attr3;
            case TELEDEST:
                e.attr3 = e.attr2;
                e.attr2 = e.attr1;
                e.attr1 = (int)player1->yaw;
                break;
        }
    }

    void entradius(entities::classes::BaseEntity &e, bool color)
    {
        switch(e.type)
        {
            case TELEPORT:
                loopv(g_ents) if(g_ents[i]->type == TELEDEST && e.attr1==g_ents[i]->attr2)
                {
                    renderentarrow(e, vec(g_ents[i]->o).sub(e.o).normalize(), e.o.dist(g_ents[i]->o));
                    break;
                }
                break;

            case JUMPPAD:
                renderentarrow(e, vec((int)(char)e.attr3*10.0f, (int)(char)e.attr2*10.0f, e.attr1*12.5f).normalize(), 4);
                break;

            case FLAG:
            case TELEDEST:
            {
                vec dir;
                vecfromyawpitch(e.attr1, 0, 1, 0, dir);
                renderentarrow(e, dir, 4);
                break;
            }
        }
    }

    bool printent(entities::classes::BaseEntity &e, char *buf, int len)
    {
        return false;
    }

    const char *entnameinfo(entity &e) {
        entities::classes::BaseEntity  *ptr_e = (entities::classes::BaseEntity *)&e;
        std::string str;
        str = ptr_e->classname;
        // TODO: List attributes here? Maybe...
        return str.c_str();
    }
    const char *entname(int i)
    {
        static const char * const entnames[MAXENTTYPES] =
        {
            "none?", "light", "mapmodel", "playerstart", "envmap", "particles", "sound", "spotlight", "decal",
            "teleport", "teledest", "jumppad",
            "flag", "gameentity"
        };
        return i>=0 && size_t(i)<sizeof(entnames)/sizeof(entnames[0]) ? entnames[i] : "";
    }

    void editent(int i, bool local)
    {
//        entities::classes::BaseEntity &e = *ents[i];
        extern int edit_entity;
        edit_entity = i;
        //conoutf("%i", i);

        //e.flags = 0;
        //if(local) addmsg(N_EDITENT, "rii3ii5", i, (int)(e.o.x*DMF), (int)(e.o.y*DMF), (int)(e.o.z*DMF), e.type, e.attr1, e.attr2, e.attr3, e.attr4, e.attr5);
    }

    float dropheight(entity &e)
    {
        if(e.type==FLAG) return 0.0f;
        return 4.0f;
    }
#endif
}

