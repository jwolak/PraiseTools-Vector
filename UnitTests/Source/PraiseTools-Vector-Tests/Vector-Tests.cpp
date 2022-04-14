/*
 * Vector-Tests.cpp
 *
 *  Created on: 2022
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Janusz Wolak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <gtest/gtest.h>

#include <memory>

#include "../../PraiseTools-Vector/PraiseTools-Vector/Source/Vector.h"

namespace vector_tests {

namespace {
typedef int TestTypeInt;
const TestTypeInt kInitElement = 7;
const TestTypeInt kInitElementNoTwo = 21;
}

template<class T>
class VectorSmokeTests : public ::testing::Test {
 public:
  VectorSmokeTests() : vector { new praise_tools::Vector<T> } {}

  std::unique_ptr<praise_tools::Vector<T>> vector;
};

using MyTypes = ::testing::Types<TestTypeInt>;
TYPED_TEST_SUITE(VectorSmokeTests, MyTypes);

TYPED_TEST(VectorSmokeTests, test) {

}

TEST(VectorSmokeTests, Create_Empty_Vector) {
  ASSERT_NO_THROW(praise_tools::Vector<TestTypeInt> vector);
}

TEST(VectorSmokeTests, Create_Vector_With_Init_Element) {
  ASSERT_NO_THROW(praise_tools::Vector<TestTypeInt> vector(kInitElement));
}

TEST(VectorSmokeTests, Braces_Operator_Test) {
  praise_tools::Vector<TestTypeInt> vector(kInitElement);
  ASSERT_EQ(vector[0], kInitElement);
}

TEST(VectorSmokeTests, Copy_Constructor_Test) {
  praise_tools::Vector<TestTypeInt> source_vector(kInitElement);
  ASSERT_NO_THROW(praise_tools::Vector<TestTypeInt> vector(source_vector));
}

TEST(VectorSmokeTests, Copy_Constructor_Test_And_Check_Copied_Value) {
  praise_tools::Vector<TestTypeInt> source_vector(kInitElement);
  praise_tools::Vector<TestTypeInt> vector(source_vector);
  ASSERT_EQ(vector[0], kInitElement);
}

TEST(VectorSmokeTests, DISABLED_Move_Constructor_Test) {
  praise_tools::Vector<TestTypeInt> source_vector(kInitElement);
  ASSERT_NO_THROW(praise_tools::Vector<TestTypeInt> vector(std::move(source_vector)));
}

TEST(VectorSmokeTests, Is_Equal_Operator_Test) {
  praise_tools::Vector<TestTypeInt> source_vector(kInitElement);
  praise_tools::Vector<TestTypeInt> vector;
  ASSERT_NO_THROW(vector = source_vector);
}

TEST(VectorSmokeTests, Is_Equal_Operator_And_Check_Copied_Value) {
  praise_tools::Vector<TestTypeInt> source_vector(kInitElement);
  praise_tools::Vector<TestTypeInt> vector;
  vector = source_vector;
  ASSERT_EQ(vector[0], kInitElement);
}

TEST(VectorSmokeTests, Equality_Operator_Test_Two_Equal_Vectors_And_True_Should_Be_Returned) {
  praise_tools::Vector<TestTypeInt> source_vector(kInitElement);
  praise_tools::Vector<TestTypeInt> vector(kInitElement);
  ASSERT_TRUE(vector == source_vector);
}

TEST(VectorSmokeTests, Equality_Operator_Test_Two_NOT_Equal_Vectors_And_False_Should_Be_Returned) {
  praise_tools::Vector<TestTypeInt> source_vector(kInitElement);
  praise_tools::Vector<TestTypeInt> vector(kInitElementNoTwo);
  ASSERT_FALSE(vector == source_vector);
}

} /*namespace vector_tests*/
