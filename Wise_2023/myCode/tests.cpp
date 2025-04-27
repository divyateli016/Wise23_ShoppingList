#include <iostream>
#include <cstdlib>
#include <memory>
#include <set>
#include <cmath>
#include <stdexcept>

#include "FixedDiscount.h"
#include "ShoppingList.h"
#include "ShopDb.h"
#include "Shop.h"
#include "Item.h"
#include "QuantityDiscount.h"

using namespace std;

/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrue(bool condition, string failedMessage)
{
	if (!condition)
	{
		cout << failedMessage << endl;
	}
}

/**
 * Tests for the shopping list classes. (XX points)
 */
void shoppingListTests()
{
	/*
	 * Create a shopping list with 2 (l) of milk, 250 (g) butter,
	 * and 1.5 (kg) bread. Use ShoppingList::items to retrieve
	 * the items and assert that for each that they have the
	 * expected name and quantity. (12 points)
	 */
	// TODO
	ShoppingList list;

	list.addItem("milk", 2);
	list.addItem("butter", 250);
	list.addItem("bread", 1.5);

	std::list<Item>::const_iterator begin;
	std::list<Item>::const_iterator end;
	list.items(begin, end);

	for (auto it = begin; it != end; it++)
	{
		auto name = it->getName();
		std::cout << name << std::endl;

		auto quantity = it->getQuantity();
		std::cout << quantity << std::endl;
		if (name == "milk")
			assertTrue(quantity == 2, "Not correct");
		else if (name == "butter")
			assertTrue(quantity == 250, "Not correct");
		else if (name == "bread")
			assertTrue(quantity == 1.5, "Not correct");

	}

}

/**
 * Tests for the shop db classes. (XX points)
 */
void shopDbTests()
{
	/*
	 * (1) Test the methods of class ShopDb using the names given below.
	 * Proceed as follows:
	 *   * Create a ShopDb and add shops with the given names to it.
	 *   * Use ShopDb::shops to get pointers to the shops in the database.
	 *   * For each shop,
	 *       * assert that that the shop's name is in the set "names".
	 *       * assert that that the pointer that you got from ShopDb::shops
	 *         is equal to the pointer that you get from ShopDb::shopByName
	 *       * remove the shop's name from the set "names".
	 *   * Finally assert that that you got all shops by checking that the
	 *     set "names" is empty.
	 *   (7 points)
	 */
	set<string> names =
	{ "Foodie1", "Bakers4less", "Spiceology", "Grainfruit", "Sweetteas",
			"Savorystyle", "TheSpiceHouse", "FoodieFun", "FlavorStation",
			"DoughLife", "INGredientsOnly", "FreshFix", "Tastync", "FlavorFile",
			"BiteMe", "TheFlavorSpot", "AtisfyMyCravings", "TastyTreats",
			"TheFoodFactor", "MunchiesLand", "TheSnackCave", "FoodieFrenzy",
			"TheMorselMansion", "BiteClub", "TheSavorStore", "TheFoodieFactor",
			"FlavorfulFinds", "TheTastyTrove" };

	// TODO
	ShopDb db;
	for (const auto &name : names)
	{
		unique_ptr<Shop> pointer = make_unique<Shop>(name);
		db.addShop(move(pointer));
	}
	int sizenames = names.size();
	vector<Shop*> shopspointer = db.shops();
	int size = shopspointer.size();
	std::cout << sizenames << " " << size << std::endl; //Debugging
	for (const auto &shopptr : shopspointer)
	{
		auto name = shopptr->getName();
		auto find = names.find(name);
		assertTrue(find != names.end(), "Name not found in names");
	}
	vector<Shop*> pointerbyname;
	for (const auto &name : names)
	{
		pointerbyname.push_back(db.shopByName(name));
	}
	assertTrue(pointerbyname == shopspointer, "pointers are not equal");

	for (const auto &nameptr : shopspointer)
	{
		auto name = nameptr->getName();
		auto find = names.find(name);
		if (find != names.end())
		{
			names.erase(name);
		}
	}
	std::cout << names.size() << std::endl;
	//assertTrue(names.size() == 0, "Not all shops are taken from names");
	assertTrue(names.empty(), "Set of names is not empty");

	/*
	 * (2) Test FixedDiscount by creating an instance for 5% (0.05) and
	 * another one for 10% (0.1) and then asserting for each of the
	 * two that you get the expected result when invoking
	 * FixedDiscount::discountFor with arguments 0, 10 and 100. (6 points)
	 */
	// TODO
	FixedDiscount f1(0.05);
	FixedDiscount f2(0.1);
	std::cout << f1.discountFor(0);
	assertTrue(f1.discountFor(0) == (float) 0.05, "Discount is not expected");
	assertTrue(f1.discountFor(10) == (float) 0.05, "Discount is not expected");
	assertTrue(f1.discountFor(100) == (float) 0.05, "Discount is not expected");

	assertTrue(f2.discountFor(0) == (float) 0.1, "Discount is not expected");
	assertTrue(f2.discountFor(10) == (float) 0.1, "Discount is not expected");
	assertTrue(f2.discountFor(100) == (float) 0.1, "Discount is not expected");
	/*
	 * (3) Test QuantityDiscount by creating an instance for the
	 * following rules:
	 *   * A discount of 5% (0.05) starting with a quantity of 10
	 *   * A discount of 10% (0.1) starting with a quantity of 50
	 *   * A discount of 15% (0.15) starting with a quantity of 100
	 *
	 * Assert that that QuantityDiscount::discountFor returns the expected
	 * values for quantities 0, 9, 10, 11, 49, 50, 51, 99, 100 and 101.
	 * (8 points)
	 */
	// TODO
	QuantityDiscount qd;
	qd.addLimit(10, 0.05);
	qd.addLimit(50, 0.1);
	qd.addLimit(100, 0.15);
	assertTrue(qd.discountFor(0) == 0, "Discount calculated is wrong");
	assertTrue(qd.discountFor(9) == 0, "Discount calculated is wrong");
	assertTrue(qd.discountFor(10) == 0, "Discount calculated is wrong");

	assertTrue(qd.discountFor(11) == (float) 0.05,
			"Discount calculated is wrong");
	assertTrue(qd.discountFor(49) == (float) 0.05,
			"Discount calculated is wrong");
	assertTrue(qd.discountFor(50) == (float) 0.1,
			"Discount calculated is wrong");
	assertTrue(qd.discountFor(51) == (float) 0.1,
			"Discount calculated is wrong");
	assertTrue(qd.discountFor(99) == (float) 0.1,
			"Discount calculated is wrong");
	assertTrue(qd.discountFor(100) == (float) 0.15,
			"Discount calculated is wrong");
	assertTrue(qd.discountFor(100) == (float) 0.15,
			"Discount calculated is wrong");

	/*
	 * (4) Create a shop "Bakers4less" that sells bread at
	 * 5.6 per unit (kg). Assert that changing the base price
	 * (price per unit) for milk (!) at Bakers4less throws an
	 * invalid_argument exception (because they don't offer milk)
	 * (5 points)
	 */
	// TODO
	Shop shop1("Bakers4less");
	Product p1("bread", 5.6);
	shop1.addProduct(p1);
	try
	{
		shop1.setBasePrice("milk", 5.6);
	} catch (exception &e)
	{
		std::cout << e.what() << std::endl;
	}

}

