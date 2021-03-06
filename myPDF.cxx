/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *                                                                           *
 * A simple AA PDF class by Ivan Heredia de la Cruz on 4/25/16.              *
 *****************************************************************************/ 

#include "Riostream.h" 

#include "myPDF.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

#include <map>

ClassImp(myPDF) 

 myPDF::myPDF(const char *name, const char *title, 
	      // B^0 -> psi(nS) K* -> mu+ mu- K- pi+
	      RooAbsReal& _mKP,
	      RooAbsReal& _cJ,
	      RooAbsReal& _mPsiP,
	      RooAbsReal& _phi,
	      RooAbsReal& _B0beauty,
	      //const vector< pair<TString, pair< pair<Double_t, Double_t>, pair<Double_t, Double_t> > > >& _Kstar_spin,
	      const vector< pair<TString, pair<const Double_t, const Double_t> > >& _Kstar_spin,
	      const vector< TString >& _varNames,
	      const RooArgSet _amplitudeVars,
	      const TString& _psi_nS,
	      const Double_t& _dRadB0, const Double_t& _dRadKs
          ) :
   RooAbsPdf(name,title),
  
   // B^0 -> psi(nS) K* -> mu+ mu- K- pi+
   mKP("mKP","mKP",this,_mKP),
   cJ("cJ","cJ",this,_cJ),
   mPsiP("mPsiP","mPsiP",this,_mPsiP),
   phi("phi","phi",this,_phi),
   B0beauty("B0beauty","B0beauty",this,_B0beauty),
   //
   Kstar_spin(_Kstar_spin),
   varNames(_varNames),
   amplitudeVars(_amplitudeVars),
   psi_nS(_psi_nS),
   dRadB0(_dRadB0), dRadKs(_dRadKs)
{ 
  // Remember to add any global variable you use in this constructor in the "other" constructor as variable(other.variable) because the evaluate method is called on a copy of the class!

  for (Int_t iAmplitudevar=0; iAmplitudevar<amplitudeVars.getSize(); ++iAmplitudevar) {
    TString varName = varNames[iAmplitudevar];
    amplitudeVarProxy_map[varName] = new RooRealProxy(varName,varName,this,(RooAbsReal&)(*(amplitudeVars.find(varName)))) ;
    //amplitudeVarProxy_map[varName] = new RooRealProxy(varName,varName,amplitudeVars.find(varName),(RooAbsReal&)(*(amplitudeVars.find(varName)))) ;
  } 

  if (psi_nS.EqualTo("1")) 
    MPsi_nS = MJpsi;
  else if (psi_nS.EqualTo("2"))
    MPsi_nS = MPsi2S;
  else {
    cout <<"psi_nS = " <<psi_nS <<" not allowed at the moment." <<endl;
    return;
  }

} 

myPDF::myPDF(const myPDF& other, const char* name) :  
   RooAbsPdf(other,name), 
   // B^0 -> psi(nS) K* -> mu+ mu- K- pi+
   mKP("mKP",this,other.mKP),
   cJ("cJ",this,other.cJ),
   mPsiP("mPsiP",this,other.mPsiP),
   phi("phi",this,other.phi),
   B0beauty("B0beauty",this,other.B0beauty),
   //
   MPsi_nS(other.MPsi_nS),
   //cKs(other.cKs),
   Kstar_spin(other.Kstar_spin),
   varNames(other.varNames),
   amplitudeVars(other.amplitudeVars),
   amplitudeVarProxy_map(other.amplitudeVarProxy_map),
   psi_nS(other.psi_nS),
   dRadB0(other.dRadB0), dRadKs(other.dRadKs)
 {
 }


 Double_t myPDF::evaluate() const 
 {
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
   if (fabs(cJ) > 1  ||  fabs(phi) > TMath::Pi())
     return 0.;

   if ((mKP < MKaon + MPion) || (mKP > MBd - MPsi_nS) || (mPsiP < MPsi_nS + MPion) || (mPsiP > MBd - MKaon))
     return 0.;

   // cos(theta(K*)) from masses
   Double_t mKP2 = mKP*mKP;
   Double_t mPsiP2 = mPsiP*mPsiP;
   Double_t MPsi_nS2 = MPsi_nS*MPsi_nS;
   Double_t _cKs = cosTheta_FromMasses_host(mKP2, mPsiP2, MPsi_nS2, MBd2, MKaon2, MPion2);
   //cout <<"_cKs = " <<_cKs <<" for mKP2 = " <<mKP2 <<" and mPsiP2 = " <<mPsiP2 <<endl;
   
   if (fabs(_cKs) > 1) {
     //cout <<"_cKs = " <<_cKs <<" for mKP2 = " <<mKP2 <<" and mPsiP2 = " <<mPsiP2 <<endl;
     return 0.;
   }
 
   Double_t _phiTrue = phi; 
   if (B0beauty < 0)
     _phiTrue *= -1;

   return PDF(_cKs,_phiTrue);
 }

 Int_t myPDF::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* ) const //rangeName
 { 
   // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
   // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
   // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
   // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
   // EXPRESSION MULTIPLE TIMES

    // if (matchArgs(allVars,analVars,mKP)) return 1 ;
    // if (matchArgs(allVars,analVars,mKP,cJ)) return 2 ;

     return 0 ;
 } 


 Double_t myPDF::analyticalIntegral(Int_t code, const char* rangeName) const  
 { 
   // RETURN ANALYTICAL INTEGRAL DEFINED BY RETURN CODE ASSIGNED BY getAnalyticalIntegral
   // THE MEMBER FUNCTION x.min(rangeName) AND x.max(rangeName) WILL RETURN THE INTEGRATION
   // BOUNDARIES FOR EACH OBSERVABLE x
     
//     if (code==1){
//         return 1;
//     }
//     if (code==2){
//         return 1;

     return 0 ;
 }


