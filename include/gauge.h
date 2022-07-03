#include<stdio.h>

#ifndef _GAUGE_H_
#define _GAUGE_H_ 1

#define GAUGE_BUFFER_SIZE 50

#define Gauge_str(buffer, name, value) sprintf((buffer), "%s:%d|g", (name), (value))

#endif