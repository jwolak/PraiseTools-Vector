/*
 * Vector-Interface-Handler.cpp
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


#include "Vector-Interface-Handler.h"

#include <cstdlib>

#include "Logger.h"

template<class T>
bool praise_tools::VectorInterfaceHandler<T>::InitVectorObj() {

  LOG_DEBUG("%s","VectorInterfaceHandler<T>::InitVectorObj()");

  vector_data_container_->vector_data = (T**) std::malloc(sizeof(T*));
  vector_data_container_->vector_data_size = 0;

  LOG_DEBUG("%s", "Vector initialized successfully");
  return true;
}

template<class T>
bool praise_tools::VectorInterfaceHandler<T>::DisposeOfVectorObj() {

  LOG_DEBUG("%s", "VectorInterfaceHandler<T>::DisposeOfVectorObj()");

  if (vector_data_container_->vector_data != nullptr) {
    LOG_DEBUG("%s", "vector_data_container_->vector_data is not nullptr");
    if (vector_data_container_->vector_data_size > 0) {
      LOG_DEBUG("%s%d","vector_data_container_->vector_data_size: ", vector_data_container_->vector_data_size);
      for (int i = 0; i < vector_data_container_->vector_data_size; ++i) {
        delete vector_data_container_->vector_data[i];
        LOG_DEBUG("%s%d%s", "vector_data_container_->vector_data[", i, "] deleted");
      }
    } else {
      LOG_DEBUG("%s", "DisposeOfVectorObj(): Vector has no elements added");
    }

    LOG_DEBUG("%s", "Try to dispose of vector_data_container_->vector_data");
    free(vector_data_container_->vector_data);
    LOG_DEBUG("%s", "DisposeOfVectorObj(): vector_data_container_->vector_data has been disposed of");

  } else {
    LOG_DEBUG("%s", "DisposeOfVectorObj(): Vector object has not been initialized");
    return false;
  }

  LOG_DEBUG("%s", "vector_data_container_->vector_data_size set to zero" );
  vector_data_container_->vector_data_size = 0;

  return true;
}

template<class T>
bool praise_tools::VectorInterfaceHandler<T>::AddNewElelemntToVector(T new_element) {

  if (*vector_data_container_->vector_data == nullptr) {
    LOG_ERROR("%s", "Vector not initialized");
    return false;
  }

  vector_data_container_->vector_data = (T**) std::realloc(vector_data_container_->vector_data, (vector_data_container_->vector_data_size + 1) * sizeof(T*));

  if (vector_data_container_->vector_data == nullptr) {
    LOG_ERROR("%s%d", "Failed of **vector_data realloc to size: ", vector_data_container_->vector_data_size + 1);
    return false;
  }

  vector_data_container_->vector_data[vector_data_container_->vector_data_size] = new (T);

  if (vector_data_container_->vector_data[vector_data_container_->vector_data_size] == nullptr) {
    LOG_ERROR("%s", "New Vector element allocation is failed");
    return false;
  }

  *vector_data_container_->vector_data[vector_data_container_->vector_data_size] = new_element;

  ++vector_data_container_->vector_data_size;
  LOG_DEBUG("%s%d", "New Vector element added successfully. Vector size is: ", vector_data_container_->vector_data_size);
  return true;
}

template<class T>
bool praise_tools::VectorInterfaceHandler<T>::CopyVectorToVector(const praise_tools::VectorDataContainer<T> &source_vector_data_container) {

  LOG_DEBUG("%s", "VectorInterfaceHandler<T>::CopyVectorToVector");
  LOG_DEBUG("%s%d", "Number of Vector elements to be copied: ", source_vector_data_container.vector_data_size);

  for (int i = 0; i < source_vector_data_container.vector_data_size; ++i) {
    if (AddNewElelemntToVector(*source_vector_data_container.vector_data[i])) {
      LOG_DEBUG("%s%d", "Copied element no: ", i + 1);
      LOG_DEBUG("%s", "Copy Vector element is successful");
    } else {
      LOG_ERROR("%s", "Copy Vector element is is failed");
      return false;
    }
  }

  LOG_DEBUG("%s", "Copy vector to vector is successful");
  return true;
}

template<class T>
bool praise_tools::VectorInterfaceHandler<T>::MoveVectorToVector(VectorDataContainer<T> &&source_vector_data_container) {

  LOG_DEBUG("%s", "VectorInterfaceHandler<T>::MoveVectorToVector");
  LOG_DEBUG("%s%d", "Number of Vector elements to be moved: ", source_vector_data_container.vector_data_size);

  *vector_data_container_ = static_cast<praise_tools::VectorDataContainer<T>&&>(std::move(source_vector_data_container));
  if (vector_data_container_ == nullptr) {
    LOG_ERROR("%s", "Move of source_vector_data_container failed");
    return false;
  }

  LOG_DEBUG("%s", "Move vector to vector is successful");
  return true;
}

template<class T>
T& praise_tools::VectorInterfaceHandler<T>::GetElementByIndex(uint32_t element_index) {

  LOG_DEBUG("%s", "VectorInterfaceHandler<T>::GetElementByIndex");
  LOG_DEBUG("%s%d", "Index number: ", element_index);

  if (element_index > vector_data_container_->vector_data_size) {
    LOG_ERROR("%s%d%s", "Provided index:", element_index, " is out of Vector range");
    exit(1);
  }

  LOG_DEBUG("%s%d%s", "Element with index:", element_index, " found and returned");
  return *vector_data_container_->vector_data[element_index];
}
