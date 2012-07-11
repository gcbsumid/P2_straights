#include <iostream>
#include <stdlib.h>
#include "Gameplay.h"

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Card.h"

using namespace std;

int Gameplay::CARD_COUNT = 52; 

// Constructor
Gameplay::Gameplay() : mQuit(false) {
    // Creates the deck
    for (int i = 0; i < CARD_COUNT; i++) {
	    mCardsArray[i] = new Card((Suit)(i / RANK_COUNT), (Rank)(i % RANK_COUNT)); // Creates cards
        mArrangedCards[i] = mCardsArray[i]; // pointers to an arranged set of cards
    }
    
    // create players either human or computer
    for (int i = 0; i < 4; i++) {
        cout << "Is player " << i + 1 << " a human(h) or a computer(c)?\n>";
        char player_type;
        cin >> player_type;
        if (player_type == 'h') {
            mPlayers[i] = new HumanPlayer(this, i + 1);
        } else {
            mPlayers[i] = new ComputerPlayer(this, i + 1);
        }
    }
}

Gameplay::~Gameplay() {
    // Delete the cards
    for (int i = 0; i < CARD_COUNT; i++) {
        delete mCardsArray[i];
    }
    
    // Delete the players
    for (int i = 0; i < 4; i++) {
        delete mPlayers[i];
    }
}

void Gameplay::PlayRound() {
    // shuffle and deal deck
//     for(int i = 0; i < CARD_COUNT; i++){
//         mCardsArray[i] = mArrangedCards[i];
//     }
    shuffle(mCardsArray);
    DealCards();
    
    int nextPlayer = PlayerWithSevenOfSpades();

    // Which turn are we on?
    int turnCounter = 0;
    
    cout << "A new round begins. It's player " << nextPlayer-- << "'s turn to play." << endl;
    
    while (turnCounter < CARD_COUNT) {
        mPlayers[nextPlayer]->TakeTurn();
        // If we have a human player, we need to take various actions depending on what they input.
        if (mPlayers[nextPlayer]->IsHuman()) {
            // Get a human pointer so we can call human-specific methods.
            HumanPlayer* human = (HumanPlayer*)mPlayers[nextPlayer];

            if (human->IsRageQuitted()) {
                // Convert human into computer player.
                Player* comp = new ComputerPlayer(human); // Note: the copy constructor must not copy the rage quit boolean
                delete human;
                mPlayers[nextPlayer] = comp;
                cout << "Player " << mPlayers[nextPlayer]->GetID() << " ragequits. A computer will now take over." << endl;
                mPlayers[nextPlayer]->TakeTurn();    // The computer player must take a turn for the rage quit player.
            }
        }
        if (mQuit) {
            break;
        }
        turnCounter++;
        nextPlayer++;
        nextPlayer %= 4;
    }
    
    mCardsOnTable.clear();
}

void Gameplay::PrintCardsOnTable() const {
    cout << "Cards on the table:" << endl;
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                cout << "Clubs:";
                break;
            case 1:
                cout << "Diamonds:";
                break;
            case 2:
                cout << "Hearts:";
                break;
            case 3:
                cout << "Spades:";
                break;
            default:
                // Should never get here.
                break;
        }
        for (int j = 0; j < 13; j++) {
            // Print out all cards in that suit which are on the table.
            if (mCardsOnTable.count(mArrangedCards[i*13 + j]) > 0) {
                cout << " " << mArrangedCards[i*13 + j]->getRankName();
            }
        }
        cout << endl;
    }
}

// Adds a card pointer to the set. the pointer points to a card that should be on the table
void Gameplay::AddCardToTable(Card* card) {
    mCardsOnTable.insert(card);
}

bool Gameplay::IsLegal(Card* card) const {
    if (card->getRank() == SEVEN) {
        // 7 is always a legal play.
        return true;
    }
    
    // If card has same suit and adjacent rank as a card on the table.
    for (set<Card*>::iterator testCard = mCardsOnTable.begin(); testCard != mCardsOnTable.end(); testCard++) {
        if ((*testCard)->getSuit() != card->getSuit()) {
            continue;
        }

        if ((*testCard)->getRank() + 1 == card->getRank() || (*testCard)->getRank() - 1 == card->getRank()) {
            return true;
        }
    }
    return false;
}

bool Gameplay::IsGameOver() {
    if (mQuit) {
        return true;
    }
    bool gameover = false;

    // Keep track of the lowest score so we can see who won.
    int winner = -1;
    int minScore = 100000;
    for (int i = 0; i < 4; i++) {
        mPlayers[i]->PrintDiscard();  // Print the player's discarded cards and calculate their final score.
        int score = mPlayers[i]->GetScore();
        if (score > 79) {
            gameover = true;
        }
        if (score < minScore) {
            minScore = score;
            winner = mPlayers[i]->GetID();
        }
    }
    if (gameover) {
        cout << "Player " << winner << " wins!" << endl;
    }
    return gameover;
}

int Gameplay::PlayerWithSevenOfSpades() const {
    for (int i = 0; i < 4; i++) {
        // Card #45 is the seven of spades.
        if (mPlayers[i]->PlayerHas(mArrangedCards[45])) {
            return mPlayers[i]->GetID();
        }
    }
    // This should never happen.
    cerr << "Nobody has the Seven of Spades." << endl;
    return 4;
}

void Gameplay::PrintAllCards() const {
    for (int i = 0; i < CARD_COUNT - 1; i++) {
        cout << *mCardsArray[i] << " ";
    }
    // Print out last card separately so we don't put a space after it.
    cout << *mCardsArray[CARD_COUNT - 1] << endl;
}

void Gameplay::Quit() {
    mQuit = true;
}

void Gameplay::DealCards() {
    for (int i = 0; i < 4; i++) {
        // Slice up the cards into individual hands, represented as vectors.
        Card** handBegin = mCardsArray + (i * 13);
        Card** handEnd = handBegin + 13 * sizeof(Card*);
        mPlayers[i]->ReceiveCards(vector<Card*>(handBegin, handEnd));
    }
}

void Gameplay::shuffle(Card** cards_) {
    int n = Gameplay::CARD_COUNT;

    while (n > 1) {
        int k = (int) (lrand48() % n);
        --n;
        Card *c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
}
