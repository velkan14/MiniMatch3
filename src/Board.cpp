#include "Board.h"
#include <iostream>
#include <memory>
#include <array>
#include "Constants.h"
#include "Game.h"

Board::Board(Score * s)
{
    background = new Texture();
    gem1 = new Texture();
    gem2 = new Texture();
    gem3 = new Texture();
    gem4 = new Texture();
    gem5 = new Texture();
    score = s;
    state = Board::CREATION;
}

Board::~Board()
{
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            delete board[i][j];
        }
    }
    delete null_gem ;
    delete score;
}

void Board::init() {
    background = Game::texture_loader->load_texture("assets/Backdrop13.jpg");
    gem1 = Game::texture_loader->load_texture("assets/Color-1.png");
    gem2 = Game::texture_loader->load_texture("assets/Color-2.png");
    gem3 = Game::texture_loader->load_texture("assets/Color-3.png");
    gem4 = Game::texture_loader->load_texture("assets/Color-4.png");
    gem5 = Game::texture_loader->load_texture("assets/Color-5.png");

    //Set board empty
    null_gem = new GemEmpty(this);
    score->init();

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            board[i][j] = null_gem;
        }
    }
}

Gem* Board::generate_gem(int i, int j) {
    Gem* new_gem = new Gem(this);
    new_gem->set_position(MARGIN_X + i * 70.0f, j * 70.0f - MARGIN_Y * 4.0f);
    int r = rand() % 5;
    new_gem->set_type(static_cast<gem_type>(r + 1));
    new_gem->i = i;
    new_gem->j = j;
    new_gem->set_target(vec2(MARGIN_X + i * 70.0f, j * 70.0f + MARGIN_Y));
    switch (r + 1) {
    case BLACK:
        new_gem->set_texture(gem1);
        break;
    case WHITE:
        new_gem->set_texture(gem2);
        break;
    case PINK:
        new_gem->set_texture(gem3);
        break;
    case BLUE:
        new_gem->set_texture(gem4);
        break;
    case ORANGE:
        new_gem->set_texture(gem5);
        break;
    }
    return new_gem;
}


void Board::swap_gem(Gem* g1, Gem* g2) {
    board[g1->i][g1->j] = g2;
    board[g2->i][g2->j] = g1;
    int i2 = g2->i;
    int j2 = g2->j;
    g2->i = g1->i;
    g2->j = g1->j;
    g1->i = i2;
    g1->j = j2;
    g1->set_target(vec2(MARGIN_X + g1->i * 70.0f, g1->j * 70.0f + MARGIN_Y));
    g2->set_target(vec2(MARGIN_X + g2->i * 70.0f, g2->j * 70.0f + MARGIN_Y));
    last_swaped[0] = g1;
    last_swaped[1] = g2;
    g1->set_swapping();
    g2->set_swapping();
    state = MOVING;
}

void Board::swap_gem(Gem* g1, int i, int j) {
    if (i >= 0 && i < LINES && j >= 0 && j < COLLUMNS) {
        swap_gem(g1, board[i][j]);
    }
}

void Board::select_gem(Gem* gem)
{
    if (selected_gem == NULL) {
        selected_gem = gem;
        gem->selected = true;
    }
    else {
        if (selected_gem == gem) {
            selected_gem = NULL;
            gem->selected = false;
        }
        else if (selected_gem->is_neighbor(gem)) {
            swap_gem(selected_gem, gem);
            gem->selected = false;
            selected_gem->selected = false;
            selected_gem = NULL;
            state = MOVING;
        }
        else {
            gem->selected = true;
            selected_gem->selected = false;
            selected_gem = gem;
        }
    }
}

bool Board::input(SDL_Event* e) {
    bool processed = false;
    if (state != Board::CHECK_INPUT && (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)) {
        return true;
    }
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if (board[i][j]->input(e)) {
                processed = true;
                break;
            }
        }
        if (processed) {
            break;
        }
    }
    return processed;
}

