#include "player.h"

/*
@param [def_coord] default coordinate that will be in player
@return PLAYER class instance
*/
PLAYER createPlayer(COORD def_coord)
{
    PLAYER player;

    player.dim.coord = def_coord;
    player.dim.size = (SIZE) {1, 1};
    player.s_type = S_PLAYER;
    player.sprite = 'o';

    return player;
}