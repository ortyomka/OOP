#include "stdafx.h"
#include "vector_functions.h"

void ProcessVector(std::vector <double> & numbers)
{
	if (numbers.empty())
	{
		return;
	}

	double multiplier = GetMultiplier(numbers);

	transform(numbers.begin(), numbers.end(), numbers.begin(), [=](double element) {
		return element * multiplier;
	});
}

void PrintVector(std::ostream & output, const std::vector <double> & numbers)
{
	for (const double & element : numbers)
	{
		output << std::fixed << std::setprecision(3) << element << " ";
	}
	output << std::endl;
}

double GetMultiplier(const std::vector <double> & numbers)
{
	auto minMax = GetMaxMinElement(numbers);
	double result = *minMax.second;

	if (*minMax.first != 0)
	{
		result /= *minMax.first;
	}

	return result;
}