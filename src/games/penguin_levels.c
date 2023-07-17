

#include "./common.h"
#include "./penguin_levels.h"

static char i, r;

const char half_levels[HALF_LEVEL_BYTES] = {
  0xff, 
  0x89, 
  0x2b, 
  0xff, 
  0x83, 
  0xff, 
  0x2b, 
  0xff, 
  0x81, 
  0xff, 
  0xff, 
  0xa9, 
  0xab, 
  0xef, 
  0x09, 
  0xff, 
  0x23, 
  0xef, 
  0xab, 
  0xfb, 
  0xff, 
  0xab, 
  0x03, 
  0xff, 
  0x81, 
  0xff, 
  0x03, 
  0xff, 
  0x81, 
  0xff, 
  0xef, 
  0xab, 
  0xab, 
  0xbb, 
  0x81, 
  0xef, 
  0xab, 
  0xab, 
  0xab, 
  0xbb, 
  0xff, 
  0x89, 
  0x2b, 
  0xff, 
  0x83, 
  0xff, 
  0xa9, 
  0xff, 
  0x03, 
  0xff, 
  0xfb, 
  0x2b, 
  0xab, 
  0xef, 
  0x23, 
  0xbf, 
  0x89, 
  0xef, 
  0xab, 
  0xbf, 
  0xff, 
  0x81, 
  0x81, 
  0xef, 
  0xab, 
  0xab, 
  0xab, 
  0xab, 
  0xab, 
  0xbb, 
  0xfb, 
  0xab, 
  0x8b, 
  0xef, 
  0x23, 
  0xf7, 
  0x81, 
  0xff, 
  0x03, 
  0xff, 
  0xff, 
  0x2b, 
  0x83, 
  0xef, 
  0x29, 
  0xff, 
  0x83, 
  0xff, 
  0x29, 
  0xff, 
  0xff, 
  0xab, 
  0x23, 
  0xff, 
  0x89, 
  0xff, 
  0x23, 
  0xff, 
  0x89, 
  0xff, 
  0xff, 
  0x89, 
  0xab, 
  0xff, 
  0x23, 
  0xab, 
  0xab, 
  0xff, 
  0x89, 
  0xbf, 
  0xff, 
  0x8b, 
  0xa1, 
  0xff, 
  0x0b, 
  0xff, 
  0xa1, 
  0xff, 
  0x0b, 
  0xff, 
  0xff, 
  0xab, 
  0x83, 
  0xef, 
  0x29, 
  0xff, 
  0x83, 
  0xff, 
  0x29, 
  0xff, 
  0xff, 
  0xab, 
  0x89, 
  0xff, 
  0x23, 
  0xff, 
  0x89, 
  0xff, 
  0x23, 
  0xff, 
  0xff, 
  0xab, 
  0x89, 
  0xff, 
  0xab, 
  0xab, 
  0x23, 
  0xff, 
  0xab, 
  0x8b, 
  0xff, 
  0x8b, 
  0x81, 
  0xff, 
  0x09, 
  0xef, 
  0xab, 
  0xab, 
  0xab, 
  0xbb, 
};

static const char left_half_order[16] = {0x0F,0x00,0x04,0x08,0x0C,0x01,0x05,0x09,0x0D,0x02,0x06,0x0A,0x0E,0x03,0x07,0x0B};
static const char right_half_order[16] = {0x01,0x05,0x09,0x0D,0x02,0x06,0x0A,0x0E,0x03,0x07,0x0B,0x0F,0x04,0x08,0x0C,0x00};

void load_half_level(char level_num, char side, char tilenum) {
    i = level_num * HALF_LEVEL_HEIGHT;
    for(r = 0; r < HALF_LEVEL_HEIGHT; ++r) {
        field[((r+MAZE_OFFSET_ROW) << 4) + 0 + side] = (half_levels[i] & 0b10000000) ? 0 : tilenum;
        field[((r+MAZE_OFFSET_ROW) << 4) + 1 + side] = (half_levels[i] & 0b01000000) ? 0 : tilenum;
        field[((r+MAZE_OFFSET_ROW) << 4) + 2 + side] = (half_levels[i] & 0b00100000) ? 0 : tilenum;
        field[((r+MAZE_OFFSET_ROW) << 4) + 3 + side] = (half_levels[i] & 0b00010000) ? 0 : tilenum;
        field[((r+MAZE_OFFSET_ROW) << 4) + 4 + side] = (half_levels[i] & 0b00001000) ? 0 : tilenum;
        field[((r+MAZE_OFFSET_ROW) << 4) + 5 + side] = (half_levels[i] & 0b00000100) ? 0 : tilenum;
        field[((r+MAZE_OFFSET_ROW) << 4) + 6 + side] = (half_levels[i] & 0b00000010) ? 0 : tilenum;
        i++;
    }
}

#define LEVEL_LEFT_SIDE 0
#define LEVEL_RIGHT_SIDE 8

void load_level_num() {
    load_half_level(left_half_order[level_num & 15], LEVEL_LEFT_SIDE, 11);
    load_half_level(0xF & (((level_num) & 0xF) + ((level_num) >> 4)), LEVEL_RIGHT_SIDE, 11);
}