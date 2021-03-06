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
const TestTypeInt kInitElementNoThree = 77;
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

TEST(VectorSmokeTests, Push_Back_One_Elelement_Test) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  ASSERT_EQ(vector[0], kInitElement);
}

TEST(VectorSmokeTests, Push_Back_Two_Elelements_Test) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  vector.Push_back(kInitElementNoTwo);
  ASSERT_EQ(vector[0], kInitElement);
  ASSERT_EQ(vector[1], kInitElementNoTwo);
}

TEST(VectorSmokeTests, Get_Element_With_One_Elelement_Test) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  ASSERT_EQ(vector.GetElement(0), kInitElement);
}

TEST(VectorSmokeTests, Get_Element_With_Two_Elelements_Test) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  vector.Push_back(kInitElementNoTwo);
  ASSERT_EQ(vector.GetElement(0), kInitElement);
  ASSERT_EQ(vector.GetElement(1), kInitElementNoTwo);
}

TEST(VectorSmokeTests, Empty_Vector_And_IsEmpty_Returns_True) {
  praise_tools::Vector<TestTypeInt> vector;
  ASSERT_TRUE(vector.IsEmpty());
}

TEST(VectorSmokeTests, NOT_Empty_Vector_And_IsEmpty_Returns_False) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  ASSERT_FALSE(vector.IsEmpty());
}

TEST(VectorSmokeTests, Get_Vector_Size_Equal_To_Zero) {
  praise_tools::Vector<TestTypeInt> vector;
  ASSERT_EQ(vector.Size(), 0);
}

TEST(VectorSmokeTests, Get_Vector_Size_Equal_To_One) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  ASSERT_EQ(vector.Size(), 1);
}

TEST(VectorSmokeTests, Get_Vector_Size_Equal_To_Two) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  vector.Push_back(kInitElementNoTwo);
  ASSERT_EQ(vector.Size(), 2);
}

TEST(VectorSmokeTests, Clear_Vector_Test) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  vector.Push_back(kInitElementNoTwo);
  ASSERT_EQ(vector.Size(), 2);
  vector.Clear();
  ASSERT_EQ(vector.Size(), 0);
}

TEST(VectorSmokeTests, Erase_The_Second_Element_Test) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  vector.Push_back(kInitElementNoTwo);
  vector.Push_back(kInitElementNoThree);
  ASSERT_EQ(vector.Size(), 3);
  vector.Erase(1);
  ASSERT_EQ(vector.Size(), 2);
  ASSERT_EQ(vector[0], kInitElement);
  ASSERT_EQ(vector[1], kInitElementNoThree);
}

TEST(VectorSmokeTests, Erase_The_Firs_Element_Test) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  vector.Push_back(kInitElementNoTwo);
  vector.Push_back(kInitElementNoThree);
  ASSERT_EQ(vector.Size(), 3);
  vector.Erase(0);
  ASSERT_EQ(vector.Size(), 2);
  ASSERT_EQ(vector[0], kInitElementNoTwo);
  ASSERT_EQ(vector[1], kInitElementNoThree);
}

TEST(VectorSmokeTests, Insert_Element_At_The_Begenning) {
  praise_tools::Vector<TestTypeInt> vector;
  vector.Push_back(kInitElement);
  vector.Push_back(kInitElementNoTwo);
  ASSERT_EQ(vector.Size(), 2);
  vector.Insert(kInitElementNoThree);
  ASSERT_EQ(vector.Size(), 3);
  ASSERT_EQ(vector[0], kInitElementNoThree);
  ASSERT_EQ(vector[1], kInitElement);
  ASSERT_EQ(vector[2], kInitElementNoTwo);
}


} /*namespace vector_tests*/
