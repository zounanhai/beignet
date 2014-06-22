kernel void compiler_smoothstep(global float *src1, global float *src2, global float *src3, global float *dst) {
  int i = get_global_id(0);
  dst[i] = smoothstep(src1[i], src2[i], src3[i]);
}
