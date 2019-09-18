#include "game.h"

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
    // GENERAL GAME COMMANDS.                                                                      //
    //---------------------------------------------------------------------------------------------//
    // Changes the map, of course.
    ICOMMAND(map, "s", (char *s), changemap(s));

    //---------------------------------------------------------------------------------------------//
    // ENTITY COMMANDS.                                                                            //
    //---------------------------------------------------------------------------------------------//
    // ent_set_attr - Sets the value of the designated key property.
    // args: (str)key (str)value.
    ICOMMAND(ent_set_attr, "ss", (char *s1, char *s2),
    {
        // TODO: Fix the namespace variable issues.
        //extern vector<entities::classes::BaseEntity *> entities::ents;

        if (entities::edit_entity > -1 && entities::edit_entity < entities::g_ents.length()) {
            entities::classes::BaseEntity *ent = (entities::classes::BaseEntity*)entities::g_ents[entities::edit_entity];

            // Ensure both string lengths are > 0
            if (strlen(s1) > 0 && strlen(s2) > 0) {
                // Set the attribute value.
                // TODO: Check if it already exists or not? Maybe just ignore that.
                ent->attributes[s1] = s2;

                // Update our entity about the changes.
                ent->onAttributeSet(s1, s2);
            } else {
                // Inform the user.
                conoutf("%s", "No key:value string has been passed.");
            }
        } else {
            conoutf("%s", "No valid in range entity selected.");
        }
    });

    // ent_get_attr - Retreives the value of the designated key property.
    // args: (str)key
    ICOMMAND(ent_get_attr, "s", (char *s1), {
        // TODO: Fix the namespace variable issues.
        //extern vector<entities::classes::BaseEntity *> entities::ents;

        if (entities::edit_entity > -1 && entities::edit_entity < entities::g_ents.length()) {
            entities::classes::BaseEntity *ent = (entities::classes::BaseEntity*)entities::g_ents[entities::edit_entity];

            if (ent->attributes.find(s1) != ent->attributes.end()) {
                conoutf("%s : %s", s1, ent->attributes[s1].c_str());
            }
        } else {
            conoutf("%s", "No valid entity selected to fetch an attribute from.");
        }
    });

    // ent_list_attr - Lists all the properties of the given entity.
    ICOMMAND(ent_list_attr, "", (), {
        // TODO: Fix the namespace variable issues.
        //extern vector<entities::classes::BaseEntity *> entities::ents;

        if (entities::edit_entity > -1 && entities::edit_entity < entities::g_ents.length()) {
            entities::classes::BaseEntity *ent = (entities::classes::BaseEntity*)entities::g_ents[entities::edit_entity];

            for(std::map<std::string, std::string>::iterator i = ent->attributes.begin(); i != ent->attributes.end(); ++i) {
                conoutf("%s : %s", i->first.c_str(), i->second.c_str());
            }
        } else {
            conoutf("%s", "No valid entity selected to fetch an attribute from.");
        }
    });
}
