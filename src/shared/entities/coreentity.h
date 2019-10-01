#ifndef COREENTITY_H
#define COREENTITY_H

namespace entities {
    // Classes.
    namespace classes {
        class BaseEntity;
    //        // Entity
    //        o(0, 0, 0), attr1(0), attr2(0), attr3(0), attr4(0), attr5(0), et_type(ET_EMPTY), ent_type(ENT_INANIMATE), game_type(GAMEENTITY), reserved(0), model_idx(0),

    //        // Dynent.
    //        blocked(false), ragdoll(NULL), query(NULL), lastrendered(0),

    //        // Physent.
    //        deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(25),
    //                   radius(2.4), eyeheight(7), maxheight(8), aboveeye(2), xradius(1.67), yradius(1.67), zmargin(0),
    //                   state(CS_ALIVE), editstate(CS_ALIVE),
    //                   collidetype(COLLIDE_ELLIPSE)

        // Core legacy entity class.
        class CoreEntity
        {
        public:
            // Constructors.
            CoreEntity();
    //            CoreEntity(const CoreEntity &e) {
    //                //
    //                // Legacy Core Entity data.
    //                //
    //                o = e.o;                             // position
    //                attr1 = e.attr1;                     // Old integer attributes, still used for storing/loading certain attributes of ET_TYPES.
    //                attr2 = e.attr2;
    //                attr3 = e.attr3;
    //                attr4 = e.attr4;
    //                attr5 = e.attr5;
    //                et_type = e.et_type;                              // These are for the ET(Engine Type) values.
    //                ent_type = e.ent_type;                             // These are for ENT_(DynEnt/PhysEnt Type) values.
    //                game_type = e.game_type;                            // the internal game entity type values.
    //                reserved = e.reserved;
    //                name = e.name;
    //                classname = e.classname;
    //                attributes = e.attributes;
    //                flags = e.flags;
    //                attached = e.attached;
    //                model_idx = e.model_idx;
    //            }

            virtual ~CoreEntity() {}

            //
            // Legacy Core Entity data.
            //
            vec o;                                      // position
            short attr1, attr2, attr3, attr4, attr5;    // Old integer attributes, still used for storing/loading ET_TYPES.
            uchar et_type;                              // These are for the ET(Engine Type) values.
            uchar ent_type;                             // These are for ENT_(DynEnt/PhysEnt Type) values.
            uchar game_type;                            // the internal game entity type values.
            uchar reserved;

            //
            // Legacy Core ExtEntity data and functions.
            //
            int flags;
            BaseEntity *attached;

            bool spawned() const;
            void setspawned(bool val);
            void setspawned();
            void clearspawned();

            //
            // Legacy of ours, but it made more sense than using short attr1 ... etc.
            //
            short model_idx;

            //
            // CoreEntity functions.
            //
            virtual void reset();

        public:
            //
            // Core BaseEntity data.
            //
            // Entity Name. (Used for trigger events.)
            std::string name;
            // Entity class name. (Used to spawn the proper inheritance class instance.)
            std::string classname;
            // Contains the json attributes.
            std::map<std::string, std::string> attributes;
        };
    } // classes
} // entities

#endif
