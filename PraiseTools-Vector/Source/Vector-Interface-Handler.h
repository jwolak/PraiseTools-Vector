/*
 * Vector-Interface-Handler.h
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

#ifndef SOURCE_VECTOR_INTERFACE_HANDLER_H_
#define SOURCE_VECTOR_INTERFACE_HANDLER_H_

#include "Vector-Data-Container.h"

#include <memory>

#include "Logger.h"

namespace praise_tools {

template<class T>
class VectorInterfaceHandler {
 public:
  VectorInterfaceHandler(std::shared_ptr<VectorDataContainer<T>> vec_data_container)
      :
      vector_data_container_ { vec_data_container } {
  }

  bool InitVectorObj() {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::InitVectorObj()");

    if (vector_data_container_ == nullptr) {
      LOG_ERROR("%s", "vector_data_container_ not initialized");
      return false;
    } else {
      LOG_DEBUG("%s", "vector_data_container_ is initialized");
    }

    vector_data_container_->vector_data = (T**) std::malloc(sizeof(T*));
    vector_data_container_->vector_data_size = 0;

    LOG_DEBUG("%s", "Vector initialized successfully");
    return true;
  }

  bool DisposeOfVectorObj() {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::DisposeOfVectorObj()");

    if (vector_data_container_->vector_data != nullptr) {
      LOG_DEBUG("%s", "vector_data_container_->vector_data is not nullptr");
      if (vector_data_container_->vector_data_size > 0) {
        LOG_DEBUG("%s%d", "vector_data_container_->vector_data_size: ", vector_data_container_->vector_data_size);
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

    LOG_DEBUG("%s", "vector_data_container_->vector_data_size set to zero");
    vector_data_container_->vector_data_size = 0;

    return true;
  }

  bool AddNewElelemntToVector(T new_element) {

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

  bool AddNewElelemntToVector(T* new_element) {

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

    *vector_data_container_->vector_data[vector_data_container_->vector_data_size] = *new_element;

    ++vector_data_container_->vector_data_size;
    LOG_DEBUG("%s%d", "New Vector element added successfully. Vector size is: ", vector_data_container_->vector_data_size);
    return true;
  }

  bool CopyVectorToVector(const praise_tools::VectorDataContainer<T> &source_vector_data_container) {

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

  bool MoveVectorToVector(VectorDataContainer<T> &&source_vector_data_container) {

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

  T& GetElementByIndex(uint32_t element_index) {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::GetElementByIndex");
    LOG_DEBUG("%s%d", "Index number: ", element_index);

    if (element_index > vector_data_container_->vector_data_size) {
      LOG_ERROR("%s%d%s", "Provided index:", element_index, " is out of Vector range");
      exit(1);
    }

    LOG_DEBUG("%s%d%s", "Element with index:", element_index, " found and returned");
    return *vector_data_container_->vector_data[element_index];
  }

  bool CompareVectorToVector(const VectorDataContainer<T> &source_vector_data_container) {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::CompareVectorToVector");

    LOG_DEBUG("%s%d", "vector_data_container_->vector_data_size: ", vector_data_container_->vector_data_size);
    LOG_DEBUG("%s%d", "source_vector_data_container->vector_data_size: ", source_vector_data_container.vector_data_size);

    if (vector_data_container_->vector_data_size != source_vector_data_container.vector_data_size) {
      LOG_DEBUG("%s", "Compared Vectors size is different");
      return false;
    }

    for (int i = 0; i < vector_data_container_->vector_data_size; ++i) {
      LOG_DEBUG("%s%d%s%d%s", "Checks if vector_data_container_->vector_data[", i, "] is equal to source_vector_data_container.vector_data[", i, "]");
      if (*vector_data_container_->vector_data[i] != *source_vector_data_container.vector_data[i]) {
        LOG_DEBUG("%s", "Compared Vectors are not equal");
        return false;
      }
    }

    LOG_DEBUG("%s", "Compared Vectors are equal");
    return true;
  }

  bool IsVectorEmpty() {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::IsVectorEmpty");

    return vector_data_container_->vector_data_size == 0;
  }

  uint32_t GetVectorSize() {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::GetVectorSize");
    LOG_DEBUG("%s%d", "Vector size is: ", vector_data_container_->vector_data_size);
    return vector_data_container_->vector_data_size;
  }

  bool ClearVector() {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::ClearVector");

    int i = 0;

    if (vector_data_container_->vector_data != nullptr) {
      LOG_DEBUG("%s", "vector_data_container_->vector_data is not nullptr");
      if (vector_data_container_->vector_data_size > 0) {
        LOG_DEBUG("%s%d", "vector_data_container_->vector_data_size: ", vector_data_container_->vector_data_size);
        for (i = 0; i < vector_data_container_->vector_data_size; ++i) {
          delete vector_data_container_->vector_data[i];
          LOG_DEBUG("%s%d%s", "vector_data_container_->vector_data[", i, "] deleted");
        }
      } else {
        LOG_DEBUG("%s", "ClearVector(): Vector has no elements added");
      }

    } else {
      LOG_DEBUG("%s", "ClearVector(): Vector object has not been initialized");
      return false;
    }

    if (vector_data_container_->vector_data_size == i) {
      LOG_DEBUG("%s", "Vector cleared");
      LOG_DEBUG("%d%s", i, " element(s) removed");
      vector_data_container_->vector_data_size = 0;
      LOG_DEBUG("%s", "Vector size reset to zero");
      return true;
    }
    return false;
  }

  bool EraseElement(uint32_t element_index) {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::EraseElement(uint32_t)");

    LOG_DEBUG("%s%d", "Index of element to be erased: ", element_index);
    LOG_DEBUG("%s%d%s", "Element placed in cell: vector_data_container_->vector_data[", element_index- 1, "] to be erased");

    uint32_t number_of_shifts = 0;

    if (vector_data_container_->vector_data != nullptr) {

      LOG_DEBUG("%s", "Starts to shifting elements in cells:");
      for (int i = element_index - 1; i < vector_data_container_->vector_data_size; ++i) {
        LOG_DEBUG("%s%d%s%d%s", "vector_data_container_->vector_data[", i + 1, "] shifted to new place vector_data_container_->vector_data[",  i, "]");
        vector_data_container_->vector_data[i] = std::move(vector_data_container_->vector_data[i + 1]);
        ++number_of_shifts;
      }

      LOG_DEBUG("%s%d", "Number of cells shifted: ", number_of_shifts);
      --vector_data_container_->vector_data_size;
      LOG_DEBUG("%s%d", "Size of o Vector after element was erased: ", vector_data_container_->vector_data_size);

    } else {
      LOG_DEBUG("%s", "EraseElement(): Vector object has not been initialized");
      return false;
    }

    LOG_DEBUG("%d%s", element_index, " element has been erased");
    return true;
  }

  bool InsertInHead(T new_element) {

    LOG_DEBUG("%s", "VectorInterfaceHandler<T>::InsertInHead(T)");

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

    ++vector_data_container_->vector_data_size;

    uint32_t number_of_shifts = 0;
    for (int i = vector_data_container_->vector_data_size - 1; i > 0; --i) {
      LOG_DEBUG("%s%d%s%d%s", "Shifts data from cell vector_data_container_->vector_data[", i - 1, "] to vector_data_container_->vector_data[", i, "]");
      *vector_data_container_->vector_data[i] = *vector_data_container_->vector_data[i - 1];
      ++number_of_shifts;
    }

    *vector_data_container_->vector_data[0] = new_element;

    LOG_DEBUG("%s%d", "New element at the beginning of Vector added successfully. Vector size is: ", vector_data_container_->vector_data_size);
    LOG_DEBUG("%s%d", "Number of shifted elements is: ", number_of_shifts);
    return true;
  }

 private:
  std::shared_ptr<VectorDataContainer<T>> vector_data_container_;
};

} /*namespace praise_tools */

#endif /* SOURCE_VECTOR_INTERFACE_HANDLER_H_ */
