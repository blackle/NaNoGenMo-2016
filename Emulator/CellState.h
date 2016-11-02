#ifndef __CELL_STATE__
#define __CELL_STATE__

typedef enum cellState {
  CELL_EMPTY,
  CELL_OOB, //out of bounds
  CELL_BLACK,
  CELL_WHITE,
} CellState;

#endif
