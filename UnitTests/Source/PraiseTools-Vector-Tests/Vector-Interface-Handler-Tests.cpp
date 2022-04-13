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

#include "../../PraiseTools-Vector/PraiseTools-Vector/Source/Vector-Interface-Handler.h"

namespace vector_interface_handler_tests {

namespace {
typedef int TestTypeInt;
const int kNewVectorElement = 1;
const int kNewVectorElementNoTwo = 2;
const int kNewVectorElementNoThree = 3;
const int kNewVectorElementNoFour = 4;
const int kNewVectorElementToCompare = 11;

const int kNumberOfElementsInVector = 10;
}

template<class T>
class VectorInterfaceHandlerTests : public ::testing::Test {
 public:
  VectorInterfaceHandlerTests()
      :
      vector_data_container { new praise_tools::VectorDataContainer<T> },
      vector_interface_handler { new praise_tools::VectorInterfaceHandler<T> { vector_data_container } },
      vector_data_container_source { new praise_tools::VectorDataContainer<T> }
      {
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

  void AllocateVectorDataContainerSource() {
    vector_data_container_source->vector_data = (T**) std::malloc(sizeof(T*));
    vector_data_container_source->vector_data_size = 0;
    vector_data_container_source->vector_data[vector_data_container_source->vector_data_size] = new (T);
    *vector_data_container_source->vector_data[vector_data_container_source->vector_data_size] = kNewVectorElement;
    ++vector_data_container_source->vector_data_size;
  }

  std::shared_ptr<praise_tools::VectorDataContainer<T>> vector_data_container;
  std::unique_ptr<praise_tools::VectorInterfaceHandler<T>> vector_interface_handler;
  std::unique_ptr<praise_tools::VectorDataContainer<T>> vector_data_container_source;
};

using MyTypes = ::testing::Types<TestTypeInt>;
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

TYPED_TEST(VectorInterfaceHandlerTests, Allocate_Source_Vector_Data_Container_And_Try_To_Copy_It_To_Another_Vector_Container_And_Element_Is_Copied) {
  this->AllocateVectorDataContainerSource();
  this->vector_interface_handler->CopyVectorToVector(*this->vector_data_container_source);
  ASSERT_EQ(*this->vector_data_container->vector_data[0], kNewVectorElement);
}

TYPED_TEST(VectorInterfaceHandlerTests, Allocate_Source_Vector_Data_Container_And_Try_To_Copy_It_To_Another_Vector_Container_And_Size_Is_Set_To_One) {
  this->AllocateVectorDataContainerSource();
  this->vector_interface_handler->CopyVectorToVector(*this->vector_data_container_source);
  ASSERT_EQ(this->vector_data_container->vector_data_size, 1);
}

TYPED_TEST(VectorInterfaceHandlerTests, Allocate_Source_Vector_Data_Container_And_Try_To_Move_It_To_Another_Vector_Container_And_Element_Is_Moved) {
  this->AllocateVectorDataContainerSource();
  this->vector_interface_handler->MoveVectorToVector(std::move(*this->vector_data_container_source));
  ASSERT_EQ(*this->vector_data_container->vector_data[0], kNewVectorElement);
}

TYPED_TEST(VectorInterfaceHandlerTests, Allocate_Source_Vector_Data_Container_And_Try_To_Move_It_To_Another_Vector_Container_And_Size_Is_Set_To_One) {
  this->AllocateVectorDataContainerSource();
  this->vector_interface_handler->MoveVectorToVector(std::move(*this->vector_data_container_source));
  ASSERT_EQ(this->vector_data_container->vector_data_size, 1);
  ASSERT_EQ(*this->vector_data_container->vector_data[0], kNewVectorElement);
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_New_Element_To_Vector_And_Get_It_By_Index_Is_Successfull) {
  this->AddTestElement(kNewVectorElement);
  ASSERT_EQ(this->vector_interface_handler->GetElementByIndex(0), kNewVectorElement);
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_New_Elements_To_Vector_And_Get_It_By_Index_Is_Successfull) {
  this->AddTestElement(kNewVectorElement);
  this->AddTestElement(kNewVectorElement + 1);
  ASSERT_EQ(this->vector_interface_handler->GetElementByIndex(1), kNewVectorElement + 1);
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_More_Elements_To_Vector_And_Get_It_By_Index_Is_Successfull) {
  this->AddTestElement(kNewVectorElement);
  this->AddTestElement(kNewVectorElement + 1);
  this->AddTestElement(kNewVectorElement + 2);
  ASSERT_EQ(this->vector_interface_handler->GetElementByIndex(2), kNewVectorElement + 2);
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_Same_Elements_To_Two_Vectors_And_Compared_Them_And_True_Returned) {
  this->AddTestElement(kNewVectorElement);
  this->AllocateVectorDataContainerSource();
  ASSERT_TRUE(this->vector_interface_handler->CompareVectorToVector(*this->vector_data_container_source));
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_Different_Elements_To_Two_Vectors_And_Compared_Them_And_False_Returned) {
  this->AddTestElement(kNewVectorElementToCompare);
  this->AllocateVectorDataContainerSource();
  ASSERT_FALSE(this->vector_interface_handler->CompareVectorToVector(*this->vector_data_container_source));
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_One_Elements_And_IsVectorEmpty_Should_Return_False) {
  this->AddTestElement(kNewVectorElement);
  ASSERT_FALSE(this->vector_interface_handler->IsVectorEmpty());
}

TYPED_TEST(VectorInterfaceHandlerTests, None_Elements_And_IsVectorEmpty_Should_Return_True) {
  ASSERT_TRUE(this->vector_interface_handler->IsVectorEmpty());
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_One_Elements_And_GetVectorSize_Should_Return_One) {
  this->AddTestElement(kNewVectorElement);
  ASSERT_EQ(this->vector_interface_handler->GetVectorSize(), 1);
}

TYPED_TEST(VectorInterfaceHandlerTests, None_Elements_And_GetVectorSize_Should_Return_Zero) {
  ASSERT_EQ(this->vector_interface_handler->GetVectorSize(), 0);
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_Three_Elements_To_Vector_And_Remove_All_Of_Them_And_True_Returned) {
  this->AddTestElement(kNewVectorElement);
  this->AddTestElement(kNewVectorElementNoTwo);
  this->AddTestElement(kNewVectorElementNoThree);
  ASSERT_TRUE(this->vector_interface_handler->ClearVector());
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_Three_Elements_To_Vector_And_Remove_All_Of_Them_And_Vector_Size_Reseted_To_Zero) {
  this->AddTestElement(kNewVectorElement);
  this->AddTestElement(kNewVectorElementNoTwo);
  this->AddTestElement(kNewVectorElementNoThree);
  ASSERT_EQ(this->vector_data_container->vector_data_size, 3);
  this->vector_interface_handler->ClearVector();
  ASSERT_EQ(this->vector_data_container->vector_data_size, 0);
}

TYPED_TEST(VectorInterfaceHandlerTests, Add_Four_Elements_And_Try_To_Removed_With_Index_Two_One_And_Element_Number_Two_Removed) {
  this->AddTestElement(kNewVectorElement);
  this->AddTestElement(kNewVectorElementNoTwo);
  this->AddTestElement(kNewVectorElementNoThree);
  this->AddTestElement(kNewVectorElementNoFour);
  ASSERT_EQ(this->vector_data_container->vector_data_size, 4);
  this->vector_interface_handler->EraseElement(2);
  ASSERT_EQ(this->vector_data_container->vector_data_size, 3);

  ASSERT_EQ(*this->vector_data_container->vector_data[0], kNewVectorElement);
  ASSERT_EQ(*this->vector_data_container->vector_data[1], kNewVectorElementNoThree);
  ASSERT_EQ(*this->vector_data_container->vector_data[2], kNewVectorElementNoFour);

}

} /*namespace vector_interface_handler_tests*/


