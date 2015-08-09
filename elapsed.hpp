#ifndef ELAPSED_HPP
#define ELAPSED_HPP

#include <thread>
#include <chrono>
#include <iostream>
#include <string>

class Elapsed
{
private:
	std::chrono::high_resolution_clock::time_point start;

public:
	inline void Start();
	double End(std::string name);
	double End();
};

// START
inline void Elapsed::Start()
{
	this->start = std::chrono::high_resolution_clock::now();
};

// END
// returns time in millisonds and prints a string with
// a name parameter
inline double Elapsed::End(std::string name)
{
	double e = this->End();
	std::cout << name << " (" << e << "ms)" << std::endl;
	return e;
};

// END
// returns elapsed time in milliseconds
inline double Elapsed::End()
{
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - this->start);
	return ms.count();
};

#endif
