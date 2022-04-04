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

template<class T>
class VectorInterfaceHandlerTests : public ::testing::Test {
 public:
  VectorInterfaceHandlerTests()
      :
      vector_data_container { new praise_tools::VectorDataContainer<T> },
      vector_interface_handler { new praise_tools::VectorInterfaceHandler<T> { vector_data_container } } {
  }

  std::shared_ptr<praise_tools::VectorDataContainer<T>> vector_data_container;
  std::unique_ptr<praise_tools::VectorInterfaceHandler<T>> vector_interface_handler;
};

using MyTypes = ::testing::Types<char, int, unsigned int>;
TYPED_TEST_SUITE(VectorInterfaceHandlerTests, MyTypes);

TYPED_TEST(VectorInterfaceHandlerTests, Test1) {
  this->vector_interface_handler->InitVectorObj();
  ASSERT_TRUE(this->vector_data_container->vector_data != nullptr);
}

} /*namespace vector_interface_handler_tests*/


