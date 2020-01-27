#pragma once
#include "Texture.h"
#include "Gem.h"
#include "GemEmpty.h"

class Board
{
public:
    Board();
    virtual ~Board();
    void init();
    bool input(SDL_Event* e);
    void process(float delta_time);
    void render();

    void swap_gem(Gem* g1, int i, int j);
    void select_gem(Gem* gem);

protected:

private:
    Texture* background;

    static int const LINES = 8;
    static int const COLLUMNS = 8;
    int const margin_x = 232;
    int const margin_y = 104;
    Texture* gem1;Texture* gem2;Texture* gem3;Texture* gem4;Texture* gem5;

    enum {
        CREATION,
        MOVING,
        DESTROYING,
        ANIMATING,
        CHECK_INPUT
    };
    int state = CREATION;

    /*struct {
        int i = 0;
        int j = 0;
        bool visited = false;
        Gem* gem;
    } board[LINES][COLLUMNS];*/
    Gem* board[LINES][COLLUMNS];
    Gem* selected_gem = NULL;
    Gem* last_swaped[2] = { NULL, NULL };
    Gem* swaped_gem_1 = NULL;
    Gem* swaped_gem_2 = NULL;
    GemEmpty* null_gem = NULL;
    void swap_gem(Gem* g1, Gem* g2);
    bool check_matchs();
    Gem* generate_gem(int i, int j);
    void print_board();
    void destroy_matches();
    bool is_placing = false;
    bool check = false;
    bool matches = false;
};

