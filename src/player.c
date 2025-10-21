#include <stdlib.h>
#include "player.h"

Player *player_create(char *name, int playerId)
{
    Player *player = (Player *)malloc(sizeof(Player));
    player->x = 0;
    player->y = 0;
    player->w = 0;
    player->h = 0;
    player->PID = playerId;
    player->name = name;
}