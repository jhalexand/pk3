/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKAudioPlayer.C
 *    DATE: Tue May  6  4:57:56 US/Eastern 1997
 *************************************************************************/
#include "PKAudioPlayer.h"

#include <rplay.h>
#include <stdlib.h>
#include <stdio.h>


unsigned audioHashFunc(const PKSoundID& id) {
  return ((int)id) % 71 ;
}

/*************************************************************************
 * Function Name: PKAudioPlayer::PKAudioPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKAudioPlayer::PKAudioPlayer(PKClientInterface *client, int numSounds,
			     PKSoundID *ids, char **filenames)
  : dict_(audioHashFunc)
{
  client_ = client ;
  passedIn_ = false ;

  fd_ = rplay_open_display();
  if(fd_==-1) {
    fprintf(stderr, "connection to rplay server on %s refused\n", getenv("DISPLAY"));
    rplay_perror("");
    return;
  }

  for(int i=0; i<numSounds; i++) {
    PKAudioClass *ac = new PKAudioClass(filenames[i]);
    dict_.insertKeyAndValue(ids[i], ac);
  }    
}


/*************************************************************************
 * Function Name: PKAudioPlayer::PKAudioPlayer
 * Parameters: int fd
 * Effects: 
 *************************************************************************/

PKAudioPlayer::PKAudioPlayer(PKClientInterface *client, int fd, int numSounds,
			     PKSoundID *ids, char **filenames)
  : dict_(audioHashFunc)
{
  client_ = client ;
  fd_ = fd ;
  passedIn_ = true ;
  for(int i=0; i<numSounds; i++) {
    PKAudioClass *ac = new PKAudioClass(filenames[i]);
    dict_.insertKeyAndValue(ids[i], ac);
  }    
}


/*************************************************************************
 * Function Name: PKAudioPlayer::~PKAudioPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKAudioPlayer::~PKAudioPlayer()
{
  dprintf(("closing audio\n"));
  if(!passedIn_) rplay_close(fd_);
}


/*************************************************************************
 * Function Name: PKAudioPlayer::playAudio
 * Parameters: PKSoundID toPlay
 * Returns: boolean
 * Effects: 
 *************************************************************************/
boolean
PKAudioPlayer::playAudio(PKSoundID toPlay)
{
  if( 0 > rplay(fd_, dict_[toPlay]->rplayObject()) )
    return false ;
  else
    return true ;
}
