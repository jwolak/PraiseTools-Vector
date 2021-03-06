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
  ~Vector() {

    LOG_DEBUG("%s", "Vector<T>::~Vector()");

    if (!vector_interface_handler_->DisposeOfVectorObj()) {
      LOG_ERROR("%s", "Dispose of Vector object failed!");
    }

    LOG_DEBUG("%s", "Dispose of Vector object successful");
  }

  Vector()
      :
      vec_data_container_ { new VectorDataContainer<T> },
      vector_interface_handler_ { new VectorInterfaceHandler<T> { vec_data_container_ } } {

    LOG_DEBUG("%s", "Vector<T>::Vector()");

    if (vector_interface_handler_->InitVectorObj()) {
      LOG_DEBUG("%s", "Vector object initialization is successful");
    } else {
      LOG_ERROR("%s", "Vector object initialization is failed");
      exit(1);
    }
  }

  Vector(T init_lelement)
      :
      vec_data_container_ { new VectorDataContainer<T> },
      vector_interface_handler_ { new VectorInterfaceHandler<T> { vec_data_container_ } } {

    LOG_DEBUG("%s", "Vector<T>::Vector(T)");

    if (vector_interface_handler_->InitVectorObj()) {
      LOG_DEBUG("%s", "Vector object initialization is successful");

      if (vector_interface_handler_->AddNewElelemntToVector(init_lelement)) {
        LOG_DEBUG("%s", "Init Vector and add init element is successful");
      } else {
        LOG_ERROR("%s", "Init Vector and add init element is failed");
        exit(1);
      }

    } else {
      LOG_ERROR("%s", "Vector object initialization is failed");
      exit(1);
    }
  }

  Vector(const Vector &source_vector)
      :
      vec_data_container_ { new VectorDataContainer<T> },
      vector_interface_handler_ { new VectorInterfaceHandler<T> { vec_data_container_ } } {

    LOG_DEBUG("%s", "Copy constructor called");
    LOG_DEBUG("%s", "Vector<T>::Vector(const Vector &)");

    if (vector_interface_handler_->InitVectorObj()) {
      LOG_DEBUG("%s", "Vector object initialization is successful");

      if (!vector_interface_handler_->CopyVectorToVector(*source_vector.vec_data_container_)) {
        LOG_ERROR("%s", "Copy constructor failed to proceed");
        exit(1);
      } else {
        LOG_DEBUG("%s", "Copy constructor successfully copied all elements");
      }

    } else {
      LOG_ERROR("%s", "Vector object initialization is failed");
      exit(1);
    }
  }

  Vector(const Vector &&source_vector)
      :
        vec_data_container_ { new VectorDataContainer<T> },
      vector_interface_handler_ { new VectorInterfaceHandler<T> { vec_data_container_ } } {

    LOG_DEBUG("%s", "Move constructor called");
    LOG_DEBUG("%s", "Vector<T>::Vector(const Vector&&)");

    if (!vector_interface_handler_->MoveVectorToVector(std::move(*source_vector.vec_data_container_))) {
      LOG_ERROR("%s", "Move constructor failed to proceed");
      exit(1);
    }

    LOG_DEBUG("%s", "Move constructor successfully moved all elements");
  }

  T& operator [](uint32_t element_index) {

    LOG_DEBUG("%s", "Vector<T>::operator [] called");
    LOG_DEBUG("%s%d", "Index number requested: ", element_index);
    return vector_interface_handler_->GetElementByIndex(element_index);
  }

  void operator =(const Vector &source_vector) {

    LOG_DEBUG("%s", "Vector<T>::operator =(const Vector&) called");

    if (!vector_interface_handler_->CopyVectorToVector(*source_vector.vec_data_container_)) {
      LOG_ERROR("%s", "Copy of source Vector failed to proceed");
      exit(1);
    } else {
      LOG_DEBUG("%s", "Successfully copied all elements");
    }
  }

  bool operator ==(const Vector &source_vector) {

    LOG_DEBUG("%s", "Vector<T>::operator==(const Vector&) called");

    if (!vector_interface_handler_->CompareVectorToVector(*source_vector.vec_data_container_)) {
      LOG_DEBUG("%s", "Vectors are not equal");
      return false;
    }

    LOG_DEBUG("%s", "Vectors are equal");
    return true;
  }

  void Push_back(T new_element) {

    LOG_DEBUG("%s", "Vector<T>::Add(T&) called");

    if (vector_interface_handler_->AddNewElelemntToVector(new_element)) {
      LOG_DEBUG("%s", "Add element is successful");
    } else {
      LOG_ERROR("%s", "Add element is failed");
      exit(1);
    }
  }

  void Push_back(T* new_element) {

    LOG_DEBUG("%s", "Vector<T>::Add(T&) called");

    if (vector_interface_handler_->AddNewElelemntToVector(new_element)) {
      LOG_DEBUG("%s", "Add element is successful");
    } else {
      LOG_ERROR("%s", "Add element is failed");
      exit(1);
    }
  }

  T& GetElement(uint32_t element_index) {

    LOG_DEBUG("%s", "Vector<T>::GetElement(uint32_t) called");
    LOG_DEBUG("%s%d", "Index number requested: ", element_index);
    return vector_interface_handler_->GetElementByIndex(element_index);
  }

  bool IsEmpty() {

    LOG_DEBUG("%s", "Vector<T>::IsEmpty() called");
    return vector_interface_handler_->IsVectorEmpty();
  }

  uint32_t Size() {

    LOG_DEBUG("%s", "Vector<T>::Size() called");
    return vector_interface_handler_->GetVectorSize();
  }

  void Clear() {

    LOG_DEBUG("%s", "Vector<T>::Clear() called");
    if (!vector_interface_handler_->ClearVector()) {
      LOG_ERROR("%s", "Clear Vector failed");
      exit(1);
    }

    LOG_DEBUG("%s", "Clear Vector successful");
  }

  void Erase(uint32_t element_index) {

    LOG_DEBUG("%s", "Vector<T>::Erase(uint32_t) called");

    if ( !vector_interface_handler_->EraseElement(element_index)) {
      LOG_ERROR("%s%d%s", "Erase element: ", element_index, " failed");
      exit(1);
    }

    LOG_DEBUG("%s%d", "Erased element: ", element_index);
  }

  void Insert(T new_element) {

    LOG_DEBUG("%s", "Vector<T>::Insert(T) called");

    if (!vector_interface_handler_->InsertInHead(new_element)) {
      LOG_ERROR("%s", "Failed to insert a new element at head of Vector");
      exit(1);
    } else {
      LOG_DEBUG("%s", "Inserted a new element at head of Vector");
    }
  }

private:
  std::shared_ptr<VectorDataContainer<T>> vec_data_container_;
  std::unique_ptr<VectorInterfaceHandler<T>> vector_interface_handler_;
};

} /*namespace praise_tools*/

#endif /* SOURCE_VECTOR_H_ */
