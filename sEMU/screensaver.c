#include <am.h>
#include <klib-macros.h>
#include <stdio.h>
#include <amtest.h>
#define FPS 30
static int K = 100;  //渐变步数

static inline uint32_t pixel(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) | (g << 8) | b;
}
static inline uint8_t R(uint32_t p) { return p >> 16; }
static inline uint8_t G(uint32_t p) { return p >> 8; }
static inline uint8_t B(uint32_t p) { return p; }

uint32_t color_group[]={0x000000, 0xff0000, 0x00ff00, 0x0000ff, 0xffff00, 0xff00ff, 0x00ffff, 0xffffff};

static uint32_t line_buf[400];
// 辅助函数：获取一个简单的随机数
// 利用系统运行的微秒数作为随机源
static uint32_t get_random() {
  return io_read(AM_TIMER_UPTIME).us;
}

void draw(uint32_t color) {
  int w = io_read(AM_GPU_CONFIG).width;
  int h = io_read(AM_GPU_CONFIG).height;
  assert((uint32_t)w <= LENGTH(line_buf));
  for(int i = 0; i<w; i++){
    line_buf[i] = color;
  }
  for(int y = 0; y < h; y++){
    io_write(AM_GPU_FBDRAW, 0, y, line_buf, w, 1, false);//颜色从下网上刷（y从0到h-1）
  }
  io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true);
}

// 按键检测
static bool has_kbd;

void ESC_Press(){
  has_kbd  = io_read(AM_INPUT_CONFIG).present;
  if (has_kbd) {
    while (1) {
      AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
      if(ev.keycode == AM_KEY_ESCAPE) halt(0); // 按下 ESC 键退出屏保
      else if (ev.keycode != AM_KEY_NONE && ev.keycode != AM_KEY_ESCAPE)
      {
        K = 50; // 按下其他任意键, 则加快一轮渐变的时间
      }
      else if (ev.keycode == AM_KEY_NONE) {
        K = 100; // 释放按键后, 渐变时间恢复
        break;
      }
      
    }
  }
  
}

void screensaver_test() {
  ioe_init();
  
  int color_num = sizeof(color_group) / sizeof(uint32_t);
  uint32_t curr_c = color_group[0];


  while (1) {
  // 【关键修改点】：随机选择下一个目标颜色
  // 使用当前时间对颜色数组长度取模
  int next_idx = get_random() % color_num;
  uint32_t next_c = color_group[next_idx];
    
  // 如果随机到的颜色和当前颜色一样，就再跳一个，防止画面卡住不动
  if (next_c == curr_c) {
    next_c = color_group[(next_idx + 1) % color_num];
  }
    
    
    // 拆分 RGB 分量
    int r0 = R(curr_c), g0 = G(curr_c), b0 = B(curr_c);
    int r1 = R(next_c), g1 = G(next_c), b1 = B(next_c);

    // 线性渐变循环
    for (int i = 0; i <= K; i++) {
      unsigned long next_frame_time = io_read(AM_TIMER_UPTIME).us + 1000000 / FPS;

      // 按照公式计算当前帧的颜色
      uint8_t ri = r0 + (r1 - r0) * i / K;
      uint8_t gi = g0 + (g1 - g0) * i / K;
      uint8_t bi = b0 + (b1 - b0) * i / K;
      
      draw(pixel(ri, gi, bi));
      ESC_Press(); // 每画一帧，检测 ESC 键是否被按下，退出屏保；如果按下其他任意键, 则加快一轮渐变的时间; 释放按键后, 渐变时间恢复
      // 等待直到下一帧时间，控制动画速度
      while (io_read(AM_TIMER_UPTIME).us < next_frame_time);
    }

    // 准备下一组颜色的渐变
    curr_c = next_c;
    next_idx = (next_idx + 1) % color_num;
    
    
  }
}