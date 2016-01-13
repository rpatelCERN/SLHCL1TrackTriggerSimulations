#include "SLHCL1TrackTriggerSimulations/AMSimulationIO/interface/TTStubPlusTPReader.h"

#include "SLHCL1TrackTriggerSimulations/AMSimulationIO/interface/Helper.h"
using namespace slhcl1tt;


// _____________________________________________________________________________
TTStubPlusTPReader::TTStubPlusTPReader(int verbose)
: BasicReader(verbose),

  vp2_pt               (0),
  vp2_eta              (0),
  vp2_phi              (0),
  vp2_vx               (0),
  vp2_vy               (0),
  vp2_vz               (0),
  vp2_charge           (0),
  vp2_pdgId            (0),
  vp2_signal           (0),
  vp2_intime           (0),
  vp2_primary          (0) {}

TTStubPlusTPReader::~TTStubPlusTPReader() {
delete vp2_pt;
delete  vp2_eta;
delete  vp2_phi;
delete  vp2_vx;
delete  vp2_vy;
delete  vp2_vz;
delete  vp2_charge;
 delete vp2_pdgId;
delete  vp2_signal;
 delete vp2_intime;
delete  vp2_primary;

}
int TTStubPlusTPReader::init(TString src, bool full) {
    if (BasicReader::init(src, full))
        return 1;

    tchain->SetBranchAddress("trkParts_pt"       , &(vp2_pt));
    tchain->SetBranchAddress("trkParts_eta"      , &(vp2_eta));
    tchain->SetBranchAddress("trkParts_phi"      , &(vp2_phi));
    tchain->SetBranchAddress("trkParts_vx"       , &(vp2_vx));
    tchain->SetBranchAddress("trkParts_vy"       , &(vp2_vy));
    tchain->SetBranchAddress("trkParts_vz"       , &(vp2_vz));
    tchain->SetBranchAddress("trkParts_charge"   , &(vp2_charge));
    tchain->SetBranchAddress("trkParts_pdgId"    , &(vp2_pdgId));
    tchain->SetBranchAddress("trkParts_signal"   , &(vp2_signal));
    tchain->SetBranchAddress("trkParts_intime"   , &(vp2_intime));
    tchain->SetBranchAddress("trkParts_primary"  , &(vp2_primary));

    tchain->SetBranchStatus("trkParts_pt"       , 1);
    tchain->SetBranchStatus("trkParts_eta"      , 1);
    tchain->SetBranchStatus("trkParts_phi"      , 1);
    tchain->SetBranchStatus("trkParts_vx"       , 1);
    tchain->SetBranchStatus("trkParts_vy"       , 1);
    tchain->SetBranchStatus("trkParts_vz"       , 1);
    tchain->SetBranchStatus("trkParts_charge"   , 1);
    tchain->SetBranchStatus("trkParts_pdgId"    , 1);
    tchain->SetBranchStatus("trkParts_signal"   , 1);
    tchain->SetBranchStatus("trkParts_intime"   , 1);
    tchain->SetBranchStatus("trkParts_primary"  , 1);
    return 0;
}

void TTStubPlusTPReader::init(edm::Event& iEvent){
    std::cout<<"Before Basic Init "<<std::endl;
    BasicReader::init(iEvent);
    std::cout<<"After Basic Init "<<std::endl;
    edm::Handle< std::vector<float> >trkParts_pt,trkParts_eta,trkParts_phi,trkParts_vx, trkParts_vy, trkParts_vz;
    edm::Handle< std::vector<int> >trkParts_charge,trkParts_pdgId;
    edm::Handle< std::vector<bool> >trkParts_signal,trkParts_intime,trkParts_primary;
    //size_t tpsize=trkParts_pt->size();
   //std::cout<<"Before By Label "<<std::endl;
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@pt", trkParts_pt);
    std::cout<<"After Second Get By Label "<<std::endl;
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@eta", trkParts_eta);
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@phi", trkParts_phi);
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@vx", trkParts_vx);
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@vy", trkParts_vy);
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@vz", trkParts_vz);

    iEvent.getByLabel("ntupleTrackingParticles","trkParts@charge", trkParts_charge);
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@pdgId", trkParts_pdgId);

    iEvent.getByLabel("ntupleTrackingParticles","trkParts@signal", trkParts_signal);
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@intime", trkParts_intime);
    iEvent.getByLabel("ntupleTrackingParticles","trkParts@primary", trkParts_primary);
    
  vp2_pt=new std::vector<float>();
  vp2_eta=new std::vector<float>();
  vp2_phi=new std::vector<float>();
  vp2_vx=new std::vector<float>();
  vp2_vy=new std::vector<float>();
  vp2_vz=new std::vector<float>();
  vp2_charge=new std::vector<int>();
  vp2_pdgId=new std::vector<int>();
  vp2_signal=new std::vector<bool>();
  vp2_intime=new std::vector<bool>();
  vp2_primary=new std::vector<bool>();
  //std::cout<<"Did Get By Label "<<std::endl;
    //fill vectors:
if(trkParts_pt.isValid()){
    for(unsigned int i=0; i<trkParts_pt->size(); ++i){
        vp2_pt->push_back(trkParts_pt->at(i));
        vp2_eta->push_back(trkParts_eta->at(i));
        vp2_phi->push_back(trkParts_phi->at(i));
        vp2_vx->push_back(trkParts_vx->at(i));
        vp2_vy->push_back(trkParts_vy->at(i));
        vp2_vz->push_back(trkParts_vz->at(i));
        vp2_charge->push_back(trkParts_charge->at(i));
        vp2_pdgId->push_back(trkParts_pdgId->at(i));
        vp2_signal->push_back(trkParts_signal->at(i));
        vp2_intime->push_back(trkParts_intime->at(i));
        vp2_primary->push_back(trkParts_primary->at(i));

    }
}
}

void TTStubPlusTPReader::nullParticles(const std::vector<bool>& nulling, bool full) {
    nullVectorElements(vp2_pt        , nulling);
    nullVectorElements(vp2_eta       , nulling);
    nullVectorElements(vp2_phi       , nulling);
    nullVectorElements(vp2_vx        , nulling);
    nullVectorElements(vp2_vy        , nulling);
    nullVectorElements(vp2_vz        , nulling);
    //nullVectorElements(vp2_charge    , nulling);  // don't null this guy
    nullVectorElements(vp2_pdgId     , nulling);
    nullVectorElements(vp2_signal    , nulling);
    nullVectorElements(vp2_intime    , nulling);
    //nullVectorElements(vp2_primary   , nulling);  // don't null this guy
}


// _____________________________________________________________________________
TTStubPlusTPWriter::TTStubPlusTPWriter(int verbose)
: BasicWriter(verbose) {}

TTStubPlusTPWriter::~TTStubPlusTPWriter() {}

int TTStubPlusTPWriter::init(TChain* tchain, TString out) {
    if (BasicWriter::init(tchain, out))
        return 1;

    return 0;
}

void TTStubPlusTPWriter::fill() {
    ttree->Fill();
}
