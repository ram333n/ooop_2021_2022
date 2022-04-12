#include <iostream>
#include <vector>
#include <future>

#include "profile.h"


int main() {
	{
		LOG_DURATION("Fibonacci");
		for (int i = 0; i < 40; ++i) {
			std::cout << "[" << i << "] : " << '\t' << Fibonacci::GetNumberSingleThread(i) << std::endl;
		}
	}
}