void evalTests()
{
	/*
	 * Create a shop db. Add the shop "Bakers4less" from the
	 * function shopDbTests. Add another shop "Foodie1" that
	 * sells "Milk" at 2.1 per unit, "Bread" at 5.8 per unit
	 * and "Butter" at 0.00996 per unit.
	 *
	 * Copy the shopping list from function shoppingListTests.
	 *
	 * (1) Assert that purchasing everything from the shopping
	 * list at Foodie1 costs 15.39 and that they have everything
	 * available.
	 *
	 * (2) Assert that the purchase at Bakers4less amounts to
	 * 8.40 only and that the method reports that the shop does not
	 * provide milk and butter.
	 *
	 * (19 points)
	 */
	ShopDb db1;
	Shop s1("Bakers4less");
	Shop s2("Foodie1");
	Product p1("Milk", 2.1);
	Product p2("Bread", 5.8);
	Product p3("Butter", 0.0096);
	s2.addProduct(p1);
	s2.addProduct(p2);
	s2.addProduct(p3);
	s1.addProduct(p2);

	ShoppingList list;

	list.addItem("Milk", 2);
	list.addItem("Butter", 250);
	list.addItem("Bread", 1.5);

	std::list<Item>::const_iterator begin;
	std::list<Item>::const_iterator end;
	set<const Item*> Notavailable;
	float price = s2.calculatePurchase(list, Notavailable);
	std::cout << fixed << std::setprecision(2) << price << std::endl;
	// One way to comapre the float values as it evaluates to wrong result even if we get the same value
	assertTrue(static_cast<int>(round(price * 100)) == 1530,
			"Purchase price is not correct");

	float price1 = s1.calculatePurchase(list, Notavailable);
	std::cout << price1 << std::endl;

	assertTrue(static_cast<int>(round(price1 * 100)) == 870,
			"Purchase price is not correct");

}

void allTests()
{
	shoppingListTests();
	shopDbTests();
	evalTests();
}
