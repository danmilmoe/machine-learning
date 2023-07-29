// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

TEST(test_empty) {
  BinarySearchTree<int> tree;
  
  ASSERT_TRUE(tree.empty());
}

TEST(test_full) {
  BinarySearchTree<int> tree;
  
  tree.insert(4);
  
  ASSERT_TRUE(!tree.empty());
}

TEST(test_basic_size) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(tree.size() == 3);
}

TEST(test_size_empty) {
  BinarySearchTree<int> tree;

  ASSERT_EQUAL(tree.size(), 0);
}

TEST(test_complex_size) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(9);
  tree.insert(7);

  ASSERT_TRUE(tree.size() == 5);
}

TEST(test_complexer_size) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(9);
  tree.insert(7);
  tree.insert(0);
  tree.insert(-2);
  tree.insert(-1);

  ASSERT_TRUE(tree.size() == 8);
}

TEST(test_basic_height) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(tree.height() == 2);
}

TEST(test_complex_height_right) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(9);
  tree.insert(7);

  ASSERT_TRUE(tree.height() == 4);
}

TEST(test_complex_height_left) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(2);

  ASSERT_TRUE(tree.height() == 4);
}

TEST(test_complexer_height) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(9);
  
  ASSERT_TRUE(tree.height() == 3);

  tree.insert(7);
  tree.insert(0);
  tree.insert(-2);
  tree.insert(-1);

  ASSERT_TRUE(tree.height() == 5);
}

TEST(test_copy_ctor) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(1);
  tree.insert(5);

  BinarySearchTree<int> tree2(tree);

  auto it = tree2.begin();
  ASSERT_TRUE(*it == 1);
  ++it;
  ASSERT_TRUE(*it == 3);
  ++it;
  ASSERT_TRUE(*it == 5);

  tree2.insert(4);
  ++it;

  ASSERT_TRUE(tree2.height() == 3);
  ASSERT_TRUE(tree2.size() == 4);
  ASSERT_TRUE(*tree2.min_element() == 1);
  ASSERT_TRUE(*tree2.max_element() == 5);
  ASSERT_TRUE(*tree2.min_greater_than(3) == 4);
}

TEST(test_assignment_operator) {
  BinarySearchTree<int> tree1;
  BinarySearchTree<int> tree2;

  tree1.insert(3);
  tree1.insert(1);
  tree1.insert(5);

  tree2.insert(2);

  tree2 = tree1;

  auto it = tree2.begin();
  ASSERT_TRUE(*it == 1);
  ++it;
  ASSERT_TRUE(*it == 3);
  ++it;
  ASSERT_TRUE(*it == 5);
}

//dtor test unnecessary - Piazza

TEST(test_basic_find) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(*(tree.find(3)) == 3);
  ASSERT_TRUE(*(tree.find(4)) == 4);
  ASSERT_TRUE(*(tree.find(5)) == 5);
}

TEST(test_complex_find) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  
  ASSERT_TRUE(tree.find(9) == tree.end());

  tree.insert(9);
  tree.insert(7);

  ASSERT_TRUE(*(tree.find(9)) == 9);
  ASSERT_TRUE(*(tree.find(7)) == 7);
}

TEST(test_basic_min) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(*tree.min_element() == 3);
}

TEST(test_complex_min) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  
  ASSERT_TRUE(*tree.min_element() == 3);

  tree.insert(-1);
  tree.insert(0);

  ASSERT_TRUE(*tree.min_element() == -1);
}

TEST(test_basic_max) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(*tree.max_element() == 5);
}

TEST(test_complex_max) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  
  ASSERT_TRUE(*tree.max_element() == 5);

  tree.insert(9);
  tree.insert(7);
  tree.insert(8);

  ASSERT_TRUE(*tree.max_element() == 9);
}

TEST(test_basic_min_greater) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(-2);

  ASSERT_TRUE(*tree.min_greater_than(4) == 5);
}

TEST(test_complex_min_greater) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(-2);
  tree.insert(1);
  tree.insert(8);

  ASSERT_TRUE(*tree.min_greater_than(5) == 8);
}

TEST(test_basic_sorting_invariant) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_complex_sorting_invariant) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(-2);
  tree.insert(1);
  tree.insert(8);
  tree.insert(0);

  ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_check_sorting_invariant_false_left) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(1);
  tree.insert(5);

  auto it = tree.find(1);
  *it = 7;
  ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_check_sorting_invariant_false_right) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(1);
  tree.insert(5);

  auto it = tree.find(5);
  *it = -1;
  cout << tree.to_string() << endl;
  ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_traverse_preorder) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(-1);
  tree.insert(9);
  tree.insert(0);
  tree.insert(7);
  
  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "4 3 -1 0 5 9 7 ");
}

