/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKAIClientMain.C                                    */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 09:10:18 1997                            */
/****************************************************************/



#include "PKAIClient.h"

int main(int argc, char **argv) {
    if(argc!=4) {
        fprintf(stderr, "USAGE: %s <host> <port> <play>\n", argv[0]);
        fflush(stderr);
        assert(false);
        exit(1);
    }

    dprintf(("running %s\n", argv[0]));
    char *hostname = argv[1];
    int port = atoi(argv[2]);
    int play = atoi(argv[3]);

    PKAIClient cli(hostname, port, play);

    return 0;
} ;

