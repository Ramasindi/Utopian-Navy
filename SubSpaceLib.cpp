#include "SubSpaceLib.h"

namespace SubSpace
{
    ///Function for converting to integer
    int ConvertToInt(string strNumber)
    {
        int intNumber = 0;
        stringstream ssConvert;
        ssConvert << strNumber;
        ssConvert >> intNumber;
        if(ssConvert.fail())
        {
            cerr << "Error converting to integer \n";
            exit(ERROR_CONV);
        }
        return intNumber;
    }
    /** Generate Random number*/
    int generateRandom(int intMin,int intMax)
    {
        int range = intMax - intMin + 1;
        return rand() % range + intMin;
    }
    /** Check if is Navy Area*/
    bool isInNavyArea(SeaWorld recSeaworld, int intRow, int intCol)
	{
		if(intRow < 0)
			return false;
		if(intRow >= recSeaworld.intRows)
			return false;
		if(intCol < 0)
			return false;
		if(intCol >= recSeaworld.intCols)
			return false;
		return true;
	}
	/** Check Square Radius*/
	bool InSquareRad(SeaWorld recNavy,int intRandR,int intRandC)
	{
	      if(recNavy.Navy[intRandR + 1][intRandC].blnBouy  || recNavy.Navy[intRandR-1][intRandC].blnBouy
            || recNavy.Navy[intRandR][intRandC -1].blnBouy|| recNavy.Navy[intRandR +1][intRandC +1].blnBouy  || recNavy.Navy[intRandR -1][intRandC -1].blnBouy
            || recNavy.Navy[intRandR +1][intRandC -1].blnBouy  || recNavy.Navy[intRandR-1][intRandC +1].blnBouy)
            {
                        /// Place the food item.
                        recNavy.Navy[intRandR][intRandC].blnBouy = true;
            }
            return true;
	}
    /** Placing Characters*/
    void placeCharacter(SeaWorld recNavy, SymbolValues symbols, int intNumSymbols)
	{
		int intSymbolDeployed = 1 ;
		while(intSymbolDeployed < (intNumSymbols))
		{
			int intRandR = generateRandom(1, recNavy.intRows - 1);
			int intRandC = generateRandom(1, recNavy.intCols - 1);
			intSymbolDeployed++;
			if(symbols == BOUY )
			{
				/// We are placing Bouys
				if(!recNavy.Navy[intRandR][intRandC].blnBouy)
				{
                        /// Place the food item.
                        recNavy.Navy[intRandR][intRandC].blnBouy = true;
                        intSymbolDeployed++;
                }
			}
			else if(symbols == SEA_MINE)
			{
				/// We are placing Sea Mines
				if(!recNavy.Navy[intRandR][intRandC].blnSeaMine)
				{
					recNavy.Navy[intRandR][intRandC].blnSeaMine = true;
					intSymbolDeployed++;
				}
			}
		}
	}
	/** Placing a Player*/
    void placePlayer(SeaWorld& recNavy)
	{
	    bool IsOutRad;
		int intRandR = generateRandom(0, recNavy.intRows - 1);
		int intRandC = generateRandom(0, recNavy.intCols - 1);
		while(IsOutRad)
        {
            intRandR = generateRandom(0, recNavy.intRows - 1);
            intRandC = generateRandom(0, recNavy.intCols - 1);
            if(recNavy.Navy[intRandR][intRandC].blnLauch || recNavy.Navy[intRandR][intRandC].blnBouy  || recNavy.Navy[intRandR + 1][intRandC].blnBouy  || recNavy.Navy[intRandR-1][intRandC].blnBouy
            || recNavy.Navy[intRandR][intRandC -1].blnBouy|| recNavy.Navy[intRandR +1][intRandC +1].blnBouy  || recNavy.Navy[intRandR -1][intRandC -1].blnBouy
            || recNavy.Navy[intRandR +1][intRandC -1].blnBouy  || recNavy.Navy[intRandR-1][intRandC +1].blnBouy)
            {
                IsOutRad = false;
            }
        }
		while(recNavy.Navy[intRandR][intRandC].blnBouy)
		{
			recNavy.intPLRow = generateRandom(0, recNavy.intRows - 1);
			recNavy.intPLCol = generateRandom(0, recNavy.intCols - 1);
		}
		/// Simply recording the location of the player.
		/// Not necessarily placing the player in any of the worlds.

		recNavy.intPLRow = intRandR;
		recNavy.intPLCol = intRandC;
	}
	/** Placing Lauching Position*/
    void placeLauchPosition(SeaWorld& recSeaworld)
	{
		int intLaPRow = generateRandom(0, recSeaworld.intRows - 1);
		int intLaPCol = generateRandom(0, recSeaworld.intCols - 1);
		while(recSeaworld.Navy[intLaPRow][intLaPCol].blnBouy)
		{
			recSeaworld.intLaPRow = generateRandom(0, recSeaworld.intRows - 1);
			recSeaworld.intLaPCol = generateRandom(0, recSeaworld.intCols - 1);
		}
		/// Simply recording the location of the player.
		recSeaworld.intLaPRow = intLaPRow;
		recSeaworld.intLaPCol = intLaPCol;
	}
    /** Create BouysMines*/
    SeaWorld InitSeaWorld(int intRows,int intCols,int intDefences)
    {
        SeaWorld recNavy;
        recNavy.intRows = intRows;
        recNavy.intCols = intCols;
        recNavy.intDefences = intDefences;
        recNavy.blnInSurface = true;
        recNavy.Navy = new recGameCell*[intRows];
        for(int r =0;r < intRows;r++)
        {
            recNavy.Navy[r] = new recGameCell[intCols];
            for(int c =0;c < intCols;c++)
            {
                recNavy.Navy[r][c].blnBouy = false;
                recNavy.Navy[r][c].blnSeaMine = false;
                recNavy.Navy[r][c].blnLauch = false;
            }
        }
        //recNavy.Test = "NOT YET";
        placeCharacter(recNavy, BOUY, intDefences);
		placeCharacter(recNavy, SEA_MINE, intDefences);
		placeLauchPosition(recNavy);
		placePlayer(recNavy);
        return recNavy;
    }
    /** Check GAme status*/
    bool isEndOfGame(SeaWorld recSeaworld)
	{
           return true;
	}
	 /** Display World*/
    void displaySeaWorld(SeaWorld recSeaworld)
    {
        for(int r =0;r < recSeaworld.intRows;r++)
        {
            for(int c =0;c < recSeaworld.intCols;c++)
            {
				if(recSeaworld.intPLRow == r && recSeaworld.intPLCol == c)
                    cout << ARR_SYMBOLS[PLAYER] << ' ';

                else if(recSeaworld.intLaPRow == r && recSeaworld.intLaPCol == c)
                {
                        cout << ARR_SYMBOLS[LAUNCH_POSITION] << ' ';
                }
				else if(recSeaworld.blnInSurface)
				{
					if(recSeaworld.Navy[r][c].blnBouy)
						cout << ARR_SYMBOLS[BOUY] << ' ';
					else
						cout << ARR_SYMBOLS[EMPTY_SPACE] << ' ';
				}
				else
				{
					if(recSeaworld.Navy[r][c].blnSeaMine)
						cout << ARR_SYMBOLS[SEA_MINE] << ' ';
					else
						cout << ARR_SYMBOLS[EMPTY_SPACE] << ' ';
				}
            }
            cout << endl;
        }
    }
    /** Move The Submarine*/
    void movePlayer(SeaWorld& recSeaworld, char chOption)
	{
		int intRow = recSeaworld.intPLRow;
		int intCol = recSeaworld.intPLCol;
		switch(chOption)
		{
			case 'C':
			case 'c':
				recSeaworld.blnInSurface = !recSeaworld.blnInSurface;
				break;
			case 'W':
			case 'w':
				intRow--;
				break;
			case 'S':
			case 's':
				intRow++;
				break;
			case 'A':
			case 'a':
				intCol--;
				break;
			case 'D':
			case 'd':
				intCol++;
				break;
		}
		/// First validate intDRow and intDCol...
		if(isInNavyArea(recSeaworld, intRow, intCol))
		{
			/// Check if the player is in the same cell as a food/coin item.
			if(recSeaworld.blnInSurface)//== intRow && recSeaworld.intLaPCol == intCol)
			{
                if(recSeaworld.Navy[intRow + 1][intCol].blnBouy || recSeaworld.Navy[intRow -1][intCol].blnBouy
                   || recSeaworld.Navy[intRow][intCol -1].blnBouy || recSeaworld.Navy[intRow][intCol +1].blnBouy
                   || recSeaworld.Navy[intRow +1][intCol +1].blnBouy || recSeaworld.Navy[intRow -1][intCol -1].blnBouy
                   || recSeaworld.Navy[intRow +1][intCol -1].blnBouy || recSeaworld.Navy[intRow -1][intCol +1].blnBouy)
                {
                    recSeaworld.Test = "DETECTED";
				}
			    if(recSeaworld.Navy[intRow][intCol].blnBouy)//== intRow && recSeaworld.intLaPCol == intCol)
                {
                    recSeaworld.Test = "YOU HIT";
				}
				if(recSeaworld.intLaPRow == intRow && recSeaworld.intLaPCol == intCol)
                {
                    recSeaworld.Test = "WON";
				}
			}
			else
			{
			    if(recSeaworld.Navy[intRow + 1][intCol].blnSeaMine || recSeaworld.Navy[intRow -1][intCol].blnSeaMine
                   || recSeaworld.Navy[intRow][intCol -1].blnSeaMine|| recSeaworld.Navy[intRow][intCol +1].blnSeaMine
                   || recSeaworld.Navy[intRow +1][intCol +1].blnSeaMine || recSeaworld.Navy[intRow -1][intCol -1].blnSeaMine
                   || recSeaworld.Navy[intRow +1][intCol -1].blnSeaMine || recSeaworld.Navy[intRow -1][intCol +1].blnSeaMine)
                {
                    recSeaworld.Test = "DETECTED";
				}
				if(recSeaworld.intLaPRow == intRow && recSeaworld.intLaPCol == intCol)
                {
                    recSeaworld.Test = "WON";
				}
			}
			/// Update the player's location.
			recSeaworld.intPLRow = intRow;
			recSeaworld.intPLCol = intCol;
	}
	}
    /** Destroy Sea World*/
    void destroySeaWorld(SeaWorld& recSeaworld)
	{
		assert(recSeaworld.Navy != nullptr);
		for(int r = 0; r < recSeaworld.intRows; r++)
		{
			delete [] recSeaworld.Navy[r];
		}
		delete [] recSeaworld.Navy;
		recSeaworld.Navy = nullptr;
	}
}
