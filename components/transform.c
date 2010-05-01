#include "components/transform.h"

#include <stdlib.h>

struct _transform_s{
    double pos[2];
};

static void release(game_s *game, actor_s *actor, void *component)
{
    free(component);
}

transform_s *make_transform(game_s *game, actor_s *actor)
{
    transform_s *transform = (transform_s *)malloc(sizeof(transform_s));
    transform->pos[0] = 0;
    transform->pos[1] = 0;

    game_register_callback(game, actor, transform, CALLBACK_RELEASE, release);

    return transform;
}
