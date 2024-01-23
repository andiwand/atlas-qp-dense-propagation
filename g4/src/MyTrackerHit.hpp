#ifndef MyTrackerHit_h
#define MyTrackerHit_h 1

#include "G4Allocator.hh"
#include "G4Circle.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VHit.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "tls.hh"

class TrackerHit : public G4VHit {
public:
  TrackerHit() = default;
  TrackerHit(const TrackerHit &) = default;
  ~TrackerHit() override = default;

  // operators
  TrackerHit &operator=(const TrackerHit &) = default;
  G4bool operator==(const TrackerHit &right) const {
    return (this == &right) ? true : false;
  }

  inline void *operator new(size_t);
  inline void operator delete(void *);

  // methods from base class
  void Draw() override {
    G4VVisManager *pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager) {
      G4Circle circle(fPos);
      circle.SetScreenSize(4.);
      circle.SetFillStyle(G4Circle::filled);
      G4Colour colour(1., 1., 1.);
      G4VisAttributes attribs(colour);
      circle.SetVisAttributes(attribs);
      pVVisManager->Draw(circle);
    }
  }

  void Print() override {
    G4cout << "  trackID: " << fTrackID << " chamberNb: " << fChamberNb
           << "Edep: " << std::setw(7) << G4BestUnit(fEdep, "Energy")
           << " Position: " << std::setw(7) << G4BestUnit(fPos, "Length")
           << G4endl;
  }

  // Set methods
  void SetTrackID(G4int track) { fTrackID = track; };
  void SetChamberNb(G4int chamb) { fChamberNb = chamb; };
  void SetEdep(G4double de) { fEdep = de; };
  void SetPos(G4ThreeVector xyz) { fPos = xyz; };

  // Get methods
  G4int GetTrackID() const { return fTrackID; };
  G4int GetChamberNb() const { return fChamberNb; };
  G4double GetEdep() const { return fEdep; };
  G4ThreeVector GetPos() const { return fPos; };

private:
  G4int fTrackID = -1;
  G4int fChamberNb = -1;
  G4double fEdep = 0.;
  G4ThreeVector fPos;
};

using TrackerHitsCollection = G4THitsCollection<TrackerHit>;

G4ThreadLocal G4Allocator<TrackerHit> *TrackerHitAllocator;

inline void *TrackerHit::operator new(size_t) {
  if (!TrackerHitAllocator)
    TrackerHitAllocator = new G4Allocator<TrackerHit>;
  return (void *)TrackerHitAllocator->MallocSingle();
}

inline void TrackerHit::operator delete(void *hit) {
  TrackerHitAllocator->FreeSingle((TrackerHit *)hit);
}

#endif
