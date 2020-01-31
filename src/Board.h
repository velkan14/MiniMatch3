#pragma once
#include "Texture.h"
#include "Gem.h"
#include "GemEmpty.h"
#include "Score.h"
#include "Screen.h"

class Board : public Screen
{
public:
    Board(Score* s);
    virtual ~Board();
    void init() override;
    bool input(SDL_Event* e) override;
    void process(float delta_time) override;
    void render() override;

    void swap_gem(Gem* g1, int i, int j);
    void select_gem(Gem* gem);

protected:

private:
    enum {
        CREATION,
        MOVING,
        DESTROYING,
        ANIMATING,
        CHECK_INPUT
    } state;

    static int const LINES = 8;
    static int const COLLUMNS = 8;

    Texture* background = NULL;
    Texture* gem1 = NULL;
    Texture* gem2 = NULL;
    Texture* gem3 = NULL;
    Texture* gem4 = NULL;
    Texture* gem5 = NULL;

    Gem* board[LINES][COLLUMNS];
    GemEmpty* null_gem = NULL;
    Gem* selected_gem = NULL;
    Gem* last_swaped[2] = { NULL, NULL };
    
    bool is_placing = false;
    bool check = false;
    bool matches = false;

    void swap_gem(Gem* g1, Gem* g2);
    Gem* generate_gem(int i, int j);
    bool check_matchs();
    void print_board();
    void destroy_matches();

    Score* score = NULL;
};

