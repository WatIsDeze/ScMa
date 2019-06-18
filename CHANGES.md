# TODO:
- Do proper file error handling and use internal engine streams for writing and reading json.
- Do proper error checking on JSON Entity data that is being loaded back in.
- Add BaseEntity to the engine folder instead of game folder. Since extentity has been sortof replaced by it.

# Changes - 2019-06-18
- Added the ext folder in src, currently contains nlohmann his single_header json implementation.
- Ensured the constructors are properly solved in the entity classes. (Virtual destructors, properly call parent constructors.)
- Added saving entities to JSON, removed saving them into the .ogz map file.
- Added loading entities by JSON, removed loading them from the .ogz map file.
- Replaced extentity by entities::classes::BaseEntity

# Changes - 2019-06-12
- Added ALUI
- Modified newgent to support string class types.
	- In order to do so, there is a copy of the newent functions, just renamed and changed to support gameentity types.

# Changes - 2019-06-06
- Renamed newentity of the game interface to newgameentity
- Renamed deleteentity of the game interface to deletegameentity

