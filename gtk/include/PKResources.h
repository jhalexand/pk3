#ifndef PKResources_HEADER
#define PKResources_HEADER

#include <debug.h>
#include <PKids.h>

#define PK_DEFAULT_SERVER "mothra"
#define PK_DEFAULT_PORT    4380

class PKResources {
private:
  const char *nickname_ ;
  const char *server_ ;
  const char *paddle_ ;
  PKBackgroundID background_ ;
  unsigned short port_ ;
  int team_ ;
public:
  PKResources() ; // built-in defaults
  void readFile(const char *file='\0'); // read from file (~/.pk3rc if null)
  void readCommandLine(int argc, const char * const *argv) ; // read from parms
  void saveCurrentDefaults(const char *file='\0') ; // write to file

  const char *nickname() { return nickname_; }
  const char *server() { return server_ ; }
  unsigned short port() { return port_ ; }
  const char *paddle() { return paddle_ ; }
  int team() { return team_ ; }
  PKBackgroundID background() { return background_; }

  void nickname(const char *) ;
  void server(const char *) ;
  void port(unsigned short) ;
  void paddle(const char *) ;
  void team(int) ;
  void background(PKBackgroundID) ;
} ;

// automatically initialized if this symbol is ever used
extern PKResources pk3rc ;

#endif
