/*
 * Shop.cpp
 *
 *  Created on: 10.02.2024
 *      Author: mnl
 */

#include <list>
#include <stdexcept>

#include "Shop.h"
#include "ShoppingList.h"
#include "Item.h"
#include "Discount.h"

using namespace std;

Shop::Shop(std::string name) :
		name
		{ name }
{
}

std::string Shop::getName() const
{
	return name;
}

Shop& Shop::addProduct(const Product &product)
{
	// TODO (add code)
	std::string name = product.getName();
	products.insert(make_pair(name, product));
	return *this;

}

Shop& Shop::setBasePrice(std::string productName, float basePrice)
{
	// TODO (add code)
	auto name = products.find(productName);
	if (name != products.end())
	{
		name->second.setBasePrice(basePrice);
	}
	else
	{
		throw invalid_argument("product not found");
	}

	return *this;
}

Shop& Shop::setDiscount(std::string productName,
		std::shared_ptr<Discount> discount)
{
	auto name = products.find(productName);
	if (name != products.end())
	{
		name->second.setDiscount(discount);
	}
	else
	{
		throw invalid_argument("product not found");
	}
	return *this;
}

float Shop::calculatePurchase(const ShoppingList &shoppingList,
		std::set<const Item*> &notAvailable) const
{
	notAvailable.clear();
	std::list<Item>::const_iterator begin;
	std::list<Item>::const_iterator end;
	shoppingList.items(begin, end);
	float purcahsecost = 0;

	for (auto it = begin; it != end; it++)
	{
		const Item *itemptr = &(*it);/**it is like pointer deref gives item
		 object & provides address of item it pointing
		 to**/
		auto find = products.find(it->getName());
		if (find == products.end())
		{
			notAvailable.insert(itemptr);
		}
		else if (find != products.end())
		{
			purcahsecost += find->second.priceFor(it->getQuantity());
		}
	}
	return (float)purcahsecost;

}

