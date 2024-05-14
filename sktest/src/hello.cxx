#include <hello.h>

namespace test
{
  std :: string HelloWorld (const std :: string & name)
  {
    std :: string msg = "Hello " + name;
    return msg;
  }

} // end namespace test
