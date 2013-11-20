//
//  gomo_board.h
//  Gomoku
//
//  Created by Nels Salminen on 11/20/13.
//  Copyright (c) 2013 Nels Salminen. All rights reserved.
//

#ifndef __Gomoku__gomo_board__
#define __Gomoku__gomo_board__

#include <iostream>

class gomo_board_cel {
public:
    char color;
    gomo_board_cel* neighbors[8];
    gomo_board_cel ();
};

class gomo_board {
private:
    gomo_board_cel* entrance;
    int height, width;
public:
    gomo_board ();
    gomo_board (int height, int width);
    ~gomo_board ();
    void print ();
};

#endif /* defined(__Gomoku__gomo_board__) */