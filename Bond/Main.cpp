#include "ChronoDate.h"
#include "DayCounts.h"
#include "Bond.h"

#include <vector>
#include <algorithm> // std::transform
#include <utility> // std::make_unique
#include <chrono> // weekend_roll()

using std::cout;
using std::endl;

void example();

void main()
{
    example();
}

void example()
{
    std::vector<ChronoDate> pmt_dates(7);
    const ChronoDate first_pmt_date{ 2022, 11, 14 };

    unsigned i = 0;
    cout << "Raw dates in schedule: " << endl;
    for (auto& date : pmt_dates)
    { 
        ChronoDate ob(first_pmt_date);
        pmt_dates[i] = ob.add_months(i * 6);
        cout << date << " ";
        ++i;
    }
    cout << endl;

    std::transform(pmt_dates.begin(), pmt_dates.end(), pmt_dates.begin(),
        [](ChronoDate d) { return d.weekend_roll(); });

    cout << "Rolled dates: " << endl;
    for (auto& date : pmt_dates)
    {
        cout << date << " ";
    }
    cout << endl;

    auto day_count = std::make_unique<Thirty360>();
    Bond bond{ 50.0, 1000.0, pmt_dates, std::move(day_count) };

    ChronoDate sett_date{ 2022, 9, 1 };
    std::vector<double> rates{ 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04 };
    
    double bond_price = bond.price(sett_date, rates);

    cout << endl << "Bond price = $" << bond_price << endl;
}