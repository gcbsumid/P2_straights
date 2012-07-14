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

    // Make sure these guys are always size 4, so we can address specific indices without worrying.
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
    // Don't call srand48 just yet, since we only use the new seed in the next game.
    mSeed = seed;
}

void GameState::Initialize() {
    // Initialize the random number generator at the beginning of the game.
    srand48(mSeed);
    // Delete the players
    for (int i = 0; i < mPlayers.size(); i++) {
        if (mPlayers[i]) {
            delete mPlayers[i];
        }
        mScores[i] = 0;
        mDiscards[i].clear();
    }
    // Have 0 players until they get added.
    mPlayers.clear();
    // Get rid of the cards on the table.
    mCardsOnTable.clear();

    // We start at the 0th round (this immediately gets incremented to 1 by NewRound).
    mRound = 0;
}

void GameState::AddObserver(ModelObserver* o) {
    cout << "Adding an observer to the game state" << endl;
    mObservers.push_back(o);
}

void GameState::AddPlayer(bool IsHuman, ViewInterface* v) {
    assert(mPlayers.size() < 4);
    if (IsHuman) {
        mPlayers.push_back(new HumanPlayer(mGamePlay, this, v, mPlayers.size() + 1));
    } else {
        mPlayers.push_back(new ComputerPlayer(mGamePlay, this, v, mPlayers.size() + 1));
    }
    // Alert the observers that this player was added.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_PlayerAdded(IsHuman, mPlayers.size());
    }
}

void GameState::Shuffle() {
    // This is the provided shuffle function.
    // Shuffle the cards as they were ordered previously, not from scratch.
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
        // Stick the cards in the hand we're building.
        for (int j = 0; j < 13; j++) {
            hand.push_back(mCardsArray[card++]);
        }
        mHands.push_back(hand);
        if (mPlayers[i]->IsHuman()) {
            // If we're dealing with the hand for a human, put the full hand in what we're telling the observers.
            observerUpdate.push_back(mHands[i]);
            assert(observerUpdate[i].size() == 13);
        } else {
            // Let the observer know that we're dealing with a computer by pushing an empty hand.
            vector<Card*> v;
            observerUpdate.push_back(v);
            assert(observerUpdate[i].empty());
        }
    }
    // Let the observers know about the hands.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_CardsDealt(observerUpdate);
    }
}

void GameState::NewRound() {
    mRound++;
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_NewRound(mRound);
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
    assert(false);
}

bool GameState::PlayerHas(int player, Card* card) const {
    assert(player < 5 && player > 0);
    for (int i = 0; i < 13; i++) {
        // mHands[player - 1] is NULL if the card that was originally in that slot has been played.
        if (mHands[player - 1][i]) {
            // Use the comparison operator on Card.
            if (*mHands[player - 1][i] == *card) {
                return true;
            }
        }
    }
    // Been through entire hand, couldn't find it. Guess the player doesn't have the card.
    return false;
}

Player* GameState::NextPlayer() {
    mCurrentPlayer++;
    mCurrentPlayer %= 4;
    return mPlayers[mCurrentPlayer];
}

Player* GameState::CurrentPlayer() {
    return mPlayers[mCurrentPlayer];
}

void GameState::ResetNextPlayer(int player) {
    // We want to change mCurrentPlayer, which is one before the next player.
    if (player == 1) {
        player = 4;
    } else {
        player--;
    }
    // mCurrentPlayer is 0-indexed.
    mCurrentPlayer = player - 1;
}

Player* GameState::HumanToComputer(HumanPlayer* human) {
    cout << "Converting player " << human->GetID() << " to a computer" << endl;
    Player* comp = new ComputerPlayer(human);
    int id = human->GetID();

    // Clean up the player.
    delete human;
    mPlayers[id - 1] = comp; // Replace the human with the new computer player.

    // Let the observers know.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_PlayerRageQuitted(id);
    }

    // Return the computer player in case the controller wants to take its turn.
    return comp;
}

Player* GameState::PlayerWithID(int player) const {
    assert(player > 0 && player < 5);
    return mPlayers[player - 1];
}

void GameState::ClearCardsOnTable() {
    mCardsOnTable.clear();
    // Let the observers know that the cards have been cleared.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_CardsCleared();
    }
}

Card* GameState::CardInHand(int player, Card* card) const {
    assert(player < 5 && player > 0 && card != NULL);
    // Loop through the cards in the player's hand, comparing the card in the hand with the given card.
    for (int i = 0; i < 13; i++) {
        if (mHands[player - 1][i] &&
            mHands[player - 1][i]->getSuit() == card->getSuit() &&
            mHands[player - 1][i]->getRank() == card->getRank()) {
            // Found it, return the pointer to the actual card.
            return mHands[player - 1][i];
        }
    }
    // Couldn't find the card.
    return NULL;
}

int GameState::CardsInHand(int player) const {
    assert(player < 5 && player > 0);
    int count = 0;
    for (int i = 0; i < 13; i++) {
        // The Card*s in mHands are NULL if the card has been played or discarded.
        if (mHands[player - 1][i]) {
            count++;
        }
    }
    return count;
}

void GameState::PlayCard(int player, Card* card) {
    assert(player > 0 && player < 5 && card != NULL);

    // Get a pointer to the actual card in the player's hand.
    Card* c = CardInHand(player, card);
    assert(c);
    RemoveFromHand(player, c);

    // Stick the card on the table.
    mCardsOnTable.insert(c);
    // Update observers.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_CardPlayed(player, c);
    }
}

void GameState::DiscardCard(int player, Card* card) {
    assert(player > 0 && player < 5 && card != NULL);
    // Get a pointer to the actual card in the player's hand.
    Card* c = CardInHand(player, card);
    assert(c);
    RemoveFromHand(player, c);
    // Put the card in the discard pile.
    mDiscards[player - 1].push_back(c);
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_CardDiscarded(player, c);
    }
}


void GameState::RemoveFromHand(int player, Card* card) {
    // Find the card in the player's hand, and set that pointer to NULL.
    cout << "Removing " << *card << " From " << player << endl;
    for (int i = 0; i < 13; i++) {
        if (mHands[player - 1][i] && *mHands[player - 1][i] == *card) {
            mHands[player - 1][i] = NULL;
            return;
        }
    }
    assert(false); // Tried to remove a card that wasn't in the player's hand.
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
        // The card is now known to be the same suit as a card on the table. Compare the ranks.

        if ((*testCard)->getRank() + 1 == card->getRank() || (*testCard)->getRank() - 1 == card->getRank()) {
            // Adjacent rank and same suit as a card on the table.
            return true;
        }
    }
    // Couldn't find a neighbouring card on the table.
    return false;
}

void GameState::UpdateScore(int player, int score) {
    assert(player < 5 && player > 0);
    int prevScore = mScores[player -1];
    mScores[player - 1] = score;
    // Let the observers know of the score change.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_ScoreUpdated(player, score, prevScore);
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
    // Alert the observers that the player's discard pile has been cleared.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_DiscardsCleared(player);
    }
}


void GameState::EndGame(vector<int> player) {
    // Let the observers know who won.
    for (vector<ModelObserver*>::iterator i = mObservers.begin(); i != mObservers.end(); i++) {
        (*i)->Model_EndGame(player);
    }
}
