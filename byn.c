#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.h"
#include "riffle.h"

typedef struct {
    int shortest;
    int longest;
    int average;
} Stats;


Stats *statistics(int Nplayers, int games);
/**calcualte statistics for beggar function
 * finds the shortest, average and longest turn time for the game
 * 
 * @param Nplayers Number of players to test for
 * @param games number of games to repeat
 * 
 * @return pointer to Stats struct
*/
Stats *statistics(int Nplayers, int games) {
    int i;
    Stats *stat;;
    if(!(stat = (Stats*)malloc(sizeof(Stats)))) {
        printf("failed to malloc memory for player\n");
        exit(1);
    };
    stat->shortest = 1000;
    stat->longest = 0;
    stat->average = 0;
    int turn = 0;
    int average = 0;

    for (i = 0; i< games; i++) {
        int deck[52] = {
        2,2,2,2,
        3,3,3,3,
        4,4,4,4,
        5,5,5,5,
        6,6,6,6,
        7,7,7,7,
        8,8,8,8,
        9,9,9,9,
        10,10,10,10,
        11,11,11,11,
        12,12,12,12,
        13,13,13,13,
        14,14,14,14
        };
        srand(time(NULL));
        riffle(deck, 52, sizeof(int), 5);
        turn = beggar(Nplayers,deck,0);
        if (turn < stat->shortest) {
            stat->shortest = turn;
        } 
        if (turn > stat->longest) {
            stat->longest = turn;
        }
        average += turn;
    }
    stat->average = average/games;
    return stat;

}

int main(int argc,char **argv) {
    if (argc < 3) {
        printf("Please specify number of players and trials to run\n");
        exit(1);
    }
    int maxPlayers = atoi(argv[1]);
    int trials = atoi(argv[2]);
    int i = 2;
    for (i; i <= maxPlayers; i++) {
        Stats *stat;
        stat = statistics(i, trials);
        printf("Average turn time for %d players: %d\n", i,stat->average);
        printf("Longest turn time for %d players: %d\n", i,stat->longest);
        printf("Shortest turn time for %d players: %d\n", i,stat->shortest);
        free(stat);
    }
    
}