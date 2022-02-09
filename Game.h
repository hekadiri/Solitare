#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

#include "Card.h"
#include "Stack.h"
#include "Exceptions.h"

using namespace std;

class Game{
    private:
        int timesUnDealtDeckFlipped;
        int score;

        Card* cardDeck[52];

        Stack deck;
        Stack discardPile;

        Stack heartPile;
        Stack diamondPile;
        Stack spadePile;
        Stack clubsPile;
    
        string topOfHeartPile;
        string topOfDiamondPile;
        string topOfClubPile;
        string topofSpadePile;

        Stack pile[7];
        Card* emptyCard = new Card();
        Card* twoDArray[7][13] = {emptyCard};
    
        ofstream file{"cis200Solitare.txt"};

    public:

        Game(){
            
            file << "Starting Program" << endl;
            
            string ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
            int rankInts[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
            char suits[] = {'H','D','S','C'};
            int index = 0;

            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 13; j++){
                    cardDeck[index] = new Card(ranks[j], rankInts[j], suits[i], nullptr);
                    index++;
                }
            }

            
            makeDeckVisible();
            cout << "Initial Card Deck: \n";
            file << "Printing initial card deck" << endl;
            printCardDeck();
            cout << endl << endl;

            cout << "Sorted Card Deck (Increasing): \n";
            file << "Printing increasing sorted card deck" << endl;
            sortCardDeckIncreasingOrder();
            printCardDeck();
            cout << endl << endl;

            cout << "Sorted Card Deck (Decreasing): \n";
            file << "Printing decreasing sorted deck" << endl;
            sortCardDeckDecreasingOrder();
            printCardDeck();
            cout << endl << endl;

            cout << "Shuffled Card Deck: \n";
            file << "Printing shuffled card deck" << endl;
            shuffleCardDeck();
            printCardDeck();

            makeDeckNotVisible();

            pile[6].push(cardDeck[1]);
            pile[6].push(cardDeck[2]);
            pile[6].push(cardDeck[3]);
            pile[6].push(cardDeck[4]);
            pile[6].push(cardDeck[5]);
            pile[6].push(cardDeck[6]);
            cardDeck[7]->setUncovered(true);
            pile[6].push(cardDeck[7]);

            pile[5].push(cardDeck[8]);
            pile[5].push(cardDeck[9]);
            pile[5].push(cardDeck[10]);
            pile[5].push(cardDeck[11]);
            pile[5].push(cardDeck[12]);
            cardDeck[13]->setUncovered(true);
            pile[5].push(cardDeck[13]);

            pile[4].push(cardDeck[14]);
            pile[4].push(cardDeck[15]);
            pile[4].push(cardDeck[16]);
            pile[4].push(cardDeck[17]);
            cardDeck[18]->setUncovered(true);
            pile[4].push(cardDeck[18]);

            pile[3].push(cardDeck[19]);
            pile[3].push(cardDeck[20]);
            pile[3].push(cardDeck[21]);
            cardDeck[22]->setUncovered(true);
            pile[3].push(cardDeck[22]);

            pile[2].push(cardDeck[23]);
            pile[2].push(cardDeck[24]);
            cardDeck[25]->setUncovered(true);
            pile[2].push(cardDeck[25]);

            pile[1].push(cardDeck[26]);
            cardDeck[27]->setUncovered(true);
            pile[1].push(cardDeck[27]);

            cardDeck[28]->setUncovered(true);
            pile[0].push(cardDeck[28]);

