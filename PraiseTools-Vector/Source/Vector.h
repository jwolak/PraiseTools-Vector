/*
 * Vector.h
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

#ifndef SOURCE_VECTOR_H_
#define SOURCE_VECTOR_H_

#include <cstdint>
#include <memory>

#include "Vector-Interface-Handler.h"
#include "Logger.h"

namespace praise_tools {

template<class T>
class Vector {
 public:
  ~Vector();
  Vector();
  Vector(T &init_lelement);
  Vector(const Vector &source_vector);
  Vector(const Vector &&source_vector);

  T& operator [](uint32_t);
  void operator=(const Vector&);
  void operator==(const Vector&);
  void Add(T&);
  T& GetElement();
  bool IsEmpty();
  uint32_t Size();
  void Clear();
  void Insert(T&);
  void Erase(uint32_t);
  void Push_back(T&);
  void Emplace_back(T&);

private:
  std::unique_ptr<VectorInterfaceHandler<T>> vector_interface_handler_;
  std::shared_ptr<VectorDataContainer<T>> vec_data_container_;
/*  T **tab_vector_;
  uint32_t vector_size_;*/
};

} /*namespace praise_tools*/

#endif /* SOURCE_VECTOR_H_ */
