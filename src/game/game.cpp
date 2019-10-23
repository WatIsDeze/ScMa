#include "game.h"
#include "entities.h"
#include "entities/playerstart.h"
#include "entities/player.h"
#include "engine/scriptexport.h"



namespace game
{
    // Global player entity pointer.
    ::entities::classes::Player *player1 = NULL;

    // List of connected players. (For future network usage.)
	//vector<::entities::classes::Player*> players;

    // Networking State properties.
    bool connected = false;

    // Map Game State properties.
    cubestr clientmap = "";     // Current map filename.
    int maptime = 0;            // Frame time.
    int maprealtime = 0;        // Total time.

    void updateworld() {
        // Update the map time. (First frame since maptime = 0.
        if(!maptime) { maptime = lastmillis; maprealtime = totalmillis; return; }

        // Escape this function if there is no currenttime yet from server to client. (Meaning it is 0.)
        if(!curtime) return; //{ gets2c(); if (player1->) c2sinfo(); return; } //c2sinfo(); }///if(player1->clientnum>=0) c2sinfo(); return; }
        //if(!curtime) return; //{ gets2c(); c2sinfo(); }///if(player1->clientnum>=0) c2sinfo(); return; }

		// Update the physics.
        physicsframe();

        // Update all our entity objects.
        updateentities();
        // gets2c();
		// if(player->clientnum >=0) c2sinfo();   // do this last, to reduce the effective frame lag
    }

    void SpawnPlayer()   // place at random spawn
    {
        if (player1)
        {
            player1->reset();
            player1->respawn();
        } else {
            player1 = new entities::classes::Player();
            player1->respawn();
        }
    }

    void updateentities() {
        // Execute think actions for entities.
        loopv(entities::getents())
        {
            // Let's go at it!
            if (entities::getents().inrange(i)) {
                entities::classes::BaseEntity *e = dynamic_cast<entities::classes::BaseEntity *>(entities::getents()[i]);
                if (e != NULL && e->ent_type != ENT_PLAYER)
                    e->think();
            }

        }

        if (game::player1)
            game::player1->think();
    }

    void gameconnect(bool _remote)
    {
        // Store connection state.
        //connected = _remote;
        connected = true;

        // Toggle edit mode if required.
        if(editmode)
            toggleedit();
    }

    void gamedisconnect(bool cleanup)
    {
        // Disconnected.
        connected = false;
    }

    SCRIPTEXPORT void changemap(const char *name)
    {
        // Are we connected? If not, connect locally.
        if(!connected) localconnect();

        // Toggle edit mode if required.
        if(editmode)
            toggleedit();

        // If world loading fails, start a new empty map instead.
        if(!load_world(name))
            emptymap(0, true, name);
    }

    void forceedit(const char *name) {
        // Trigger a changemap by force edit, which in return toggles edit mode.
        changemap(name);
    }

    // Never seen an implementation of this function, should be part of BaseEntity.
    void dynentcollide(entities::classes::BaseDynamicEntity *d, entities::classes::BaseDynamicEntity *o, const vec &dir) {
        conoutf("dynentcollide D et_type: %i ent_type: %i game_type: %i --- O et_type: %i ent_type: %i game_type %i", d->et_type, d->ent_type, d->game_type, o->et_type, o->ent_type, o->game_type);
    }

    void mapmodelcollide(entities::classes::CoreEntity *d, entities::classes::CoreEntity *o, const vec &dir) {
        conoutf("mmcollide D et_type: %i ent_type: %i game_type: %i --- O et_type: %i ent_type: %i game_type %i", d->et_type, d->ent_type, d->game_type, o->et_type, o->ent_type, o->game_type);
    }

    // Never seen an implementation of this function, should be part of BaseEntity.
    void bounced(entities::classes::BasePhysicalEntity *d, const vec &surface) {}

    // Unsure what to do with these yet.
    void edittrigger(const selinfo &sel, int op, int arg1, int arg2, int arg3, const VSlot *vs) {

    }
    void vartrigger(ident *id) {

    }

    // These speak for themselves.
    const char *getclientmap() {
        return clientmap;
    }
    const char *getmapinfo() {
        return NULL;
    }
    void resetgamestate() {
        //clearprojectiles();
        //clearbouncers();
    }
    void suicide(entities::classes::CoreEntity *d) {

    }
    void newmap(int size) {
        // Copy into mapname and reset maptime.
        maptime = 0;

        // Clear old entity list..
        entities::clearents();

        // SpawnPlayer.
        SpawnPlayer();

        // Find our playerspawn.
        findplayerspawn(player1);
    }
    void loadingmap(const char *name) {

    }

    void startmap(const char *name)
    {
        // Reset entity spawns.
		entities::resetspawns();

        // Spawn our player.
        SpawnPlayer();

		// Find player spawn point.
		findplayerspawn(player1);

        copycubestr(clientmap, name ? name : "");
        execident("mapstart");
    }

    bool needminimap() {
        return false;
    }

    float abovegameplayhud(int w, int h) {
        switch(player1->state)
        {
            case CS_EDITING:
                return 1;
            default:
                return (h-min(128, h))/float(h);
        }
    }

    void gameplayhud(int w, int h) {

    }

    float clipconsole(float w, float h) {
        return 0;
    }

    void preload() {
        entities::preloadentities();
    }

