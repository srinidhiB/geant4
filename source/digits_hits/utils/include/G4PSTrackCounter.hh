//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4PSTrackCounter.hh,v 1.2 2007/06/21 15:03:56 gunter Exp $
// GEANT4 tag $Name: geant4-09-00 $
//

#ifndef G4PSTrackCounter_h
#define G4PSTrackCounter_h 1

#include "G4VPrimitiveScorer.hh"
#include "G4THitsMap.hh"

#include "G4PSDirectionFlag.hh"


//////////////////////////////////////////////////////////////////////////////////
// (Description)
//   This is a primitive scorer class for scoring Number of Steps in the cell.
// 
// Created: 2007-02-02 Tsukasa ASO, Akinori Kimura.
// 
///////////////////////////////////////////////////////////////////////////////


class G4PSTrackCounter : public G4VPrimitiveScorer
{
 
 public: // with description
      G4PSTrackCounter(G4String name, G4int direction, G4int depth=0);

  protected: // with description
      virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*);

  public:
      virtual ~G4PSTrackCounter();

      inline void Weighted(G4bool flg=true) { weighted = flg; }
      // Multiply track weight

  public: 
      virtual void Initialize(G4HCofThisEvent*);
      virtual void EndOfEvent(G4HCofThisEvent*);
      virtual void clear();

  public:
      virtual void DrawAll();
      virtual void PrintAll();

  private:
      G4int HCID;
      G4int fDirection;
      G4THitsMap<G4double>* EvtMap;
      G4bool weighted;

  public:


};



#endif