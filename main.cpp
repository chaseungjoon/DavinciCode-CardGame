#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <thread>
#include <chrono>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0,21);

struct Card {
    std::string color;
    int num;
    bool show = false;
};

Card Deck[22];
Card Opponent[22];
Card Player[22];
Card Drawed;
Card Drawed_O;

void CreateDeck();
void PlayerGuess();
void OpponentGuess();
void PrintVisual();
void Start();
void PrintStatus();
bool compareCards(const Card &a, const Card &b);

int O_n = 4;
int P_n = 4;

int O_sc = 0;
int P_sc = 0;

bool draw_flag = false;
bool draw_flag_O = false;

int main(){

    //덱 만들기
    CreateDeck();

    //시작 카드 뽑기
    Start();

    //본 게임
    while (true){
        //덱 정렬
        std::sort(Opponent, Opponent + O_n, compareCards);
        std::sort(Player, Player + P_n, compareCards);

        PlayerGuess();

        if (O_n==O_sc) {
            std::cout << "\nPlayer Win!" << '\n';
            break;
        }
        if (P_n==P_sc){
            std::cout << "\nOpponent Win!" << '\n';
            break;
        }

        OpponentGuess();
        if (O_n==O_sc) {
            std::cout << "\nPlayer Win!" << '\n';
            break;
        }
        if (P_n==P_sc){
            std::cout << "\nOpponent Win!" << '\n';
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return 0;
}

void PrintStatus(){
    std::cout << "***Player Deck***" << '\n';
    std::cout << '\n';
    for (int i = 0; i<P_n; i++){
        if (Player[i].show)std::cout << i << ' ' << Player[i].color <<  ", "<< Player[i].num << " SHOWN" << '\n';
        else std::cout << i << ' ' << Player[i].color <<  ", "<< Player[i].num << '\n';
    }
    std::cout << '\n';
    std::cout << "****************" << '\n';

/*
    std::cout << "CHEATSHEET" << '\n';
    for (int i = 0; i<O_n; i++){
        std::cout << Opponent[i].color << ", " << Opponent[i].num << '\n';
    }
    std::cout << "***********" << '\n';
*/

    //상대 패 공개
    std::cout << "***Opponent Deck****" << '\n';
    std::cout << '\n';
    for (int i = 0; i<O_n; i++){
        if (Opponent[i].show) std::cout << i << ' ' << Opponent[i].color << ", " << Opponent[i].num << '\n';
        else std::cout << i << ' ' << Opponent[i].color << '\n';
    }
    std::cout << '\n';
    std::cout << "****************" << '\n';
}

void PrintVisual(){
    std::string line_3_l_w= "┃  ";
    std::string line_3_r_w= "  ┃";
    std::string line_3_l_b= "┃■■";
    std::string line_3_r_b= "■■┃";
    std::string temp_num = "??";

    std::string line_white_1 = "┏━━━━━━┓";
    std::string line_white_2 = "┃      ┃";
    std::string line_white_3 = "┗━━━━━━┛";

    std::string line_black_1 = "┃■■■■■■┃";

    //Opponent Visual
    std::string Line_0 = "";
    std::string Line_1 = "";
    std::string Line_2 = "";
    std::string Line_3 = "";
    std::string Line_4 = "";
    std::string Line_5 = "";
    std::string Line_6 = "";
    std::string Line_7 = "";

    for (int i = 0; i<O_n; i++){
        if (i<10) Line_7 += "    " + std::to_string(i) + "     ";
        else Line_7 += "   " + std::to_string(i) + "     ";

        if (draw_flag_O && Opponent[i].color==Drawed_O.color && Opponent[i].num == Drawed_O.num) {
            Line_0 += "  NEW";
            draw_flag = false;
        }
        else Line_0 += "          ";

        if (!Opponent[i].show){
            if (Opponent[i].color == "white"){
                Line_1 += line_white_1 + "  ";
                Line_2 += line_white_2 + "  ";
                Line_4 += line_white_2 + "  ";
                Line_5 += line_white_3 + "  ";
            }
            else{
                Line_1 += line_white_1 + "  ";
                Line_2 += line_black_1 + "  ";
                Line_4 += line_black_1 + "  ";
                Line_5 += line_white_3 + "  ";
            }
        }
        else{
            if (Opponent[i].color == "white"){
                Line_1 += "          ";
                Line_2 += "          ";
                Line_3 += "━━━━━━━   ";
                Line_5 += " ━━━━━━━  ";
            }
            else{
                Line_1 += "          ";
                Line_2 += "          ";
                Line_3 += "■■■■■■■   ";
                Line_5 += " ■■■■■■■  ";
            }
        }
        if (Opponent[i].show){
            if (Opponent[i].num < 10) temp_num = ' ' + std::to_string(Opponent[i].num);
            else temp_num = std::to_string(Opponent[i].num);

            if (Opponent[i].color == "black") Line_4 += "\\■■" + temp_num + "■■\\  ";
            else Line_4 += "\\  " + temp_num + "  \\  ";
        }
        else{
            if (Opponent[i].color=="black") Line_3 += line_3_l_b + temp_num + line_3_r_b + "  ";
            else Line_3 += line_3_l_w + temp_num + line_3_r_w + "  ";
        }
        temp_num = "??";
    }
    std::cout << "\n<Opponent Cards>\n";
    std::cout << '\n';
    std::cout << Line_0 << '\n';
    std::cout << Line_1 << '\n';
    std::cout << Line_2 << '\n';
    std::cout << Line_3 << '\n';
    std::cout << Line_4 << '\n';
    std::cout << Line_5 << '\n';
    std::cout << '\n';
    std::cout << Line_7 << '\n';


    std::cout << " \n";
    std::cout << " \n";

    //Player Visual
    Line_0 = "";
    Line_1 = "";
    Line_2 = "";
    Line_3 = "";
    Line_4 = "";
    Line_5 = "";
    Line_6 = "";
    Line_7 = "";
    temp_num = "??";

    for (int i = 0; i<P_n; i++){
        if (i<10) Line_7 += "    " + std::to_string(i) + "     ";
        else Line_7 += "   " + std::to_string(i) + "     ";

        if (draw_flag && Player[i].color==Drawed.color && Player[i].num == Drawed.num) {
            Line_0 += "  NEW";
            draw_flag = false;
        }
        
        else Line_0 += "          ";

        if (!Player[i].show){
            if (Player[i].color == "white"){
                Line_1 += line_white_1 + "  ";
                Line_2 += line_white_2 + "  ";
                Line_4 += line_white_2 + "  ";
                Line_5 += line_white_3 + "  ";
            }
            else{
                Line_1 += line_white_1 + "  ";
                Line_2 += line_black_1 + "  ";
                Line_4 += line_black_1 + "  ";
                Line_5 += line_white_3 + "  ";
            }
        }
        else {
            if (Player[i].color == "white"){
                Line_1 += "          ";
                Line_2 += "          ";
                Line_3 += " ━━━━━━━  ";
                Line_5 += "━━━━━━━   ";
            }
            else{
                Line_1 += "          ";
                Line_2 += "          ";
                Line_3 += " ■■■■■■■  ";
                Line_5 += "■■■■■■■   ";
            }
        }
        //if (Player[i].show) Line_6 += "          ";
        //else Line_6 += " HIDDEN   ";

        if (Player[i].num < 10) temp_num = ' ' + std::to_string(Player[i].num);
        else temp_num = std::to_string(Player[i].num);

        if (!Player[i].show){
            if (Player[i].color=="black") Line_3 += line_3_l_b + temp_num + line_3_r_b + "  ";
            else Line_3 += line_3_l_w + temp_num + line_3_r_w + "  ";
        }
        else {
            if (Player[i].color=="black") Line_4 += "/■■"+temp_num + "■■/  ";
            else Line_4 += "/  " + temp_num + "  /  ";
        }
        temp_num = "??";
    }

    std::cout << "<My Cards>\n";
    std::cout << '\n';
    std::cout << Line_0 << '\n';
    std::cout << Line_1 << '\n';
    std::cout << Line_2 << '\n';
    std::cout << Line_3 << '\n';
    std::cout << Line_4 << '\n';
    std::cout << Line_5 << '\n';
    //std::cout << Line_6 << '\n';
    std::cout << '\n' << Line_7 << '\n';


}

void PlayerGuess(){
    if (O_n+P_n != 22){
        //숫자 뽑기
        int draw;
        while (true){
            draw = distrib(gen);
            // Deck에 존재하는 카드일 경우
            if (Deck[draw].color != "None"){
                //Player 에게 카드 추가
                Player[P_n].color = Deck[draw].color;
                Player[P_n].num = Deck[draw].num;
                P_n+=1;
                //최근 뽑은것 저장
                Drawed.color = Deck[draw].color;
                Drawed.num = Deck[draw].num;
                // Deck에서 그 카드 삭제
                Deck[draw].color = "None";
                Deck[draw].num = -1;
                draw_flag = true;
                break;
            }
        }
    }
    //카드정렬
    std::sort(Player, Player + P_n, compareCards);

    // 맞춰보기
    int pos, guess, choice;
    while (true){
        PrintVisual();
        std::cout << "\nGuess the cards! (Enter : Position, Number) >> ";
        std::cin >> pos >> guess;

        if (Opponent[pos].show){
            std::cout << "\nAlready shown!" << '\n';
            continue;
        }

        if (Opponent[pos].num == guess){
            std::cout << "\nCORRECT!" << '\n';
            Opponent[pos].show = true;
            O_sc+=1;

            if (O_sc==O_n) return;

            std::cout << "\nWish to continue : 1, to stop : 0 >> ";
            std::cin >> choice;
            if (choice==0) break;
        }
        else {
            std::cout << "\nWRONG!" << '\n';
            for (int i = 0; i<P_n; i++){
                if (Player[i].color == Drawed.color && Player[i].num == Drawed.num) Player[i].show = true;
            }
            P_sc+=1;
            break;
        }

    }
}

void OpponentGuess(){
    if (O_n + P_n != 22){
        //std::cout << "OPPONENT DRAW!" << '\n';
        int draw;
        //상대 숫자뽑기
        while (true){
            draw = distrib(gen);
            // Deck에 존재하는 카드일 경우
            if (Deck[draw].color != "None"){
                //Player 에게 카드 추가
                Opponent[O_n].color = Deck[draw].color;
                Opponent[O_n].num = Deck[draw].num;
                O_n+=1;
                //최근 뽑은것 저장
                Drawed_O.color = Deck[draw].color;
                Drawed_O.num = Deck[draw].num;
                // Deck에서 그 카드 삭제
                Deck[draw].color = "None";
                Deck[draw].num = -1;
                draw_flag_O = true;
                break;
            }
        }
    }

    //상대가 아는 카드 모음
    Card O_know[22];
    int P_cnt = 0;

    for (int i = 0; i<P_n; i++){
        if (Player[i].show==true){
            P_cnt+=1;
            O_know[i].color = Player[i].color;
            O_know[i].num = Player[i].num;
        }
    }
    for (int i = 0; i<O_n; i++){
        O_know[P_cnt+i].color = Opponent[i].color;
        O_know[P_cnt+i].num = Opponent[i].num;
    }
    //아는 카드 정리
    std::sort(O_know, O_know + (P_cnt + O_n), compareCards);

    // 모르는 카드에 대해 예측
    double probabilities[22] = {0.0};

    for (int i = 0; i < P_n; i++) {
        if (!Player[i].show) {
            for (int j = 0; j < (P_cnt + O_n); j++) {
                if (O_know[j].num == Player[i].num) {
                    probabilities[i] -= 1.0;
                }
            }
            probabilities[i] += 1.0 / (22 - (P_cnt + O_n));
        }
    }

    int highestProbIndex = -1;
    double highestProb = -1.0;
    for (int i = 0; i < P_n; i++) {
        if (probabilities[i] > highestProb && Player[i].show == false) {
            highestProb = probabilities[i];
            highestProbIndex = i;
        }
    }

    int guess = 0;
    for (int i = 1; i <= 11; i++) {
        bool found = false;
        for (int j = 0; j < (P_cnt + O_n); j++) {
            if (i == O_know[j].num) {
                found = true;
                break;
            }
        }
        if (!found) {
            guess = i;
            break;
        }
    }

    std::cout << '\n';
    std::cout << "\nOpponent's Guess : " << highestProbIndex << " th card is " << guess << "\n";

    if (Player[highestProbIndex].num == guess) {
        std::cout << "\nOPPONENT CORRECT!" << std::endl;
        Player[highestProbIndex].show = true;
        P_sc++;
    } else {
        std::cout << "\nOPPONENT WRONG!" << std::endl;
        Opponent[O_n - 1].show = true;
        O_sc++;
    }
    std::cout << '\n';
}

bool compareCards(const Card &a, const Card &b) {
    if (a.num != b.num) {
        return a.num < b.num;
    }
    return a.color == "black" && b.color != "black";
}

void CreateDeck(){
    std::string color;
    int n, i;

    for (i = 0; i<22; i++){
        if (i>10){
            color = "black";
            n = i%11;
        }
        else {
            color = "white";
            n = i;
        }

        Deck[i].color = color;
        Deck[i].num = n+1;
    }
}

void Start(){
    int complete = 1;
    int temp, i;
    bool done;
    int nums[8];
    //8개 랜덤 숫자 추출
    while (complete <= 8){
        temp  = distrib(gen);
        done = true;
        for (int j = 0; j < complete; j++){
            if (temp == nums[j]){
                done = false;
                break;
            }
        }
        if (done){
            nums[complete-1]=temp;
            complete += 1;
        }
    }
    //4개 상대에게 주기
    for (i=0; i<4; i++){
        Opponent[i].color = Deck[nums[i]].color;
        Opponent[i].num = Deck[nums[i]].num;

        // 덱에서 그 카드 삭제
        Deck[nums[i]].color = "None";
        Deck[nums[i]].num = -1;
    }
    //4개 플레이어 주기
    for (i=4; i<8; i++){
        Player[i%4].color = Deck[nums[i]].color;
        Player[i%4].num = Deck[nums[i]].num;

        // 덱에서 그 카드 삭제
        Deck[nums[i]].color = "None";
        Deck[nums[i]].num = -1;
    }
}
