// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#include <gtest/gtest.h>

#include "SharedPtr.hpp"

TEST(SharedPtr, constructor) {
  int buff_int = 5067;
  std::string buff_string = "string";
  auto *ptr_int = new int(buff_int);
  auto *ptr_string = new std::string(buff_string);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
  auto shared_ptr_null = SharedPtr<int>();
}

TEST(SharedPtr, copy) {
  int buff_int = 5067;
  auto *ptr_int = new int(buff_int);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_int_Copy = shared_ptr_int;

  EXPECT_EQ(shared_ptr_int_Copy.get(), ptr_int);
  EXPECT_EQ(shared_ptr_int_Copy.use_count(), 2);
}

TEST(SharedPtr, move) {
  int buff_int = 5067;
  auto *ptr_int = new int(buff_int);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_int_Copy = shared_ptr_int;

  auto shared_ptr_int_Move = SharedPtr<int>(std::move(shared_ptr_int_Copy));

  EXPECT_EQ(shared_ptr_int_Move.get(), ptr_int);
  EXPECT_EQ(shared_ptr_int_Move.use_count(), 2);
  EXPECT_EQ(shared_ptr_int_Copy.get(), nullptr);
}


TEST(SharedPtr, type) {
  int buff_int = 5067;
  std::string buff_string = "string";
  auto *ptr_int = new int(buff_int);
  auto *ptr_string = new std::string(buff_string);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
  auto shared_ptr_null = SharedPtr<int>();

  EXPECT_EQ(static_cast<bool>(shared_ptr_int), true);
  EXPECT_EQ(static_cast<bool>(shared_ptr_string), true);
  EXPECT_EQ(static_cast<bool>(shared_ptr_null), false);
}

TEST(SharedPtr, count) {
  int buff_int = 5067;
  std::string buff_string = "string";
  auto *ptr_int = new int(buff_int);
  auto *ptr_string = new std::string(buff_string);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
  auto shared_ptr_null = SharedPtr<int>();

  auto shared_ptr_int_Copy = shared_ptr_int;
  auto shared_ptr_int_Move = SharedPtr<int>(std::move(shared_ptr_int_Copy));

  EXPECT_EQ(shared_ptr_int.use_count(), 2);
  EXPECT_EQ(shared_ptr_string.use_count(), 1);
  EXPECT_EQ(shared_ptr_null.use_count(), 0);
}

TEST(SharedPtr, object_value) {
  int buff_int = 5067;
  std::string buff_string = "string";
  auto *ptr_int = new int(buff_int);
  auto *ptr_string = new std::string(buff_string);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_string = SharedPtr<std::string>(ptr_string);

  EXPECT_EQ(*shared_ptr_int, buff_int);
  EXPECT_EQ(*shared_ptr_string, buff_string);
}

TEST(SharedPtr, pointer) {
  int buff_int = 5067;
  std::string buff_string = "string";
  auto *ptr_int = new int(buff_int);
  auto *ptr_string = new std::string(buff_string);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
  auto shared_ptr_null = SharedPtr<int>();

  EXPECT_EQ(shared_ptr_int.get(), ptr_int);
  EXPECT_EQ(shared_ptr_string.get(), ptr_string);
  EXPECT_EQ(shared_ptr_null.get(), nullptr);
}

TEST(SharedPtr, operat) {
  int buff_int = 5067;
  std::string buff_string = "string";
  auto *ptr_int = new int(buff_int);
  auto *ptr_string = new std::string(buff_string);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
  auto shared_ptr_null = SharedPtr<int>();

  EXPECT_EQ(shared_ptr_int.operator->(), ptr_int);
  EXPECT_EQ(shared_ptr_string->empty(), ptr_string->empty());
  EXPECT_EQ(shared_ptr_null.operator->(), nullptr);
}

TEST(SharedPtr, swap) {
  int buff_int = 5067;
  auto *ptr_int = new int(buff_int);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_null = SharedPtr<int>();

  shared_ptr_int.swap(shared_ptr_null);

  EXPECT_EQ(shared_ptr_int.get(), nullptr);
  EXPECT_EQ(shared_ptr_null.get(), ptr_int);
}

TEST(SharedPtr, reset) {
  int buff_int = 5067;
  auto *ptr_int = new int(buff_int);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_null = SharedPtr<int>();

  shared_ptr_null.reset(ptr_int);
  shared_ptr_int.reset();

  EXPECT_EQ(shared_ptr_int.get(), nullptr);
  EXPECT_EQ(shared_ptr_null.get(), ptr_int);
}
