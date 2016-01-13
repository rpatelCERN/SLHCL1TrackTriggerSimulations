#include "SLHCL1TrackTriggerSimulations/AMSimulationIO/interface/BasicReader.h"

#include "SLHCL1TrackTriggerSimulations/AMSimulationIO/interface/Helper.h"
using namespace slhcl1tt;


// _____________________________________________________________________________
BasicReader::BasicReader(int verbose)
: vp_pt               (0),
  vp_eta              (0),
  vp_phi              (0),
  vp_vx               (0),
  vp_vy               (0),
  vp_vz               (0),
  vp_charge           (0),
  //
  vb_x                (0),
  vb_y                (0),
  vb_z                (0),
  vb_r                (0),
  vb_eta              (0),
  vb_phi              (0),
  vb_coordx           (0),
  vb_coordy           (0),
  vb_trigBend         (0),
  vb_roughPt          (0),
  vb_clusWidth0       (0),
  vb_clusWidth1       (0),
  vb_modId            (0),
  vb_tpId             (0),
  //
  verbose_(verbose) {
  vp_pt=new std::vector<float>();
  vp_eta=new std::vector<float>();
  vp_phi=new std::vector<float>();
  vp_vx=new std::vector<float>();
  vp_vy=new std::vector<float>();
  vp_vz=new std::vector<float>();
  vp_charge=new std::vector<int>();

  vb_x=new std::vector<float>();
  vb_y=new std::vector<float>();
  vb_z=new std::vector<float>();
  vb_r=new std::vector<float>();
  vb_eta=new std::vector<float>();
  vb_phi=new std::vector<float>();
  vb_coordx=new std::vector<float>();
  vb_coordy=new std::vector<float>();
  vb_trigBend=new std::vector<float>();
  vb_roughPt=new std::vector<float>();
  vb_clusWidth0=new std::vector<float>();
  vb_clusWidth1=new std::vector<float>();
  vb_modId=new std::vector<unsigned>();
  vb_tpId=new std::vector<int>();
}



BasicReader::~BasicReader() {
    if (tchain)  delete tchain;

  //
  delete vp_pt;
  //
  delete vp_eta;
  delete  vp_phi;
  delete  vp_vx;
  delete  vp_vy;
  delete  vp_vz;
  delete  vp_charge;
  delete  vb_x;
  delete  vb_y;
  delete  vb_z;
       delete  vb_r;
       delete  vb_eta;
       delete  vb_phi;
       delete  vb_coordx;;
       delete  vb_coordy;
       delete  vb_trigBend;
       delete  vb_roughPt;
       delete  vb_clusWidth0;
       delete  vb_clusWidth1;
       delete  vb_modId;
       delete  vb_tpId;
  
  //     }
}

