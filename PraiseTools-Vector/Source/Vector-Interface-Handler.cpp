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

  vector_data_container_->vector_data = (T**) std::malloc(sizeof(T*));
  vector_data_container_->vector_data_size = 0;

  return true;
}

template<class T>
bool praise_tools::VectorInterfaceHandler<T>::DisposeOfVectorObj() {

  if (vector_data_container_->vector_data != nullptr) {
    if (vector_data_container_->vector_data_size > 0) {
      for (int i = 0; i < vector_data_container_->vector_data_size; ++i) {
        delete vector_data_container_->vector_data[i];
      }
    } else {
      LOG_DEBUG("%s", "DisposeOfVectorObj(): Vector object is empty");
    }

    free(vector_data_container_->vector_data);
    LOG_DEBUG("%s", "DisposeOfVectorObj(): All Vector's objects have been disposed of");

  } else {
    LOG_DEBUG("%s", "DisposeOfVectorObj(): Vector object has not been created");
    return false;
  }

  return true;
}

template<class T>
bool praise_tools::VectorInterfaceHandler<T>::AddNewElelemntToVector(T &new_element) {

  if (*vector_data_container_->vector_data == nullptr) {
    LOG_ERROR("%s", "Vector not initialized");
    return false;
  }

  vector_data_container_->vector_data[vector_data_container_->vector_data_size] = new (T);

  if (vector_data_container_->vector_data[vector_data_container_->vector_data_size] == nullptr) {
    LOG_ERROR("%s", "New Vector element allocation is failed");
    return false;
  }

  *vector_data_container_->vector_data[vector_data_container_->vector_data_size] = new_element;

  ++vector_data_container_->vector_data_size;
  LOG_DEBUG("%s%d", "New Vector element added successfuly. Vector size is: ", vector_data_container_->vector_data_size);
  return true;
}