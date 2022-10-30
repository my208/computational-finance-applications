#include "ChronoDate.h"
#include "DayCounts.h"

#include <vector>
#include <memory> // unique_ptr

class Bond
{
public:
    // pmt_dates is the vector of coupon payment dates.
    // The DayCount object is stored polymorphically.    
    Bond(double cpn_pmt, double face_value, const std::vector<ChronoDate>& pmt_dates, 
        std::unique_ptr<DayCount> dc);

    // sett_date is the day the bond is exchanged for cash.
    // spot_rates are the market spot yield rates at each payment date
    // as seen as of the settlement date.
    double price(const ChronoDate& sett_date, 
        const std::vector<double>& spot_rates) const; 

private:
    double cpn_pmt_, face_value_;
    std::vector<ChronoDate> pmt_dates_;
    std::unique_ptr<DayCount> dc_;
};