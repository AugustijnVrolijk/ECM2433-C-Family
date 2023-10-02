#ifndef BEGGAR_H_
#define BEGGAR_H_

typedef struct {
    int deck[52];
    int front;
    int back;
    int size;
} Player;


Player *create_player();
void add_card(Player *p, int card);
int remove_card(Player *p);
int finished(Player *p);
int penalty(int card);
Player *take_turn(Player *player, Player *pile);
int beggar(int Nplayers, int *deck, int talkative);

#endif