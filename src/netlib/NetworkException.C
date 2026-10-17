#include "NetworkException.h"

const char * const
NETERR::errname_[] = {
  "No error",
  "Open failed",
  "Connect failed",
  "Bind failed",
  "Read 0 bytes",
  "Read too few bytes",
  "Received SIGPIPE"
} ;
