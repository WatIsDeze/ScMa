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
#include "shared/entities/entityfactory.h"

namespace entities
{
    using namespace game;

#ifndef STANDALONE

    vector<entities::classes::CoreEntity *> &getents() {
		static vector<entities::classes::CoreEntity *> g_ents;
		return g_ents;
	}

    bool mayattach(entities::classes::BasePhysicalEntity *e) { return false; }
    bool mayattach(entities::classes::CoreEntity *e) { return false; }
    bool attachent(entities::classes::CoreEntity *e, entities::classes::CoreEntity *a) { return false; }

    const char *itemname(int i)
    {
        return nullptr;
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

    const char *entmodel(const entities::classes::CoreEntity *e)
    {
        return nullptr;
    }

    void preloadentities()
    {
        // Execute preload actions for entities.
        loopv(entities::getents())
        {
            if (getents().inrange(i) && getents()[i] != nullptr) {
                // Let's go at it!
                entities::classes::BaseEntity *e = dynamic_cast<entities::classes::BaseEntity*>(entities::getents()[i]);
				if (!e)
					continue;
                // Ensure that they don't get preloaded in preload, should be done in the constructor of ET_MAPMODEL entities.
                //if (e->et_type != ET_MAPMODEL)
                e->preload();
             }
        }

        // Specifically load in the client player model.
        if (game::player1 != nullptr) {
            game::player1->preload();
        }
    }

    void resetspawns() {
        loopv(entities::getents())
            if (entities::getents().inrange(i) && entities::getents()[i] != nullptr)
                entities::getents()[i]->clearspawned();

        if (game::player1 != nullptr)
            game::player1->clearspawned();
    }

    void setspawn(int i, bool on) { if(entities::getents().inrange(i) && entities::getents()[i] != nullptr) entities::getents()[i]->setspawned(on); }

    // Returns the entity class respectively according to its registered name.
    entities::classes::CoreEntity *newgameentity(const char *strclass) {
            auto e = entities::EntityFactory::constructEntity(std::string(strclass));

            if (e) {
                conoutf("Returned %s", strclass);
            } else {
                conoutf("Failed to create %s", strclass);
            }

            return e;
    }
    // Deletes the entity class in specific.
    void deletegameentity(entities::classes::CoreEntity *e) {
        if (!e)
            return;

        delete e;
    }

    // Deletes all game entities in the stack.
    void clearents()
    {
        // Delete stack entities.
        while(entities::getents().length()) deletegameentity(entities::getents().pop());
    }

    void animatemapmodel(const entities::classes::CoreEntity *e, int &anim, int &basetime)
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

    void entradius(entities::classes::CoreEntity *e, bool color)
    {
/*		switch(e->game_type)
        {
            case TELEPORT:
				loopv(entities::getents()) if(entities::getents()[i]->game_type == TELEDEST && e->attr1==entities::getents()[i]->attr2)
                {
					renderentarrow(e, vec(entities::getents()[i]->o).sub(e->o).normalize(), e->o.dist(entities::getents()[i]->o));
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
		}*/
    }

    bool printent(entities::classes::CoreEntity *e, char *buf, int len)
    {
        return false;
    }

    const char *entnameinfo(entities::classes::CoreEntity *e) {
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
//        entities::classes::CoreEntity *e = ents[i];
        extern int edit_entity;
        edit_entity = i;
        //conoutf("%i", i);

        //e.flags = 0;
        //if(local) addmsg(N_EDITENT, "rii3ii5", i, (int)(e.o.x*DMF), (int)(e.o.y*DMF), (int)(e.o.z*DMF), e.et_type, e.attr1, e.attr2, e.attr3, e.attr4, e.attr5);
    }

    float dropheight(entities::classes::CoreEntity *e)
    {
//		if(e->game_type==FLAG) return 0.0f;
        return 4.0f;
    }
#endif
}
