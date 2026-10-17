/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: main.cxx                                                     */
/*    DATE: Tue Apr 22 21:52:47 1997                                     */
/*************************************************************************/

#include <iostream.h>
#include <stdlib.h>

#include <PKids.h>
#include <PKGameServerInterface.h>
#include <PKGameEngineInterface.h>

int
main(int argc, const char* argv[]) {

    PKTypeID playertypes[4];
    playertypes[0] = PK_TYPE_LIU_KANG_1;
    playertypes[1] = PK_TYPE_LIU_KANG_2;
    playertypes[2] = PK_TYPE_KABAL_2;
    playertypes[3] = PK_TYPE_REPTILE_2;
    
//    PKGameServerInterface* server = new PKGameServerInterface("cslab4c",
//												  1234, 1);
    PKGameEngineInterface* engine = new
	   PKGameEngineInterface(NULL, 2, playertypes, PK_KOMBAT_KODE_NONE);

    //test functions of game engine
    engine->mainloop();

    delete engine;
    cout<<"All done."<<endl;    
 
}
