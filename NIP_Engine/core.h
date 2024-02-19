#pragma once

// Application
#define NE_VERSION "v0.1"
#define NE_TARGET_TICKRATE 60
#define NE_TICKRATE_TIME (1000 / NE_TARGET_TICKRATE)
#define NE_DELTATIME (1.0 / NE_TARGET_TICKRATE)
// Logging
#define NE_LOG_INFO(...) fprintf(stdout, __VA_ARGS__)
#define NE_LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
// Constants
#define NE_PI 3.1415f