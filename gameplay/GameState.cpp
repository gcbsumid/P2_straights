#include "Card.h"

#include "GamePlay.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "ModelObserver.h"
#include <cassert>
#include <cstdlib>
#include <vector>
#include <set>

using namespace std;


// Constructor - set up the cards.
GameState::GameState(GamePlay* gameplay) : mGamePlay(gameplay), mCurrentPlayer(-1), mSeed(0) {
    for (int i = 0; i < GamePlay::CARD_COUNT; i++) {
	    mCardsArray[i] = new Card((Suit)(i / RANK_COUNT), (Rank)(i % RANK_COUNT)); // Creates cards
        mArrangedCards[i] = mCardsArray[i]; // pointers to an arranged set of cards
    }
    mScores.resize(4);
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

void GameState::ResetSeed(int seed) {
    mSeed = seed;
}

void GameState::Initialize() {
    srand48(mSeed);
    // Delete the players
    for (int i = 0; i < mPlayers.size(); i++) {
        if (mPlayers[i]) {
            delete mPlayers[i];
        }
        mScores[i] = 0;
        mDiscards[i].clear();
    }
    mPlayers.clear();
    mCardsOnTable.clear();
}

void GameState::AddObserver(ModelObserver* o) {
    cout << "Adding an observer to the game state" << endl;
    mObservers.push_back(o);
}

void GameState::AddHumanPlayer(ViewInterface* v) {
    assert(mPlayers.size() < 4);
    mPlayers.push_back(new HumanPlayer(mGamePlay, this, v, mPlayers.size() + 1));
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_PlayerAdded(true, mPlayers.size());
    }
}

void GameState::AddComputerPlayer(ViewInterface* v) {
    assert(mPlayers.size() < 4);
    mPlayers.push_back(new ComputerPlayer(mGamePlay, this, v, mPlayers.size() + 1));
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_PlayerAdded(false, mPlayers.size());
    }
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
    cout << "Dealing cards" << endl;
    assert(mPlayers.size() == 4);
    // We only tell the observers about human cards.
    vector<vector<Card*> > observerUpdate;
    int card = 0;
    mHands.clear();
    for (int i = 0; i < 4; i++) {
        vector<Card*> hand;
        for (int j = 0; j < 13; j++) {
            hand.push_back(mCardsArray[card++]);
        }
        mHands.push_back(hand);
        if (mPlayers[i]->IsHuman()) {
            observerUpdate.push_back(mHands[i]);
            cout << "This hand " << i << " has " << observerUpdate[i].size() << " cards " << endl;
            assert(observerUpdate[i].size() == 13);
        } else {
            vector<Card*> v;
            observerUpdate.push_back(v);
            assert(observerUpdate[i].empty());
        }
    }
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        cout << "Sending a vector of size " << observerUpdate.size() << " to an observer for dealing cards " << endl;
        (*i)->Model_CardsDealt(observerUpdate);
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
    for (int i = 0; i < 4; i++) {
        // Card #45 is the seven of spades.
        for (int j = 0; j < 13; j++) {
            cout << *mHands[i][j] << endl;
        }
    }
    assert(false);
}

bool GameState::PlayerHas(int player, Card* card) const {
    assert(player < 5 && player > 0);
    for (int i = 0; i < 13; i++) {
        if (mHands[player - 1][i]) {
            if (*mHands[player - 1][i] == *card) {
                return true;
            }
        }
    }
    return false;
}

Player* GameState::NextPlayer() {
    mCurrentPlayer++;
    mCurrentPlayer %= 4;
    Player* p = mPlayers[mCurrentPlayer];
    return p;
}

Player* GameState::CurrentPlayer() {
    Player* p = mPlayers[mCurrentPlayer];
    return p;
}

void GameState::ResetNextPlayer(int player) {
    player--;
    if (player == 0) {
        player = 3;
    } else {
        player--;
    }
    mCurrentPlayer = player;
}

Player* GameState::HumanToComputer(HumanPlayer* human) {
    cout << "Converting player " << human->GetID() << " to a computer" << endl;
    Player* comp = new ComputerPlayer(human);
    int id = human->GetID() - 1;
    delete human;
    mPlayers[id] = comp;

    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_PlayerRageQuitted(id + 1);
    }
    return comp;
}

Player* GameState::PlayerWithID(int player) const {
    assert(player > 0 && player < 5);
    return mPlayers[player - 1];
}

void GameState::ClearCardsOnTable() {
    mCardsOnTable.clear();
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_CardsCleared();
    }
}

void GameState::PlayCard(int player, Card* card) {
    assert(player > 0 && player < 5 && card != NULL);
    player--;
    for (int i = 0; i < 13; i++) {
        if (mHands[player][i] && mHands[player][i] == card) {
            mHands[player][i] = NULL;
            mCardsOnTable.insert(card);
            for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
                (*i)->Model_CardPlayed(player + 1, card);
            }
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
            for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
                (*i)->Model_CardDiscarded(player + 1, card);
            }
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
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_ScoreUpdated(player, score);
    }
}

int GameState::GetScore(int player) const {
    assert(player < 5 &&  player > 0);
    return mScores[player - 1];
}


vector<Card*> GameState::GetDiscards(int player) const {
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
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_DiscardsCleared(player);
    }
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
int GameState::CardsInHand(int player) const {
    int count = 0;
    for (int i = 0; i < 13; i++) {
        if (mHands[player][i]) {
            count++;
        }
    }
    return count;
}

void GameState::EndGame(int player) {
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_EndGame(player);
    }
}