/*
// second last term in slide 11 last line
// "c" stands for conjugate
Double_t myPDF::cWignerD_Lb(string helLb, string helLs, string helJ) const
{

    if(helLb=="m1h" && helLs=="m1h" && helJ=="m1")
        return -TMath::Sin(TMath::ACos(cLb)/2.);
    else if(helLb=="m1h" && helLs=="m1h" && helJ=="0")
        return TMath::Cos(TMath::ACos(cLb)/2.);
    else if(helLb=="m1h" && helLs=="m1h" && helJ=="p1")
        return 0.0;
    else if(helLb=="m1h" && helLs=="p1h" && helJ=="m1")
        return 0.0;
    else if(helLb=="m1h" && helLs=="p1h" && helJ=="0")
        return -TMath::Sin(TMath::ACos(cLb)/2.);
    else if(helLb=="m1h" && helLs=="p1h" && helJ=="p1")
        return TMath::Cos(TMath::ACos(cLb)/2.);
    else if(helLb=="m1h" && helLs=="p3h" && helJ=="p1")
        return -TMath::Sin(TMath::ACos(cLb)/2.);
    else if(helLb=="p1h" && helLs=="m1h" && helJ=="m1")
        return TMath::Cos(TMath::ACos(cLb)/2.);
    else if(helLb=="p1h" && helLs=="m1h" && helJ=="0")
        return TMath::Sin(TMath::ACos(cLb)/2.);
    else if(helLb=="p1h" && helLs=="m1h" && helJ=="p1")
        return 0.0;
    else if(helLb=="p1h" && helLs=="p1h" && helJ=="m1")
        return 0.0;
    else if(helLb=="p1h" && helLs=="p1h" && helJ=="0")
        return TMath::Cos(TMath::ACos(cLb)/2.);
    else if(helLb=="p1h" && helLs=="p1h" && helJ=="p1")
        return TMath::Sin(TMath::ACos(cLb)/2.);
    else return 0.0;

}
*/
/*
// exponential * last term in slide 11 last line
TComplex myPDF::WignerDLsSpinOneHalf(string helLs, string help) const
{
    
    if(helLs=="m1h" && help=="m1h")
        return -(TComplex::Exp((TComplex::I()*phiK)/2.)*TMath::Sin(TMath::ACos(cLs)/2.));
    else if(helLs=="m1h" && help=="p1h")
        return TComplex::Exp((TComplex::I()*phiK)/2.)*TMath::Cos(TMath::ACos(cLs)/2.);
    else if(helLs=="p1h" && help=="m1h")
        return TMath::Cos(TMath::ACos(cLs)/2.)/TComplex::Exp((TComplex::I()*phiK)/2.);
    else if(helLs=="p1h" && help=="p1h")
        return TMath::Sin(TMath::ACos(cLs)/2.)/TComplex::Exp((TComplex::I()*phiK)/2.);
    else
        return 0;
    
}

TComplex myPDF::cWignerDLsSpinOneHalf(TComplex WignerDLsSpinOneHalf) const
// "c" stands for conjugate
{
  return TComplex::Conjugate( WignerDLsSpinOneHalf ) ;
}
*/
// Second last sum terms of slide 11: Exp(i*helJ*phiMu) * (Wigner small d-matrix for spin 1)
TComplex myPDF::WignerD_J(string helJ, string helDmu, Double_t angle) const
{

  if (helJ=="m1") {
    if (helDmu=="m1")
      return +((+1. + cJ)*TComplex::Exp(TComplex::I()*angle))/2.;
    else if (helDmu=="p1")
      return -((-1. + cJ)*TComplex::Exp(TComplex::I()*angle))/2.;
    else {
      cout <<"helDmu = " <<helDmu <<" not allowed in \"WignerD_J\" functions for helJ = " <<helJ <<" at the moment. Returning 0 -> \"AngularTerm\" = 0" <<endl ; 
      return 0; }
  } else if (helJ=="0") {
    if (helDmu=="m1")
      return -(TMath::Sqrt(1. - TMath::Power(cJ,2))/TMath::Sqrt2());
    else if (helDmu=="p1")
      return +(TMath::Sqrt(1. - TMath::Power(cJ,2))/TMath::Sqrt2());
    else {
      cout <<"helDmu = " <<helDmu <<" not allowed in \"WignerD_J\" functions for helJ = " <<helJ <<" at the moment. Returning 0 -> \"AngularTerm\" = 0" <<endl ; 
      return 0; }
  } else if(helJ=="p1") {
    if (helDmu=="m1")
      return -(-1. + cJ)/(2.*TComplex::Exp(TComplex::I()*angle));
    else if (helDmu=="p1")
      return +(+1. + cJ)/(2.*TComplex::Exp(TComplex::I()*angle));
    else {
      cout <<"helDmu = " <<helDmu <<" not allowed in \"WignerD_J\" functions for helJ = " <<helJ <<" at the moment. Returning 0 -> \"AngularTerm\" = 0" <<endl ; 
      return 0; }
  } else {
    cout <<"helJ = " <<helJ <<" not allowed in \"WignerD_J\" functions at the moment. Returning 0 -> \"AngularTerm\" = 0" <<endl ; 
    return 0;
  }
    
}

