/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKAudioPlayer.h                                     */
/*    ASGN:                                                     */
/*    DATE: Tue May  6 04:54:45 1997                            */
/****************************************************************/


#ifndef PKAUDIOPLAYER_HEADER
#define PKAUDIOPLAYER_HEADER

#include <rw/tvhdict.h>
#include <debug.h>
class PKClientInterface ;
#include <PKids.h>
#include "PKAudioClass.h"

class PKAudioPlayer {
private:
  int fd_;
  boolean passedIn_;
  PKClientInterface *client_;
  RWTValHashDictionary<PKSoundID, PKAudioClass*> dict_;
public:
  PKAudioPlayer(PKClientInterface *client, int numSounds, PKSoundID *ids, char **filenames); // writes to /dev/fd
  PKAudioPlayer(PKClientInterface *client, int fd, int numSounds, PKSoundID *ids, char **filenames); // writes to the file descriptor (i.e. a socket)
  virtual ~PKAudioPlayer(); // closes the file descriptor if we opened it

  boolean playAudio(PKSoundID toPlay); // plays it if it can; returns false if not
} ;

#endif
