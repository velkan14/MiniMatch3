#include "Board.h"
#include <iostream>
#include <memory>
#include <array>

Board::Board()
{
    //Board
}

Board::~Board()
{
    //dtor
}

void Board::init() {
    //Load textures
    background = new Texture();
    if (!background->loadFromFile("assets/Backdrop13.jpg")) {
        std::cout << "Failed to load image Backdrop.png" << std::endl;
    }
    gem1 = new Texture();
    if (!gem1->loadFromFile("assets/Color-1.png")) {
        std::cout << "Failed to load image Color-1.png" << std::endl;
    }
    gem2 = new Texture();
    if (!gem2->loadFromFile("assets/Color-2.png")) {
        std::cout << "Failed to load image Color-1.png" << std::endl;
    }
    gem3 = new Texture();
    if (!gem3->loadFromFile("assets/Color-3.png")) {
        std::cout << "Failed to load image Color-1.png" << std::endl;
    }
    gem4 = new Texture();
    if (!gem4->loadFromFile("assets/Color-4.png")) {
        std::cout << "Failed to load image Color-1.png" << std::endl;
    }
    gem5 = new Texture();
    if (!gem5->loadFromFile("assets/Color-5.png")) {
        std::cout << "Failed to load image Color-1.png" << std::endl;
    }


    //Set board empty
    null_gem = new GemEmpty();

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            board[i][j] = null_gem;
        }
    }
}

Gem* Board::generate_gem(int i, int j) {
    Gem* new_gem = new Gem();
    new_gem->pos = vec2(margin_x + i * 70.0, j * 70.0 - margin_y * 4.0);
    int r = rand() % 5;
    new_gem->set_type(r + 1);
    new_gem->i = i;
    new_gem->j = j;
    switch (r) {
    case 0:
        new_gem->set_texture(gem1);
        break;
    case 1:
        new_gem->set_texture(gem2);
        break;
    case 2:
        new_gem->set_texture(gem3);
        break;
    case 3:
        new_gem->set_texture(gem4);
        break;
    case 4:
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
}

bool Board::input(SDL_Event* e) {
    bool processed = false;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if (board[i][j]->input(e)) {
                //std::cout << board[i][j]->i << ":" << board[i][j]->j << std::endl;
                processed = true;
                if (selected_gem != NULL) {
                    if (selected_gem == board[i][j]) {
                        selected_gem = NULL;
                    }
                    else {
                        selected_gem_2 = board[i][j];
                    }
                }
                else {
                    selected_gem = board[i][j];
                }
                break;
            }
        }
        if (processed) {
            break;
        }
    }
    return processed;
}

void Board::process(float delta_time) {
    bool is_placing = false;
    switch (state) {
    case CREATION:
        //Create gems if it is empty
        //std::cout << "Creating Gems" << std::endl;
        for (int i = 0; i < LINES; i++) {
            for (int j = COLLUMNS - 1; j >= 0; j--) {
                if (board[i][j]->get_type() == 0) {
                    Gem* empty_gem = board[i][j];
                    for (int n = j - 1; n >= -1; n--) {
                        if (n < 0 || (board[i][n]->get_type() == 0 && n == 0)) {
                            board[i][j] = generate_gem(i, j);
                            break;
                        }
                        else if (board[i][n]->get_type() != 0) {
                            Gem* replace_gem = board[i][n];
                            replace_gem->i = i;
                            replace_gem->j = j;
                            board[i][n] = empty_gem;
                            board[i][j] = replace_gem;
                            break;
                        }
                    }

                }

            }
        }
        state = MOVING;
        break;
    case MOVING:
        //Move gems
        //std::cout << "Moving Gems" << std::endl;
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
    case DESTROYING:
        //std::cout << "DESTROYING" << std::endl;
        //Check Matchs and explode
        matches = check_matchs();
        if (matches) {
            for (int i = 0; i < LINES; i++) {
                for (int j = 0; j < COLLUMNS; j++) {
                    if (board[i][j] != NULL) {
                        if (board[i][j]->match > 0) {
                            delete board[i][j];
                            board[i][j] = null_gem;
                        }
                    }
                }
            }
            state = CREATION;
        }
        else {
            if (swaped_gem_1 != NULL && swaped_gem_2 != NULL) {
                swap_gem(swaped_gem_1, swaped_gem_2);
                swaped_gem_1 = NULL;
                swaped_gem_2 = NULL;
                state = MOVING;
            }
            else {
                state = CHECK_INPUT;

            }
        }
        break;
    case CHECK_INPUT:
        //std::cout << "CHECK_INPUT" << std::endl;
        for (int i = 0; i < LINES; i++) {
            for (int j = 0; j < COLLUMNS; j++) {
                board[i][j]->process(delta_time);
            }
        }
        //Check input
        if (selected_gem != NULL && selected_gem_2 != NULL) {
            if (selected_gem->is_neighbor(selected_gem_2)) {
                swap_gem(selected_gem, selected_gem_2);
                swaped_gem_1 = selected_gem;
                swaped_gem_2 = selected_gem_2;
                state = MOVING;
            }
            selected_gem = NULL;
            selected_gem_2 = NULL;
        }
        break;
    }    
}

void Board::render() {
    background->render(0, 0);
    Gem* top = NULL;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if (board[i][j]->is_moving) {
                top = board[i][j];
            }
            else
                board[i][j]->render();
        }
    }
    if (top != NULL) top->render();
}

bool Board::check_matchs() {
    bool there_are_matchs = false;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            //std::cout << i << ":" << j << " " << board[i - 1][j]->type << " <- " << board[i][j]->type << " -> " << board[i + 1][j]->type << std::endl;
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