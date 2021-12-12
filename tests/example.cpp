// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#include <gtest/gtest.h>

#include "SharedPtr.hpp"

TEST(SharedPtr, global) {
  int buff_int = 5067;
  std::string buff_string = "string";
  auto *ptr_int = new int(buff_int);
  auto *ptr_string = new std::string(buff_string);

  // Constructor
  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
  auto shared_ptr_null = SharedPtr<int>();

  // Copy
  auto shared_ptr_int_Copy = shared_ptr_int;
  // Copy exception
  EXPECT_EQ(shared_ptr_int_Copy.get(), ptr_int);
  EXPECT_EQ(shared_ptr_int_Copy.use_count(), 2);

  // Move constructor
  auto shared_ptr_int_Move = SharedPtr<int>(std::move(shared_ptr_int_Copy));

  // Exception
  EXPECT_EQ(shared_ptr_int_Move.get(), ptr_int);
  EXPECT_EQ(shared_ptr_int_Move.use_count(), 2);
  EXPECT_EQ(shared_ptr_int_Copy.get(), nullptr);

  // Object exception
  EXPECT_EQ(static_cast<bool>(shared_ptr_int), true);
  EXPECT_EQ(static_cast<bool>(shared_ptr_string), true);
  EXPECT_EQ(static_cast<bool>(shared_ptr_null), false);

  // Count exception
  EXPECT_EQ(shared_ptr_int.use_count(), 2);
  EXPECT_EQ(shared_ptr_string.use_count(), 1);
  EXPECT_EQ(shared_ptr_null.use_count(), 0);

  // Object value exception
  EXPECT_EQ(*shared_ptr_int, buff_int);
  EXPECT_EQ(*shared_ptr_string, buff_string);

  // Pointer exception
  EXPECT_EQ(shared_ptr_int.get(), ptr_int);
  EXPECT_EQ(shared_ptr_string.get(), ptr_string);
  EXPECT_EQ(shared_ptr_null.get(), nullptr);

  EXPECT_EQ(shared_ptr_int.operator->(), ptr_int);
  EXPECT_EQ(shared_ptr_string->empty(), ptr_string->empty());
  EXPECT_EQ(shared_ptr_null.operator->(), nullptr);

  // Swap
  shared_ptr_int.swap(shared_ptr_null);
  // Swap exception
  EXPECT_EQ(shared_ptr_int.get(), nullptr);
  EXPECT_EQ(shared_ptr_null.get(), ptr_int);

  // Reset
  shared_ptr_int.reset(ptr_int);
  shared_ptr_null.reset();

  // Reset exception
  EXPECT_EQ(shared_ptr_int.get(), ptr_int);
  EXPECT_EQ(shared_ptr_null.get(), nullptr);
}
