///////////////////////////////////////////////////
//
// MIT License. Copyright (c) 2023 Rico Possienka
//
///////////////////////////////////////////////////

#pragma once

#include <stdio.h>
#include <raylib.h>

typedef struct ray_video_t {
  //doun't touch this!
  struct ray_video_thread_context_t * ctx;
  double time_in_s_till_next_frame;
  double frame_time_s;
  int video_state;

  //info data
  double worker_time;
  double update_time;
  double upload_time;
  double fps;
  int width;
  int height;
  int mipmaps;
  bool ok;

  Texture texture;
} ray_video_t;

#if defined(__cplusplus)
extern "C" {
#endif

// Keep in mind that ray_video keeps the file handle life and
// will close it on it's own when ray_video_destroy is called.
ray_video_t ray_video_open(const char * path);
ray_video_t ray_video_open_file_handle(FILE * file);
int ray_video_update(ray_video_t *, double deltatime_s);
void ray_video_destroy(ray_video_t *);

#if defined(__cplusplus)
}
#endif