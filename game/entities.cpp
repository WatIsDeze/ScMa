#include "game.h"
#include "entities/playerstart.h"

namespace entities
{
    using namespace game;

#ifndef STANDALONE
    vector<classes::BaseEntity *> ents;

    vector<classes::BaseEntity *> &getents() { return ents; }

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
        loopi(MAXENTTYPES)
        {
            const char *mdl = entmdlname(i);
            if(!mdl) continue;
            preloadmodel(mdl);
        }
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

    void renderentities()
    {
        loopv(ents)
        {
            entities::classes::BaseEntity &e = *ents[i];
            int revs = 10;
            switch(e.type)
            {
                case TELEPORT:
                    if(e.attr2 < 0) continue;
                    break;
                default:
                    if(!e.spawned()) continue;
                    break;
            }
            const char *mdlname = entmodel(e);
            if(mdlname)
            {
                vec p = e.o;
                p.z += 1+sinf(lastmillis/100.0+e.o.x+e.o.y)/20;
                rendermodel(mdlname, ANIM_MAPMODEL|ANIM_LOOP, p, lastmillis/(float)revs, 0, 0, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED);
            }
        }
    }

    void resetspawns() { loopv(ents) ents[i]->clearspawned(); }

    void setspawn(int i, bool on) { if(ents.inrange(i)) ents[i]->setspawned(on); }

    // Returns the entity class respectively according to its registered name.
    entities::classes::BaseEntity *newgameentity(char *strclass) {
        if (strclass != NULL && strcmp(strclass, "playerstart") == 0) {
            conoutf("%s", "Found Playerstart");
            return new entities::classes::PlayerStart();
        } else {
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
        while(ents.length()) deletegameentity(ents.pop());
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

    // WatIs: Testing the set and get properties of entities.
	int edit_entity = -1;

    ICOMMAND(ent_set_attr, "ss", (char *s1, char *s2),
	{
		if (edit_entity > -1 && edit_entity < ents.length()) {
            entities::classes::BaseEntity *ent = (entities::classes::BaseEntity*)ents[edit_entity];

            // Ensure both string lengths are > 0
            if (strlen(s1) > 0 && strlen(s2) > 0) {
                // Set the attribute value.
                // TODO: Check if it already exists or not? Maybe just ignore that.
                ent->attributes[s1] = s2;
            } else {
                // Inform the user.
                conoutf("%s", "No key:value string has been passed.");
            }
		} else {
			conoutf("%s", "No valid in range entity selected.");
		}
	});

    ICOMMAND(ent_get_attr, "s", (char *s1), {
		if (edit_entity > -1 && edit_entity < ents.length()) {
            entities::classes::BaseEntity *ent = (entities::classes::BaseEntity*)ents[edit_entity];

            if (ent->attributes.find(s1) != ent->attributes.end()) {
                conoutf("%s : %s", s1, ent->attributes[s1].c_str());
            }
		} else {
            conoutf("%s", "No valid entity selected to fetch an attribute from.");
		}
	});

    ICOMMAND(ent_list_attr, "", (), {
        if (edit_entity > -1 && edit_entity < ents.length()) {
            entities::classes::BaseEntity *ent = (entities::classes::BaseEntity*)ents[edit_entity];

            for(std::map<std::string, std::string>::iterator i = ent->attributes.begin(); i != ent->attributes.end(); ++i) {
                conoutf("%s : %s", i->first.c_str(), i->second.c_str());
            }
        } else {
            conoutf("%s", "No valid entity selected to fetch an attribute from.");
        }
    });

    void entradius(entities::classes::BaseEntity &e, bool color)
    {
        switch(e.type)
        {
            case TELEPORT:
                loopv(ents) if(ents[i]->type == TELEDEST && e.attr1==ents[i]->attr2)
                {
                    renderentarrow(e, vec(ents[i]->o).sub(e.o).normalize(), e.o.dist(ents[i]->o));
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
        entities::classes::BaseEntity &e = *ents[i];

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

