#include "SLHCL1TrackTriggerSimulations/AMSimulation/interface/Converter.h"

#include <bitset>
#include <iostream>

static const unsigned MAX_NLAYERS = 8;


int Converter::bankToTxt(TString src, TString out, TString fmt) {
    if (!src.EndsWith(".root")) {
        std::cout << Error() << "Input filename must be .root" << std::endl;
        return 1;
    }
    if (!out.EndsWith(".txt")) {
        std::cout << Error() << "Output filename must be .txt" << std::endl;
        return 1;
    }
    fmt.ToLower();
    if (!(fmt == "i" || fmt == "x" || fmt == "b" || fmt == "s")) {
        std::cout << Error() << "Unrecognized format option: " << fmt << std::endl;
        return 1;
    }

    if (verbose_)  std::cout << Info() << "Opening " << src << std::endl;

    TFile* tfile = TFile::Open(src);
    if (!tfile) {
        std::cout << Error() << "Cannot open file: " << src << std::endl;
        return 1;
    }
    TTree* ttree = (TTree*) tfile->Get(bankName_);
    if (!ttree) {
        std::cout << Error() << "Cannot get tree: " << bankName_ << std::endl;
        return 1;
    }

    long long nentries = ttree->GetEntries();
    if (nEvents_ > nentries)
        nEvents_ = nentries;

    if (verbose_)  std::cout << Info() << "Reading " << nEvents_ << " events." << std::endl;
    if (verbose_)  std::cout << Info() << "Writing " << out << ", using format '" << fmt << "'." << std::endl;

    ofstream fout;
    fout.open(out.Data());
    if (!fout.is_open()) {
        std::cout << Error() << "Cannot open text file: " << out << std::endl;
        return 1;
    }

    // _________________________________________________________________________
    // Actual work starts here
    std::vector<unsigned>       * superstripIds = 0;
    //std::vector<unsigned short> * superstripBits = 0;
    ttree->SetBranchAddress("superstripIds" , &superstripIds);
    //ttree->SetBranchAddress("superstripBits", &superstripBits);

    for (long long ievt=skipEvents_; ievt<nEvents_; ++ievt) {
        ttree->GetEntry(ievt);

        if (fmt == "i") {
            for (unsigned l=0; l<MAX_NLAYERS; ++l) {
                fout << superstripIds->at(l) << " ";
            }
        } else if (fmt == "x") {
            for (unsigned l=0; l<MAX_NLAYERS; ++l) {
                fout << std::hex << superstripIds->at(l) << " ";
            }
        } else if (fmt == "b") {
            for (unsigned l=0; l<MAX_NLAYERS; ++l) {
                fout << (std::bitset<32>) superstripIds->at(l) << " ";
            }
        } else if (fmt == "s") {
            unsigned ssId, moduleId, col, row;
            for (unsigned l=0; l<MAX_NLAYERS; ++l) {
                ssId = superstripIds->at(l);
                moduleId = (ssId >> 14) & 0x3FFFF;
                col      = (ssId >> 9 ) & 0x1F;
                row      = (ssId >> 0 ) & 0x1FF;

                fout << Form("(%6u,%2u,%4u)", moduleId, col, row) << " ";
            }
        }
        fout << "\n";
    }

    fout.close();

    return 0;
}
