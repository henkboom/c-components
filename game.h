#ifndef GAME_H
#define GAME_H

#include "actor.h"
#include "kernel.h"

typedef struct _game_s game_s;

typedef enum {
    CALLBACK_RELEASE,

    FIRST_DRAW_CALLBACK,
    CALLBACK_DRAW_SETUP = FIRST_DRAW_CALLBACK,
    CALLBACK_DRAW,
    CALLBACK_DRAW_GUI,
    LAST_DRAW_CALLBACK = CALLBACK_DRAW_GUI,

    FIRST_UPDATE_CALLBACK,
    CALLBACK_UPDATE_SETUP = FIRST_UPDATE_CALLBACK,
    CALLBACK_UPDATE,
    CALLBACK_UPDATE_CLEANUP,
    LAST_UPDATE_CALLBACK = CALLBACK_UPDATE_CLEANUP,

    CALLBACK_COUNT
} callback_e;

typedef void (*callback_f)(game_s *game, actor_s *actor, void *component);

game_s *make_game(void);
void release_game(game_s *game);

kernel_scene_s *game_scene(game_s *game);

void game_register_actor(game_s *game, actor_s *actor);

void game_register_callback(
    game_s *game,
    actor_s *actor,
    void *component,
    callback_e callback_type,
    callback_f callback);

#endif
