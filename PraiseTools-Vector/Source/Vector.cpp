/*
 * Vector.cpp
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

#include "Vector.h"
#include "Logger.h"

template<class T>
praise_tools::Vector<T>::~Vector() {

  LOG_DEBUG("%s", "Vector<T>::~Vector()");

  if (!vector_interface_handler_->DisposeOfVectorObj()) {
    LOG_ERROR("%s", "Dispose of Vector object failed!");
  }

  LOG_DEBUG("%s", "Dispose of Vector object successful");
}

template<class T>
praise_tools::Vector<T>::Vector()
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

template<class T>
praise_tools::Vector<T>::Vector(T &init_lelement)
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

template<class T>
praise_tools::Vector<T>::Vector(const Vector &source_vector)
    :
    vec_data_container_ { new VectorDataContainer<T> },
    vector_interface_handler_ { new VectorInterfaceHandler<T> { vec_data_container_ } } {

  LOG_DEBUG("%s", "Vector<T>::Vector(const Vector &)");

  if (vector_interface_handler_->InitVectorObj()) {
    LOG_DEBUG("%s", "Vector object initialization is successful");

    for (int i = 0; i < source_vector->vec_data_container_->vector_data_size; ++i) {
      if (vector_interface_handler_->AddNewElelemntToVector(*source_vector->vec_data_container_->vector_data[i])) {
        LOG_DEBUG("%s", "Copy Vector element is successful");
      } else {
        LOG_ERROR("%s", "Copy Vector element is is failed");
        exit(1);
      }
    }

  } else {
    LOG_ERROR("%s", "Vector object initialization is failed");
    exit(1);
  }
}

template<class T>
praise_tools::Vector<T>::Vector(const Vector &&source_vector) {

  LOG_DEBUG("%s", "Vector<T>::Vector(const Vector)");

  vec_data_container_ = std::move(source_vector->vec_data_container_);
  if (vec_data_container_ == nullptr) {
    LOG_ERROR("%s", "Move of vec_data_container_ failed");
    exit(1);
  }

  vector_interface_handler_ = std::move(source_vector->vector_interface_handler_);
  if (vector_interface_handler_ == nullptr) {
    LOG_ERROR("%s", "Move of vector_interface_handler_ failed");
    exit(1);
  }
}
