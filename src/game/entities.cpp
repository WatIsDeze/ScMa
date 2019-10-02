#include "engine.h"
#include "game.h"
#include "entities.h"

// Base entities.
#include "entities/basemonster.h"
#include "entities/basemapmodel.h"

// Game entities.
#include "entities/door.h"
#include "entities/dynamiclight.h"
#include "entities/playerstart.h"
#include "entities/player.h"



namespace entities
{
    using namespace game;

#ifndef STANDALONE
    vector<entities::classes::BaseEntity *> g_ents;
    vector<entities::classes::BaseEntity *> g_lightEnts;

    vector<entities::classes::BaseEntity *> &getents() { return g_ents; }

    bool mayattach(entities::classes::BasePhysicalEntity *e) { return false; }
    bool mayattach(entities::classes::BaseEntity *e) { return false; }
    bool attachent(entities::classes::BaseEntity *e, entities::classes::BaseEntity *a) { return false; }

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
        return "";
    }

    const char *entmodel(const entities::classes::BaseEntity *e)
    {
        return NULL;
    }

    void preloadentities()
    {
        // Execute preload actions for entities.
        loopv(entities::g_ents)
        {
            if (g_ents.inrange(i) && g_ents[i] != NULL) {
                // Let's go at it!
                entities::classes::BaseEntity *e = entities::g_ents[i];

                // Ensure that they don't get preloaded in preload, should be done in the constructor of ET_MAPMODEL entities.
                //if (e->et_type != ET_MAPMODEL)
                e->preload();
             }
        }

        // Specifically load in the client player model.
        if (game::player1 != NULL) {
            game::player1->preload();
        }
    }

    void resetspawns() {
        loopv(entities::g_ents)
            if (entities::g_ents.inrange(i) && entities::g_ents[i] != NULL)
                entities::g_ents[i]->clearspawned();

        if (game::player1 != NULL)
            game::player1->clearspawned();
    }

    void setspawn(int i, bool on) { if(entities::g_ents.inrange(i) && entities::g_ents[i] != NULL) entities::g_ents[i]->setspawned(on); }

    // Returns the entity class respectively according to its registered name.
    entities::classes::BaseEntity *newgameentity(char *strclass) {
            if (strclass != NULL && strcmp(strclass, "coreentity") == 0) { return new entities::classes::BaseEntity(); }
            if (strclass != NULL && strcmp(strclass, "playerstart") == 0) { return new entities::classes::PlayerStart(); }
            if (strclass != NULL && strcmp(strclass, "basemonster") == 0) { return new entities::classes::BaseMonster(); }
            if (strclass != NULL && strcmp(strclass, "dynamiclight") == 0) { return new entities::classes::DynamicLight(); }
            if (strclass != NULL && strcmp(strclass, "door") == 0) { return new entities::classes::Door(); }
            if (strclass != NULL && strcmp(strclass, "model") == 0) { return new entities::classes::BaseMapModel(); }

            conoutf("Returned entities::class:: %s", strclass);
            // No entity was found, so we'll return base entity for now.
            // TODO: Should we do this at all? I guess returning NULL is fine too and warning our user instead.
            return new entities::classes::BaseEntity();
    }
    // Deletes the entity class in specific.
    void deletegameentity(entities::classes::BaseEntity *e) {
        if (!e)
            return;

        delete (entities::classes::BaseEntity *)e;
    }

    // Deletes all game entities in the stack.
    void clearents()
    {
        // Delete stack entities.
        while(entities::g_ents.length()) deletegameentity(entities::g_ents.pop());
    }

    void animatemapmodel(const entities::classes::BaseEntity *e, int &anim, int &basetime)
    {/*        const fpsentity &f = (const fpsentity &)e;
        if(validtrigger(f.attr3)) switch(f.triggerstate)
        {
            case TRIGGER_RESET: anim = ANIM_TRIGGER|ANIM_START; break;
            case TRIGGERING: anim = ANIM_TRIGGER; basetime = f.lasttrigger; break;
            case TRIGGERED: anim = ANIM_TRIGGER|ANIM_END; break;
            case TRIGGER_RESETTING: anim = ANIM_TRIGGER|ANIM_REVERSE; basetime = f.lasttrigger; break;
        }*/
        //const entities::classes::BaseMapModelEntity *ent = (const entities::classes::BaseMapModelEntity&)e;
        //anim = ANIM_MAPMODEL | ANIM_START | ANIM_LOOP;
        //basetime = SDL_GetTicks() - e.reserved;
        //e.reserved = SDL_GetTicks();

    }

    // Fixes entities, which mainly just mangles the attributes. I see little reason to keep this around...
    // TODO: Do we need this? Remove it?
    void fixentity(entities::classes::BaseEntity *e)
    {
		switch(e->game_type)
        {
            case FLAG:
				e->attr5 = e->attr4;
				e->attr4 = e->attr3;
            case TELEDEST:
				e->attr3 = e->attr2;
				e->attr2 = e->attr1;
				e->attr1 = (int)game::player1->yaw;
                break;
        }
    }

    void entradius(entities::classes::BaseEntity *e, bool color)
    {
		switch(e->game_type)
        {
            case TELEPORT:
				loopv(entities::g_ents) if(entities::g_ents[i]->game_type == TELEDEST && e->attr1==entities::g_ents[i]->attr2)
                {
					renderentarrow(e, vec(entities::g_ents[i]->o).sub(e->o).normalize(), e->o.dist(entities::g_ents[i]->o));
                    break;
                }
                break;

            case JUMPPAD:
				renderentarrow(e, vec((int)(char)e->attr3*10.0f, (int)(char)e->attr2*10.0f, e->attr1*12.5f).normalize(), 4);
                break;

            case FLAG:
            case TELEDEST:
            {
                vec dir;
				vecfromyawpitch(e->attr1, 0, 1, 0, dir);
                renderentarrow(e, dir, 4);
                break;
            }
        }
    }

    bool printent(entities::classes::BaseEntity *e, char *buf, int len)
    {
        return false;
    }

    const char *entnameinfo(entities::classes::BaseEntity *e) {
        std::string str;
		str = e->classname + ":" + e->name;
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
//        entities::classes::BaseEntity *e = ents[i];
        extern int edit_entity;
        edit_entity = i;
        //conoutf("%i", i);

        //e.flags = 0;
        //if(local) addmsg(N_EDITENT, "rii3ii5", i, (int)(e.o.x*DMF), (int)(e.o.y*DMF), (int)(e.o.z*DMF), e.et_type, e.attr1, e.attr2, e.attr3, e.attr4, e.attr5);
    }

    float dropheight(entities::classes::BaseEntity *e)
    {
		if(e->game_type==FLAG) return 0.0f;
        return 4.0f;
    }
#endif
}
