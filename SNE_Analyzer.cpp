#include "SNE_Analyzer.h"
#include<math.h>
#include<string>
using namespace std;

void SNE_Analyzer::calcCartCoords()
{
    double ly=(3.262)/getParallaxMean();
    double rad=getRAsc()*(3.1416)/180.0;
    double decrad=getDec()*(3.1416)/180.0;
    x=ly*cos(decrad)*cos(rad);
    y=ly*cos(decrad)*sin(rad);
    z=ly*sin(decrad);
}
string SNE_Analyzer::coordToString()
{
    char a[20];
    sprintf(a,"%.6lf",x);
    string sx(a);
    sprintf(a,"%.6lf",y);
    string sy(a);
    sprintf(a,"%.6lf",z);
    string sz(a);
    return "("+sx+","+sy+","+sz+")";
}

SNE_Analyzer & SNE_Analyzer::operator=( const
StarNearEarth &sne )
{
    setRank(sne.getRank());
    setNameCns(sne.getNameCns());
    setNumComponents(sne.getNumComponents());
    setNameLhs(sne.getNameLhs());
    setRAsc(sne.getRAsc());
    setDec(sne.getDec());
    setPropMotionMag(sne.getPropMotionMag());
    setPropMotionDir(sne.getPropMotionDir());
    setParallaxMean(sne.getParallaxMean());
    setParallaxVariance(sne.getParallaxVariance());
    setWhiteDwarfFlag(sne.getWhiteDwarfFlag());
    setSpectralType(sne.getSpectralType());
    setMagApparent(sne.getMagApparent());
    setMagAbsolute(sne.getMagAbsolute());
    setMass(sne.getMass());
    setNotes(sne.getNotes());
    setNameCommon(sne.getNameCommon());
    calcCartCoords();
    return *this;
}
