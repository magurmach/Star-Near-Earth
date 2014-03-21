
#include <iostream>
#include<stdlib.h>
using namespace std;

#include "StarNearEarth.h"
#include "SNE_Analyzer.h"
#include <algorithm>
#include <math.h>
#include "FHsparseMat.h"

// for timing our algorithms
#include <time.h>

// ----------- prototypes -------------
void displayOneStar(StarNearEarth star);


// --------------- main ---------------
int main()
{
    string outString, longBlankString
    = " "
    " ";
    int k, arraySize;
    StarNearEarthReader starInput("nearest_stars.txt");
    if (starInput.readError())
    {
        cout << "couldn't open " << starInput.getFileName() << " for input.\n";
        exit(1);
    }
    cout << starInput.getFileName() << endl;
    cout << starInput.getNumStars() << endl;
    // create an array of objects for our own use:
    arraySize = starInput.getNumStars();
    SNE_Analyzer *starArray = new
    SNE_Analyzer[arraySize];
    for (k = 0; k < arraySize; k++)
        starArray[k] = starInput[k];
    // display cartesion coords
    for (int k = 0; k < arraySize; k++)
        cout << starArray[k].getNameCommon() << " "
            << starArray[k].coordToString() << endl;

    int i;
    SpMat mat(36,71,' ');
    double minX,maxX,minY,maxY,minZ,maxZ,unitX,unitY,unitZ;

    /*maxX = minX = maxY = minY = maxZ = minZ = 0;
    there can be negetive component in coordinate
    */
    minX=starArray[0].getX(),maxX=minX;
    minY=starArray[0].getY(),maxY=minY;
    minZ=starArray[0].getZ(),maxZ=minZ;
    for(i=0;i<arraySize;i++)
    {
        double point_X=starArray[i].getX(),point_Y=starArray[i].getY();
        double point_Z=starArray[i].getZ();
        minX=min(minX,point_X);
        maxX=max(maxX,point_X);
        minY=min(minY,point_Y);
        maxY=max(maxY,point_Y);
        minZ=min(minZ,point_Z);
        maxZ=max(maxZ,point_Z);
    }
    //X-Y projection

    printf("\n\n>>X-Y projection\n");
    printf("----------------\n");
    unitX=(maxX-minX)/35.00,unitY=(maxY-minY)/70.0;
    mat.set(round(-minX/unitX),round(-minY/unitY),'S');
    for(i=0;i<arraySize;i++)
    {
        double point_X=starArray[i].getX(),point_Y=starArray[i].getY();
        char mark='*';
        if(starArray[i].getRank()<10)
        {
            mark='0'+starArray[i].getRank();
        }
        int intX=round((point_X-minX)/unitX),intY=round((point_Y-minY)/unitY);
        if(mat.get(intX,intY)==' ')
        {
            mat.set(intX,intY,mark);
        }
    }
    cout<<longBlankString<<longBlankString<<longBlankString<<endl;
    mat.show();
    //----------------------------------
    //X-Z projection

    //mat.();
    mat.clear();
    printf("\n\n>>X-Z projection\n");
    printf("----------------\n");
    unitX=(maxX-minX)/35.00,unitZ=(maxZ-minZ)/70.0;
    mat.set(round(-minX/unitX),round(-minZ/unitZ),'S');
    for(i=0;i<arraySize;i++)
    {
        double point_X=starArray[i].getX(),point_Z=starArray[i].getZ();
        char mark='*';
        if(starArray[i].getRank()<10)
        {
            mark='0'+starArray[i].getRank();
        }
        int intX=round((point_X-minX)/unitX),intZ=round((point_Z-minZ)/unitZ);
        if(mat.get(intX,intZ)==' ')
        {
            mat.set(intX,intZ,mark);
        }
    }
    cout<<longBlankString<<longBlankString<<longBlankString<<endl;
    mat.show();

    //----------------------------------
    //Y-Z projection
    mat.clear();
    printf("\n\n>>Y-Z projection\n");
    printf("----------------\n");
    unitZ=(maxZ-minZ)/70.00,unitY=(maxY-minY)/35.0;
    mat.set(round(-minY/unitY),round(-minZ/unitZ),'S');
    for(i=0;i<arraySize;i++)
    {
        double point_Z=starArray[i].getZ(),point_Y=starArray[i].getY();
        char mark='*';
        if(starArray[i].getRank()<10)
        {
            mark='0'+starArray[i].getRank();
        }
        int intZ=round((point_Z-minZ)/unitZ),intY=round((point_Y-minY)/unitY);
        if(mat.get(intY,intZ)==' ')
        {
            mat.set(intY,intZ,mark);
        }
    }
    cout<<longBlankString<<longBlankString<<longBlankString<<endl;
    mat.show();
    //---------------------------------------

    delete[] starArray;
    return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

void displayOneStar(StarNearEarth star)
{
   cout << "   #"<< star.getRank() << ".  \""
      << star.getNameCommon() <<"\"  ----------" << endl;
   cout << "    LHS Name: " << star.getNameLhs()
      << " CNS Name: " << star.getNameCns() <<  endl;
   cout << "    Absolute Mag: " << star.getMagAbsolute()
      << " Apparent Mag: " << star.getMagApparent() << endl;
   cout << "    Parallax Mean: " << star.getParallaxMean()
      << " variance: " << star.getParallaxVariance() << endl;
   cout << "    Right Asc: " << star.getRAsc()
      << " Dec: " << star.getDec() << endl;
   cout << "    Mass: " << star.getMass()
      << " Prop Mot Mag: " << star.getPropMotionMag() << endl;
}
