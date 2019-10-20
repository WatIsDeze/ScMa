#ifndef SERVER_H
#define SERVER_H
#include "game/game.h"

namespace server
{
    void *newclientinfo();
    void deleteclientinfo(void *ci);
    void serverinit();
    int reserveclients();
    int numchannels();
    void clientdisconnect(int n);
    int clientconnect(int n, uint ip);
    void localdisconnect(int n);
    void localconnect(int n);
    bool allowbroadcast(int n);
    void recordpacket(int chan, void *data, int len);
    void parsepacket(int sender, int chan, packetbuf &p);
    void sendservmsg(const char *s);
    bool sendpackets(bool force);
    void serverinforeply(ucharbuf &req, ucharbuf &p);
    void serverupdate();
    bool servercompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);

    int protocolversion();
    int serverinfoport(int servport);
    int serverport();
    const char *defaultmaster();
    int masterport();
    int laninfoport();
    void processmasterinput(const char *cmd, int cmdlen, const char *args);
    void masterconnected();
    void masterdisconnected();
    bool ispaused();
    int scaletime(int t);
}

#endif // SERVER_H
