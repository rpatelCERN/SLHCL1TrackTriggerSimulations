#ifndef AMSimulation_TrackFitterOption_h_
#define AMSimulation_TrackFitterOption_h_

#include <vector>
#include <iosfwd>
#include <string>


namespace slhcl1tt {

struct TrackFitterOption {
    float    maxChi2Red;
    int      minNdof;
    std::string mode;
};

std::ostream& operator<<(std::ostream& o, const TrackFitterOption& po);

}  // namespace slhcl1tt

#endif