// "c" stands for conjugate
TComplex myPDF::cWignerD_J(TComplex _WignerD_J) const
{
  return TComplex::Conjugate( _WignerD_J );
}

Double_t myPDF::Pmom(Double_t mkp) const
{
 
    Double_t mkp2 = mkp*mkp;
    /*
    Double_t rootterm = MJpsi4mTwoMJpsi2MLb2pMLb4 + mkp2*(mkp2 - TwoMJpsi2pTwoMLb2);
    if (rootterm > 0)
        return InvTwoMLb * TMath::Sqrt(rootterm);
    */
    Double_t rootterm = 0;
    if (psi_nS.EqualTo("1")) 
      rootterm = MJpsi4mTwoMJpsi2MBd2pMBd4 + mkp2*(mkp2 - TwoMJpsi2pTwoMBd2);
    else if (psi_nS.EqualTo("2"))
      rootterm = MPsi2S4mTwoMPsi2S2MBd2pMBd4 + mkp2*(mkp2 - TwoMPsi2S2pTwoMBd2);
    else
      cout <<"psi_nS = " <<psi_nS <<" not allowed in \"Pmom\" function at the moment. Keeping rootterm at 0" <<endl;

    //cout <<"\nrootterm for psi_nS = " <<psi_nS <<" and mkp = " <<mkp <<": " <<rootterm <<endl;
    if (rootterm > 0)
        return InvTwoMBd * TMath::Sqrt(rootterm);
    else { cout <<"WARNING! In \"Pmom\" function: rootterm (" <<rootterm <<") <= 0 for mkp = " <<mkp <<" and psi_nS = " <<psi_nS <<" -> returning 0" <<endl;
        return 0.;
    }    

}

Double_t myPDF::Qmom(Double_t mkp) const
{
    
    Double_t mkp2 = mkp*mkp;
    /*
    Double_t rootterm = MKaon4mTwoMKaon2MProton2pMProton4 + mkp2*(mkp2 - TwoMKaon2pTwoMProton2) ;
    */
    Double_t rootterm = MKaon4mTwoMKaon2MPion2pMPion4 + mkp2*(mkp2 - TwoMKaon2pTwoMPion2) ;
    if (rootterm > 0)
        return 0.5*TMath::Sqrt(rootterm)/mkp;
    else { cout <<"WARNING! In \"Qmom\" function: rootterm <= 0 for mkp = " <<mkp <<" -> returning 0" <<endl;
        return 0.;
    }    
    
}

Double_t myPDF::PhiPHSP(Double_t mkp) const
{
    return Pmom(mkp) * Qmom(mkp) ;
}


