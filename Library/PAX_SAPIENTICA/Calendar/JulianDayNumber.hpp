﻿/*##########################################################################################

	PAX SAPIENTICA Library 💀🌿🌏

	[Planning]		2023 As Project
	[Production]	2023 As Project
	[Contact Us]	wanotaitei@gmail.com			https://github.com/AsPJT/PAX_SAPIENTICA
	[License]		Distributed under the CC0 1.0.	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#ifndef PAX_SAPIENTICA_CALENDAR_JULIAN_DAY_NUMBER_HPP
#define PAX_SAPIENTICA_CALENDAR_JULIAN_DAY_NUMBER_HPP

/*##########################################################################################
	Deals with calculations related to the Julian calendar, the Gregorian calendar, and the Julian day.
	ユリウス暦、グレゴリオ暦、ユリウス日に関する計算を扱う。
##########################################################################################*/

#include <cmath>
#include <cstdint>
#include <vector>

#include <PAX_SAPIENTICA/Type/Date.hpp>
#include <PAX_SAPIENTICA/Calendar/JapaneseEra.hpp>

namespace paxs {

	template<typename Day>
	class JulianDayNumber {
	private:
		Day day{ 1808286 };
	public:
		JulianDayNumber() = default;

		JulianDayNumber(const JulianDayNumber<double>& jdn_) { day = static_cast<Day>(jdn_); }
		template<typename T>
		JulianDayNumber(const T& jdn_) { day = static_cast<Day>(jdn_); }

	private:
		static double getK(const double month) {
			return std::floor((14 - month) / 12);
		}
	public:
		Day& getDay() { return this->day; }
		// グレゴリオ暦からユリウス日を取得
		void fromGregorianCalendar(const double year, const double month, const double day) {
			const double K = getK(month);
			this->day = static_cast<Day>(std::floor((-K + year + 4800) * 1461 / 4)
				+ std::floor((K * 12 + month - 2) * 367 / 12)
				- std::floor(std::floor((-K + year + 4900) / 100) * 3 / 4)
				+ day - 32075);
		}
		// ユリウス暦からユリウス日を取得
		void fromJulianCalendar(const double year, const double month, const double day) {
			const double K = getK(month);
			this->day = static_cast<Day>(std::floor((-K + year + 4800) * 1461 / 4)
				+ std::floor((K * 12 + month - 2) * 367 / 12)
				+ day - 32113);
		}
		// グレゴリオ暦を取得
		Date toGregorianCalendar() const {
			Date ymd;
			//JDN ⇒ グレゴリオ暦
			double L = static_cast<double>(this->day) + 68569;
			const double N = std::floor(4 * L / 146097);
			L = L - std::floor((146097 * N + 3) / 4);
			const double I = std::floor(4000 * (L + 1) / 1461001);
			L = L - std::floor(1461 * I / 4) + 31;
			const double J = std::floor(80 * L / 2447);
			ymd.setDay(static_cast<DateDay>(L - std::floor(2447 * J / 80)));
			L = std::floor(J / 11);
			ymd.setMonth(static_cast<DateMonth>(J + 2 - 12 * L));
			ymd.setYear(static_cast<DateYear>(100 * (N - 49) + I + L));
			return ymd;
		}
		// ユリウス暦を取得
		Date toJulianCalendar() const {
			Date ymd;
			double L = static_cast<double>(this->day) + 1402;
			const double N = std::floor((L - 1) / 1461);
			L = L - 1461 * N;
			const double I = std::floor((L - 1) / 365) - std::floor(L / 1461);
			L = L - 365 * I + 30;
			const double J = std::floor(80 * L / 2447);
			ymd.setDay(static_cast<DateDay>(L - std::floor(2447 * J / 80)));
			L = std::floor(J / 11);
			ymd.setMonth(static_cast<DateMonth>(J + 2 - 12 * L));
			ymd.setYear(static_cast<DateYear>(4 * N + I + L - 4716));
			return ymd;
		}
		// 和暦を取得
		JapanDate toJapaneseCalendar(const std::vector<paxs::JapaneseEra>& japanese_era_list) const {
			JapanDate jp_date{ 0,1,1,1,false };

			// ユリウス日が 1480407 以上（神武 1 年 1 月 1 日以降、グレゴリオ暦 紀元前 660 年 2 月 11 日以降）
			if (day >= 1480407) {
				bool is_break = false;
				// 元号一覧からその日に合った元号を取得
				for (std::size_t i = 0; i < japanese_era_list.size() - 1; ++i) {
					auto& jeli = japanese_era_list[i];
					if (day >= jeli.start_jdn
						&& day < japanese_era_list[i + 1].start_jdn) {
						is_break = true; // 元号一覧からその日に合った元号が見つかったのでループを抜ける
						// 改元されている場合
						if (jeli.kaigen_jdn[0] != 0 &&
							day >= jeli.kaigen_jdn[0]) {
							jp_date.setGengo(jeli.gengo[1]);
							jp_date.setYear(jeli.gengo_num[1]);
						}
						else {
							jp_date.setGengo(jeli.gengo[0]);
							jp_date.setYear(jeli.gengo_num[0]);
						}
					}
					// 元号一覧からその日に合った元号が見つかった場合
					if (is_break) {
						int lm = ((jeli.leap_month == 0) ? 999 : jeli.leap_month - 1);

						int calc_day = int(day) - jeli.start_jdn; // １月１日
						// 月と日の計算
						for (int j = 0; j < 12; ++j) {
							if (calc_day < jeli.number_of_days[j]) {
								jp_date.setMonth(DateMonth(j + 1));
								jp_date.setDay(DateDay(calc_day + 1));
								jp_date.setLeapMonth(false);
								break;
							}
							calc_day -= jeli.number_of_days[j];
							if (j == lm) {
								if (calc_day < jeli.number_of_days_of_leap_month) {
									jp_date.setMonth(DateMonth(j + 1));
									jp_date.setDay(DateDay(calc_day + 1));
									jp_date.setLeapMonth(true);
									break;
								}
								calc_day -= jeli.number_of_days_of_leap_month;
							}
						}
					}
					if (is_break) break;
				}
			}

			return jp_date;
		}
	};
	using JDN_F64 = JulianDayNumber<double>;
	using JDN_S32 = JulianDayNumber<std::int_least32_t>;
	using JDN_S64 = JulianDayNumber<std::int_least64_t>;
	
}

#endif // !PAX_SAPIENTICA_CALENDAR_JULIAN_DAY_NUMBER_HPP