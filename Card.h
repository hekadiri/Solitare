#include <string>

using namespace std;

class Card  {
    private:
        string rank;
        int rankInt;
        char suit;
        bool uncovered;
        Card* next;

    public:
        Card(){
            rank = "O";
        }

        Card(const Card *&newCard){
            rank = newCard->rank;
            rankInt = newCard->rankInt;
            suit = newCard->suit;
            next = newCard->next;
            uncovered = false;
        }

        Card(string newRank, int newRankInt, char newSuit, Card* newNext){
            rank = newRank;
            rankInt = newRankInt;
            suit = newSuit;
            next = newNext;
            uncovered = false;
        }

        void setNext(Card* newNext){
            next = newNext;
        }

        Card* getNext(){
            return next;
        }

        int getRankInt(){
            return rankInt;
        }


        void setUncovered(bool set){
            uncovered = set;
        }

        string printCard(){
            if(this == (Card*)NULL){
                return "O ";
            }
            else if(rank == "O"){
                return rank + " ";
            }else if(!uncovered){
                return "? ";
            }
            else{
                return rank + suit + " ";
            }
        }

        bool equals(Card* rhs){
            return (this->rank == rhs->rank) && (this->suit == rhs->suit);
        }
    
        bool oneLess(Card *rhs){
            if(this == (Card*)NULL){
                return rhs->rankInt == 1;
            }
            else{
                return this->rankInt-1 == rhs->rankInt;
            }
        }
        
        bool oppositeColor(Card *rhs){
            bool opposite = false;
            if(this->suit == 'S' || this->suit == 'C')
                opposite = rhs->suit == 'H' || rhs->suit == 'D';
            if(this->suit == 'H' || this->suit == 'D')
                opposite = rhs->suit == 'S' || rhs->suit == 'C';
            
            return opposite;
        }
};
