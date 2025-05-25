#include "render.h"
#include "game.h"
#include "sdl_utils.h" // pour textures
#include <SDL2/SDL.h>

extern SDL_Renderer *renderer;

static SDL_Texture *chooseHead(void)
{
    return textureHead[dir];
}
static SDL_Texture *chooseTail(void)
{
    Point tail = snake[snake_len - 1];
    Point prev = snake[snake_len - 2];
    int dx = tail.x - prev.x, dy = tail.y - prev.y;
    Direction d = (dx == 1 ? RIGHT : dx == -1 ? LEFT
                                 : dy == 1    ? DOWN
                                              : UP);
    return textureTail[d];
}
static SDL_Texture *chooseStraight(Direction d)
{
    return (d == UP || d == DOWN) ? textureBodyVertical : textureBodyHorizontal;
}
static SDL_Texture *chooseCorner(Point p, Point c, Point n)
{
    // trouve dp (p->c) et dn (c->n)
    int dx1 = c.x - p.x, dy1 = c.y - p.y, dx2 = n.x - c.x, dy2 = n.y - c.y;
    Direction dp = (dx1 > 0 ? RIGHT : dx1 < 0 ? LEFT
                                  : dy1 > 0   ? DOWN
                                              : UP);
    Direction dn = (dx2 > 0 ? RIGHT : dx2 < 0 ? LEFT
                                  : dy2 > 0   ? DOWN
                                              : UP);
    // corner order: BL(LEFT→DOWN)=0, TL(LEFT→UP)=1, TR(RIGHT→UP)=2, BR(RIGHT→DOWN)=3
    if ((dp == RIGHT && dn == DOWN) || (dp == UP && dn == LEFT))
        return textureBodyCorner[0];
    if ((dp == RIGHT && dn == UP) || (dp == DOWN && dn == LEFT))
        return textureBodyCorner[1];
    if ((dp == LEFT && dn == UP) || (dp == DOWN && dn == RIGHT))
        return textureBodyCorner[2];
    return textureBodyCorner[3];
}

void render_game(void)
{
    // efface en noir
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    // damier
    for (int y = 0; y < GRID_H; y++)
        for (int x = 0; x < GRID_W; x++)
        {
            SDL_Rect r = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if ((x + y) % 2 == 0)
                SDL_SetRenderDrawColor(renderer, 170, 215, 81, 255);
            else
                SDL_SetRenderDrawColor(renderer, 162, 209, 73, 255);
            SDL_RenderFillRect(renderer, &r);
        }

    // pomme
    SDL_Rect a = {apple.x * TILE_SIZE, apple.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_RenderCopy(renderer, textureApple, NULL, &a);

    // serpent
    for (int i = 0; i < snake_len; i++)
    {
        SDL_Rect dst = {snake[i].x * TILE_SIZE, snake[i].y * TILE_SIZE,
                        TILE_SIZE, TILE_SIZE};
        if (i == 0)
        {
            SDL_RenderCopy(renderer, chooseHead(), NULL, &dst);
        }
        else if (i == snake_len - 1)
        {
            SDL_RenderCopy(renderer, chooseTail(), NULL, &dst);
        }
        else
        {
            Point p = snake[i - 1], c = snake[i], n = snake[i + 1];
            // si aligné
            if ((p.x == c.x && c.x == n.x) || (p.y == c.y && c.y == n.y))
            {
                SDL_RenderCopy(renderer,
                               chooseStraight(p.x == c.x ? (n.y > c.y ? DOWN : UP)
                                                         : (n.x > c.x ? RIGHT : LEFT)),
                               NULL, &dst);
            }
            else
            {
                SDL_RenderCopy(renderer,
                               chooseCorner(p, c, n),
                               NULL, &dst);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
