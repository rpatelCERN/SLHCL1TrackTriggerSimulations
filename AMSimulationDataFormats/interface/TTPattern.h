#ifndef AMSimulationDataFormats_TTPattern_h_
#define AMSimulationDataFormats_TTPattern_h_

#include "SLHCL1TrackTriggerSimulations/AMSimulationDataFormats/interface/TTSuperstrip.h"

#include <cassert>
#include <algorithm>
#include <iosfwd>
#include <vector>


// FIXME: eliminate the use of 64-bit integers
namespace slhcl1tt {

class TTPattern {
  public:
    // Constructors
    TTPattern()
    : frequency_(1), superstrips_() {}

    TTPattern(const std::vector<TTSuperstrip>& superstrips)
    : frequency_(1), superstrips_(superstrips) {}

    TTPattern(const TTPattern& rhs)
    : frequency_(rhs.frequency_), superstrips_(rhs.superstrips_) {}

    // Destructor
    ~TTPattern() {}

    // Setters
    // One can change the bit, but not the address since the address is
    // part of the pattern id
    void setSuperstripBit(int l, bit_type bit)  { superstrips_.at(l).setBit(bit); }

    // Getters
    std::vector<TTSuperstrip> getSuperstrips()    const { return superstrips_; }
    TTSuperstrip getSuperstrip(int l)             const { return superstrips_.at(l); }
    addr_type getSuperstripId(int l)              const { return superstrips_.at(l).id(); }
    bit_type getSuperstripBit(int l)              const { return superstrips_.at(l).bit(); }

    count_type frequency()                        const { return frequency_; }

    pattern_type id()                             const {
        pattern_type patternId;
        for (unsigned i=0; i<patternId.size(); ++i) {
            if (i<superstrips_.size())
                patternId.at(i) = superstrips_.at(i).id();
            else
                patternId.at(i) = 0;
        }
        return patternId;
    }

    pattern_bit_type bit()                        const {
        pattern_bit_type patternBit;
        for (unsigned i=0; i<patternBit.size(); ++i) {
            if (i<superstrips_.size())
                patternBit.at(i) = superstrips_.at(i).bit();
            else
                patternBit.at(i) = 1;
        }
        return patternBit;
    }

    // Functions
    void merge(const TTPattern& rhs);


  private:
    count_type frequency_;
    std::vector<TTSuperstrip> superstrips_;
};


// TTRoad is just a data holder. In actuality, a road should be a word,
// and its relevant data is retrieved using a lookup table. In software,
// we simply skip this lookup.
class TTRoad {
  public:
    // Constructors
    TTRoad()
    : patternId_(), hits_() {}

    TTRoad(const pattern_type& patternId, const std::vector<TTHit>& hits)
    : patternId_(patternId), hits_(hits) {}

    TTRoad(const TTRoad& rhs)
    : patternId_(rhs.patternId_), hits_(rhs.hits_) {}

    // Destructor
    ~TTRoad() {}

    // Setters
    // None allowed

    // Getters
    std::vector<TTHit> getHits()    const { return hits_; }
    TTHit getHit(int l)             const { return hits_.at(l); }

    pattern_type patternId()        const { return patternId_; }

  private:
    pattern_type patternId_;
    std::vector<TTHit> hits_;
};


// _____________________________________________________________________________
// To sort a collection of patterns using frequency
inline bool sortByFrequency(const TTPattern& lhs, const TTPattern& rhs) {
    return lhs.frequency() > rhs.frequency();
}

// _____________________________________________________________________________
// Output streams
std::ostream& operator<<(std::ostream& o, const pattern_type& pattId);

std::ostream& operator<<(std::ostream& o, const TTPattern& patt);

std::ostream& operator<<(std::ostream& o, const TTRoad& road);

}  // namespace slhcl1tt

#endif