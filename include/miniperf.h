///////////////////////////////////////////////////
//
// MIT License. Copyright (c) 2023 Rico Possienka
//
///////////////////////////////////////////////////

#ifndef MINIPERF_H
#define MINIPERF_H

#include "miniwindows.h"

typedef struct performance_counter_t {
  double ticktime_seconds;           // time scaler of the performance counter
  double ticktime_miliseconds;       // time scaler of the performance counter
  double ticktime_nanoseconds;       // time scaler of the performance counter
  LARGE_INTEGER start_time;  // starting time
  LARGE_INTEGER end_time;    // ending time
} performance_counter_t;

inline void performance_counter_init(performance_counter_t * c) {
  // get the frequency of the performance counter
  LARGE_INTEGER frequency;
  QueryPerformanceFrequency(&frequency);
  c->ticktime_seconds     = 1.0 / frequency.QuadPart;
  c->ticktime_miliseconds = 1000.0 / frequency.QuadPart;
  c->ticktime_nanoseconds = 1000000.0 / frequency.QuadPart;

  // get the starting time
  QueryPerformanceCounter(&c->start_time);
  c->end_time = c->start_time;
}

inline void performance_counter_next(performance_counter_t * c) {
  // get the ending time
  QueryPerformanceCounter(&c->end_time);
}

inline double performance_counter_next_seconds(performance_counter_t * c) {
  performance_counter_next(c);
  return (c->end_time.QuadPart - c->start_time.QuadPart) * c->ticktime_seconds;
}

inline double performance_counter_next_miliseconds(performance_counter_t * c) {
  performance_counter_next(c);
  return (c->end_time.QuadPart - c->start_time.QuadPart) * c->ticktime_miliseconds;
}

inline double performance_counter_next_nanoseconds(performance_counter_t * c) {
  performance_counter_next(c);
  return (c->end_time.QuadPart - c->start_time.QuadPart) * c->ticktime_nanoseconds;
}

inline void performance_counter_reset(performance_counter_t * c) {
  performance_counter_next(c);
  c->start_time = c->end_time;
}

#endif