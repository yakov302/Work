#include "mu_test.h"
#include "bst.hpp"
#include "person.hpp"
#include <memory>

using namespace bst;

// *********** int tests ************

Bst<int> getAndReturnTree(Bst<int> a_b)
{
	std::cout << std::endl << "tree in function: " << std::endl;
	a_b.forEach(IN_ORDER);
	std::cout << std::endl;

	Bst<int> returnBst;
	returnBst.push(10);
	returnBst.push(15);
	returnBst.push(7);

	return returnBst;
}

Bst<int> moveCtor(Bst<int> a_b)
{
	std::cout << std::endl << "tree get in moveCtor function: " << std::endl;
	a_b.forEach(IN_ORDER);
	std::cout << std::endl;
	return a_b;
}

std::function<bool(Node<int>*, void*)> findfirstEven(
    [](Node<int>* a_node, void* a_context)
    {
        if(a_node->data()%2 == 0)
            return false;

        return true;
    }
);

BEGIN_TEST(print_by_mode)

	Bst<int> tree;
	tree.push(5);
	tree.push(3);
	tree.push(4);
	tree.push(1);
	tree.push(8);
	tree.push(7);
	tree.push(6);
	tree.push(11);
	tree.push(15);
 	tree.push(12);
	tree.push(32);
	tree.push(75);

	std::cout << std::endl << "       ***in order mode***" << std::endl;
	tree.forEach(IN_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***post order mode***" << std::endl;
	tree.forEach(POST_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***pre order mode***" << std::endl;
	tree.forEach(PRE_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***by level mode***" << std::endl;
	tree.forEach(BY_LEVELS);
	std::cout << std::endl;

	std::cout << std::endl;
	ASSERT_PASS();

END_TEST

BEGIN_TEST(copr_op_and_ctor)

	Bst<int> tree;
	tree.push(5);
	tree.push(3);
	tree.push(4);
	tree.push(1);
	tree.push(8);
	tree.push(7);
	tree.push(6);
	tree.push(11);
	tree.push(15);
 	tree.push(12);
	tree.push(32);
	tree.push(75);

	std::cout << std::endl << "       ***copy operator***" << std::endl;
	Bst<int> tree2;
	tree2 = tree;
	tree2.forEach(IN_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***copy ctor***" << std::endl;
	getAndReturnTree(tree2); 

	std::cout << std::endl << "       ***move copy operator***" << std::endl;
	Bst<int> tree3;
	tree3 = getAndReturnTree(tree2); 
	std::cout << std::endl << "tree return from function: " << std::endl;
	tree3.forEach(IN_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***move copy ctor***" << std::endl;
	moveCtor(getAndReturnTree(tree2)); 
	
	std::cout << std::endl;
	ASSERT_PASS();

END_TEST

BEGIN_TEST(begine_and_end_iterators)

	Bst<int> tree;
	tree.push(5);
	tree.push(3);
	tree.push(4);
	tree.push(1);
	tree.push(8);
	tree.push(7);
	tree.push(6);
	tree.push(11);
	tree.push(15);
 	tree.push(12);
	tree.push(32);
	tree.push(75);

	ASSERT_EQUAL(tree.begine().data(), 1);
	ASSERT_EQUAL(tree.end().data(), 0);

	std::cout << std::endl << "       ***print tree by iterators***" << std::endl;
	BstIterator<int> it = tree.begine();
	BstIterator<int> end = tree.end();
	while(it != end)
	{
		std::cout << *it << ", ";
		it++;
	}

	std::cout << std::endl << std::endl;

END_TEST

BEGIN_TEST(pull_by_iterator_and_value)

	Bst<int> tree;
	tree.push(5);
	tree.push(3);
	BstIterator<int> four = tree.push(4);
	tree.push(1);
	tree.push(8);
	tree.push(7);
	tree.push(6);
	tree.push(11);
	BstIterator<int> fifteen = tree.push(15);
 	tree.push(12);
	tree.push(32);
	tree.push(75);

	ASSERT_EQUAL(tree.size(), 12);

	std::cout << std::endl << "       ***pull 4 by iterator***" << std::endl;
	tree.pull(four);
	tree.forEach(IN_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***pull 15 by iterator***" << std::endl;
	tree.pull(fifteen);
	tree.forEach(IN_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***pull 75 by value***" << std::endl;
	tree.pull(75);
	tree.forEach(IN_ORDER);
	std::cout << std::endl;

	std::cout << std::endl << "       ***pull 3 by value***" << std::endl;
	tree.pull(3);
	tree.forEach(IN_ORDER);
	std::cout << std::endl;

	ASSERT_EQUAL(tree.size(), 8);

	std::cout << std::endl;
	ASSERT_PASS();

END_TEST

BEGIN_TEST(find_first)

	Bst<int> tree;
	tree.push(5);
	tree.push(3);
	tree.push(4);
	tree.push(1);
	tree.push(8);
	tree.push(7);
	tree.push(6);
	tree.push(11);
	tree.push(15);
 	tree.push(12);
	tree.push(32);
	tree.push(75);

	std::cout << std::endl << "       ***find first even***" << std::endl;
	BstIterator<int> find = tree.findFirst(findfirstEven);
	std::cout << *find << std::endl;
	ASSERT_EQUAL(*find, 4);

	int num = 11;
	find = tree.findFirst(findNodeByData<int>, &num);
	ASSERT_EQUAL(find != tree.end(), true);

	num = 18;
	find = tree.findFirst(findNodeByData<int>, &num);
	ASSERT_EQUAL(find == tree.end(), true);



	std::cout << std::endl;

END_TEST

BEGIN_TEST(push_and_pull)

	Bst<int> tree;

	BstIterator<int> pushIt = tree.push(4);
	ASSERT_EQUAL(*pushIt, 4);

	BstIterator<int> push2It = tree.push(4);
	ASSERT_EQUAL(push2It == tree.end(), true);

	int n = tree.pull(pushIt);
	ASSERT_EQUAL(n, 4);

	n = tree.pull(pushIt);
	ASSERT_EQUAL(n, 0);

	std::cout << std::endl;

END_TEST

// ************ Person tests ******************

std::function<bool(Node<Person>*, void*)> printPersonData(
    [](Node<Person>* a_node, void*)
    {
        std::cout << "[id:" << a_node->data().id() << " * name:" << a_node->data().name() << "], ";
        return true;
    }
);

std::function<bool(Node<Person>*, void*)> findfirstEvenId(
    [](Node<Person>* a_node, void* a_context)
    {
        if(a_node->data().id()%2 == 0)
            return false;

        return true;
    }
);

Bst<Person> getAndReturnTree(Bst<Person> a_b)
{
	std::cout << std::endl << "tree in function: " << std::endl;
	a_b.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;

	Bst<Person> returnBst;
	returnBst.push(Person(10, "yakov"));
	returnBst.push(Person(7, "yosi"));
	returnBst.push(Person(15, "dana"));

	return returnBst;
}

Bst<Person> moveCtor(Bst<Person> a_b)
{
	std::cout << std::endl << "tree get in moveCtor function: " << std::endl;
	a_b.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;
	return a_b;
}

BEGIN_TEST(print_by_mode_person)

	Bst<Person> tree;
	tree.push(Person(5, "dana"));
	tree.push(Person(3, "yosi"));
	tree.push(Person(4, "hila"));
	tree.push(Person(1, "orel"));
	tree.push(Person(8, "shay"));
	tree.push(Person(7, "rony"));
	tree.push(Person(6, "david"));
	tree.push(Person(11, "mosh"));

	std::cout << std::endl << "       ***in order mode***" << std::endl;
	tree.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl << "       ***post order mode***" << std::endl;
	tree.forEach(POST_ORDER, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl << "       ***pre order mode***" << std::endl;
	tree.forEach(PRE_ORDER, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl << "       ***by level mode***" << std::endl;
	tree.forEach(BY_LEVELS, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl;
	ASSERT_PASS();

END_TEST

BEGIN_TEST(copr_op_and_ctor_person)

	Bst<Person> tree;
	tree.push(Person(5, "dana"));
	tree.push(Person(3, "yosi"));
	tree.push(Person(4, "hila"));
	tree.push(Person(1, "orel"));
	tree.push(Person(8, "shay"));
	tree.push(Person(7, "rony"));
	tree.push(Person(6, "david"));
	tree.push(Person(11, "mosh"));

	std::cout << std::endl << "       ***copy operator***" << std::endl;
	Bst<Person> tree2;
	tree2 = tree;
	tree2.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl << "       ***copy ctor***" << std::endl;
	getAndReturnTree(tree2); 

	std::cout << std::endl << "       ***move copy operator***" << std::endl;
	Bst<Person> tree3;
	tree3 = getAndReturnTree(tree2); 
	std::cout << std::endl << "tree return from function: " << std::endl;
	tree3.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl << "       ***move copy ctor***" << std::endl;
	moveCtor(getAndReturnTree(tree2)); 
	
	std::cout << std::endl;
	ASSERT_PASS();

END_TEST

BEGIN_TEST(begine_and_end_iterators_person)

	Bst<Person> tree;
	tree.push(Person(5, "dana"));
	tree.push(Person(3, "yosi"));
	tree.push(Person(4, "hila"));
	tree.push(Person(1, "orel"));
	tree.push(Person(8, "shay"));
	tree.push(Person(7, "rony"));
	tree.push(Person(6, "david"));
	tree.push(Person(11, "mosh"));

	ASSERT_EQUAL(tree.begine().data().id(), 1);
	ASSERT_EQUAL(tree.end().data().id(), 0);

	std::cout << std::endl << "       ***print tree by iterators***" << std::endl;
	BstIterator<Person> it = tree.begine();
	BstIterator<Person> end = tree.end();
	while(it != end)
	{
		std::cout << "id: " << it->id() << " - name: " << it->name() << std::endl;
		it++;
	}

	std::cout << std::endl;

END_TEST

BEGIN_TEST(pull_by_iterator_and_value_person)

	Bst<Person> tree;

	tree.push(Person(5, "dana"));
	tree.push(Person(3, "yosi"));
	BstIterator<Person> four = tree.push(Person(4, "hila"));
	tree.push(Person(1, "orel"));
	BstIterator<Person> it = tree.push(Person(8, "shay"));
	tree.push(Person(7, "rony"));
	BstIterator<Person> fifteen = tree.push(Person(6, "david"));
	tree.push(Person(11, "mosh"));

	ASSERT_EQUAL(tree.size(), 8);

	std::cout << std::endl << "       ***pull 4 by iterator***" << std::endl;
	tree.pull(four);
	tree.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl << "       ***pull 6 by iterator***" << std::endl;
	tree.pull(fifteen);
	tree.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;

	std::cout << std::endl << "       ***pull 8 by value***" << std::endl;
	tree.pull(*it);
	tree.forEach(IN_ORDER, printPersonData);
	std::cout << std::endl;

	ASSERT_EQUAL(tree.size(), 5);

	std::cout << std::endl;
	ASSERT_PASS();

END_TEST

BEGIN_TEST(find_first_person)

	Bst<Person> tree;
	tree.push(Person(5, "dana"));
	tree.push(Person(3, "yosi"));
	tree.push(Person(4, "hila"));
	tree.push(Person(1, "orel"));
	tree.push(Person(8, "shay"));
	tree.push(Person(7, "rony"));
	tree.push(Person(6, "david"));
	tree.push(Person(11, "mosh"));

	std::cout << std::endl << "       ***find first even***" << std::endl;
	BstIterator<Person> find = tree.findFirst(findfirstEvenId);
	std::cout << find->id() << std::endl;
	ASSERT_EQUAL(find->id(), 4);

	std::cout << std::endl;

END_TEST

BEGIN_TEST(push_and_pull_person)

	Bst<Person> tree;

	BstIterator<Person> pushIt = tree.push(Person(4, "hila"));
	ASSERT_EQUAL(pushIt->id(), 4);

	BstIterator<Person> push2It = tree.push(Person(4, "hila"));
	ASSERT_EQUAL(push2It == tree.end(), true);

	Person p = tree.pull(pushIt);
	ASSERT_EQUAL(p.id(), 4);

	p = tree.pull(pushIt);
	ASSERT_EQUAL(p.id(), 0);

	std::cout << std::endl;

END_TEST

BEGIN_SUITE(TEST)

	TEST(copr_op_and_ctor)
	TEST(begine_and_end_iterators)
	TEST(pull_by_iterator_and_value)
	TEST(find_first)
	TEST(print_by_mode)
	TEST(push_and_pull)

	TEST(copr_op_and_ctor_person)
	TEST(begine_and_end_iterators_person)
	TEST(pull_by_iterator_and_value_person)
	TEST(find_first_person)
	TEST(print_by_mode_person)
	TEST(push_and_pull_person)

END_SUITE