int BasicReader::init(TString src, bool full) {
    if (!src.EndsWith(".root") && !src.EndsWith(".txt")) {
        std::cout << Error() << "Input source must be either .root or .txt" << std::endl;
        return 1;
    }

    if (verbose_)  std::cout << Info() << "Opening " << src << std::endl;
    tchain = new TChain("ntupler/tree");

    if (src.EndsWith(".root")) {
        if (tchain->Add(src) ) {
            if (verbose_)  std::cout << Info() << "Successfully read " << src << std::endl;
        } else {
            std::cout << Error() << "Failed to read " << src << std::endl;
            return 1;
        }

    } else if (src.EndsWith(".txt")) {
        TFileCollection fc("fileinfolist", "", src);
        if (tchain->AddFileInfoList((TCollection*) fc.GetList()) ) {
            if (verbose_)  std::cout << Info() << "Successfully read " << src << std::endl;
        } else {
            std::cout << Error() << "Failed to read " << src << std::endl;
            return 1;
        }
    }

    assert(tchain != 0);
    treenumber = tchain->GetTreeNumber();

    tchain->SetBranchAddress("genParts_pt"       , &(vp_pt));
    tchain->SetBranchAddress("genParts_eta"      , &(vp_eta));
    tchain->SetBranchAddress("genParts_phi"      , &(vp_phi));
    tchain->SetBranchAddress("genParts_vx"       , &(vp_vx));
    tchain->SetBranchAddress("genParts_vy"       , &(vp_vy));
    tchain->SetBranchAddress("genParts_vz"       , &(vp_vz));
    tchain->SetBranchAddress("genParts_charge"   , &(vp_charge));
    if (full)  tchain->SetBranchAddress("TTStubs_x"         , &(vb_x));
    if (full)  tchain->SetBranchAddress("TTStubs_y"         , &(vb_y));
    tchain->SetBranchAddress("TTStubs_z"         , &(vb_z));
    tchain->SetBranchAddress("TTStubs_r"         , &(vb_r));
    tchain->SetBranchAddress("TTStubs_eta"       , &(vb_eta));
    tchain->SetBranchAddress("TTStubs_phi"       , &(vb_phi));
    tchain->SetBranchAddress("TTStubs_coordx"    , &(vb_coordx));
    tchain->SetBranchAddress("TTStubs_coordy"    , &(vb_coordy));
    tchain->SetBranchAddress("TTStubs_trigBend"  , &(vb_trigBend));
    if (full)  tchain->SetBranchAddress("TTStubs_roughPt"   , &(vb_roughPt));
    if (full)  tchain->SetBranchAddress("TTStubs_clusWidth0", &(vb_clusWidth0));
    if (full)  tchain->SetBranchAddress("TTStubs_clusWidth1", &(vb_clusWidth1));
    tchain->SetBranchAddress("TTStubs_modId"     , &(vb_modId));
    tchain->SetBranchAddress("TTStubs_tpId"      , &(vb_tpId));

    tchain->SetBranchStatus("*"                 , 0);
    tchain->SetBranchStatus("genParts_pt"       , 1);
    tchain->SetBranchStatus("genParts_eta"      , 1);
    tchain->SetBranchStatus("genParts_phi"      , 1);
    tchain->SetBranchStatus("genParts_vx"       , 1);
    tchain->SetBranchStatus("genParts_vy"       , 1);
    tchain->SetBranchStatus("genParts_vz"       , 1);
    tchain->SetBranchStatus("genParts_charge"   , 1);
    if (full)  tchain->SetBranchStatus("TTStubs_x"         , 1);
    if (full)  tchain->SetBranchStatus("TTStubs_y"         , 1);
    tchain->SetBranchStatus("TTStubs_z"         , 1);
    tchain->SetBranchStatus("TTStubs_r"         , 1);
    tchain->SetBranchStatus("TTStubs_eta"       , 1);
    tchain->SetBranchStatus("TTStubs_phi"       , 1);
    tchain->SetBranchStatus("TTStubs_coordx"    , 1);
    tchain->SetBranchStatus("TTStubs_coordy"    , 1);
    tchain->SetBranchStatus("TTStubs_trigBend"  , 1);
    if (full)  tchain->SetBranchStatus("TTStubs_roughPt"   , 1);
    if (full)  tchain->SetBranchStatus("TTStubs_clusWidth0", 1);
    if (full)  tchain->SetBranchStatus("TTStubs_clusWidth1", 1);
    tchain->SetBranchStatus("TTStubs_modId"     , 1);
    tchain->SetBranchStatus("TTStubs_tpId"      , 1);
    return 0;
}

void BasicReader::nullStubs(const std::vector<bool>& nulling, bool full) {
    if (full)  nullVectorElements(vb_x         , nulling);
    if (full)  nullVectorElements(vb_y         , nulling);
    nullVectorElements(vb_z         , nulling);
    nullVectorElements(vb_r         , nulling);
    nullVectorElements(vb_eta       , nulling);
    nullVectorElements(vb_phi       , nulling);
    nullVectorElements(vb_coordx    , nulling);
    nullVectorElements(vb_coordy    , nulling);
    nullVectorElements(vb_trigBend  , nulling);
    if (full)  nullVectorElements(vb_roughPt   , nulling);
    if (full)  nullVectorElements(vb_clusWidth0, nulling);
    if (full)  nullVectorElements(vb_clusWidth1, nulling);
    //nullVectorElements(vb_modId     , nulling);  // don't null this guy
    nullVectorElements(vb_tpId      , nulling);
}


// _____________________________________________________________________________
BasicWriter::BasicWriter(int verbose)
: verbose_(verbose) {}

BasicWriter::~BasicWriter() {
    if (ttree)  delete ttree;
    if (tfile)  delete tfile;
}

int BasicWriter::init(TChain* tchain, TString out) {
    gROOT->ProcessLine("#include <vector>");  // how is it not loaded?

    if (!out.EndsWith(".root")) {
        std::cout << Error() << "Output filename must be .root" << std::endl;
        return 1;
    }

    if (verbose_)  std::cout << Info() << "Opening " << out << std::endl;
    tfile = TFile::Open(out, "RECREATE");

    if (tfile) {
        if (verbose_)  std::cout << Info() << "Successfully opened " << out << std::endl;
    } else {
        std::cout << Error() << "Failed to open " << out << std::endl;
        return 1;
    }

    tfile->mkdir("ntupler")->cd();
    ttree = (TTree*) tchain->CloneTree(0); // Do not copy the data yet
    // The clone should not delete any shared i/o buffers.
    ResetDeleteBranches(ttree);
    return 0;
}

