#ifndef SUBSPACELIB_H_INCLUDED
#define SUBSPACELIB_H_INCLUDED

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#define NDEBUG
#include <cassert>
using namespace std;
namespace SubSpace
{
    struct recGameCell
	{
		bool blnBouy; /** Sea surface.*/
		bool blnSeaMine; /** Undersea.*/
		bool blnLauch; /** Lauch Position.*/
	};
    /** Creating Dynamic array*/
    typedef recGameCell** arrNavy;

	struct SeaWorld
	{
		arrNavy Navy;
		int intRows;
		int intCols;
		int intDefences;
		//Location of Lauch Area
		int intLaPRow;
		int intLaPCol;

		//Location of the Player
		int intPLRow;
		int intPLCol;
		//Surface or Undersea
		bool blnInSurface;
		string Test;
	};

    /** Array of Characters & enum for corresponding symbols*/
    enum SymbolValues
    {
        PLAYER,
        EMPTY_SPACE,
        LAUNCH_POSITION,
        BOUY,
        SEA_MINE

    };

    const char ARR_SYMBOLS[] = {'P','.','X','O','U'};

    /** Using ennumaration to handle error codes*/
    enum ErrorCodes
    {
        SUCCESS,
        ERROR_CONV,
        ERROR_NOT_EVEN,
        ERROR_HIGHER_RANGE,
        ERROR_CMD_ARG_COUNT,
    };

    /** FUnction for converting to integer*/
    int ConvertToInt(string strNumber);

    /** Function for Initialising a 2D Array*/
    arrNavy init2DArray(int intRows,int intCols);

    /** Create BouysMines*/
    SeaWorld InitSeaWorld(int intRows,int intCols,int intDefences);

    /** Display World*/
    void displaySeaWorld(SeaWorld recSeaworld);

    /** Generating Random Number*/
    int generateRandom(int intMin,int intMax);

    /** Placing Characters*/
    void placeCharacter(SeaWorld recSeaworld, SymbolValues symbols, int intNumSymbols);

    /** Check if is in Navy Area*/
    bool isInNavyArea(SeaWorld recSeaworld, int intRow, int intCol);

    /** Destroy Sea World*/
    void destroySeaWorld(SeaWorld& recSeaworld);

    /** Placing Player*/
    void placePlayer(SeaWorld& recSeaworld);

    /** Placing Lauching Position*/
    void placeLauchPosition(SeaWorld& recSeaworld);

    /** Moving Player*/
    void movePlayer(SeaWorld& recSeaworld, char chOption);


}
#endif // SUBSPACELIB_H_INCLUDED
