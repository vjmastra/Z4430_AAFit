/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "sqDalitzToMassesPdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

#include "RooRealVar.h" 
#include "myPDF.h" 
//#include "utilities.h" // already included

ClassImp(sqDalitzToMassesPdf) 

 sqDalitzToMassesPdf::sqDalitzToMassesPdf(const char *name, const char *title, 
					  RooAbsReal& _x,
					  RooAbsReal& _y,
					  const RooAbsPdf *_squareDalitz,
					  RooRealVar* _m2KPi,
					  RooRealVar* _cosKstar,
					  const Double_t _MPsi_nS
					  ) :
  RooAbsPdf(name,title), 
  x("x","x",this,_x),
  y("y","y",this,_y),
  squareDalitz(_squareDalitz),
  m2KPi(_m2KPi),
  cosKstar(_cosKstar),
  MPsi_nS(_MPsi_nS)
{ 
} 


 sqDalitzToMassesPdf::sqDalitzToMassesPdf(const sqDalitzToMassesPdf& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   y("y",this,other.y),
   squareDalitz(other.squareDalitz),
   m2KPi(other.m2KPi),
   cosKstar(other.cosKstar),
   MPsi_nS(other.MPsi_nS)
 { 
 } 



 Double_t sqDalitzToMassesPdf::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
   Double_t x2 = TMath::Power(x,2);
   Double_t y2 = TMath::Power(y,2);
   Double_t m2Psi_nS = TMath::Power(MPsi_nS,2);
   m2KPi->setVal(x2);
   cosKstar->setVal( cosTheta_FromMasses_host(x2, y2, m2Psi_nS, MBd2, MKaon2, MPion2) );

   // see section "Change of Variables for a Double Integral" at http://tutorial.math.lamar.edu/Classes/CalcIII/ChangeOfVariables.aspx
   Double_t jacobianDen2 = denom2_for_cosTheta_FromMasses(x2, m2Psi_nS, MBd2, MKaon2, MPion2) ;
   if (jacobianDen2 > 0) {
     Double_t jacobian = fabs( (2*x)*(-x2*y/TMath::Sqrt(jacobianDen2)) ) ;
     //printf("\njacobian = %f", jacobian);
     jacobian = 1;
     return squareDalitz->getVal() * jacobian ; 
   }
   else return 0;

 }



