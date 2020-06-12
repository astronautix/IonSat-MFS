#ifndef RTOS_H_INC
#define RTOS_H_INC

#define OS FREERTOS

#if OS == FREERTOS
    #include "FreeRTOS/FreeRTOS.h"
#else
    #include "standard/standard.h"
#endif

#endif
