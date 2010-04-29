#ifndef COMPONENTS_TRANSFORM_H
#define COMPONENTS_TRANSFORM_H

#include "game.h"
#include "actor.h"

typedef struct _transform_s transform_s;

transform_s *make_transform(game_s *game, actor_s *actor);

#endif