Double_t myPDF::BlattWeisskopf_half(Int_t Lmin, Double_t qOrq0, Double_t D) const
{
    Double_t x2 = (D*qOrq0)*(D*qOrq0);
    
    if (Lmin==0)
      return 1. ;
    else if (Lmin==1)
      return (1. + x2) ;
    else if (Lmin==2)
      return (9. + x2*(3 + x2)) ;
    else if (Lmin==3)
      return (225. + x2*(45 + x2*(6 + x2))) ;
    else if (Lmin==4)
      return (11025. + x2*(1575 + x2*(135 + x2*(10 + x2)))) ;
    else if (Lmin==5)
      return (893025. + x2*(99225 + x2*(6300 + x2*(315 + x2*(15 + x2))))) ;
    else { cout <<"WARNING! Lmin = " <<Lmin <<" is not implemented for BlattWeisskopf_half function at the moment. Returning 1" <<endl;
      return 1.;
    }    
    
}

Double_t myPDF::BlattWeisskopf(Int_t Lmin, Double_t q, Double_t q0, Double_t D) const
{
    Double_t rootterm = BlattWeisskopf_half(Lmin, q0, D) / BlattWeisskopf_half(Lmin, q, D) ;
        
    if (rootterm > 0)
        return TMath::Sqrt( rootterm );
    else { cout <<"WARNING! In \"BlattWeisskopf\" function: rootterm <= 0 -> returning 1" <<endl;
        return 1.;
    }    
}

Double_t myPDF::BWGamma(Double_t RMass, Double_t RGamma, Int_t Lmin, Double_t D) const
{

    Double_t QmKP = Qmom(mKP);
    Double_t QRMass = Qmom(RMass);
    Int_t expoterm = 2*Lmin + 1 ;

    Double_t BWG = ( RGamma * RMass * TMath::Power(QmKP/QRMass,expoterm) * TMath::Power(BlattWeisskopf(Lmin, QmKP, QRMass, D),2) ) / mKP;
    //cout <<"BWGamma for RMass = " <<RMass <<": " <<BWG <<endl;
    return BWG ;
    
}

TComplex myPDF::BW(Double_t RMass, Double_t RGamma, Int_t Lmin, Double_t D) const
{

    Double_t num1term = RMass*RMass - mKP*mKP ;
    Double_t num2term = RMass * BWGamma(RMass, RGamma, Lmin, D) ;
    Double_t denoterm = num1term*num1term + num2term*num2term ;

    TComplex bw = TComplex(num1term / denoterm, num2term / denoterm);
    //cout <<"BW for RMass = " <<RMass <<": " <<bw <<endl;
    return bw ;
    
}

