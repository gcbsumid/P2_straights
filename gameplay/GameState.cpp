#include "Card.h"

#include "GamePlay.h"
#include "HumanPlayer.h"
#include "Player.h"
#include <cassert>
#include <cstdlib>

using namespace std;


// Constructor - set up the cards.
GameState::GameState(GamePlay* gameplay) : mGamePlay(gameplay), mCurrentPlayer(-1) {
    for (int i = 0; i < GamePlay::CARD_COUNT; i++) {
	    mCardsArray[i] = new Card((Suit)(i / RANK_COUNT), (Rank)(i % RANK_COUNT)); // Creates cards
        mArrangedCards[i] = mCardsArray[i]; // pointers to an arranged set of cards
    }
    for (int i = 0; i < 4; i++) {
        mScores.push_back(0);
    }
    mHands.resize(4);
    mDiscards.resize(4);
}

// Destructor - delete cards, players.
GameState::~GameState() {
    // Delete the cards
    for (int i = 0; i < GamePlay::CARD_COUNT; i++) {
        delete mCardsArray[i];
    }
    
    // Delete the players
    for (int i = 0; i < 4; i++) {
        delete mPlayers[i];
    }
}

void GameState::AddHumanPlayer() {
    assert(mPlayers.size() < 4);
    mPlayers.push_back(new HumanPlayer(mGamePlay, this, mPlayers.size() + 1));
}

void GameState::AddComputerPlayer() {
    assert(mPlayers.size() < 4);
    mPlayers.push_back(new ComputerPlayer(mGamePlay, this, mPlayers.size() + 1));
}

void GameState::Shuffle() {
    int n = GamePlay::CARD_COUNT;

    while (n > 1) {
        int k = (int) (lrand48() % n);
        --n;
        Card *c = mCardsArray[n];
        mCardsArray[n] = mCardsArray[k];
        mCardsArray[k] = c;
    }
}


void GameState::DealCards() {
    assert(mPlayers.size() == 4);
    for (int i = 0; i < 4; i++) {
        // Slice up the cards into individual hands, represented as vectors.
        Card** handBegin = mCardsArray + (i * 13);
        Card** handEnd = handBegin + 13 * sizeof(Card*);
        mHands[i] = vector<Card*>(handBegin, handEnd);
    }
}
int GameState::PlayerWithSevenOfSpades() const {
    for (int i = 0; i < 4; i++) {
        // Card #45 is the seven of spades.
        if (PlayerHas(i + 1, mArrangedCards[45])) {
            return mPlayers[i]->GetID();
        }
    }
    // This should never happen.
    cerr << "Nobody has the Seven of Spades." << endl;
    return 4;
}

bool GameState::PlayerHas(int player, Card* card) const {
    assert(player < 5 && player > 0);
    for (int i = 0; i < 13; i++) {
        if (mHands[player][i + 1]) {
            if (*mHands[player][i + 1] == *card) {
                return true;
            }
        }
    }
    return false;
}

Player* GameState::NextPlayer() {
    Player* p = mPlayers[mCurrentPlayer];
    mCurrentPlayer++;
    mCurrentPlayer %= 4;
    return p;
}

void GameState::ResetNextPlayer(int player) {
    mCurrentPlayer = player - 1;
}

Player* GameState::HumanToComputer(HumanPlayer* human) {
    Player* comp = new ComputerPlayer(human);
    int id = human->GetID() - 1;
    delete human;
    mPlayers[id] = comp;
    return comp;
}

Player* GameState::PlayerWithID(int player) const {
    assert(player > 0 && player < 5);
    return mPlayers[player];
}

void GameState::ClearCardsOnTable() {
    mCardsOnTable.clear();
}

void GameState::PlayCard(int player, Card* card) {
    assert(player > 0 && player < 5 && card != NULL);
    player--;
    for (int i = 0; i < 13; i++) {
        if (mHands[player][i] && mHands[player][i] == card) {
            mHands[player][i] = NULL;
            mCardsOnTable.insert(card);
            return;
        }
    }
    // Tried to play a card that wasn't in the hand.
    cerr << "Tried to play card " << *card << " that wasn't in player " << player + 1 << "'s hand." << endl;
    assert(false);
}

void GameState::DiscardCard(int player, Card* card) {
    assert(player > 0 && player < 5 && card != NULL);
    player--;
    for (int i = 0; i < 13; i++) {
        if (mHands[player][i] && mHands[player][i] == card) {
            mHands[player][i] = NULL;
            mDiscards[player].push_back(card);
            return;
        }
    }
    // Tried to discard a card that wasn't in the hand.
    cerr << "Tried to discard card " << *card << " that wasn't in player " << player + 1 << "'s hand." << endl;
    assert(false);
}

bool GameState::IsLegal(Card* card) const {
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

void GameState::UpdateScore(int player, int score) {
    assert(player < 5 && player > 0);
    mScores[player - 1] = score;
}

int GameState::GetScore(int player) const {
    assert(player < 5 &&  player > 0);
    return mScores[player - 1];
}


const vector<Card*> GameState::GetDiscards(int player) const {
    assert(player < 5 && player > 0);
    return mDiscards[player - 1];
}

vector<Card*> GameState::GetHand(int player) const {
    assert(player < 5 && player > 0);
    return mHands[player - 1];
}

void GameState::ClearDiscard(int player) {
    assert(player < 5 && player > 0);
    mDiscards[player - 1].clear();
}

Card* GameState::CardInHand(int player, Card* card) const {
    assert(player < 5 && player > 0 && card != NULL);
    player--;
    for (int i = 0; i < 13; i++) {
        if (mHands[player][i] &&
            mHands[player][i]->getSuit() == card->getSuit() &&
            mHands[player][i]->getRank() == card->getRank()) {
            return mHands[player][i];
        }
    }
    return NULL;
}

