#ifndef UTIL_H
#define UTIL_h

#include <atomic>
#include <exception>
#include <map>
#include <memory>
#include <stdint.h>
#include <string>


template <typename Callable> void TraceThread(const char* name,  Callable func)
{
    //std::string s = strprintf("bitcoin-%s", name);
    //RenameThread(s.c_str());
    try
    {
      //  LogPrintf("%s thread start\n", name);
        func();
    //    LogPrintf("%s thread exit\n", name);
    }
   // catch (const boost::thread_interrupted&)
   // {
       // LogPrintf("%s thread interrupt\n", name);
   //     throw;
   // }
   // catch (const std::exception& e) {
       // PrintExceptionContinue(&e, name);
    //    throw;
   // }
    catch (...) {
       // PrintExceptionContinue(nullptr, name);
        throw;
    }
}



#endif
