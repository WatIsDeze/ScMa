#include "basemonster.h"
#include "../game.h"
#include "shared/entities/entityfactory.h"

namespace entities {
namespace classes {

BaseMonster::BaseMonster() : BaseEntity() {
    ent_type = ENT_AI;
}

BaseMonster::~BaseMonster() {

}

void BaseMonster::preload() {
    conoutf("%s", "Preloading basemonster entity");
}

void BaseMonster::think() {
    //moveplayer(this, 10, true);
}

void BaseMonster::render() {
    // TODO: Fix this.
    //if(isthirdperson()) renderclient(player1, "ogro", NULL, 0, ANIM_ATTACK1, 300, player1->lastaction, player1->lastpain);
}

CoreEntity* BaseMonster::factory(){
	return new BaseMonster();
}

ADD_ENTITY_TO_FACTORY(BaseMonster, base_monster);

} // classes
} // entities
