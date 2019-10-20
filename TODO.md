###### TODO ENGINE Alpha 0.1:
### IMPORTANT FOR STABILITY:
- Do proper entity file loading for readents function which is used only in the case of a server build.
- Do proper file error handling for JSON IO.
- Use internal engine streams for read/write JSON in world load/save.
- Do proper error checking on JSON Entity data that is being loaded back in.
- Add support for editing entities in coop mode using the newgent function etc. (Check for N_EDITENT in the old-game folder as an example.)
- Try and ponder, ServerThink and ClientThink, so we can either have a server code folder inside of our game, and place client related stuff in a client folder.

### REGULAR TODO:
### SERVER/CLIENT SYSTEM:
- Logs etc, also the private folder being used on Linux(and OsX?) are still named Tesseract.
- Resolve how our "new entity system" truly works in the networking aspect of code. We do seek multiplayer, this has changed.
We best try and get this done by as mentioned for stability, implementing a client and server think. Maybe even for preloads etc, the same has to be done.

### ENTITY SYSTEM:
- Create a macro such as in the HL1 SDK, where we can do LINK_ENTITY_CLASS(stringname, ClassName). This has the advantage that we don't have to scan for string class names in the newgameentity anymore. (It'll do so automatically instead of us having to add them by hand.)	
  
### OTHERS: 
- Change the COMMAND macros so they can allow for an extra string that serves as a help(how to use) message.
- Add support for footstep audio based on material/texture type.
- Add a dynamic/flickering light entity that can move, and flicker based on a sequence. (Like sin wave etc.)
- Add doors, this will be done by ENT_INANIMATE backporting.
- Add triggers, so entities can trigger others by name, which will execute a cubescript function for flexibility.
- Allow for 64 bots, maybe even more, so we can use these for AI. Otherwise, reimplement AI like in Cube 2, and work from there.

