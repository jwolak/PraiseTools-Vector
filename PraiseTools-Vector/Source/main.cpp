/*
 * main.cpp
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


#include <iostream>
#include <cstdlib>


using namespace std;

template<class T> class vector {
  //T* tab[10]
  T **tab;
  int size;

 public:
  ~vector() {
    for (int i = 0; i < size; ++i) {
      //std::cout << "\nDeleted element: " << *tab[i] << std::endl;
      delete tab[i];
    }

    free(tab);
  }

  vector() : size { 0 } {
    tab = (T**)std::malloc(sizeof(T*));
    //tab = new T*[1];
  }

  vector(T new_element)
      :
      size { 0 } {
    //tab = new (T*);
    *tab = (T*)std::malloc(sizeof(T*));
    tab[size] = new (T);
    *tab[size] = new_element;
    ++size;
  }

  void Add(T new_element) {
/*    std::cout<<"Add size: "<<size<<std::endl;
    *tab = (T*)std::realloc(*tab, (size + 1)*sizeof(T*));
    tab[size] = new (T);
    *tab[size] = new_element;
    ++size;
    std::cout<<"size: "<<size<<std::endl;*/
    tab = (T**)std::realloc(tab, (size + 1)*sizeof(T*));
    tab[size] = new (T);
    *tab[size] = new_element;
    ++size;
  }

  void Print() {
    for (int i = 0; i < size; ++i) {
      std::cout << "\n" << *tab[i];
    }

    std::cout<<endl;
  }

};

int main() {
  cout << "Hello World\n";

  vector<int> vec/*(5)*/;
  vec.Add(6);

  for (int i = 0; i < 90; ++i) {
    vec.Add(i+1);
  }

  vec.Print();

  return 0;
}

