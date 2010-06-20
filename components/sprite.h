#ifndef COMPONENTS_SPRITE_H
#define COMPONENTS_SPRITE_H

#include "game.h"
#include "components/transform.h"

typedef struct {
    transform_s *transform;
    int time;
} sprite_s;

sprite_s * make_sprite(
    game_s *game,
    actor_s *actor,
    transform_s *transform);

#endif
