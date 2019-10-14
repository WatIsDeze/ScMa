#include "game.h"
#include "engine/scriptexport.h"

#include "entities.h"
#include "entities/player.h"

// This file its soul purpose is to have all CubeScript COMMAND definitions located in a single file.
//---------------------------------------------------------------------------------------------//
// VARIABLES USED BY COMMANDS.                                                                 //
//---------------------------------------------------------------------------------------------//
// COMMAND(S): ent_....
namespace entities {
    int edit_entity = -1;
}

namespace game {
    //---------------------------------------------------------------------------------------------//
    // ENTITY COMMANDS.                                                                            //
    //---------------------------------------------------------------------------------------------//
    // ent_set_attr - Sets the value of the designated key property.
    // args: (str)key (str)value.
    SCRIPTEXPORT void ent_set_attr(char *s1, char *s2)
    {
        // TODO: Fix the namespace variable issues.
        //extern vector<entities::classes::CoreEntity *> entities::ents;

        if (entities::edit_entity > -1 && entities::edit_entity < entities::getents().length()) {
            entities::classes::CoreEntity *ent = (entities::classes::CoreEntity*)entities::getents()[entities::edit_entity];

            // Ensure both string lengths are > 0
            if (strlen(s1) > 0 && strlen(s2) > 0) {
                // Update our entity about the changes.
                ent->onAttributeSet(s1, s2);
            } else {
                // Inform the user.
                conoutf("%s", "No key:value string has been passed.");
            }
        } else {
            conoutf("%s", "No valid in range entity selected.");
        }
    };

    // ent_get_attr - Retreives the value of the designated key property.
    // args: (str)key
    SCRIPTEXPORT void ent_get_attr(char *s1)
    {
        // TODO: Fix the namespace variable issues.
        //extern vector<entities::classes::BaseEntity *> entities::ents;

        if (entities::edit_entity > -1 && entities::edit_entity < entities::ents.length()) {
            entities::classes::BaseEntity *ent = (entities::classes::BaseEntity*)entities::ents[entities::edit_entity];

			auto attributeValue = ent->onAttributeGet(s1);
            if (!attributeValue.empty()) {
                conoutf("%s : %s", s1, attributeValue.c_str());
            }
        } else {
            conoutf("%s", "No valid entity selected to fetch an attribute from.");
        }
    };

    // ent_list_attr - Lists all the properties of the given entity.
    SCRIPTEXPORT void ent_list_attr()
    {
        if (entities::edit_entity > -1 && entities::edit_entity < entities::getents().length()) {
            entities::classes::CoreEntity *ent = entities::getents()[entities::edit_entity];

			auto attributeList = ent->onAttributeList();
            for(auto key : attributeList) {
				auto value = ent->onAttributeGet(key);
                conoutf("%s : %s", key.c_str(), value.c_str());
            }
        } else {
            conoutf("%s", "No valid entity selected to fetch an attribute from.");
        }
    });

    SCRIPTEXPORT void gotosel()
    {
        if(player1->state!=CS_EDITING) return;
        player1->o = getselpos();
        vec dir;
        vecfromyawpitch(player1->yaw, player1->pitch, 1, 0, dir);
        player1->o.add(dir.mul(-32));
        player1->resetinterp();
    }
}