TComplex myPDF::RFunction(Double_t RMass, Double_t RGamma, Double_t MomMass, Int_t LminMom, Int_t LminR, Double_t DB0, Double_t DKs) const
{
    Double_t PmKP = Pmom(mKP);
    Double_t PRMass = Pmom(RMass);
    Double_t QmKP = Qmom(mKP);
    Double_t QRMass = Qmom(RMass);    

    //TComplex RFunc = BlattWeisskopf(LminMom, PmKP, PRMass, D) * TMath::Power(PmKP/MomMass,LminMom) * BW(RMass, RGamma, LminR, D) * BlattWeisskopf(LminR, QmKP, QRMass, D) * TMath::Power(QmKP/RMass,LminR);
    TComplex RFunc = BlattWeisskopf(LminMom, PmKP, PRMass, DB0) * TMath::Power(PmKP/MomMass,LminMom) * BW(RMass, RGamma, LminR, DKs) * BlattWeisskopf(LminR, QmKP, QRMass, DKs) * TMath::Power(QmKP/mKP,LminR);
    //cout <<"BlattWeisskopf(LminR, QmKP, QRMass, D) for RMass " <<RMass <<" = " <<BlattWeisskopf(LminR, QmKP, QRMass, D) <<endl;
    //cout <<"BlattWeisskopf(LminMom, PmKP, PRMass, D) for RMass " <<RMass <<" = " <<BlattWeisskopf(LminMom, PmKP, PRMass, D) <<endl;
    //cout <<"BlattWeisskopf(LminMom, PmKP, PRMass, D) * BlattWeisskopf(LminR, QmKP, QRMass, D) for RMass " <<RMass <<" = " <<BlattWeisskopf(LminMom, PmKP, PRMass, D) * BlattWeisskopf(LminR, QmKP, QRMass, D) <<endl;
    //cout <<"TMath::Power(QmKP/RMass,LminR) for RMass " <<RMass <<" = " <<TMath::Power(QmKP/mKP,LminR) <<endl;
    //cout <<"TMath::Power(PmKP/MomMass,LminMom) * TMath::Power(QmKP/RMass,LminR) for RMass " <<RMass <<" = " <<(TMath::Power(PmKP/MomMass,LminMom) * TMath::Power(QmKP/RMass,LminR)) <<endl;
    //cout <<"\nRFunction for RMass " <<RMass <<" = " <<RFunc <<"\n\n" <<endl;
    return RFunc ;
}
/*
// (R * H^{Lambda*} from slide 11 second last line) * (H^{LambdaB} * exp * d^{1/2} from slide 11 last line)
TComplex myPDF::Cterm(string helLs, string helJ, string help) const
{
    if ( (helLs=="p1h" && helJ=="p1") || (helLs=="p1h" && helJ=="0") || (helLs=="m1h" && helJ=="0") || (helLs=="m1h" && helJ=="m1") )
    {
      // K+ spin = 0 and proton spin = 1/2 -> second last argument of Lambda* RFunction can have several values
      TComplex sum1h = HLb1670(helLs, helJ) * HLs1670(help) * RFunction(M1670, G1670, MLb, 0, 0, dRad) + HLb1600(helLs, helJ) * HLs1600(help) * RFunction(M1600, G1600, MLb, 0, 1, dRad) ;
            
        return sum1h * WignerDLsSpinOneHalf(helLs, help) ;
        //return sum1h * cWignerDLsSpinOneHalf(helLs, help) ;
        
    }

    return 0.;
}

// Second last line terms of slide 11 plus last line H^{LambdaB}*exp*d^{1} functions
TComplex myPDF::Cfterm(string helLs, string helJ, string help, string helDmu) const
{

  //return Cterm(helLs, helJ, help) *  WignerD_J(helJ, helDmu, phiMu) ;
  return Cterm(helLs, helJ, help) *  cWignerD_J(WignerD_J(helJ, helDmu, phiMu)) ;
    
}
*/
//Double_t myPDF::Wignerd_R(string spinR, string helJ) const 
Double_t myPDF::Wignerd_R(Double_t cKs, TString spinR, string helJ) const 
{
  Double_t helJ_m1 = 0, helJ_0 = 0;

  if (spinR=="0") {
    helJ_0 = 1. ;
    if (helJ!="0") 
      cout <<"helJ = " <<helJ <<" is not allowed for spinR-" <<spinR <<" Wigner d^{spinR}_{helJ,0} functions. Returning 0" <<endl;
  } else if (spinR=="1") {
    helJ_0 = cKs ;
    helJ_m1 = +(TMath::Sin(TMath::ACos(cKs)) / TMath::Sqrt2()) ;
  } else if (spinR=="2") {
    helJ_0 = +(3*TMath::Power(cKs,2) -1)/2. ;
    helJ_m1 = +(TMath::Sin(2*TMath::ACos(cKs)) * TMath::Sqrt(3./8.)) ;
  } else if (spinR=="3") {
    helJ_0 = +(5*TMath::Power(cKs,3) - 3*cKs)/2. ;
    helJ_m1 = +(TMath::Sin(TMath::ACos(cKs)) * (5*TMath::Cos(2*TMath::ACos(cKs)) + 3.) * TMath::Sqrt(3.)/8.) ;
  } else if (spinR=="5") {
    helJ_0 = +(63*TMath::Power(cKs,5) - 70*TMath::Power(cKs,3) + 15*cKs)/8. ;
    helJ_m1 = +(TMath::Sin(2*TMath::ACos(cKs)) * (21*TMath::Power(cKs,4) - 14*TMath::Power(cKs,2) + 1) * TMath::Sqrt(15./2.)) / 8. ;
  } else {
    cout <<"spinR = " <<spinR <<" is not implemented for Wigner d^{spinR}_{helJ,0} functions at the moment. Returning 0 -> \"AngularTerm\" = 0" <<endl;
    return 0 ;
  }

  if (helJ=="0")
    return helJ_0 ;
  else if (helJ=="m1")
    return helJ_m1 ;
  else if (helJ=="p1")
    return -helJ_m1 ;
  else { cout <<"helJ = " <<helJ <<" is not allowed for spinR-" <<spinR <<" Wigner d^{spinR}_{helJ,0} functions. Returning 0" <<endl;
    return 0 ;
  }

}

