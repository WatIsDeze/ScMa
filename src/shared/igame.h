// the interface the engine uses to run the gameplay module

namespace entities
{
    // Predefined.
    namespace classes {
        class BaseEntity;
    }

    extern void editent(int i, bool local);
    extern const char *entnameinfo(entities::classes::CoreEntity *e);
    extern const char *entname(int i);
    extern float dropheight(entities::classes::CoreEntity *e);
    extern void fixentity(entities::classes::CoreEntity *e);
    extern void entradius(entities::classes::CoreEntity *e, bool color);
    extern bool mayattach(entities::classes::CoreEntity *e);
    extern bool attachent(entities::classes::CoreEntity *e, entities::classes::CoreEntity *a);
    extern bool printent(entities::classes::CoreEntity *e, char *buf, int len);
    extern entities::classes::CoreEntity *newgameentity(const char *strclass);
    extern void deletegameentity(entities::classes::CoreEntity *e);
    extern void clearents();
    extern vector<entities::classes::CoreEntity *> &getents();
    extern const char *entmodel(const entities::classes::CoreEntity *e);
    extern void animatemapmodel(entities::classes::CoreEntity *e, int &anim, int &basetime);
}

namespace game
{
    extern void parseoptions(vector<const char *> &args);

    extern void gamedisconnect(bool cleanup);
    extern void parsepacketclient(int chan, packetbuf &p);
    extern void connectattempt(const char *name, const char *password, const ENetAddress &address);
    extern void connectfail();
    extern void gameconnect(bool _remote);
    extern bool allowedittoggle();
    extern void edittoggled(bool on);
    extern void writeclientinfo(stream *f);
    extern void toserver(char *text);
    extern void changemap(const char *name);
    extern void forceedit(const char *name);
    extern bool ispaused();
    extern int scaletime(int t);
    extern bool allowmouselook();

    extern const char *gameident();
    extern const char *gameconfig();
    extern const char *savedconfig();
    extern const char *restoreconfig();
    extern const char *defaultconfig();
    extern const char *autoexec();
    extern const char *savedservers();
    extern void loadconfigs();

    extern void updateworld();
    extern void initclient();
    extern void physicstrigger(entities::classes::BasePhysicalEntity *d, bool local, int floorlevel, int waterlevel, int material = 0);
    extern void bounced(entities::classes::BasePhysicalEntity *d, const vec &surface);
    extern void edittrigger(const selinfo &sel, int op, int arg1 = 0, int arg2 = 0, int arg3 = 0, const VSlot *vs = NULL);
    extern void vartrigger(ident *id);
    extern void dynentcollide(entities::classes::BaseDynamicEntity *d, entities::classes::BaseDynamicEntity *o, const vec &dir);

    // WatIsDeze: TODO: Maybe remove.
    extern void mapmodelcollide(entities::classes::CoreEntity *d, entities::classes::CoreEntity *o, const vec &dir);
    extern const char *getclientmap();
    extern const char *getmapinfo();
    extern const char *getscreenshotinfo();
    extern void resetgamestate();
    extern void suicide(entities::classes::CoreEntity *d);
    extern void newmap(int size);
    extern void startmap(const char *name);
    extern void preload();
    extern float abovegameplayhud(int w, int h);
    extern void gameplayhud(int w, int h);
    extern bool canjump();
    extern bool cancrouch();
    extern bool allowmove(entities::classes::BasePhysicalEntity *d);
    extern entities::classes::CoreEntity *iterdynents(int i);
    extern int numdynents();
    extern void RenderGameEntities();
    extern void renderavatar();
    extern void renderplayerpreview(int model, int color, int team, int weap);
    extern int numanims();
    extern void findanims(const char *pattern, vector<int> &anims);
    extern void writegamedata(vector<char> &extras);
    extern void readgamedata(vector<char> &extras);
    extern float clipconsole(float w, float h);
    extern const char *defaultcrosshair(int index);
    extern int selectcrosshair(vec &col);
    extern void setupcamera();
    extern bool detachcamera();
    extern bool collidecamera();
    extern void renderDynamicLights();
    extern void particletrack(entities::classes::CoreEntity *owner, vec &o, vec &d);
    extern void dynlighttrack(entities::classes::CoreEntity *owner, vec &o, vec &hud);
    extern bool needminimap();
}

namespace server
{
    extern void *newclientinfo();
    extern void deleteclientinfo(void *ci);
    extern void serverinit();
    extern int reserveclients();
    extern int numchannels();
    extern void clientdisconnect(int n);
    extern int clientconnect(int n, uint ip);
    extern void localdisconnect(int n);
    extern void localconnect(int n);
    extern bool allowbroadcast(int n);
    extern void recordpacket(int chan, void *data, int len);
    extern void parsepacket(int sender, int chan, packetbuf &p);
    extern void sendservmsg(const char *s);
    extern bool sendpackets(bool force = false);
    extern void serverinforeply(ucharbuf &req, ucharbuf &p);
    extern void serverupdate();
    extern int protocolversion();
    extern int laninfoport();
    extern int serverport();
    extern const char *defaultmaster();
    extern int masterport();
    extern void processmasterinput(const char *cmd, int cmdlen, const char *args);
    extern void masterconnected();
    extern void masterdisconnected();
    extern bool ispaused();
    extern int scaletime(int t);
}

