#pragma once

namespace std {

	/* execute func on [begin, end] if the comparator given returns true */
	template <typename Iter, typename FuncType, typename CompType>
	inline void for_each_if(Iter begin, Iter end, FuncType func, CompType comparator) {

		for (Iter it = begin; it != end; it++) {

			if (comparator(*it)) {

				func(*it);

			}

		}

	}

	/* execute func on [begin, begin + count] if the comparator given returns true */
	template <typename Iter, typename FuncType, typename CompType>
	inline void for_each_n_if(Iter begin, size_t count, FuncType func, CompType comparator) {

		size_t i = 0;
		Iter current = begin;
		while (i < count) {

			if (comparator(*current)) {

				func(*current);

			}

			current++;
			i++;

		}

	}

}