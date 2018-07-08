#ifndef HPRIVEXPORT_H
#define HPRIVEXPORT_H

#if defined (_WIN32) || defined (WIN32)
    #if defined(PRIV_DLL)
        #define PRIV_EXPORT __declspec(dllexport)
    #else
        #define PRIV_EXPORT __declspec(dllimport)
    #endif
#else
    #define PRIV_EXPORT

#endif
#endif // HPRIVEXPORT_H

