/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: PKRoundEngine.C
 *    DATE: Sat Oct  3 17:21:14 US/Eastern 1998
 *************************************************************************/
#include "PKRoundEngine.h"
#include <unistd.h>

/*************************************************************************
 * Function Name: PKRoundEngine::mainloop
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKRoundEngine::mainloop()
{
  int done=0;
  while (!done) {
    _current_game = new PKGameEngine (_server, _numplayers, _players, _kode);
    int winner = _current_game->mainloop();
    _score[winner-1]++;
    delete _current_game;
    _current_game = NULL;
    //sleep(1);
    if (_score[0] == 2 || _score[1] == 2) done = TRUE; else done = FALSE;
    _server->broadcastPauseGame(false);
  }
}


