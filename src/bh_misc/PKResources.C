/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKResources.C
 *    DATE: Sun Oct  5 19:39:59 US/Eastern 1997
 *************************************************************************/
#include "PKResources.h"

#include <ctype.h> // isspace
#include <errno.h> // errno
#include <limits.h> // PATH_MAX
#include <pwd.h>   // getpwuid
#include <stdlib.h> // getenv, sprintf
#include <stdio.h> // fopen, fclose, fgets
#include <string.h> // strcpy, strchr, strtok
#include <sys/types.h> // passwd
#include <unistd.h> // getuid



/*************************************************************************
 * Function Name: PKResources::PKResources
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKResources::PKResources() 
{
  dprintf(("PKResources: initalizing defaults\n")) ;
  nickname_ = server_ = paddle_ = null ;
  port_ = 0 ;
  background_ = (PKBackgroundID)0 ;
  team_ = 0 ;

  // defaults that are different from 0
  nickname(getpwuid(getuid())->pw_name) ;
  server(PK_DEFAULT_SERVER) ;
  port(PK_DEFAULT_PORT) ;
  background((PKBackgroundID)-1) ;
}



  
  
/*************************************************************************
 * Function Name: PKResources::readFile
 * Parameters: const char *filename
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::readFile(const char *filename) 
{
  char buf[STRLEN] ;
  char rcname[PATH_MAX] ;

  if(filename) {
    strcpy(rcname, filename) ;
  }
  else {
    sprintf(rcname, "%s/.pk3rc", getenv("HOME"));
  }
  
  FILE *rcfile = fopen(rcname, "r"); // open for read only

  if(!rcfile) {
    dprintf(("PK3RC: Error opening %s: %s\n",
	     rcname, strerror(errno)));
    return ;
  }

  dprintf(("PK3RC: Found resource file %s\n", rcname)) ;

  while (fgets(buf, STRLEN, rcfile)) {
    // kill the new-line if present
    int len = strlen(buf) ;
    if(buf[len-1]=='\n') buf[len-1]='\0';
#if defined(DEBUG) || defined(USEDPRINTF)
    char buf2[STRLEN] ; // this because buf will be overwritten by strtok
    strcpy(buf2, buf) ;
#endif
    char *curchar = buf ;

    // skip initial whitespace
    while(isspace(*curchar)) curchar++ ;

    // skip comments, blank lines
    if (strchr("!#\n", buf[0])) continue ;

    // prepare to read the first word
    strtok(curchar, " \t");

    if (!strcmp(curchar, "nickname")) {
      curchar = strtok(null, " \t");
      if(!curchar) {
	dprintf(("PK3RC: Error processing nickname in line\n\t%s", buf2));
	continue ;
      }
      nickname(curchar);
    }
    else if (!strcmp(curchar, "server")) {
      curchar = strtok(null, " \t");
      if(!curchar) {
	dprintf(("PK3RC: Error processing server in line\n\t%s", buf2));
	continue ;
      }
      server(curchar) ;
    }
    else if (!strcmp(curchar, "port")) {
      curchar = strtok(null, " \t");
      if(!curchar) {
	dprintf(("PK3RC: Error processing port in line\n\t%s", buf2));
	continue ;
      }
      port((unsigned short)atoi(curchar)) ;
    }
    else if (!strcmp(curchar, "background")) {
      curchar = strtok(null, " \t");
      if(!curchar) {
	dprintf(("PK3RC: Error processing background in line\n\t%s", buf2));
	continue ;
      }
      background((PKBackgroundID)atoi(curchar)) ;
    }
    else if (!strcmp(curchar, "team")) {
      curchar = strtok(null, " \t");
      if(!curchar) {
	dprintf(("PK3RC: Error processing team in line\n\t%s", buf2));
	continue ;
      }
      team(atoi(curchar)) ;
    }
    else if (!strcmp(curchar, "paddle")) {
      curchar = strtok(null, " \t");
      if(!curchar) {
	dprintf(("PK3RC: Error processing paddle in line\n\t%s", buf2));
	continue ;
      }
      paddle(curchar) ;
    }

  }

  fclose(rcfile) ;
}


/*************************************************************************
 * Function Name: PKResources::readCommandLine
 * Parameters: int argc, char **argv
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::readCommandLine(int argc, const char * const *argv) 
{
  int a = 0 ;
  while (++a < argc) {
    char cur = argv[a][0];
    if (cur != '-') {
      fprintf(stderr, "pk3: warning: ignoring unknown option \"%s\"\n",
	      argv[a]);
    }
    else {
      cur = argv[a][1] ;
      switch(cur) {
      case 'n':
	a++;
	nickname(argv[a]);
	  break;
      case 's':
	a++;
	server(argv[a]);
	break;
      case 'p':
	a++;
	port((unsigned short)atoi(argv[a]));
	break;
      case 'k':
	a++;
	paddle(argv[a]);
	break;
      case 't':
	a++;
	team(atoi(argv[a]));
	break;
      case 'b':
	a++;
	background((PKBackgroundID)atoi(argv[a]));
	break;
      default:
	fprintf(stderr, "pk3: warning: ignoring unknown switch '%c'\n", cur);
      }
    }
  }  
}


/*************************************************************************
 * Function Name: PKResources::saveCurrentDefaults
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::saveCurrentDefaults(const char *filename) 
{
  unimplemented("PKResources::saveCurrentDefaults()") ;
}


/*************************************************************************
 * Function Name: PKResources::nickname
 * Parameters: const char *
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::nickname(const char *name) 
{
  if(nickname_) free((void*)nickname_);
  nickname_ = strdup(name) ;
}


/*************************************************************************
 * Function Name: PKResources::server
 * Parameters: const char *
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::server(const char *server) 
{
  if(server_) free((void*)server_) ;
  server_ = strdup(server);
}


/*************************************************************************
 * Function Name: PKResources::port
 * Parameters: unsigned short
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::port(unsigned short port) 
{
  port_ = port ;
}


/*************************************************************************
 * Function Name: PKResources::paddle
 * Parameters: const char *
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::paddle(const char *paddle) 
{
  if(paddle_) free((void*)paddle_) ;
  paddle_ = strdup(paddle) ;
}


/*************************************************************************
 * Function Name: PKResources::team
 * Parameters: int
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::team(int team) 
{
  team_ = team ;
}


/*************************************************************************
 * Function Name: PKResources::background
 * Parameters: PKBackgroundID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKResources::background(PKBackgroundID bg) 
{
  background_ = bg ;
}


