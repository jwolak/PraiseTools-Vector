# PraiseTools - Vector
**Experimental vector implementation based om std::vector (but does not intend to replace it ever )**

**Defined in Vector.h header**
- template <class T> class Vector

**Constructors:**
- Vector()
- Vector(T)
- Vector(const Vector &)
- Vector(const Vector &&)

**Operators:**
- T& operator [index]
- operator =
- bool operator ==

**Element access:**
- T& GetElement(index)
- T& operator [index]

**Capacity:**
- bool IsEmpty()
- uint32_t Size()

**Modifiers:**
- Clear()
- Erase(index)
- Insert(T) (insert at the beginning)
- Push_back(T) (insert at the end)
- Push_back(T*) (insert at the end)

## Building for source

###### Build EquinoxLogger first (linked as static library):

```sh
cd EquinoxLogger/Build/
cmake CMakeLists.txt
make
```

###### Build PraiseTools-Vector:

```sh
cd PraiseTools-Vector/Build/
cmake CMakeLists.txt
make
```

###### For UnitTests:

```sh
cd UnitTests/Build
cmake CMakeLists.txt
make
```
## Examples:
```sh
#include "Vector.h"
#include <iostream>

int main() {

  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_ERROR);

  praise_tools::Vector<int> test_vector;
  test_vector.Push_back(21);
  test_vector.Insert(22);

  std::cout<<"test_vector[0]: "<<test_vector[0]<<std::endl;
  std::cout<<"test_vector[1]: "<<test_vector[1]<<std::endl;

  std::cout<<"test_vector.GetElement(0): "<<test_vector.GetElement(0)<<std::endl;
  std::cout<<"test_vector.GetElement(1): "<<test_vector.GetElement(1)<<std::endl;

  std::cout<<"test_vector.Size(): "<<test_vector.Size()<<std::endl;

  test_vector.Erase(1);
  std::cout<<"test_vector.Size() after erase: "<<test_vector.Size()<<std::endl;
  std::cout<<"test_vector.GetElement(0): "<<test_vector.GetElement(0)<<std::endl;

  return 0;
}
```

## License

BSD 3-Clause License
**Copyright (c) 2022, Janusz Wolak,**
All rights reserved.