            for(int i = 29; i < 52; ++i){
                deck.push(cardDeck[i]);
            }

        }

        void makeDeckVisible(){
            for(int i = 0; i < 52; ++i){
                cardDeck[i]->setUncovered(true);
            }
        }

        void makeDeckNotVisible(){
            for(int i = 0; i < 52; ++i){
                cardDeck[i]->setUncovered(false);
            }

        }

        void printGame(){
            file << "Printing out menu" << endl;
            //Title
            cout << "\n\n\n\n";
            cout << setw(45) << "MOHSEN's SOLITARE GAME\n";

            //Sort Piles
            cout << "\tHeart Pile: " + heartPile.peek()->printCard();
            cout << "\tDiamond Pile: " + diamondPile.peek()->printCard();
            cout << "\tSpade Pile: " + spadePile.peek()->printCard();
            cout << "\tClubs Pile: " + clubsPile.peek()->printCard();
            cout << endl;


            update2dArray();
            cout << setw(12) << "Pile 1: " + twoDArray[0][0]->printCard();
            cout << setw(12) << "Pile 2: " + twoDArray[1][0]->printCard();
            cout << setw(12) << "Pile 3: " + twoDArray[2][0]->printCard();
            cout << setw(12) << "Pile 4: " + twoDArray[3][0]->printCard();
            cout << setw(12) << "Pile 5: " + twoDArray[4][0]->printCard();
            cout << setw(12) << "Pile 6: " + twoDArray[5][0]->printCard();
            cout << setw(12) << "Pile 7: " + twoDArray[6][0]->printCard();

            cout << endl;

            for(int j = 1; j < 7; ++j){
                for(int i = 0; i < 7; ++i){
                    if(twoDArray[i][j]){
                        cout << setw(12) << twoDArray[i][j]->printCard();
                    }
                    else{
                        cout << setw(12) << " ";
                    }
                }
                cout << endl;
            }

            cout << setw(12) << "Deck: " + deck.peek()->printCard();
            if(discardPile.peek()){
                cout << setw(12) << "Discard: " + discardPile.peek()->printCard() << endl;
            } else{
                cout << setw(12) << "Discard: O" << endl;
            }
            cout << setw(12) << "Score: " << score << endl;
            
        }

        void choose(){
            cout << "\nOptions: 1) Move card to Sort Pile.\n";
            cout <<   "         2) Move card(s) in Piles or Discard.\n";
            cout <<   "         3) Flip Cards.\n";
            cout << "Your selection: ";
            int selection;
            cin >> selection;

            switch (selection){
                case 1:
                    try{
                        moveCardtoSortPiles();
                    }catch(WrongCardToSortPileException e){
                        cout << "You cannot move that card to the sort pile because it is the wrong sort pile or it is not in the correct order. Please try another move." << endl;
                    }
                    break;
                case 2:
                    try{
                        moveCardinPilesorDiscard();
                    }catch(UnableToMoveGivenCardToPileException e){
                        cout << "You cannot move that card to the specified pile because it is not the correct color or not in the correct order. Please try another move." << endl;
                    }
                    break;
                case 3:
                    flipCards();
                    break;
                default:
                    cout << "Invalid menu option.\n";
            }
        }

        int findLongestPileLength(){
            int max = 0;
            for(int i = 0; i < 7; ++i){
                if(pile[i].getCardCount() > max){
                    max = pile[i].getCardCount();
                }
            }
            return max;
        }

        void update2dArray(){
            for(int i = 6; i > -1; --i){
                Card* temp = pile[i].peek();
                int j = pile[i].getCardCount()-1;
                if(pile[i].peek() != nullptr) pile[i].peek()->setUncovered(true);
                for(int k = 12; k > j; --k){
                    twoDArray[i][k] = nullptr;
                }
                while(temp != nullptr){
                    twoDArray[i][j] = temp;
                    temp = temp->getNext();
                    j--;
                }

            }
        }

        void sortCardDeckIncreasingOrder(){
            //Insertion sort
            int i, j;
            Card* key;
            for(i = 0; i < 52; i++){
                key = cardDeck[i];
                j = i - 1;

                while(j >= 0 && cardDeck[j]->getRankInt() > key->getRankInt()){
                    cardDeck[j+1] = cardDeck[j];
                    j = j - 1;
                }
                cardDeck[j + 1] = key;
            }
        }

        void sortCardDeckDecreasingOrder(){
            //Insertion sort
            int i, j;
            Card* key;
            for(i = 0; i < 52; i++){
                key = cardDeck[i];
                j = i - 1;

                while(j >= 0 && cardDeck[j]->getRankInt() < key->getRankInt()){
                    cardDeck[j+1] = cardDeck[j];
                    j = j - 1;
                }
                cardDeck[j + 1] = key;
            }
        }

        void shuffleCardDeck(){
            srand((int)time(NULL));
            for(int i = 51; i > 0; i--){
                int j = rand() % (i+1);
                swap(cardDeck[i], cardDeck[j]);
            }
        }

        void printCardDeck(){
            for(int i = 0; i < 52; ++i){
                cout << cardDeck[i]->printCard();
            }
        }

        bool checkIfGameOver(){
            file << "Checking if game is over" << endl;
            if(timesUnDealtDeckFlipped == 3){
                cout << "\n\nGame Over! You lost :(" << endl;
                cout << "Final Score: " << score << endl;
                return true;
            }
            else if(pile[0].isEmpty() && pile[1].isEmpty() && pile[2].isEmpty() && pile[3].isEmpty() && pile[4].isEmpty() && pile[5].isEmpty() && pile[6].isEmpty() && deck.isEmpty()){
                cout << "\n\nGame Over! You won :)" << endl;
                cout << "Final Score: " << score << endl;
                return true;
            }
            else{
                return false;
            }
        }

        void moveCardtoSortPiles(){
            int pileNumber;
            string rank;
            char suit;
            char pileName;

            cout << "Which card would you like to move?" << endl;
            cout << "Pile Number: ";
            cin >> pileNumber;
            cout << "Rank: ";
            cin >> rank;
            cout << "Suit: ";
            cin >> suit;

            
            Card *move = new Card(rank, 0, suit, nullptr);
            
                        
            Card *loc = pile[pileNumber-1].search(move);
            throw WrongCardToSortPileException();
            
            cout << "While sort pile would you like to move it to? \n";
            cout << "Sort Pile Name: ";
            cin >> pileName;
        
            file << "Moving the " << rank + suit << " card from pile " << pileNumber << " to the " << pileName << endl;
            
            if(pileName == 'H'){
                if(!heartPile.peek()->oneLess(loc)) throw WrongCardToSortPileException();
                heartPile.push(loc);
            }
            if(pileName == 'S'){
                if(!heartPile.peek()->oneLess(loc)) throw WrongCardToSortPileException();
                spadePile.push(loc);
            }
            if(pileName == 'D'){
                if(!heartPile.peek()->oneLess(loc)) throw WrongCardToSortPileException();
                diamondPile.push(loc);
            }
            if(pileName == 'C'){
                if(!heartPile.peek()->oneLess(loc)) throw WrongCardToSortPileException();
                clubsPile.push(loc);
            }
            
            pile[pileNumber-1].pop();
            score+=10;
        }

        void moveCardinPilesorDiscard(){
            int pileNumber;
            string rank;
            char suit;

            cout << "Which card would you like to move?" << endl;
            cout << "Pile Number: (Enter -1 for the Discard Pile): ";
            cin >> pileNumber;
            cout << "Rank: ";
            cin >> rank;
            cout << "Suit: ";
            cin >> suit;

            Card *move = new Card(rank, 0, suit, nullptr);

            Card *loc;
            if(pileNumber != -1)
            {
                loc = pile[pileNumber-1].search(move);
            }else{
                loc = discardPile.search(move);
            }

           // loc->setNext(nullptr);
            cout << "Where would you like to move it?";

            int newpileNumber;
            string oldpileNum = (pileNumber != -1) ? to_string(pileNumber) : "discard";
            cout << "Pile Number: ";
            
            cin >> newpileNumber;

            file << "Moving the " << rank + suit << " card from pile " << oldpileNum << " to the pile " << newpileNumber << endl;
            
            
            if(pileNumber == -1){
                if(!discardPile.peek()->oneLess(loc) && !discardPile.peek()->oppositeColor(loc))
                    throw UnableToMoveGivenCardToPileException();
                else{
                    
                    discardPile.pop();
                    pile[newpileNumber-1].push(loc);
                    update2dArray();
                    printGame();
                }
            }
            else{
                if(!pile[newpileNumber-1].peek()->oneLess(loc) && !pile[newpileNumber-1].peek()->oppositeColor(loc)) throw UnableToMoveGivenCardToPileException();
                else{
                    pile[pileNumber-1].pop();
                    pile[newpileNumber-1].push(loc);
                    update2dArray();
                    printGame();
                }
            }
        }

        void flipCards(){
            
            file << "Flipping the next 3 cards in the undealt deck";

            if(!deck.isEmpty()){
                Card* temp = deck.peek();
                deck.pop();
                discardPile.push(temp);
                discardPile.peek()->setUncovered(true);
            } else{
                for(int i = 0; i < discardPile.getCardCount(); ++i){
                    Card* temp = discardPile.peek();
                    discardPile.pop();
                    deck.push(temp);
                    deck.peek()->setUncovered(false);
                }
                timesUnDealtDeckFlipped++;
                file << "Flipping over the entire undealt deck";
            }

            if(!deck.isEmpty()){
                Card* temp = deck.peek();
                deck.pop();
                discardPile.push(temp);
                discardPile.peek()->setUncovered(true);
            } else{
                for(int i = 0; i < discardPile.getCardCount(); ++i){
                    Card* temp = discardPile.peek();
                    discardPile.pop();
                    deck.push(temp);
                    deck.peek()->setUncovered(false);
                }
                timesUnDealtDeckFlipped++;
                file << "Flipping over the entire undealt deck";
            }

            if(!deck.isEmpty()){
                Card* temp = deck.peek();
                deck.pop();
                discardPile.push(temp);
                discardPile.peek()->setUncovered(true);
            } else{
                for(int i = 0; i < discardPile.getCardCount(); ++i){
                    Card* temp = discardPile.peek();
                    discardPile.pop();
                    deck.push(temp);
                    deck.peek()->setUncovered(false);
                }
                timesUnDealtDeckFlipped++;
                file << "Flipping over the entire undealt deck";
            }
        }
};






