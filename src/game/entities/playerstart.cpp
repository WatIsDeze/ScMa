#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() : BaseEntity() {
	// Reset defaults.
	reset();

	// Setup specifics.
    et_type = ET_GAMESPECIFIC;
    ent_type = ENT_INANIMATE;
    game_type = PLAYERSTART;
    
    // This is a joke for Micha.
    conoutf("\f3Hey Micha! Conoutf Boy! Haha! PlayerStart constructed.");
}

PlayerStart::~PlayerStart() {

}

void PlayerStart::preload() {

}

void PlayerStart::think() {

}

void PlayerStart::render() {

}

void PlayerStart::reset() {
	// Reset Base.
    BaseEntity::reset();

	// Set names.
    setName("PlayerStart");
}

void PlayerStart::toJson(nlohmann::json& document)
{
	BaseEntity::toJson(document);
	
	document[classname] = {
		{"yaw", yaw}
	};
}

void PlayerStart::fromJson(const nlohmann::json& document)
{
	BaseEntity::fromJson(document);

	if (document.find(classname) != document.end())
	{
		auto& subDoc = document.at(classname);
		
		if (subDoc.find("yaw") != subDoc.end())
		{
			yaw = subDoc.at("yaw");
		}
		else
		{
            yaw = 0.0f;
		}
	}
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY(PlayerStart, "playerstart");
