//Stack Linked-List Implentation

class Stack{
    private:
        Card* top;
        int cardCount;

    public:
        Stack()
        {
            top = nullptr;
            cardCount = 0;
        }

        int getCardCount(){
            return cardCount;
        }

        bool isFull()
        {
            return cardCount == 52 ?  true : false;

        }

        bool isEmpty()
        {
            return top == nullptr;
        }

        void push(Card *item)
        {
            if (isFull())
            {
                cout << "Stack is full, can not add item to stack!" << endl;
                return;
            }
            else
            {

                Card* temp = new Card(*item);
                temp->setNext(top);
                top = temp;
                cardCount++;

            }
        }

        void pop()
        {
            Card* temp;
            if (isEmpty())
            {
                cout << "Stack is empty, can not remove item from stack!" << endl;
                return;
            }
            else
            {
                temp = top;
                top = top->getNext();
                temp->setNext(nullptr);
                delete temp;
                cardCount--;
            }
        }


        Card* peek()
        {
            if (isEmpty())
            {
                return nullptr;
            }
            else
            {
                return top;
            }
        }


        Card* search(Card* s){
            Card* temp = top;
            while(temp && !temp->equals(s))
            {
                temp = temp->getNext();
            }
            return temp;
        }
};

