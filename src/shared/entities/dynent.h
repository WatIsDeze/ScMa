#ifndef DYNENT_H
#define DYNENT_H

struct occludequery;
struct ragdolldata;

// Animated Characters, which can possibly receive input
struct dynent : physent
{
    bool k_left, k_right, k_up, k_down;         // see input code - I think they meant, determine which key is pressed lolol.

    animinterpinfo animinterp[MAXANIMPARTS];
    ragdolldata *ragdoll;
    occludequery *query;
    int lastrendered;

    dynent();

    ~dynent();

    void stopmoving();

    void reset();

    vec abovehead();
};


#endif // DYNENT_H
