/*
 * Vector-Interface-Handler-Tests.cpp
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

#include "../../PraiseTools-Vector/PraiseTools-Vector/Source/Vector-Interface-Handler.cpp"

namespace vector_interface_handler_tests {

namespace {
const int kNewVectorElement = 7;
const int kNumberOfElementsInVector = 10;
}

template<class T>
class VectorInterfaceHandlerTests : public ::testing::Test {
 public:
  VectorInterfaceHandlerTests()
      :
      vector_data_container { new praise_tools::VectorDataContainer<T> },
      vector_interface_handler { new praise_tools::VectorInterfaceHandler<T> { vector_data_container } } {
  }

  void SetUp() override {
    this->vector_interface_handler->InitVectorObj();
  }

  void AddTestElement(T new_element) {

    if (*vector_data_container->vector_data == nullptr) {
      LOG_ERROR("%s", "Vector not initialized");
      return;
    }

    vector_data_container->vector_data = (T**) std::realloc(vector_data_container->vector_data, (vector_data_container->vector_data_size + 1) * sizeof(T*));

    if (vector_data_container->vector_data == nullptr) {
      LOG_ERROR("%s%d", "Failed of **vector_data realloc to size: ", vector_data_container->vector_data_size + 1);
      return;
    }

    vector_data_container->vector_data[vector_data_container->vector_data_size] = new (T);

    if (vector_data_container->vector_data[vector_data_container->vector_data_size] == nullptr) {
      LOG_ERROR("%s", "New Vector element allocation is failed");
      return;
    }

    *vector_data_container->vector_data[vector_data_container->vector_data_size] = new_element;
    ++vector_data_container->vector_data_size;
  }

  std::shared_ptr<praise_tools::VectorDataContainer<T>> vector_data_container;
  std::unique_ptr<praise_tools::VectorInterfaceHandler<T>> vector_interface_handler;
};

using MyTypes = ::testing::Types<int>;
TYPED_TEST_SUITE(VectorInterfaceHandlerTests, MyTypes);

TYPED_TEST(VectorInterfaceHandlerTests, Try_To_Init_Vactor_Object_And_Vector_Data_Pointer_Is_Not_Null) {
  ASSERT_TRUE(this->vector_data_container->vector_data != nullptr);
}

TYPED_TEST(VectorInterfaceHandlerTests, Try_Add_New_Element_To_Vector_And_Size_Is_Equal_To_One) {
  this->vector_interface_handler->AddNewElelemntToVector(kNewVectorElement);
  ASSERT_EQ(this->vector_data_container->vector_data_size, 1);
}

TYPED_TEST(VectorInterfaceHandlerTests, Try_Add_New_Element_To_Vector_And_The_Element_Is_Placed_In_The_Vector) {
  this->vector_interface_handler->AddNewElelemntToVector(kNewVectorElement);
  ASSERT_EQ(*this->vector_data_container->vector_data[0], kNewVectorElement);
}

TYPED_TEST(VectorInterfaceHandlerTests, Try_Add_New_Elements_To_Vector_And_Size_Is_Equal_To_The_Number_Of_Inserted_Elements) {

  for (int i = 0; i < kNumberOfElementsInVector; ++i) {
    this->vector_interface_handler->AddNewElelemntToVector(kNewVectorElement + i);
  }

  ASSERT_EQ(this->vector_data_container->vector_data_size, kNumberOfElementsInVector);
}

TYPED_TEST(VectorInterfaceHandlerTests, Try_Add_New_Elements_To_Vector_And_The_Elements_Are_Placed_In_The_Vector) {

  for (int i = 0; i < kNumberOfElementsInVector; ++i) {
    this->vector_interface_handler->AddNewElelemntToVector(kNewVectorElement + i);
  }

  for (int i = 0; i < kNumberOfElementsInVector; ++i) {
    ASSERT_EQ(*this->vector_data_container->vector_data[i], kNewVectorElement + i);
  }
}

TYPED_TEST(VectorInterfaceHandlerTests, Try_To_Dispose_Of_Vector_Object_And_Vector_Data_Size_Is_Set_To_Zero) {
  this->AddTestElement(kNewVectorElement);
  this->vector_interface_handler->DisposeOfVectorObj();
  ASSERT_EQ(this->vector_data_container->vector_data_size, 0);
}

} /*namespace vector_interface_handler_tests*/


