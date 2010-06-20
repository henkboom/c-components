#ifndef ACTOR_H
#define ACTOR_H

typedef struct {
    int dead;
    int _marked_dead;
} actor_s;

actor_s * make_actor(void);

void release_actor(actor_s *actor);

#endif
