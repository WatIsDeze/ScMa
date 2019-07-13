###### TODO ENGINE Alpha 0.1:
### IMPORTANT FOR STABILITY:
- Do proper entity file loading for readents function which is used only in the case of a server build.
- Do proper file error handling for JSON IO.
- Use internal engine streams for read/write JSON in world load/save.
- Do proper error checking on JSON Entity data that is being loaded back in.
- Add support for editing entities in coop mode using the newgent function etc. (Check for N_EDITENT as an example.)

### REGULAR TODO:
### SERVER/CLIENT SYSTEM:
- Logs etc, also the private folder being used on Linux(and OsX?) are still named Tesseract.
- Resolve how our "new entity system" truly works in the networking aspect of code. This is partially related to the game code.
Ultimately we do not seek multiplayer, so it is best to try and erase it from the engine as is.

### ENTITY SYSTEM:
- Create a macro such as in the HL1 SDK, where we can do LINK_ENTITY_CLASS(stringname, ClassName). This has the advantage that we don't have to scan for string class names in the newgameentity anymore. (It'll do so automatically instead of us having to add them by hand.)	
- Rename PlayerStart to Player, but ensure it can be spawned by "playerstart", and there can be only 1 for now.
  NOTE THAT: We should keep in mind this may need to be refactored since it could conflict in possible multiplayer cases.
  
### OTHERS: 
- Add support for footstep audio based on material/texture type.
- Add a dynamic/flickering light entity that can move, and flicker based on a sequence. (Like sin wave etc.)
- Add doors, this will be done by ENT_INANIMATE backporting.
- Add triggers, so entities can trigger others by name, which will execute a cubescript function for flexibility.
- Allow for 64 bots, maybe even more, so we can use these for AI. Otherwise, reimplement AI like in Cube 2, and work from there.

###### TODO GAME Alpha 0.1:
### Create a basic test map:
	- Requires Dynamic Light entities. (Flickering by sequence.)
	- Requires doors, and platforms, ENT_INANIMATE.
	- Requries trigger entities, the new type(not ancient Cube 2.)

### Entity Types:
	- MapModel
	- DynamicLight (Allow for it to move, flickering by sequence.)
	- Doors (Needs custom models.)
	- Platforms (Needs custom models.)
	- Buttons (Needs custom models.)
	- Basic AI Monster (Needs custom models.)
	- Dialoguer 
	- Pellet Single Shot Rifle (Needs custom models.)
	- Pellet Machinegun Rifle (Needs custom models.)
	
### Game Functionalities:	
- Weapon reloading.
- Add a knife melee weapon.
- Add a pellet gun single shot rifle.
- Add a pellet gun machinegun.
- Create a basic inventory for weapon switching and item management.
- Create a basic dialogue entity.

-------------------------------------------------------------------------------------------------------------
# Changes - 2019-07-08
- Placed the server code as it belongs, in a header and a cpp file.
- Added setting up the type for PlayerStart, it is now ENT_PLAYER, however the classname is still off....
- Added the basemonster entity type, which still requires a reimplementation of ENT_AI
- Added commands.cpp for all commands that CubeScript can call.

# Changes - 2019-07-06
- Renamed the game folder to oldgame.
- Created a minimal template, at the current moment there is no client/server handling. All we can do is move around.

# Changes - 2019-07-05
- The entity attributes map is now saved and loaded throughout json.
- ent_set_attr and ent_get_attr have been modified to work with key:value.
- added ent_list_attr

# Changes - 2019-07-04
- Exchanged char classname[256] with std::string in BaseEntity class.
- Removed str_attr# variables, added std::map<std::string, std::string> instead for properties. 

# Changes - 2019-06-28
- Removed writeent, saveent, and extraentinfosize functions. No need for them anymore since we now use JSON.


# Changes - 2019-06-18
- Added the ext folder in src, currently contains nlohmann his single_header json implementation.
- Ensured the constructors are properly solved in the entity classes. (Virtual destructors, properly call parent constructors.)
- Added saving entities to JSON, removed saving them into the .ogz map file.
- Added loading entities by JSON, removed loading them from the .ogz map file.
- Replaced extentity by entities::classes::BaseEntity

# Changes - 2019-06-12
- Added ALUI
- Modified newgent to support string class types.
	- In order to do so, newent still handles legacy entity types for now. (So far only still used for light, particles, sound, decals.)

# Changes - 2019-06-06
- Renamed newentity of the game interface to newgameentity
- Renamed deleteentity of the game interface to deletegameentity

