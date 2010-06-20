#include "actor.h"

#include <stdlib.h>

actor_s * make_actor(void)
{
    actor_s *actor = (actor_s *)malloc(sizeof(actor_s));

    actor->dead = 0;
    actor->_marked_dead = 0;

    return actor;
}

void release_actor(actor_s *actor)
{
    free(actor);
}
