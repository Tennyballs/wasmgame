#ifndef PLAYER_H
#define PLAYER_H

// attributes
typedef struct Player
{
    int x, y,
        w, h,
        PID;
    char *name;
} Player;

// constructor
Player *player_create(char *name, int playerId);

// methods
void player_update(Player *player, double delta, double direction);

#endif // PLAYER_H