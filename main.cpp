#include <iostream>
#include "SubSpaceLib.h"

using namespace std;
using namespace SubSpace;

int main(int argc,char* argv[])
{
    srand(time(0));

    int intROWS = 0;
    int intCOLS = 0;
    int intDEFENCES = 0;

   if(argc != 4)
    {
        cerr << "Usage of Utopian Navy: [Number of ROWS] [Number of COLS] [Number of DEFENCES] \n";
        exit(ERROR_CMD_ARG_COUNT);
    }
        intROWS = ConvertToInt(argv[1]);
        intCOLS = ConvertToInt(argv[2]);
        if(ConvertToInt(argv[3]) % 2 != 0){
           cerr << "ERROR: Number of DEFENCES must be an even Number \n";
           exit(ERROR_NOT_EVEN);
        }
        intDEFENCES = ConvertToInt(argv[3]);

    SeaWorld recNavy = InitSeaWorld(intROWS,intCOLS,intDEFENCES);

    bool blnContinue = true;
    do
    {

        system("cls");
        cout << "************************************************************** \n";
        cout << "****************WELCOME TO THE UTOPIAN NAVY!****************** \n";
        cout << "************************************************************** \n";
        displaySeaWorld(recNavy);

        cout << "                                                                     ... " << endl;
        cout << " PLAYER(P)--LAUCH POSITION(X)--BOUY(O)--SEA_MINE(U)--DETECTION_RANGE(.O.)" << endl
             << "                                                                     ... " << endl
             << " W)-Move UP" << endl
             << " S)-Move DOWN" << endl
             << " A)-Move LEFT" << endl
             << " D)-Move RIGHT" << endl
             << " C)-CHANGE World" << endl
             << " X)-Exit Utopian Navy" << endl
             << "Enter an option: ";

        char chOption = '\0';
        cin >> chOption;
        switch(chOption)
        {
        case 'W':
        case 'w':
        case 'S':
        case 's':
        case 'A':
        case 'a':
        case 'D':
        case 'd':
        case 'C':
        case 'c':
            movePlayer(recNavy, chOption);
            break;
        case 'X':
        case 'x':
            cout << "************************************************************** \n";
            cout << "**********GOODBYE THANKS FOR PLAYING UTOPIAN NAVY!************ \n";
            cout << "************************************************************** \n";
            blnContinue = false;
            break;
        default:
            cerr << "Wrong input!!!" << endl;
            break;
        }


        if(recNavy.Test == "WON"){
            cout << "************************************************************** \n";
            cout << "*********************CONGRATS YOU WON!!!********************** \n";
            cout << "************************************************************** \n";
            blnContinue = false;
        }
        else if(recNavy.Test == "DETECTED")
        {
            cout << "************************************************************** \n";
            cout << "*******************YOU HAVE BEEN DETECTED********************* \n";
            cout << "************************GAMEOVER!!**************************** \n";
            cout << "************************************************************** \n";

            blnContinue = false;
        }
    }while(blnContinue);

    destroySeaWorld(recNavy);

    return SUCCESS;
}
