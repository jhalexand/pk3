/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: NETClasses.C
 *    DATE: Sun Apr 27  3:57:28 US/Eastern 1997
 *************************************************************************/
#include "NETStream.h"

#include <PKGameClasses.h>

#include <PKObject.h>
#include <PKids.h>

#include <Network/NETReadWriteSocket.h>


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: int eger
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const double& eger)
{
  socket_->sendDouble(eger);
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: int eger
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const int& eger)
{
  socket_->sendInt(eger);
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const char *string
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const char *string)
{
  socket_->sendString(string);
  return *this;
}



/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const NETPort& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const NETPort::NETPortID& id)
{
  socket_->sendStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKBackgroundID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKActionID& id)
{
  socket_->sendStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKAILevel& lvl
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKAILevel& lvl)
{
  socket_->sendStruct(&lvl, sizeof(lvl));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKBackgroundID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKAnimID& id)
{
  socket_->sendStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKBackgroundID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKBackgroundID& id)
{
  socket_->sendStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKGameParameters& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKGameParameters& obj)
{
  operator << (obj.numPlayers());
  for(int i=0; i<obj.numPlayers(); i++) {
    operator << (obj.players()[i]);
  }
  operator << (obj.gameInProgress());
  operator << (obj.background());
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKGameProgress& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKGameProgress& obj)
{
  operator << (obj.creatorName());
  operator << (obj.numPlayers());
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKGameStatus& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKGameStatus& obj)
{
  operator << (obj.paused());
  operator << (obj.numPlayers());
  for(int i=0; i<obj.numPlayers(); i++) {
    operator << (obj.life()[i]);
  }
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKID& id
 * Returns: NETStream&
 * Effects: "multiple declaration" with const int& id
 *************************************************************************/
// NETStream&
// NETStream::operator << (const PKID& id)
// {
//   socket_->sendStruct(&id, sizeof(id));
//   return *this;
// }


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKObject& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKObject& obj)
{
  operator << (obj.getUniqueID());
  operator << (obj.getTypeID());
  operator << (obj.getPosition());
  operator << (obj.getVector());
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKPlayerInfo& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKPlayerInfo& obj)
{
  operator << (obj.playerNumber());
  operator << (obj.team());
  operator << (obj.paddle());
  operator << (obj.username());
  operator << (obj.account());
  operator << (obj.hostname());
  operator << (obj.life());
  operator << (obj.aiLevel());
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKPoint& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKPoint& id)
{
  socket_->sendDouble(id[0]);
  socket_->sendDouble(id[1]);
  socket_->sendDouble(id[2]);
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const NETPort& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKSoundID& id)
{
  socket_->sendStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKTypeID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKTypeID& id)
{
  socket_->sendStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKVector& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator << (const PKVector& id)
{
  socket_->sendDouble(id[0]);
  socket_->sendDouble(id[1]);
  socket_->sendDouble(id[2]);
  return *this;
}










/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: int eger
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (double& eger)
{
  socket_->getDouble(eger);
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: int eger
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (int& eger)
{
  socket_->getInt(eger);
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: const char *string
 * Returns: NETStream&
 * Effects: doesn't allocate the string
 *************************************************************************/
NETStream&
NETStream::operator >> (char *string)
{
  socket_->getString(string);
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: const char *string
 * Returns: NETStream&
 * Effects: allocates the string
 *************************************************************************/
NETStream&
NETStream::operator >> (char **string)
{
  *string = socket_->getString();
  return *this;
}




/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: NETPort::NETPortID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (NETPort::NETPortID& id)
{
  socket_->getStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKActionID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKActionID& id)
{
  socket_->getStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKAILevel& lvl
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKAILevel& lvl)
{
  socket_->getStruct(&lvl, sizeof(lvl));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKAnimID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKAnimID& id)
{
  socket_->getStruct(&id, sizeof(id));
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKBackgroundID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKBackgroundID& id)
{
  socket_->getStruct(&id, sizeof(id));
  return *this;
}

/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKGameParameters& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKGameParameters& obj)
{
  int numPlayers ;
  PKPlayerInfo *players;
  int gameInProgress;
  PKBackgroundID background;
  int i;
  
  operator >> (numPlayers);
  players = new PKPlayerInfo[numPlayers] ;
  for(i=0; i<numPlayers; i++) {
    operator >> (players[i]);
  }
  operator >> (gameInProgress) ;
  operator >> (background) ;

  
  obj.setNumPlayers(numPlayers);
  for(i=0; i<numPlayers; i++) {
    obj.getPlayer(i) = players[i];
  }
  obj.setGameInProgress(gameInProgress);
  obj.setBackground(background);

  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator << 
 * Parameters: const PKGameProgress& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKGameProgress& obj)
{
  char *name;
  int numPlayers;

  operator >> (&name) ;
  operator >> (numPlayers);

  obj.setCreatorName(name);
  obj.setNumPlayers(numPlayers);

  free(name);

  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKGameStatus& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKGameStatus& obj)
{
  obj.setPaused(get());
  obj.setNumPlayers(get());
  for(int i=0; i<obj.numPlayers(); i++) {
    obj.life()[i] = get();
  }
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKID& id
 * Returns: NETStream&
 * Effects: "multiple declaration" with int& id
 *************************************************************************/
// NETStream&
// NETStream::operator >> (PKID& id)
// {
//   socket_->getStruct(&id, sizeof(id));
//   return *this;
// }


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKPlayerInfo& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKPlayerInfo& obj)
{
  int playerNum;
  int team;
  PKTypeID paddle;
  char *name, *acct, *host;
  int life;
  PKAILevel aiLevel;
  
  operator >> (playerNum);
  operator >> (team);
  operator >> (paddle);
  operator >> (&name);
  operator >> (&acct);
  operator >> (&host);
  operator >> (life);
  operator >> (aiLevel);
  
  obj.setPlayerNumber(playerNum);
  obj.setTeam(team);
  obj.setPaddle(paddle);
  obj.setUsername(name); free(name);
  obj.setAccount(acct); free(acct);
  obj.setHostname(host); free(host);
  obj.setLife(life);
  obj.setAILevel(aiLevel);
  
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: const PKTypeID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKTypeID& id)
{
  socket_->getStruct(&id, sizeof(id));
  return *this;
}



/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKObject& obj
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKObject& obj)
{
  PKID id ;
  PKTypeID typeID ;
  PKPoint pos ;
  PKVector vector ;

  operator >> (id) ;
  operator >> (typeID) ;
  operator >> (pos) ;
  operator >> (vector) ;

  obj.setUniqueID(id);
  obj.setTypeID(typeID);
  obj.setPosition(pos);
  obj.setVector(vector);

  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: const PKPoint& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKPoint& id)
{
  id = PKPoint(socket_->getDouble(),
	       socket_->getDouble(),
	       socket_->getDouble());
  return *this;
}


/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: PKBackgroundID& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKSoundID& id)
{
  socket_->getStruct(&id, sizeof(id));
  return *this;
}

/*************************************************************************
 * Function Name: NETStream::operator >> 
 * Parameters: const PKVector& id
 * Returns: NETStream&
 * Effects: 
 *************************************************************************/
NETStream&
NETStream::operator >> (PKVector& id)
{
  id = PKVector(socket_->getDouble(),
		socket_->getDouble(),
		socket_->getDouble());
  return *this;
}

