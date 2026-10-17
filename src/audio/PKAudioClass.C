
#include "PKAudioClass.h"

#include <debug.h>
#include <fcntl.h>
#include <rplay.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



PKAudioClass::PKAudioClass(const char *filename) {
  dprintf(("Opening sound file %s\n", filename));

  rplayObject_ = rplay_create(RPLAY_PLAY);
  rplay_set(rplayObject(), RPLAY_APPEND, RPLAY_SOUND, filename, null);
}

PKAudioClass::~PKAudioClass() {
  rplay_destroy(rplayObject());
}
