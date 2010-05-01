#include "game.h"

#include <assert.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "stb_sb.h"

typedef struct
{
    actor_s *actor;
    void *component;
    callback_f callback;
} callback_record_s;

struct _game_s
{
    kernel_scene_s scene;
    callback_record_s *callbacks[CALLBACK_COUNT];
};

static void call_callbacks(game_s *game, int first, int last)
{
    int callback_type;
    for(callback_type = first; callback_type <= last; callback_type++)
    {
        int len = sbcount(game->callbacks[callback_type]);
        int i;
        for(i = 0; i != len; i++)
        {
            callback_record_s *callback_record =
                &game->callbacks[callback_type][i];
            callback_record->callback(
                game,
                callback_record->actor,
                callback_record->component);
        }
    }
}

static void update(void *data)
{
    game_s *game = (game_s *)data;
    call_callbacks(game, FIRST_UPDATE_CALLBACK, LAST_UPDATE_CALLBACK);
}

static void draw(void *data)
{
    game_s *game = (game_s *)data;
    call_callbacks(game, FIRST_DRAW_CALLBACK, LAST_DRAW_CALLBACK);
}

game_s *make_game()
{
    game_s *game = (game_s *)malloc(sizeof(game_s));

    game->scene.update = update;
    game->scene.draw = draw;
    game->scene.data = game;
    
    int i;
    for(i = 0; i < CALLBACK_COUNT; i++)
    {
        game->callbacks[i] = NULL;
    }

    return game;
}

void release_game(game_s *game)
{
    call_callbacks(game, CALLBACK_RELEASE, CALLBACK_RELEASE);

    int callback_type;
    for(callback_type = 0; callback_type != CALLBACK_COUNT; callback_type++)
    {
        sbfree(game->callbacks[callback_type]);
    }

    free(game);
}


kernel_scene_s *game_scene(game_s *game)
{
    return &game->scene;
}

void game_register_callback(
    game_s *game,
    actor_s *actor,
    void *component,
    callback_e callback_type,
    callback_f callback)
{
    assert(0 <= callback_type && callback_type < CALLBACK_COUNT);

    callback_record_s *callback_record =
        sbadd(game->callbacks[callback_type], 1);
    callback_record->actor = actor;
    callback_record->component = component;
    callback_record->callback = callback;
}
