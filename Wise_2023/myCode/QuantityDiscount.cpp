/*
 * QuantityDiscount.cpp
 *
 *  Created on: 11.02.2024
 *      Author: mnl
 */

#include "QuantityDiscount.h"

QuantityDiscount& QuantityDiscount::addLimit(float quantity, float discount)
{
	// TODO (add code)
	limits.insert(std::make_pair(quantity, discount));
	return *this;

}

float QuantityDiscount::discountFor(float quantity) const
{
	// TODO (add code/replace dummy return)
	auto smallitr = limits.begin();
	auto smallquantity = smallitr->first;
	auto smalldiscount = smallitr->second;
	std::set<float> smallequal;
	if (quantity <= smallquantity)
	{
		return 0;
	}
	for (const auto &pair : limits)
	{
		if (pair.first <= quantity)
		{
			smallequal.insert(pair.first);
		}
	}
	auto largestquantity = *smallequal.rbegin();

	return limits.at(largestquantity);
}
