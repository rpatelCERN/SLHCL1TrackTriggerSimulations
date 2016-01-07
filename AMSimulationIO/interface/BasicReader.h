#ifndef AMSimulationIO_BasicReader_h_
#define AMSimulationIO_BasicReader_h_

#include "TChain.h"
#include "TFile.h"
#include "TFileCollection.h"
#include "TROOT.h"
#include "TString.h"
#include "TTree.h"
#include <cassert>
#include <memory>
#include <vector>
#include "FWCore/Framework/interface/Event.h"
namespace slhcl1tt {


// _____________________________________________________________________________
class BasicReader {
  public:
    BasicReader(int verbose=1);
    ~BasicReader();

    int init(TString src, bool full=true);
    void init(edm::Event& iEvent);
    template <typename T>
    void nullVectorElements(std::vector<T>* v, const std::vector<bool>& nulling);

    void nullStubs(const std::vector<bool>& nulling, bool full=true);

    Long64_t loadTree(Long64_t entry) { return tchain->LoadTree(entry); }

    Int_t getEntry(Long64_t entry) { return tchain->GetEntry(entry); }

    TChain* getChain() { return tchain; }

    // genParticle information
    std::vector<float> *          vp_pt;
    std::vector<float> *          vp_eta;
    std::vector<float> *          vp_phi;
    std::vector<float> *          vp_vx;
    std::vector<float> *          vp_vy;
    std::vector<float> *          vp_vz;
    std::vector<int> *            vp_charge;

    // Stub information
    std::vector<float> *          vb_x;
    std::vector<float> *          vb_y;
    std::vector<float> *          vb_z;
    std::vector<float> *          vb_r;
    std::vector<float> *          vb_eta;
    std::vector<float> *          vb_phi;
    std::vector<float> *          vb_coordx;
    std::vector<float> *          vb_coordy;
    std::vector<float> *          vb_trigBend;
    std::vector<float> *          vb_roughPt;
    std::vector<float> *          vb_clusWidth0;
    std::vector<float> *          vb_clusWidth1;
    std::vector<unsigned> *       vb_modId;
    std::vector<int> *            vb_tpId;

  protected:
    TChain* tchain;
    int treenumber;
    const int verbose_;
};


// _____________________________________________________________________________
class BasicWriter {
  public:
    BasicWriter(int verbose=1);
    ~BasicWriter();

    int init(TChain* tchain, TString out);

    Long64_t writeTree();

  protected:
    TFile* tfile;
    TTree* ttree;
    const int verbose_;
};


// _____________________________________________________________________________
// Template implementation
template <typename T>
void BasicReader::nullVectorElements(std::vector<T>* v, const std::vector<bool>& nulling) {
    assert(v->size() == nulling.size());
    for (unsigned i=0; i<nulling.size(); ++i) {
        if (nulling.at(i))
            v->at(i) = 0;
    }
}

}  // namespace slhcl1tt

#endif
