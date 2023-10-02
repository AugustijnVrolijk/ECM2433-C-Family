#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.h"

/** A function which creates a Player struct - this is pretty much a queue
 * 
 * @returns A player struct initialised with empty queue
 */
Player *create_player() {
    Player *player;
    if(!(player = (Player*) malloc(sizeof(Player)))) {
        printf("failed to malloc memory for player\n");
        exit(1);
    };
    player->front = 0;
    player->back = -1;
    player->size = 0;
    return player;
}

/** Add a card to a certain player struct
 * 
 * @param p A pointer to a Player struct
 * @param card card to be added to player struct
 */
void add_card(Player *p, int card) {
    p->back = (p->back + 1)%52;
    p->deck[p->back] = card;
    p->size++;
}

/** remove the bottom most card from the struct
 * 
 * @param p A pointer to a Player struct
 * 
 * @returns card that was removed from player struct
 */
int remove_card(Player *p) {
    int card = p->deck[p->front];
    p->front = (p->front + 1)%52;
    p->size--;
    return card;
}

/** checks whether a struct is empty of cards
 * 
 * @param p A pointer to a Player struct
 * 
 * @returns int whether or not the player struct is empty or not
 */
int is_empty(Player *p) {
    if(p->size == 0) {
        return 1;
    }
    return 0;
}

/** moves all cards from one Player struct to another
 * 
 * @param pile A pointer to a Player struct to move cards from
 * @param p A pointer to a Player struct to move cards to
 *
 */
void move_queue(Player *pile, Player *p) {

    while (!is_empty(pile)) {
        int card = remove_card(pile);
        add_card(p, card);
    }
    return;
}

/** prints out the cards within a player struct - used for talkative
 * 
 * @param pile A pointer to a Player struct
 */
void print_queue(Player *p) {
    printf("{");
    int i = p->front;
    int j;
    for (j = 0; j < p->size; j++) {
        printf("%d, ", p->deck[i]);
        i = (i + 1) %52;
    }
    printf("}\n");
    return;
}


/** checks if a player struct has the full 52 cards
 * 
 * @param p A pointer to a Player struct
 */
int finished(Player *p) {
    if (p->size == 52) {
        return 1;
    } else {
        return 0;
    }
}

/** correlates penalty card to number of penalty turns it gives
 * 
 * @param card A integer representing the number of a card
 */
int penalty(int card) {
    switch (card) {
        case 14: return 4;
        case 13: return 3;
        case 12: return 2;
        case 11: return 1;
        default: return 0;
    }
}

/** enables a player to take a single turn of the game
 * 
 * @param player a pointer to a player struct
 * @param pile a pointer to a player struct
 */
Player *take_turn(Player *player, Player *pile) {
    Player *reward = create_player();
    
    /* Not a penalty card, just add it to the pile */
    int topCard = pile->deck[pile->back];
    if (topCard <= 10) {   
        int card = remove_card(player);
        add_card(reward, card);
        return reward;
    }  
    /* Penalty card, pay the penalty and take the pile */
    int n_penalty = penalty(topCard);
    int i;
    for (i = 0; i < n_penalty; i++) {
        int card = remove_card(player);
        add_card(reward, card);
        if (card > 10) {
            break;
        }
        if (is_empty(player)) {
            break;
        }
    }
    return reward;
    
}

/** main function to run the beggar your neighbour game
 * 
 * @param Nplayers Number of players to set the game up for
 * @param deck a pointer to a deck to give out to players
 * @param talkative whether or not to print out details of each turn
 */
int beggar(int Nplayers, int *deck, int talkative) {
    Player **players;
    if (!(players = (Player**)malloc(Nplayers * sizeof(Player*)))) {
        printf("failed to malloc memory for players\n");
        exit(1);
    }
    int i;
    for (i = 0; i < Nplayers; i++) {
        Player *player = create_player();
        players[i] = player;
    }

    Player *pile = create_player();
    int player_setup = 0;
    int pileStart = 0;
    for (i = 0; i < 52; i++) {
        if (deck[i] < 11 && pileStart == 0) {
            add_card(pile, deck[i]);
            pileStart++;
            continue;
        }
        add_card(players[player_setup], deck[i]);
        player_setup = (player_setup+1)%Nplayers;
    }

    int turn = 0;
    int winner = 0;
    int player_turn = 0;
    int current_penalty_winner = -1;

    if (talkative) {

        printf("\n\nTurn: %d\n", turn);
        printf("Pile: ");
        print_queue(pile);
        int i;
        for (i = 0; i < Nplayers; i++) {
            printf("    %d: ", i);
            print_queue(players[i]);
        }
    }
    while (!winner) {
        if (players[player_turn]->size == 0) {
            player_turn = (player_turn+1)%Nplayers;
            continue;
        }
        Player *reward;
        reward = take_turn(players[player_turn], pile);
        int last_card = reward->deck[reward->back];

        if (last_card > 10) {
            current_penalty_winner = player_turn;
            move_queue(reward, pile);

        } else if (current_penalty_winner != -1)  {
            move_queue(reward, players[current_penalty_winner]);
            move_queue(pile, players[current_penalty_winner]);
            if (finished(players[current_penalty_winner])) {
                winner = 1;
            }
        } else {
            move_queue(reward, pile);
        }
        free(reward);
        turn++;
        player_turn = (player_turn+1)%Nplayers;

        if (talkative) {
            printf("\n\nTurn: %d\n", turn);
            printf("Pile: ");
            print_queue(pile);
            
            int i;
            for (i = 0; i < Nplayers; i++) {
                printf("    %d: ", i);
                print_queue(players[i]);
            
            }
        }
    }
    free(pile);
    for (i = 0; i < Nplayers; i++) {
        free(players[i]);
    }
    free(players);
    return turn;
}