TEST(test_traverse_inorder) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(-1);
  tree.insert(9);
  tree.insert(0);
  tree.insert(7);

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "-1 0 3 4 5 7 9 ");
}

TEST(test_min_greater_than_map_analagous) {
  BinarySearchTree<int> tree;

  tree.insert(5);
  tree.insert(7);
  tree.insert(6);

  ASSERT_TRUE(*(tree.min_greater_than(6)) == 7);
}

TEST(test_basic_begin) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(*tree.begin() == 3);
}

TEST(test_complex_begin) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);
  tree.insert(-1);
  tree.insert(9);
  tree.insert(0);
  tree.insert(7);

  ASSERT_TRUE(*tree.begin() == -1);
}

TEST(test_itr_deref) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(5);
  tree.insert(1);

  auto it = tree.begin();
  ASSERT_EQUAL(*it, 1);
}

TEST(test_itr_prefix_inc) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(5);
  tree.insert(1);

  auto it = tree.begin();
  ++it;
  ASSERT_EQUAL(*it, 3);
}

TEST(test_itr_postfix_inc) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(5);
  tree.insert(1);

  auto it = tree.begin();
  it++;
  ASSERT_EQUAL(*it, 3);
}

TEST(test_itr_equals) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(5);
  tree.insert(1);

  auto it = tree.begin();
  ++it;
  auto it2 = tree.begin();
  ++it2;

  ASSERT_TRUE(it == it2);
}

TEST(test_itr_not_equals) {
  BinarySearchTree<int> tree;

  tree.insert(3);
  tree.insert(5);
  tree.insert(1);

  auto it = tree.begin();
  ++it;
  auto it2 = tree.begin();

  ASSERT_TRUE(it != it2);
}

TEST(itr_test_insert) {
  BinarySearchTree<int> tree;

  auto it = tree.insert(3);
  ASSERT_EQUAL(*it, 3);
}

TEST(itr_arrow) {
  BinarySearchTree<std::pair<int, double>> tree;
  auto it = tree.insert({ 3, 4.1 });
  ASSERT_EQUAL(it->first, 3);
  ASSERT_EQUAL(it->second, 4.1);
}


TEST(test_empty_1) {
  BinarySearchTree<int> tree;
  
  ASSERT_TRUE(tree.empty());
  ASSERT_EQUAL(tree.size(), 0);
  ASSERT_EQUAL(tree.height(), 0);

  BinarySearchTree<int> tree2(tree);
  ASSERT_TRUE(tree2.empty());
  ASSERT_EQUAL(tree2.size(), 0);
  ASSERT_EQUAL(tree2.height(), 0);
}

TEST(test_full_1) {
  BinarySearchTree<int> tree;
  
  tree.insert(4);
  
  ASSERT_TRUE(!tree.empty());
}

TEST(test_basic_tree) {
  BinarySearchTree<int> tree;

  tree.insert(4);
  tree.insert(5);
  tree.insert(3);

  ASSERT_TRUE(tree.size() == 3);
  ASSERT_TRUE(tree.height() == 2);
  ASSERT_TRUE(*tree.begin() == 3);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.max_element() == 5);
  ASSERT_TRUE(*tree.min_greater_than(4) == 5);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*(tree.find(3)) == 3);
  ASSERT_TRUE(tree.find(9) == tree.end());

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "4 3 5 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 4 5 ");

  BinarySearchTree<int> tree2(tree);

  auto it = tree2.begin();
  ASSERT_TRUE(*it == 3);
  ++it;
  ASSERT_TRUE(*it == 4);
  ++it;
  ASSERT_TRUE(*it == 5);

  tree2.insert(7);
  ++it;

  ASSERT_TRUE(tree2.height() == 3);
  ASSERT_TRUE(tree2.size() == 4);
  ASSERT_TRUE(*tree2.min_element() == 3);
  ASSERT_TRUE(*tree2.max_element() == 7);
  ASSERT_TRUE(*tree2.min_greater_than(3) == 4);
}