void Board::print_board() {
    for (int i = 0; i < LINES; i++) {
        std::cout << "|";
        for (int j = 0; j < COLLUMNS; j++) {
            std::cout << " " << board[i][j]->get_type() << " |";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::destroy_matches() {
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if (board[i][j]->match > 0) {
                delete board[i][j];
                board[i][j] = null_gem;
            }
        }
    }
}

void Board::process(float delta_time) {
    bool is_placing = false;
    switch (state) {
    case Board::CREATION:
        //Create gems if it is empty
        for (int i = 0; i < LINES; i++) {
            for (int j = COLLUMNS - 1; j >= 0; j--) {
                if (board[i][j]->get_type() == EMPTY) {
                    Gem* empty_gem = board[i][j];
                    for (int n = j - 1; n >= -1; n--) {
                        if (n < 0 || (board[i][n]->get_type() == EMPTY && n == 0)) {
                            board[i][j] = generate_gem(i, j);
                            break;
                        }
                        else if (board[i][n]->get_type() != EMPTY) {
                            Gem* replace_gem = board[i][n];
                            replace_gem->i = i;
                            replace_gem->j = j;
                            replace_gem->set_target(vec2(MARGIN_X + i * 70.0f, j * 70.0f + MARGIN_Y));
                            board[i][n] = empty_gem;
                            board[i][j] = replace_gem;
                            break;
                        }
                    }

                }

            }
        }
        state = Board::MOVING;
        break;
    case Board::MOVING:
        //Move gems
        is_placing = false;
        for (int i = 0; i < LINES; i++) {
            for (int j = 0; j < COLLUMNS; j++) {
                if (board[i][j] != NULL) {
                    board[i][j]->process(delta_time);
                    if (board[i][j]->is_placing) {
                        is_placing = true;
                    }
                }
            }
        }
        if (!is_placing) state = DESTROYING;
        break;
    case Board::ANIMATING:
        check = false;

        for (int i = 0; i < LINES; i++) {
            for (int j = 0; j < COLLUMNS; j++) {
                board[i][j]->process(delta_time);
                if (board[i][j]->animating) {
                    check = true;
                }
            }
        }
        if (!check) {
            destroy_matches();
            state = Board::CREATION;
        }
        break;
    case Board::DESTROYING:
        //Check Matchs and explode
        matches = check_matchs();

        if (matches) {
            for (int i = 0; i < LINES; i++) {
                for (int j = 0; j < COLLUMNS; j++) {
                    if (board[i][j] != NULL) {
                        if (board[i][j]->match > 0) {
                            board[i][j]->destroy();
                            score->add_gem_destroyed(board[i][j]->get_type(), 1);
                        }
                    }
                }
            }
            last_swaped[0] = NULL;
            last_swaped[1] = NULL;
            state = Board::ANIMATING;
        }
        else {
            if (last_swaped[0] != NULL && last_swaped[1] != NULL) {
                swap_gem(last_swaped[0], last_swaped[1]);
                score->miss_swap();
                last_swaped[0] = NULL;
                last_swaped[1] = NULL;
                state = Board::MOVING;
            }
            else {
                if (score->passed()) is_completed = true;
                state = Board::CHECK_INPUT;

            }
        }
        break;
    case Board::CHECK_INPUT:
        //Check input
        for (int i = 0; i < LINES; i++) {
            for (int j = 0; j < COLLUMNS; j++) {
                board[i][j]->process(delta_time);
            }
        }
        break;
    }    
}

void Board::render() {
    background->render(0, 0);
    Gem* top = NULL;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if (board[i][j]->is_dragging()) {
                top = board[i][j];
            }
            else
                board[i][j]->render();
        }
    }
    if (top != NULL) top->render();

    score->render();
}

bool Board::check_matchs() {
    bool there_are_matchs = false;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if ((i != 0 && i != LINES - 1) && board[i][j]->get_type() == board[i - 1][j]->get_type() && board[i][j]->get_type() == board[i + 1][j]->get_type()) {
                board[i][j]->match++;
                board[i + 1][j]->match++;
                board[i - 1][j]->match++;
                there_are_matchs = true;
            }
            if ((j != 0 && j != COLLUMNS - 1) && board[i][j]->get_type() == board[i][j - 1]->get_type() && board[i][j]->get_type() == board[i][j + 1]->get_type()) {
                board[i][j]->match++;
                board[i][j + 1]->match++;
                board[i][j - 1]->match++;
                there_are_matchs = true;
            }
        }
    }
    return there_are_matchs;
}