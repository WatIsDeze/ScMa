#ifndef DYNENT_H
#define DYNENT_H

struct occludequery;
struct ragdolldata;

// Animated Characters, which can possibly receive input
class dynent : public physent
{
public:
    //
    // Core dynent functions.
    //
    dynent();
    virtual ~dynent();

    void stopmoving();
    void reset();

    vec abovehead();

    //
    // Key input states.
    //
    bool k_left, k_right, k_up, k_down;         // see input code - I think they meant, determine which key is pressed lolol.

    //
    // Rendering data.
    //
    animinterpinfo animinterp[MAXANIMPARTS];
    ragdolldata *ragdoll;
    occludequery *query;
    int lastrendered;
};


#endif // DYNENT_H
