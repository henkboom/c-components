#include "actors/player.h"

#include <stdlib.h>

#include "components/transform.h"
#include "components/sprite.h"

void make_player(game_s *game)
{
    actor_s *actor = make_actor();
    game_register_actor(game, actor);

    transform_s *transform = make_transform(game, actor);
    sprite_s *sprite = make_sprite(game, actor, transform);
    (void)sprite;
}