//TComplex myPDF::AngularTerm(string R, string spinR, string helJ, string helDmu) const
TComplex myPDF::AngularTerm(Double_t cKs, TString R, TString spinR, string helJ, string helDmu, Double_t phiTrue) const
{
  //cout <<"\nAngularTerm for K* " <<R <<" and helDmu = " <<helDmu <<" and helJ = " <<helJ <<" is made of Wignerd_R(spinR, helJ) * cWignerD_J(helJ, helDmu, phi) = " <<Wignerd_R(spinR, helJ) <<" * " <<cWignerD_J( WignerD_J(helJ, helDmu, phi) ) <<endl;
  //cout <<"It is multiplied by H(R,helJ) = H(" <<R <<"," <<helJ <<") = " <<H(R,helJ) <<endl;
  return H(R,helJ) * Wignerd_R(cKs, spinR, helJ) * cWignerD_J( WignerD_J(helJ, helDmu, phiTrue) ) ;

}
/*
// all allowed sums terms in slide 11 last equation
TComplex myPDF::ME(string helLb, string help, string helDmu) const
{
    
    return
    Cfterm("m1h", "m1", help, helDmu) * cWignerD_Lb(helLb, "m1h", "m1") +
    Cfterm("m1h", "0",  help, helDmu) * cWignerD_Lb(helLb, "m1h", "0") +
    Cfterm("m1h", "p1", help, helDmu) * cWignerD_Lb(helLb, "m1h", "p1") +
    Cfterm("p1h", "m1", help, helDmu) * cWignerD_Lb(helLb, "p1h", "m1") +
    Cfterm("p1h", "0",  help, helDmu) * cWignerD_Lb(helLb, "p1h", "0") +
    Cfterm("p1h", "p1", help, helDmu) * cWignerD_Lb(helLb, "p1h", "p1") 
    ;
    
}
*/
TComplex myPDF::ME( Double_t cKs, string helDmu, Double_t phiTrue ) const
{
  /*
  // K+ and pi- have 0 spin -> second last argument of K* RFunction is = spin(K*)
  return
    RFunction(M892, G892, MBd, 0, 1, dRad) * ( AngularTerm("K*(892)", "1", "m1", helDmu) + 
						      AngularTerm("K*(892)", "1", "0", helDmu) +
						      AngularTerm("K*(892)", "1", "p1", helDmu) )
    // + ...
    ;
  // any other K* should be added above   
  */
  TComplex matrixElement = 0.;
  // K+ and pi- have 0 spin -> third last argument of K* RFunction is = spin(K*)
  for (Int_t iKstar_S=0; iKstar_S<(Int_t)Kstar_spin.size(); ++iKstar_S) {
    TString R = Kstar_spin[iKstar_S].first ;
    TString spin = R(Kstar_spin[iKstar_S].first.Length() -1) ;
    TString mass = R(0, Kstar_spin[iKstar_S].first.Length() -2) ;
    TComplex matrixElement_R = 0.;
    if (spin.EqualTo("0")) { // for spin0 K*, fourth last argument = spin(psi_nS) = spin.Atoi() + 1 = 1
      matrixElement_R = RFunction(Kstar_spin[iKstar_S].second.first, Kstar_spin[iKstar_S].second.second, MBd, spin.Atoi()+1, spin.Atoi(), dRadB0, dRadKs) *
	                AngularTerm(cKs, R, spin, "0", helDmu, phiTrue) ;
    } else { // for non-0 spin K*, fourth last argument = spin(K*) - spin(psi_nS) = spin.Atoi() - 1
      matrixElement_R = RFunction(Kstar_spin[iKstar_S].second.first, Kstar_spin[iKstar_S].second.second, MBd, spin.Atoi()-1, spin.Atoi(), dRadB0, dRadKs) *
	                ( AngularTerm(cKs, R, spin, "m1", helDmu, phiTrue) + AngularTerm(cKs, R, spin, "0", helDmu, phiTrue) + AngularTerm(cKs, R, spin, "p1", helDmu, phiTrue) ) ;
    }
    //cout <<"\nAngularTerm.Rho() for " <<R <<" = " <<(AngularTerm(R, spin, "0", helDmu)).Rho() <<endl;
    //cout <<"matrixElement for (R,helDmu) = (" <<R <<"," <<helDmu <<") = H(R,helJ) * RFunction * AngularTerm = " <<matrixElement_R <<endl;
    matrixElement += matrixElement_R;
    //cout <<"matrixElement_R.Rho2() for (R,helDmu) = (" <<R <<"," <<helDmu <<") = " <<matrixElement_R.Rho2() <<"\n\n" <<endl;
  }
  return matrixElement ;

}

