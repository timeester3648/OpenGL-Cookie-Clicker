#pragma once

#include <time.h>
#include <string>
#include <chrono>

namespace EOUL::Util {

	class Timer final {

		public:

			enum class TimeType : unsigned char {

				Nano,
				Micro,
				Milli,
				Sec,
				Min,
				Hr,
				Day,
				Week

			};

		private:

			std::chrono::time_point<std::chrono::high_resolution_clock> begin, end;
			bool started = false;

		public:

			Timer() = default;
			Timer(Timer&& other) noexcept {

				this->swap(other);

			}

		public:

			/* swaps 2 Timers */
			inline void swap(Timer& other) {

				std::swap(this->end, other.end);
				std::swap(this->begin, other.begin);
				std::swap(this->started, other.started);

			}

			/* starts timer */
			inline void start() {

				this->begin = std::chrono::high_resolution_clock::now();
				this->started = true;

			}
			/* stops timer if it has been started */
			inline void stop() {

				if (this->started) {

					this->end = std::chrono::high_resolution_clock::now();
					this->started = false;

				}

			}

			/* returns the time past between the start() and stop() calls */
			inline double getDuration(TimeType type = TimeType::Sec) {

				switch (type) {

					case TimeType::Nano: {

						return (this->started ? 0.0 : (this->end - this->begin).count());

					}

					case TimeType::Micro: {

						return (this->started ? 0.0 : (this->end - this->begin).count() / 1e3);

					}

					case TimeType::Milli: {

						return (this->started ? 0.0 : (this->end - this->begin).count() / 1e6);

					}

					case TimeType::Sec: {

						return (this->started ? 0.0 : (this->end - this->begin).count() / 1e9);

					}

					case TimeType::Min: {

						return (this->started ? 0.0 : (this->end - this->begin).count() / (1e9 * 60.0));

					}

					case TimeType::Hr: {

						return (this->started ? 0.0 : (this->end - this->begin).count() / (1e9 * 60.0 * 60.0));

					}

					case TimeType::Day: {

						return (this->started ? 0.0 : (this->end - this->begin).count() / (1e9 * 60.0 * 60.0 * 24.0));

					}

					case TimeType::Week: {

						return (this->started ? 0.0 : (this->end - this->begin).count() / (1e9 * 60.0 * 60.0 * 24.0 * 7.0));

					}

				}

			}

	};

	/* returns the current date */
	inline std::string date() {

		time_t now = time(0);
		tm tstruct = {};
		char buf[80];

		strftime(buf, sizeof(buf), "%m-%d-%Y-%X", &tstruct);

		return buf;

	}

	/* returns the current second the clock is at */
	inline unsigned short second() {

		time_t now = time(0);
		tm tstruct;

		localtime_s(&tstruct, &now);

		return (unsigned short) tstruct.tm_sec;

	}
	/* returns the current minute the clock is at */
	inline unsigned short minute() {

		time_t now = time(0);
		tm tstruct;

		localtime_s(&tstruct, &now);

		return (unsigned short) tstruct.tm_min;

	}
	/* returns the current hour the clock is at */
	inline unsigned short hour() {

		time_t now = time(0);
		tm tstruct;

		localtime_s(&tstruct, &now);

		return (unsigned short) tstruct.tm_hour;

	}
	/* returns the current day, if year based then returns the day from January 1st (0 - 365 else), otherwise it is from 0 - 6 (Sunday = 0) */
	inline unsigned short day(bool yearBased = false) {

		time_t now = time(0);
		tm tstruct;

		localtime_s(&tstruct, &now);

		if (!yearBased) {

			return (unsigned short) tstruct.tm_mday;

		} else {

			return (unsigned short) tstruct.tm_yday;

		}

	}
	/* returns the current month since January from 0 - 11 */
	inline unsigned short month() {

		time_t now = time(0);
		tm tstruct;

		localtime_s(&tstruct, &now);

		return (unsigned short) tstruct.tm_mon;

	}
	/* returns the current year */
	inline unsigned short year() {

		time_t now = time(0);
		tm tstruct;

		localtime_s(&tstruct, &now);

		return (unsigned short) tstruct.tm_year + 1900;

	}

}