#include "Bond.h"

#include <iostream>
#include <utility> // std::move
#include <numeric> // std::accumulate

Bond::Bond(double cpn_pmt, double face_value, 
    const std::vector<ChronoDate>& pmt_dates, std::unique_ptr<DayCount> dc):
    cpn_pmt_{ cpn_pmt }, face_value_{ face_value }, 
    pmt_dates_{ pmt_dates }, dc_{ std::move(dc) } {}

double Bond::price(const ChronoDate& sett_date, const std::vector<double>& spot_rates) const
{
    std::vector<double> disc_cpn_pmts;
    disc_cpn_pmts.reserve(spot_rates.size());

    auto calc_df = [this, &sett_date](double rate, const ChronoDate& pmt_date)
    {
		return std::exp(- rate * dc_ -> year_fraction(sett_date, pmt_date));
    };

    auto iter = pmt_dates_.begin();
    for (auto rate : spot_rates)
    {
        disc_cpn_pmts.push_back(cpn_pmt_ * calc_df(rate, *iter));
        ++iter;
    }

    double bond_price = std::accumulate(disc_cpn_pmts.begin(), disc_cpn_pmts.end(), 0.0);
    bond_price +=  face_value_ * calc_df(spot_rates.back(), pmt_dates_.back());

    return bond_price;	
}