#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <stdio.h>
#include <string.h>

#ifdef DEBUG
    #define LOG_INFO(fmt, ...)  fprintf(stderr, "[INFO] %s:%d | " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define LOG_ERROR(fmt, ...) fprintf(stderr, "[ERR]  %s:%d | " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define LOG_MEM(ptr, sz)    fprintf(stderr, "[MEM]  %s:%d | ptr=%p size=%zu\n", __FILE__, __LINE__, (void*)(ptr), (size_t)(sz))
#else
    #define LOG_INFO(fmt, ...)  do {} while(0)
    #define LOG_ERROR(fmt, ...) do {} while(0)
    #define LOG_MEM(ptr, sz)    do {} while(0)
#endif

#endif