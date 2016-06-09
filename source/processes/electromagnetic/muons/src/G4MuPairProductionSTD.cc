//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id: G4MuPairProductionSTD.cc,v 1.10 2003/06/16 17:01:51 gunter Exp $
// GEANT4 tag $Name: geant4-05-02 $
//
// -------------------------------------------------------------------
//
// GEANT4 Class file
//
//
// File name:     G4MuPairProductionSTD
//
// Author:        Laszlo Urban
//
// Creation date: 30.05.1998
//
// Modifications:
//
// 04-06-98 in DoIt,secondary production condition:
//          range>std::min(threshold,safety)
// 26-10-98 new stuff from R. Kokoulin + cleanup , L.Urban
// 06-05-99 bug fixed , L.Urban
// 10-02-00 modifications+bug fix , new e.m. structure, L.Urban
// 29-05-01 V.Ivanchenko minor changes to provide ANSI -wall compilation
// 10-08-01 new methods Store/Retrieve PhysicsTable (mma)
// 17-09-01 migration of Materials to pure STL (mma)
// 20-09-01 (L.Urban) in ComputeMicroscopicCrossSection, remove:
//          if(MaxPairEnergy<CutInPairEnergy) MaxPairEnergy=CutInPairEnergy
// 26-09-01 completion of store/retrieve PhysicsTable
// 28-09-01 suppression of theMuonPlus ..etc..data members (mma)
// 29-10-01 all static functions no more inlined (mma)
// 07-11-01 particleMass becomes a local variable (mma)
// 19-08-02 V.Ivanchenko update to new design
// 23-12-02 Change interface in order to move to cut per region (V.Ivanchenko)
// 26-12-02 Secondary production moved to derived classes (V.Ivanchenko)
// 13-02-03 SubCutoff regime is assigned to a region (V.Ivanchenko)
//
// -------------------------------------------------------------------
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "G4MuPairProductionSTD.hh"
#include "G4Electron.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4MuPairProductionModel.hh"
#include "G4UniversalFluctuation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4MuPairProductionSTD::G4MuPairProductionSTD(const G4String& name) 
  : G4VEnergyLossSTD(name),
    theParticle(0),
    theBaseParticle(0),
    subCutoff(false)
{
  InitialiseProcess();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4MuPairProductionSTD::~G4MuPairProductionSTD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4MuPairProductionSTD::InitialiseProcess()
{
  SetSecondaryParticle(G4Electron::Electron());

  SetDEDXBinning(120);
  SetLambdaBinning(120);
  SetMinKinEnergy(0.1*keV);
  SetMaxKinEnergy(100.0*TeV);

  G4VEmModel* em = new G4MuPairProductionModel();
  em->SetLowEnergyLimit(0.1*keV);
  em->SetHighEnergyLimit(100.0*TeV);
  AddEmModel(1, em);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

const G4ParticleDefinition* G4MuPairProductionSTD::DefineBaseParticle(
                      const G4ParticleDefinition* p)
{
  if(!theParticle) theParticle = p;
  return theBaseParticle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4MuPairProductionSTD::PrintInfoDefinition()
{
  G4VEnergyLossSTD::PrintInfoDefinition();

  G4cout << "      Parametrised model "
         << G4endl;
//  G4cout << *(LambdaTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4MuPairProductionSTD::SetSubCutoff(G4bool val)
{
  subCutoff = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....