TEST(test_left_children_tree) {
  BinarySearchTree<int> tree;

  tree.insert(7);
  tree.insert(6);
  tree.insert(5);
  tree.insert(4);
  tree.insert(3);

  ASSERT_TRUE(tree.size() == 5);
  ASSERT_TRUE(tree.height() == 5);
  ASSERT_TRUE(*tree.begin() == 3);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_greater_than(6) == 7);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*(tree.find(3)) == 3);
  ASSERT_TRUE(tree.find(9) == tree.end());

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "7 6 5 4 3 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 4 5 6 7 ");

  BinarySearchTree<int> tree2(tree);

  tree2.insert(2);

  ASSERT_TRUE(!tree2.empty());
  ASSERT_TRUE(tree2.height() == 6);
  ASSERT_TRUE(tree2.size() == 6);
  ASSERT_TRUE(*tree2.min_element() == 2);
  ASSERT_TRUE(*tree2.max_element() == 7);
  ASSERT_TRUE(*tree2.min_greater_than(2) == 3);
  ASSERT_TRUE(tree2.check_sorting_invariant());
}

TEST(test_right_children_tree) {
  BinarySearchTree<int> tree;

  tree.insert(7);
  tree.insert(8);
  tree.insert(9);
  tree.insert(10);
  tree.insert(11);

  ASSERT_TRUE(tree.size() == 5);
  ASSERT_TRUE(tree.height() == 5);
  ASSERT_TRUE(*tree.begin() == 7);
  ASSERT_TRUE(*tree.min_element() == 7);
  ASSERT_TRUE(*tree.max_element() == 11);
  ASSERT_TRUE(*tree.min_greater_than(6) == 7);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*(tree.find(11)) == 11);
  ASSERT_TRUE(tree.find(2) == tree.end());

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "7 8 9 10 11 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "7 8 9 10 11 ");

  BinarySearchTree<int> tree2(tree);

  tree2.insert(12);

  ASSERT_TRUE(!tree2.empty());
  ASSERT_TRUE(tree2.height() == 6);
  ASSERT_TRUE(tree2.size() == 6);
  ASSERT_TRUE(*tree2.min_element() == 7);
  ASSERT_TRUE(*tree2.max_element() == 12);
  ASSERT_TRUE(*tree2.min_greater_than(11) == 12);
  ASSERT_TRUE(tree2.check_sorting_invariant());
}

TEST(test_extreme_tree) {
  BinarySearchTree<int> tree;

  tree.insert(50);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(39);
  tree.insert(25);
  tree.insert(24);
  tree.insert(28);
  tree.insert(29);
  tree.insert(75);
  tree.insert(60);
  tree.insert(61);
  tree.insert(62);
  tree.insert(87);
  tree.insert(92);
  tree.insert(90);
  tree.insert(88);
  tree.insert(89);
  tree.insert(91);

  ASSERT_TRUE(tree.size() == 19);
  ASSERT_TRUE(tree.height() == 7);
  ASSERT_TRUE(*tree.begin() == 20);
  ASSERT_TRUE(*tree.min_element() == 20);
  ASSERT_TRUE(*tree.max_element() == 92);
  cout << *tree.min_greater_than(88) << endl;
  ASSERT_TRUE(*tree.min_greater_than(61) == 62);
  ASSERT_TRUE(*tree.min_greater_than(88) == 89);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*(tree.find(28)) == 28);
  ASSERT_TRUE(tree.find(63) == tree.end());

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  string correct1 = "50 20 30 25 24 28 29 40 39 75 60 61 62 87 92 90 88 89 91 ";
  ASSERT_TRUE(oss_preorder.str() == correct1);

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  string correct2 = "20 24 25 28 29 30 39 40 50 60 61 62 75 87 88 89 90 91 92 ";
  ASSERT_TRUE(oss_inorder.str() == correct2);

  BinarySearchTree<int> tree2(tree);

  tree2.insert(12);
  tree2.insert(9);
  tree2.insert(15);

  ASSERT_TRUE(!tree2.empty());
  ASSERT_TRUE(tree2.height() == 7);
  ASSERT_TRUE(tree2.size() == 22);
  ASSERT_TRUE(*tree2.min_element() == 9);
  ASSERT_TRUE(*tree2.max_element() == 92);
  cout << *tree2.min_greater_than(13) << endl;
  ASSERT_TRUE(*tree2.min_greater_than(13) == 15);
  ASSERT_TRUE(tree2.check_sorting_invariant());
}

TEST(test_min_greater_than_nullptr) {
  BinarySearchTree<int> tree;

  tree.insert(7);

  ASSERT_TRUE(tree.min_greater_than(7) == tree.end());
}

TEST_MAIN()