// all allowed sums terms in slide 11 second last equation
/*
TComplex myPDF::ME2() const
{
  // M_{HelLambdaB,HelP,DeltaHelMu} in slide 11
    TComplex MEm1hm1hm1 = ME("m1h", "m1h", "m1");
    TComplex MEm1hm1hp1 = ME("m1h", "m1h", "p1");
    TComplex MEm1hp1hm1 = ME("m1h", "p1h", "m1");
    TComplex MEm1hp1hp1 = ME("m1h", "p1h", "p1");

    TComplex MEp1hm1hm1 = ME("p1h", "m1h", "m1");
    TComplex MEp1hm1hp1 = ME("p1h", "m1h", "p1");
    TComplex MEp1hp1hm1 = ME("p1h", "p1h", "m1");
    TComplex MEp1hp1hp1 = ME("p1h", "p1h", "p1");

    
    return
    MEm1hm1hm1 * TComplex::Conjugate(MEm1hm1hm1) +
    MEm1hm1hp1 * TComplex::Conjugate(MEm1hm1hp1) +
    MEm1hp1hm1 * TComplex::Conjugate(MEm1hp1hm1) +
    MEm1hp1hp1 * TComplex::Conjugate(MEm1hp1hp1) +
    MEp1hm1hm1 * TComplex::Conjugate(MEp1hm1hm1) +
    MEp1hm1hp1 * TComplex::Conjugate(MEp1hm1hp1) +
    MEp1hp1hm1 * TComplex::Conjugate(MEp1hp1hm1) +
    MEp1hp1hp1 * TComplex::Conjugate(MEp1hp1hp1)
    ;

}
*/
/*
TComplex myPDF::ME2() const
{
  // M_{DeltaHelMu}
    TComplex MEm1 = ME("m1");
    TComplex MEp1 = ME("p1");

    return
    MEm1 * TComplex::Conjugate(MEm1) +
    MEp1 * TComplex::Conjugate(MEp1)
    ;
}
*/
Double_t myPDF::ME2(Double_t cKs, Double_t phiTrue) const
{
  //cout <<"\nME(cKs,\"m1\",phiTrue) + ME(cKs,\"p1\",phiTrue) = " <<ME(cKs,"p1",phiTrue) <<" + " <<ME(cKs,"p1",phiTrue) <<endl;
  //cout <<"ME(cKs,\"m1\",phiTrue).Rho2() + ME(cKs,\"p1\",phiTrue).Rho2() = " <<ME(cKs,"m1",phiTrue).Rho2() <<" + " <<ME(cKs,"p1",phiTrue).Rho2() <<endl;
  return ME(cKs,"m1",phiTrue).Rho2() + ME(cKs,"p1",phiTrue).Rho2() ;
}

//TComplex myPDF::PDF() const
//Double_t myPDF::PDF(Double_t cKs) const
Double_t myPDF::PDF(Double_t cKs, Double_t phiTrue) const
{
  //cout <<"\nME2(cKs, phiTrue) = " <<ME2(cKs, phiTrue) <<endl;
  return ME2(cKs, phiTrue) * PhiPHSP(mKP);
  //return ME2() ; // missing PHSP
}

/*
// first term in slide 11 last line for Lambda*(1600)
TComplex myPDF::HLb1600(string helLs, string helJ) const
{
    
    if(helLs=="m1h" && helJ=="m1")
        return (-2.*a1600L0S1 + 2.*a1600L1S1 - TMath::Sqrt2()*a1600L1S3 + TMath::Sqrt2()*a1600L2S3 + TComplex::I()*(-2.*b1600L0S1 + 2.*b1600L1S1 + TMath::Sqrt2()*(-b1600L1S3 + b1600L2S3)))/(2.*TMath::Sqrt(3.));
    else if(helLs=="m1h" && helJ=="0")
        return -(TMath::Sqrt2()*a1600L0S1 + TMath::Sqrt2()*a1600L1S1 + 2.*a1600L1S3 + 2.*a1600L2S3 + TComplex::I()*(TMath::Sqrt2()*b1600L0S1 + TMath::Sqrt2()*b1600L1S1 + 2.*(b1600L1S3 + b1600L2S3)))/(2.*TMath::Sqrt(3.));
    else if(helLs=="m1h" && helJ=="p1")
        return 0.;
    else if(helLs=="p1h" && helJ=="m1")
        return 0.;
    else if(helLs=="p1h" && helJ=="0")
        return (TMath::Sqrt2()*(a1600L0S1 - a1600L1S1) + 2.*(a1600L2S3 - a1600L1S3) + TComplex::I()*(TMath::Sqrt2()*(b1600L0S1 - b1600L1S1)  + 2.*(b1600L2S3 - b1600L1S3)))/(2.*TMath::Sqrt(3.));
    else if(helLs=="p1h" && helJ=="p1")
        return (2.*a1600L0S1 + 2.*a1600L1S1 - TMath::Sqrt2()*a1600L1S3 - TMath::Sqrt2()*a1600L2S3 + TComplex::I()*(2.*b1600L0S1 + 2.*b1600L1S1 - TMath::Sqrt2()*(b1600L1S3 + b1600L2S3)))/(2.*TMath::Sqrt(3.));
    else
        return 0.;
    
}

// first term in slide 11 last line for Lambda*(1670)
TComplex myPDF::HLb1670(string helLs, string helJ) const
{
    
    if(helLs=="m1h" && helJ=="m1")
        return (-2.*a1670L0S1 + 2.*a1670L1S1 - TMath::Sqrt2()*a1670L1S3 + TMath::Sqrt2()*a1670L2S3 + TComplex::I()*(-2.*b1670L0S1 + 2.*b1670L1S1 + TMath::Sqrt2()*(-b1670L1S3 + b1670L2S3)))/(2.*TMath::Sqrt(3.));
    else if(helLs=="m1h" && helJ=="0")
        return -(TMath::Sqrt2()*a1670L0S1 + TMath::Sqrt2()*a1670L1S1 + 2.*a1670L1S3 + 2.*a1670L2S3 + TComplex::I()*(TMath::Sqrt2()*b1670L0S1 + TMath::Sqrt2()*b1670L1S1 + 2.*(b1670L1S3 + b1670L2S3)))/(2.*TMath::Sqrt(3.));
    else if(helLs=="m1h" && helJ=="p1")
        return 0.;
    else if(helLs=="p1h" && helJ=="m1")
        return 0.;
    else if(helLs=="p1h" && helJ=="0")
        return (TMath::Sqrt2()*(a1670L0S1 - a1670L1S1) + 2.*(a1670L2S3 - a1670L1S3) + TComplex::I()*(TMath::Sqrt2()*(b1670L0S1 - b1670L1S1)  + 2.*(b1670L2S3 - b1670L1S3)))/(2.*TMath::Sqrt(3.));
    else if(helLs=="p1h" && helJ=="p1")
        return (2.*a1670L0S1 + 2.*a1670L1S1 - TMath::Sqrt2()*a1670L1S3 - TMath::Sqrt2()*a1670L2S3 + TComplex::I()*(2.*b1670L0S1 + 2.*b1670L1S1 - TMath::Sqrt2()*(b1670L1S3 + b1670L2S3)))/(2.*TMath::Sqrt(3.));
    else
        return 0.;
    
}
*/

