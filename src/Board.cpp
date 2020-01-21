#include "Board.h"
#include <iostream>
#include <memory>
#include <array>

Board::Board()
{


}

Board::~Board()
{
    //dtor
}

void Board::init() {
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
    null_gem = new GemEmpty();

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            board[i][j] = null_gem;
            //board[i][j]->setPosition(margin_x + i * 70, margin_y + j * 70);
           /* int r = rand() % 5;
            board[i][j]->type = r + 1;
            board[i][j]->i = i;
            board[i][j]->j = j;
            switch (r) {
            case 0:
                board[i][j]->setTexture(gem1);
                break;
            case 1:
                board[i][j]->setTexture(gem2);
                break;
            case 2:
                board[i][j]->setTexture(gem3);
                break;
            case 3:
                board[i][j]->setTexture(gem4);
                break;
            case 4:
                board[i][j]->setTexture(gem5);
                break;
            }*/
        }
    }
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
    //g1->setPosition(232 + g1->i * 70, 104 + g1->j * 70);
    //g2->setPosition(232 + g2->i * 70, 104 + g2->j * 70);
}

bool Board::input(SDL_Event* e) {
    bool processed = false;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if (board[i][j] != NULL)
            if (board[i][j]->input(e)) {
                std::cout << board[i][j]->i << ":" << board[i][j]->j << std::endl;
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

void Board::process() {
    bool is_placing = false;
    switch (state) {
    case CREATION:
        //Create gems if it is empty
        std::cout << "Creating Gems" << std::endl;
        for (int i = 0; i < LINES; i++) {
            for (int j = COLLUMNS - 1; j >= 0; j--) {
                if (board[i][j]->type == 0) {
                    Gem* empty_gem = board[i][j];
                    for (int n = j - 1; n >= -1; n--) {
                        std::cout << i << ":" << j << ":" << n << std::endl;
                        if (n < 0 || (board[i][n]->type == 0 && n == 0)) {
                            std::cout << i << ":" << j << ":" << n << "-> Created" << std::endl;
                            Gem* replace_gem = new Gem();
                            replace_gem->pos = vec2(margin_x + i * 70, j * 70 - margin_y * 4);
                            int r = rand() % 5;
                            replace_gem->type = r + 1;
                            replace_gem->i = i;
                            replace_gem->j = j;
                            switch (r) {
                            case 0:
                                replace_gem->setTexture(gem1);
                                break;
                            case 1:
                                replace_gem->setTexture(gem2);
                                break;
                            case 2:
                                replace_gem->setTexture(gem3);
                                break;
                            case 3:
                                replace_gem->setTexture(gem4);
                                break;
                            case 4:
                                replace_gem->setTexture(gem5);
                                break;
                            }
                            board[i][j] = replace_gem;
                            break;
                        }
                        else if (board[i][n]->type != 0) {
                            std::cout << i << ":" << n << std::endl;
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
        std::cout << "Moving Gems" << std::endl;
        is_placing = false;
        for (int i = 0; i < LINES; i++) {
            for (int j = 0; j < COLLUMNS; j++) {
                if (board[i][j] != NULL) {
                    board[i][j]->process();
                    if (board[i][j]->is_placing) {
                        is_placing = true;
                    }
                }
            }
        }
        if (!is_placing) state = DESTROYING;
        break;
    case DESTROYING:
        std::cout << "DESTROYING" << std::endl;
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
            state = CHECK_INPUT;
        }
        break;
    case CHECK_INPUT:
        std::cout << "CHECK_INPUT" << std::endl;
        for (int i = 0; i < LINES; i++) {
            for (int j = 0; j < COLLUMNS; j++) {
                board[i][j]->process();
            }
        }
        //Check input
        if (selected_gem != NULL && selected_gem_2 != NULL) {
            if (selected_gem->is_neighbor(selected_gem_2)) {
                swap_gem(selected_gem, selected_gem_2);
                state = MOVING;
            }
            selected_gem = NULL;
            selected_gem_2 = NULL;
        }
    }    
}

void Board::render(SDL_Renderer* renderer) {
    background->render(0, 0);
    Gem* top = NULL;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            if (board[i][j]->is_moving) {
                top = board[i][j];
            }
            else
                board[i][j]->render(renderer);
        }
    }
    if (top != NULL) top->render(renderer);
}

bool Board::check_matchs() {
    bool there_are_matchs = false;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLLUMNS; j++) {
            //std::cout << i << ":" << j << " " << board[i - 1][j]->type << " <- " << board[i][j]->type << " -> " << board[i + 1][j]->type << std::endl;
            if ((i != 0 && i != LINES - 1) && board[i][j]->type == board[i - 1][j]->type && board[i][j]->type == board[i + 1][j]->type) {
                board[i][j]->match++;
                board[i + 1][j]->match++;
                board[i - 1][j]->match++;
                there_are_matchs = true;
            }
            if ((j != 0 && j != COLLUMNS - 1) && board[i][j]->type == board[i][j - 1]->type && board[i][j]->type == board[i][j + 1]->type) {
                board[i][j]->match++;
                board[i][j + 1]->match++;
                board[i][j - 1]->match++;
                there_are_matchs = true;
            }
        }
    }
    return there_are_matchs;
}