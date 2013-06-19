#include "utest_helper.hpp"

static void compiler_fill_image_3d_2(void)
{
  const size_t w = 512;
  const size_t h = 512;
  const size_t depth = 1;
  cl_image_format format;

  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_UNSIGNED_INT8;

  // Setup kernel and images
  OCL_CREATE_KERNEL("test_fill_image_3d_2");

  OCL_CREATE_IMAGE3D(buf[0], 0, &format, w, h, depth, 0, 0, NULL);

  // Run the kernel
  OCL_SET_ARG(0, sizeof(cl_mem), &buf[0]);
  globals[0] = w;
  globals[1] = h;
  locals[0] = 16;
  locals[1] = 16;
  OCL_NDRANGE(2);

  // Check result
  OCL_MAP_BUFFER(0);
  for (uint32_t k = 0; k < depth; k++)
    for (uint32_t j = 0; j < h; ++j)
      for (uint32_t i = 0; i < w; i++)
        OCL_ASSERT(((uint32_t*)buf_data[0])[k*w*h + j*w + i] == 0x78563412);
  OCL_UNMAP_BUFFER(0);
}

MAKE_UTEST_FROM_FUNCTION(compiler_fill_image_3d_2);
