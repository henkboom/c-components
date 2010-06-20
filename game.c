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
    actor_s **actors;
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

            if(!callback_record->actor->dead)
            {
                callback_record->callback(
                    game,
                    callback_record->actor,
                    callback_record->component);
            }
        }
    }
}

static void release_dead(game_s *game)
{
    // call the release callbacks
    {
        callback_record_s *records = game->callbacks[CALLBACK_RELEASE];
        callback_record_s *records_end = records + sbcount(records);

        callback_record_s *record;
        for(record = records_end - 1; record >= records; record--)
        {
            if(record->actor->_marked_dead)
            {
                record->callback(
                    game,
                    record->actor,
                    record->component);
            }
        }
    }

    // remove dead actors' callback entries
    {
        int callback_type;
        for(callback_type = 0; callback_type != CALLBACK_COUNT; callback_type++)
        {
            callback_record_s *records = game->callbacks[callback_type];
            callback_record_s *records_end = records + sbcount(records);

            callback_record_s *src = records;
            callback_record_s *dst = records;

            // quickly skip leading live components
            while(src != records_end && !src->actor->_marked_dead)
            {
                src++;
                dst++;
            }

            // once we've found a dead component, compact the rest
            while(src != records_end)
            {
                if(!src->actor->_marked_dead)
                {
                    *dst = *src;
                    dst++;
                }
                src++;
            }
            sbrem(records, src - dst);
        }
    }

    // collect actors, and mark dead actors for collection next frame
    {
        actor_s **actors = game->actors;
        actor_s **actors_end = actors + sbcount(actors);

        actor_s **src = actors;
        actor_s **dst = actors;

        // quickly skip leading live actors
        while(src != actors_end && !(*src)->dead)
        {
            src++;
            dst++;
        }

        // once we've found a dead actor, compact the rest
        while(src != actors_end)
        {
            if((*src)->_marked_dead)
            {
                release_actor(*src);
                *src = NULL;
            }
            else
            {
                if((*src)->dead)
                    (*src)->_marked_dead = 1;

                *dst = *src;
                dst++;
            }
            src++;
        }
        sbrem(actors, src - dst);
    }
}

static void update(void *data)
{
    game_s *game = (game_s *)data;
    call_callbacks(game, FIRST_UPDATE_CALLBACK, LAST_UPDATE_CALLBACK);
    release_dead(game);
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

    game->actors = NULL;
    
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

    actor_s **actors_end = game->actors + sbcount(game->actors);
    actor_s **actor;
    for(actor = game->actors; actor != actors_end; actor++)
        release_actor(*actor);
    sbfree(game->actors);

    free(game);
}


kernel_scene_s *game_scene(game_s *game)
{
    return &game->scene;
}

void game_register_actor(game_s *game, actor_s *actor)
{
    sbpush(game->actors, actor);
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
