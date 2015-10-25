#pragma once

template<typename T>
void Init(T arr[], size_t size, const T &val) {
	for (size_t i = 0; i < size; ++i) {
		arr[i] = val;
	}
}