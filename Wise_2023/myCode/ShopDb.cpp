/*
 * ShopDb.cpp
 *
 *  Created on: 10.02.2024
 *      Author: mnl
 */

#include "ShopDb.h"
#include "Shop.h"

using namespace std;

ShopDb& ShopDb::addShop(std::unique_ptr<Shop> &&shop)
{
	// TODO (add code)
	knownShops.insert(make_pair(shop->getName(), std::move(shop)));
	return *this;

}

vector<Shop*> ShopDb::shops() const
{
	vector<Shop*> shopptr;
	for (const auto &pair : knownShops)
	{
		shopptr.push_back(pair.second.get());
	}
	return shopptr;
}

Shop* ShopDb::shopByName(std::string name)
{
	auto findname = knownShops.find(name);
	if (findname != knownShops.end())
	{
		return findname->second.get(); //Returns the raw pointer to the Shop with the given name
	}
	return nullptr;

}
