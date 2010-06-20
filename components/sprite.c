#include "components/sprite.h"

#include <GL/gl.h>
#include <stdlib.h>

static void draw(game_s *game, actor_s *actor, void *component)
{
    sprite_s *sprite = (sprite_s *)component;
    glClearColor(sprite->time%60/60., 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void update(game_s *game, actor_s *actor, void *component)
{
    sprite_s *sprite = (sprite_s *)component;
    sprite->time++;
    if(sprite->time == 100) actor->dead = 1;
}

static void release(game_s *game, actor_s *actor, void *component)
{
    free(component);
}

sprite_s * make_sprite(
    game_s *game,
    actor_s *actor,
    transform_s *transform)
{
    sprite_s *sprite = (sprite_s *)malloc(sizeof(sprite_s));
    sprite->transform = transform;
    sprite->time = 0;

    game_register_callback(game, actor, sprite, CALLBACK_RELEASE, release);
    game_register_callback(game, actor, sprite, CALLBACK_DRAW, draw);
    game_register_callback(game, actor, sprite, CALLBACK_UPDATE, update);

    return sprite;
}