    void renderavatar() {

    }

    void renderplayerpreview(int model, int team, int weap) {

    }

    bool canjump()
    {
        return player1->state!=CS_DEAD;
    }

    bool cancrouch()
    {
        return player1->state!=CS_DEAD;
    }

    bool allowmove(entities::classes::BasePhysicalEntity *d)
    {
        return true;
        //if(d->ent_type!=ENT_PLAYER) return true;
        //return !d->ms_lastaction || lastmillis-d->ms_lastaction>=1000;
    }

    entities::classes::CoreEntity *iterdynents(int i) {
        if (i == 0) {
            return player1;
        } else {
            if (i < entities::getents().length()) {
                return dynamic_cast<entities::classes::BaseEntity *>(entities::getents()[i]);
            } else {
                return nullptr;
            }
        }

        //if (i < entities::g_lightEnts.length()) return (entities::classes::BaseEntity*)entities::g_lightEnts[i];
        //    i -= entities::g_lightEnts.length();
        //return NULL;
    }
    // int numdynents() { return players.length()+monsters.length()+movables.length(); }
    int numdynents() {
        return entities::getents().length() + 1; // + 1 is for the player.
    }

    // This function should be used to render HUD View stuff etc.
    void rendergame(bool mainpass) {
        // This function should be used to render HUD View stuff etc.
    }

    const char *defaultcrosshair(int index) {
        return "data/crosshair.png";
    }

    int selectcrosshair(vec &color) {
        if(player1->state==CS_DEAD) return -1;
        return 0;
    }

    void setupcamera() {
        entities::classes::BasePhysicalEntity *target = dynamic_cast<entities::classes::BasePhysicalEntity*>(player1);
        assert(target);
        if(target)
        {
            player1->strafe = target->strafe;
            player1->move = target->move;
            player1->yaw = target->yaw;
            player1->pitch = target->state==CS_DEAD ? 0 : target->pitch;
            player1->o = target->o;
            player1->resetinterp();
        }
    }

    bool allowthirdperson() {
        return true;
    }

    bool detachcamera() {
        return player1->state==CS_DEAD;
    }

    bool collidecamera() {
        return player1->state!=CS_EDITING;
    }

    void lighteffects(entities::classes::CoreEntity *e, vec&color, vec &dir) {
    }

    void renderDynamicLights() {
        // Loop through our light entities and render them all.
        auto &ents = entities::getents();
        loopv(ents)
        {
            // Let's go at it!
            auto e = dynamic_cast<entities::classes::BaseEntity *>(ents[i]);
            if (!e || e->et_type != ET_LIGHT) continue;
            
            e->render();
        }
    }

    void dynlighttrack(entities::classes::CoreEntity *owner, vec &o, vec &hud) {
    }

    void particletrack(entities::classes::CoreEntity *owner, vec &o, vec &d) {
    }

    void writegamedata(vector<char> &extras) {

    }
    void readgamedata (vector<char> &extras) {

    }

    const char *gameconfig() { return "config/game.cfg"; }
    const char *savedconfig() { return "config/saved.cfg"; }
    const char *restoreconfig() { return "config/restore.cfg"; }
    const char *defaultconfig() { return "config/default.cfg"; }
    const char *autoexec() { return "config/autoexec.cfg"; }
    const char *savedservers() { return "config/servers.cfg"; }

    void loadconfigs() {
        execfile("config/auth.cfg", true);
    }

    void parseoptions(vector<const char *> &args) {
        if (args.empty())
            conoutf(CON_WARN, "game::parseoption is empty");
    }
    void connectattempt(const char *name, const char *password, const ENetAddress &address) {
        // Will need this to even join a game.
        //copycubestr(connectpass, password);
    }
    void connectfail() {}
    void parsepacketclient(int chan, packetbuf &p) {}
    bool allowedittoggle() { return true; }
    void edittoggled(bool on) {}
    void writeclientinfo(stream *f) {}
    void toserver(char *text) {}
    bool ispaused() { return false; }
    int scaletime(int t) { return t*100; }
    bool allowmouselook() { return true; }

    //---------------------------------------------------------------

    void physicstrigger(entities::classes::BasePhysicalEntity *d, bool local, int floorlevel, int waterlevel, int material)
    {
        // This function seems to be used for playing material audio. No worries about that atm.
        if     (waterlevel>0) { if(material!=MAT_LAVA) playsound(S_SPLASHOUT, d==player1 ? NULL : &d->o); }
        else if(waterlevel<0) playsound(material==MAT_LAVA ? S_BURN : S_SPLASHIN, d==player1 ? NULL : &d->o);
        if     (floorlevel>0) { if(d==player1 || d->ent_type !=ENT_PLAYER) playsound(S_JUMP, d); }
        else if(floorlevel<0) { if(d==player1 || d->ent_type !=ENT_PLAYER ) playsound(S_LAND, d); }
    }

    void initclient() {
        // Setup the map time.
        maptime = 0;
		SpawnPlayer();
        findplayerspawn(player1);
    }

    const char *gameident() {
        return "SchizoMania";
    }
    const char *getscreenshotinfo() {
        return NULL;
    }


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
#if 0
#include "/Users/micha/dev/ScMaMike/src/build/binding/..+game+game.binding.cpp"
#endif
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //

}; // namespace game.

