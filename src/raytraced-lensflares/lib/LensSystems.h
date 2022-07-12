
#ifndef RR_LENSFLARES_SRC_LENSES_H_
#define RR_LENSFLARES_SRC_LENSES_H_

#include "LensSystem.h"

std::vector<LensSystem> getAvailableLensSystems() {
  return {
      {"# single bi-convex lens, Ø1, N-BK7, FL 50mm",
       {
           {50.6, 5.2, 1.517, 12.7},
           {-50.6, 48.2, 1, 12.7},
       }},
      {"# Brendel Tessar, USP 2854889, 100mm F/2.8",
       {
           {-115.33, 2.1, 1.5486, 19.2},
           {306.84, 4.16, 1, 19.2},
           {0, 4.0, 0, 15.0},
           {-59.06, 1.87, 1.6398, 17.3},
           {40.93, 10.64, 1, 17.3},
           {183.92, 7.05, 1.6910, 16.5},
           {-48.91, 79.831, 1, 16.5},
       }},
      {"# CANON, US Patent 5537259, F/2.8, 70-200mm (135)",
       {
           {118.63, 0.42, 1, 38.0},      {128.135, 8.68, 1.497, 38.0},
           {-263.46, 0.1, 1, 38.0},      {79.501, 5.72, 1.497, 35.0},
           {203.191, 26.15, 1, 35.0},    {54.391, 2.2, 1.847, 28.0},
           {45.859, 1.13, 1, 28.0},      {51.927, 8.55, 1.487, 28.0},
           {5099.30, 12.89, 1, 28.0},    {-488.6, 1.4, 1.804, 18.0},
           {35.390, 5.88, 1, 18.0},      {-78.125, 1.4, 1.487, 18.0},
           {38.137, 4.97, 1.847, 18.0},  {417.478, 2.65, 1, 18.0},
           {-66.802, 1.4, 1.729, 18.0},  {-3363.0, 15.72, 1, 18.0},
           {247.12, 3.49, 1.697, 19.0},  {-99.902, 0.15, 1, 19.0},
           {-189.99, 4.77, 1.497, 19.0}, {-40.553, 1.45, 1.834, 19.0},
           {-76.277, 0.69, 1, 19.0},     {58.421, 3.53, 1.804, 21.0},
           {133.262, 3, 1, 21.0},        {0, 0.24, 0, 21.0},
           {34.132, 6.35, 1.497, 21.0},  {2256.763, 3.72, 1.620, 21.0},
           {31.519, 28.17, 1, 21.0},     {132.947, 5.9, 1.517, 21.0},
           {-77.546, 13.94, 1, 21.0},    {-39.485, 1.8, 1.834, 21.0},
           {-95.683, 0.15, 1, 21.0},     {147.644, 3.62, 1.743, 21.0},
           {-205.76, 54.5, 1, 21.0},
       }},
      {"# CANON, US Patent 5537259, F/2.8, 70-200mm (200)",
       {
           {118.63, 0.42, 1, 38.0},      {128.135, 8.68, 1.497, 38.0},
           {-263.46, 0.1, 1, 38.0},      {79.501, 5.72, 1.497, 35.0},
           {203.191, 32.85, 1, 35.0},    {54.391, 2.2, 1.847, 28.0},
           {45.859, 1.13, 1, 28.0},      {51.927, 8.55, 1.487, 28.0},
           {5099.30, 17.23, 1, 28.0},    {-488.6, 1.4, 1.804, 18.0},
           {35.390, 5.88, 1, 18.0},      {-78.125, 1.4, 1.487, 18.0},
           {38.137, 4.97, 1.847, 18.0},  {417.478, 2.65, 1, 18.0},
           {-66.802, 1.4, 1.729, 18.0},  {-3363.0, 1.32, 1, 18.0},
           {247.12, 3.49, 1.697, 19.0},  {-99.902, 0.15, 1, 19.0},
           {-189.99, 4.77, 1.497, 19.0}, {-40.553, 1.45, 1.834, 19.0},
           {-76.277, 4.05, 1, 19.0},     {58.421, 3.53, 1.804, 21.0},
           {133.262, 3, 1, 21.0},        {0, 0.24, 0, 21.0},
           {34.132, 6.35, 1.497, 21.0},  {2256.763, 3.72, 1.620, 21.0},
           {31.519, 28.17, 1, 21.0},     {132.947, 5.9, 1.517, 21.0},
           {-77.546, 13.94, 1, 21.0},    {-39.485, 1.8, 1.834, 21.0},
           {-95.683, 0.15, 1, 21.0},     {147.644, 3.62, 1.743, 21.0},
           {-205.76, 54.5, 1, 21.0},
       }},
      {"# CANON, US Patent 5537259, F/2.8, 70-200mm (70)",
       {
           {118.63, 0.42, 1, 38.0},      {128.135, 8.68, 1.497, 38.0},
           {-263.46, 0.1, 1, 38.0},      {79.501, 5.72, 1.497, 35.0},
           {203.191, 8.78, 1, 35.0},     {54.391, 2.2, 1.847, 28.0},
           {45.859, 1.13, 1, 28.0},      {51.927, 8.55, 1.487, 28.0},
           {5099.30, 1.64, 1, 28.0},     {-488.6, 1.4, 1.804, 18.0},
           {35.390, 5.88, 1, 18.0},      {-78.125, 1.4, 1.487, 18.0},
           {38.137, 4.97, 1.847, 18.0},  {417.478, 2.65, 1, 18.0},
           {-66.802, 1.4, 1.729, 18.0},  {-3363.0, 30.32, 1, 18.0},
           {247.12, 3.49, 1.697, 19.0},  {-99.902, 0.15, 1, 19.0},
           {-189.99, 4.77, 1.497, 19.0}, {-40.553, 1.45, 1.834, 19.0},
           {-76.277, 14.7, 1, 19.0},     {58.421, 3.53, 1.804, 21.0},
           {133.262, 3, 1, 21.0},        {0, 0.24, 0, 21.0},
           {34.132, 6.35, 1.497, 21.0},  {2256.763, 3.72, 1.620, 21.0},
           {31.519, 28.17, 1, 21.0},     {132.947, 5.9, 1.517, 21.0},
           {-77.546, 13.94, 1, 21.0},    {-39.485, 1.8, 1.834, 21.0},
           {-95.683, 0.15, 1, 21.0},     {147.644, 3.62, 1.743, 21.0},
           {-205.76, 54.5, 1, 21.0},
       }},
      {"# Angenieux, US Patent 2701982; f/1.1, 100mm",
       {
           {559.28, 0.23, 1, 54.0},
           {100.12, 11.45, 1.67, 51.0},
           {213.54, 0.23, 1, 51.0},
           {58.04, 22.95, 1.691, 41.0},
           {2551, 2.58, 1.673, 41.0},
           {32.39, 15.66, 1, 27.0},
           {0, 15.00, 0, 25.5},
           {-40.42, 2.74, 1.699, 25.0},
           {192.98, 27.92, 1.62, 36.0},
           {-55.53, 0.23, 1, 36.0},
           {192.98, 7.98, 1.691, 35.0},
           {-225.28, 0.23, 1, 35.0},
           {175.1, 8.48, 1.691, 35.0},
           {-203.54, 55.742, 1, 35.0},
       }},
      {"# US patent 3376090",
       {
           {83.45, 0.14, 1, 20.0},
           {29.71, 6.29, 1.7506, 15.0},
           {20.74, 12.03, 1, 15.0},
           {0, 12.03, 0, 12.0},
           {-22.06, 1.43, 1.7200, 15.0},
           {72.28, 9.06, 1.7200, 15.0},
           {-30.86, 0.14, 1, 15.0},
           {-331.43, 6.03, 1.7506, 20.0},
           {-59.45, 71.0, 1, 20.0},
       }},
      {"# double gauss f/2.5, Lens Design, Milton Laikin, 1992, Page 75",
       {
           {351.08642, 0.5842, 1, 40.64},
           {49.8475, 15.367, 1.6204, 32.512},
           {-562.42204, 7.1882, 1.5814, 32.512},
           {32.47898, 9.652, 1, 19.05},
           {0, 12.4714, 0, 16.002},
           {-43.91914, 5.1054, 1.5814, 20.32},
           {69.19722, 17.0688, 1.6177, 29.972},
           {-58.3057, 7.2644, 1, 29.972},
           {166.9542, 10.0076, 1.6204, 38.1},
           {-225.93554, 70.6628, 1, 38.1},
       }},
      {"# double gauss, Modern Lens Design, Warren J. Smith, 1992, Page 312",
       {
           {169.66, 0.24, 1, 50.4},
           {38.55, 8.05, 1.67, 46.0},
           {81.54, 6.55, 1.699, 46.0},
           {25.5, 11.41, 1, 36.0},
           {0, 9, 0, 34.2},
           {-28.99, 2.36, 1.603, 34.0},
           {81.54, 12.13, 1.658, 40.0},
           {-40.77, 0.38, 1, 40.0},
           {874.13, 6.44, 1.717, 40.0},
           {-79.46, 72.228, 1, 40.0},
       }},
      {"# fisheye 220 degree (shimizu)",
       {
           {52.5, 28.0, 1, 52.3},        {76.4, 3.8, 1.51680, 50.0},
           {31.521, 21.8, 1, 30.5},      {150.0, 3.0, 1.51680, 27.0},
           {17.1, 16.5, 1, 16.5},        {-60.0, 7.0, 1.62041, 16.5},
           {22.625, 0.6, 1, 16.5},       {23.9, 12.6, 1.72825, 16.5},
           {78.988, 22.7, 1, 16.5},      {10000, 1.8, 1.51823, 16.5},
           {10000, 5.1, 1, 16.5},        {278.333, 3.0, 1.64831, 16.5},
           {-185.42, 0.1, 1, 16.5},      {52.030, 7.0, 1.53375, 16.5},
           {-28.5, 2.0, 1.77250, 16.5},  {-77.0, 3.0, 1, 16.5},
           {0, 10.0, 0, 16.5},           {45.0, 8.0, 1.51823, 10.0},
           {-14.4, 0.6, 1.79631, 10.0},  {-34.5, 0.1, 1, 10.0},
           {-110.0, 1.0, 1.71736, 10.0}, {35.0, 3.5, 1.51680, 10.0},
           {-25.763, 39.8, 1, 10.0},
       }},
      {"# wide angle zoom lens, Inventor: Takayuki Itoh, US Patent 4196968, "
       "100-145mm",
       {
           {914.140, 0.410, 1, 82.0},
           {187.780, 4.880, 1.806, 75.0},
           {64.230, 30.880, 1, 52.0},
           {717.900, 5.280, 1.678, 50.5},
           {120.230, 18.810, 1, 50.5},
           {113.650, 12.190, 1.805, 42.0},
           {223.460, 59.24, 1, 42.0},
           {0, 4.880, 0, 26.9},
           {171.170, 28.320, 1.806, 35.0},
           {-565.340, 9.260, 1, 35.0},
           {83.770, 10.160, 1.808, 33.0},
           {262.120, 9.130, 1, 33.0},
           {-218.780, 15.930, 1.847, 32.0},
           {85.250, 7.310, 1, 32.0},
           {-839.850, 9.140, 1.516, 32.0},
           {-94.280, 0.410, 1, 32.0},
           {-3422.750, 9.430, 1.516, 32.8},
           {-115.670, 149.674, 1, 32.8},
       }},
      {"# wide angle zoom lens, Inventor: Takayuki Itoh, US Patent 4196968, "
       "100-145mm",
       {
           {914.140, 0.410, 1, 82.0},
           {187.780, 4.880, 1.806, 75.0},
           {64.230, 30.880, 1, 52.0},
           {717.900, 5.280, 1.678, 50.5},
           {120.230, 18.810, 1, 50.5},
           {113.650, 12.190, 1.805, 42.0},
           {223.460, 33.205, 1, 42.0},
           {0, 4.880, 0, 26.9},
           {171.170, 28.320, 1.806, 35.0},
           {-565.340, 9.260, 1, 35.0},
           {83.770, 10.160, 1.808, 33.0},
           {262.120, 9.130, 1, 33.0},
           {-218.780, 15.930, 1.847, 32.0},
           {85.250, 7.310, 1, 32.0},
           {-839.850, 9.140, 1.516, 32.0},
           {-94.280, 0.410, 1, 32.0},
           {-3422.750, 9.430, 1.516, 32.8},
           {-115.670, 149.674, 1, 32.8},
       }},
      {"# wide angle zoom lens, Inventor: Takayuki Itoh, US Patent 4196968, "
       "100-145mm",
       {
           {914.140, 0.410, 1, 82.0},
           {187.780, 4.880, 1.806, 75.0},
           {64.230, 30.880, 1, 52.0},
           {717.900, 5.280, 1.678, 50.5},
           {120.230, 18.810, 1, 50.5},
           {113.650, 12.190, 1.805, 42.0},
           {223.460, 7.21, 1, 42.0},
           {0, 4.880, 0, 26.9},
           {171.170, 28.320, 1.806, 35.0},
           {-565.340, 9.260, 1, 35.0},
           {83.770, 10.160, 1.808, 33.0},
           {262.120, 9.130, 1, 33.0},
           {-218.780, 15.930, 1.847, 32.0},
           {85.250, 7.310, 1, 32.0},
           {-839.850, 9.140, 1.516, 32.0},
           {-94.280, 0.410, 1, 32.0},
           {-3422.750, 9.430, 1.516, 32.8},
           {-115.670, 149.674, 1, 32.8},
       }},
      {"# achromatic double crown/flint (#NT32-921) edmund optics archomat, "
       "~129mm",
       {
           {-62.03, 4.20, 1.5, 24.0},
           {-1240.67, 5.00, 1, 24.0},
           {0, 105.00, 0, 20.0},
       }},
      {"# Nikon, PAT S.53-131852, F/2.8, 80-200mm (140)",
       {
           {-479.279, 0.357, 1, 32.2},
           {192.855, 6.286, 1.589, 31.0},
           {-134.999, 2.214, 1.805, 31.0},
           {-874.852, 25.27, 1, 30.5},
           {-285.712, 3.893, 1.755, 19.0},
           {-44.764, 1.036, 1.517, 19.0},
           {59.357, 5.357, 1, 19.0},
           {-45.071, 1.250, 1.589, 16.0},
           {166.174, 19.23, 1, 16.0},
           {164.284, 5.000, 1.658, 15.0},
           {-33.928, 1.036, 1.795, 15.0},
           {-85.047, 10.84, 1, 15.0},
           {30.464, 5.357, 1.670, 16.7},
           {162.202, 3.071, 1, 16.3},
           {-374.997, 1.786, 1.805, 15.2},
           {259.105, 17.857, 1, 14.5},
           {0, 18.000, 0, 9.4},
           {-17.214, 1.714, 1.713, 10.5},
           {-30.230, 0.286, 1, 11.5},
           {62.857, 3.071, 1.773, 12.6},
           {-466.815, 40.08, 1, 12.6},
       }},
      {"# Nikon, PAT S.53-131852, F/2.8, 80-200mm (200)",
       {
           {-479.279, 0.357, 1, 32.2},
           {192.855, 6.286, 1.589, 31.0},
           {-134.999, 2.214, 1.805, 31.0},
           {-874.852, 48.678, 1, 30.5},
           {-285.712, 3.893, 1.755, 19.0},
           {-44.764, 1.036, 1.517, 19.0},
           {59.357, 5.357, 1, 19.0},
           {-45.071, 1.250, 1.589, 16.0},
           {166.174, 1.536, 1, 16.0},
           {164.284, 5.000, 1.658, 15.0},
           {-33.928, 1.036, 1.795, 15.0},
           {-85.047, 5.133, 1, 15.0},
           {30.464, 5.357, 1.670, 16.7},
           {162.202, 3.071, 1, 16.3},
           {-374.997, 1.786, 1.805, 15.2},
           {259.105, 17.857, 1, 14.5},
           {0, 18.000, 0, 9.4},
           {-17.214, 1.714, 1.713, 10.5},
           {-30.230, 0.286, 1, 11.5},
           {62.857, 3.071, 1.773, 12.6},
           {-466.815, 40.08, 1, 12.6},
       }},
      {"# Nikon, PAT S.53-131852, F/2.8, 80-200mm (80)",
       {
           {-479.279, 0.357, 1, 32.2},
           {192.855, 6.286, 1.589, 31.0},
           {-134.999, 2.214, 1.805, 31.0},
           {-874.852, 1.86, 1, 30.5},
           {-285.712, 3.893, 1.755, 19.0},
           {-44.764, 1.036, 1.517, 19.0},
           {59.357, 5.357, 1, 19.0},
           {-45.071, 1.250, 1.589, 16.0},
           {166.174, 36.928, 1, 16.0},
           {164.284, 5.000, 1.658, 15.0},
           {-33.928, 1.036, 1.795, 15.0},
           {-85.047, 16.55, 1, 15.0},
           {30.464, 5.357, 1.670, 16.7},
           {162.202, 3.071, 1, 16.3},
           {-374.997, 1.786, 1.805, 15.2},
           {259.105, 17.857, 1, 14.5},
           {0, 18.000, 0, 9.4},
           {-17.214, 1.714, 1.713, 10.5},
           {-30.230, 0.286, 1, 11.5},
           {62.857, 3.071, 1.773, 12.6},
           {-466.815, 40.08, 1, 12.6},
       }},
      {"# petzval-type photographic objective US2500046A (1948), scale 50%",
       {
           {-56.79, 4.5, 1.617, 23.0},
           {0, 24.0, 1, 23.0},
           {0, 25.3, 0, 18.0},
           {119.91, 3.8, 1.649, 15.0},
           {40.87, 0.9, 1, 15.0},
           {46.87, 7.4, 1.697, 15.0},
           {-282.05, 56.5, 1, 15.0},
       }},
      {"# US Patent 4310222 wide angle",
       {
           {24.997, 12.41, 1, 20.0},
           {58.28, 5.02, 1.6031, 15.0},
           {46.009, 0.15, 1, 15.0},
           {33.022, 1.7, 1.6968, 15.0},
           {17.647, 5.39, 1, 15.0},
           {32.787, 1.3, 1.7725, 12.0},
           {17.218, 6.32, 1, 12.0},
           {266.96, 1.5, 1.6968, 10.0},
           {13.984, 12.08, 1.60342, 10.0},
           {-43.016, 2.2, 1, 10.0},
           {0, 1.8, 1.51633, 7.0},
           {0, 0.8, 1, 7.0},
           {74.564, 7.84, 1.51118, 7.0},
           {-14.201, 0.94, 1, 7.0},
           {-12.614, 0.9, 1.7725, 7.0},
           {-26.958, 1.0, 1, 7.0},
           {0, 0.7, 0, 8.0},
           {129.909, 2., 1.64769, 8.0},
           {12.278, 6.9, 1.69895, 8.0},
           {50.377, 0.83, 1, 8.0},
           {-80.749, 0.8, 1.84666, 8.5},
           {28.151, 4.4, 1.48749, 8.5},
           {-15.466, 0.15, 1, 8.5},
           {493.467, 2.85, 1.7725, 10.0},
           {-33.952, 35., 1, 10.0},
       }}};
}

#endif // RR_LENSFLARES_SRC_LENSES_H_