// H term in slide 11 second last line for Lambda*(1600)
Double_t myPDF::HLs1600(string help) const
{
    
    if(help=="m1h")
        return -1.;
    else if(help=="p1h")
        return 1.;
    else { cout <<"WARNING! In \"HLs1600\" function: help = " <<help <<" -> returning 0" <<endl;
        return 0;
    }    
}

// H term in slide 11 second last line for Lambda*(1670)
Double_t myPDF::HLs1670(string help) const
{
    
    if(help=="m1h")
        return 1.;
    else if(help=="p1h")
        return 1.;
    else { cout <<"WARNING! In \"HLs1670\" function: help = " <<help <<" -> returning 0" <<endl;
        return 0;
    }    
    
}

// a + i*b
//TComplex myPDF::H(string R, string helJ) const
// a*exp(i*b)
TComplex myPDF::H(TString R, string helJ) const
{
  /*    
  if ( R=="K*(892)" ) {
    if ( helJ=="m1")
        return a892m1 + TComplex::I()*b892m1 ;
    else if ( helJ=="0" )
      return a892z + TComplex::I()*b892z ;
    else if ( helJ=="p1" )
      return a892p1 + TComplex::I()*b892p1 ;
    else {
      cout <<"helJ = \"" <<helJ <<"\" not allowed for R = \"" <<R <<"\" in the H function at the moment. Returning 0" <<endl;
      return 0.;
    }
  else {
    cout <<"helJ = \"" <<helJ <<"\" not allowed for R = \"" <<R <<"\" in the H function at the moment. Returning 0" <<endl;
    return 0.;
  }
  */
  TString name_helJ = R+"_"+helJ;
  TString a_helJ = "a"+name_helJ; TString b_helJ = "b"+name_helJ;
  RooRealProxy* a = amplitudeVarProxy_map.find(a_helJ)->second ;
  RooRealProxy* b = amplitudeVarProxy_map.find(b_helJ)->second ;
  if ( a ) {
    if ( b ) {
      return (RooRealProxy)(*a) * TComplex::Exp(TComplex::I()*(RooRealProxy)(*b)) ;
      //return (RooRealProxy)(*a) * (TMath::Cos((RooRealProxy)(*b)) + TComplex::I()*TMath::Sin((RooRealProxy)(*b))) ; // no improvement
    } else {
      cout <<"RooRealProxy = \""+b_helJ+"\" not found in amplitudeVarProxy_map. Returning 0" <<endl;
      return 0.; }  
  } else {
    cout <<"RooRealProxy = \""+a_helJ+"\" not found in amplitudeVarProxy_map. Returning 0" <<endl;
    return 0.;
  }  

}