void  BasicReader::init(edm::Event& iEvent){
    edm::Handle< std::vector<float> > genParts_pt,genParts_eta,genParts_phi,genParts_vx, genParts_vy, genParts_vz;
    edm::Handle< std::vector<int> >genParts_charge;
    edm::Handle< std::vector<float> > TTStubs_x,TTStubs_y,TTStubs_z,TTStubs_r, TTStubs_eta, TTStubs_phi,TTStubs_coordx, TTStubs_coordy, TTStubs_trigBend, TTStubs_roughPt;
    edm::Handle< std::vector<unsigned> >TTStubs_clusWidth0, TTStubs_clusWidth1,TTStubs_modId;
    edm::Handle< std::vector<int> >TTStubs_tpId ;
    std::cout<<" Before Get By Label "<<std::endl;
    iEvent.getByLabel("ntupleGenParticles","genParts@pt", genParts_pt);
    iEvent.getByLabel("ntupleGenParticles","genParts@eta", genParts_eta);
    iEvent.getByLabel("ntupleGenParticles","genParts@phi", genParts_phi);
    iEvent.getByLabel("ntupleGenParticles","genParts@vx", genParts_vx);
    iEvent.getByLabel("ntupleGenParticles","genParts@vy", genParts_vy);
    iEvent.getByLabel("ntupleGenParticles","genParts@vz", genParts_vz);
    iEvent.getByLabel("ntupleGenParticles","genParts@charge", genParts_charge);

    iEvent.getByLabel("ntupleTTStubs","TTStubs@x", TTStubs_x);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@y", TTStubs_y);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@z", TTStubs_z);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@r", TTStubs_r);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@eta", TTStubs_eta);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@phi", TTStubs_phi);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@coordx", TTStubs_coordx);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@coordy", TTStubs_coordy);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@trigBend", TTStubs_trigBend);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@roughPt", TTStubs_roughPt);
    
    iEvent.getByLabel("ntupleTTStubs","TTStubs@clusWidth0", TTStubs_clusWidth0);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@clusWidth1", TTStubs_clusWidth1);
    iEvent.getByLabel("ntupleTTStubs","TTStubs@modId", TTStubs_modId);
    
    iEvent.getByLabel("ntupleTTStubs","TTStubs@tpId", TTStubs_tpId);
     std::cout<<"Labels Got "<<genParts_pt->size()<<std::endl;

   for(unsigned int g=0; g<genParts_pt->size();++g){
	std::cout<<"Filling g "<<g<<std::endl;
        vp_pt->push_back(genParts_pt->at(g));
        vp_eta->push_back(genParts_eta->at(g));
        vp_phi->push_back(genParts_phi->at(g));
        vp_vx->push_back(genParts_vx->at(g));
        vp_vy->push_back(genParts_vy->at(g));
        vp_vz->push_back(genParts_vz->at(g));
        vp_charge->push_back(genParts_charge->at(g));
        
    }
    std::cout<<"Gen Particles Filled "<<std::endl;
    for(unsigned int s=0; s<TTStubs_eta->size();++s){
        vb_x->push_back(TTStubs_x->at(s));
        vb_y->push_back(TTStubs_y->at(s));
        vb_z->push_back(TTStubs_z->at(s));
        vb_r->push_back(TTStubs_r->at(s));
        vb_eta->push_back(TTStubs_eta->at(s));
        vb_phi->push_back(TTStubs_phi->at(s));
        vb_coordx->push_back(TTStubs_coordx->at(s));
        vb_coordy->push_back(TTStubs_coordy->at(s));
        vb_trigBend->push_back(TTStubs_trigBend->at(s));
        vb_roughPt->push_back(TTStubs_roughPt->at(s));
        vb_clusWidth0->push_back(TTStubs_clusWidth0->at(s));
        vb_clusWidth1->push_back(TTStubs_clusWidth1->at(s));
        vb_modId->push_back(TTStubs_modId->at(s));
        vb_tpId->push_back(TTStubs_tpId->at(s));
    }
}

Long64_t BasicWriter::writeTree() {
    Long64_t nentries = ttree->GetEntries();
    tfile->Write();
    //tfile->Close();
    return nentries;
}
