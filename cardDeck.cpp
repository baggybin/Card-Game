//
//
// authors:	Jonathan, Cathal, Nidhu
// date:	01.11.2014
//////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include "card.h"
#include "cardDeck.h"
#include "cardDeckException.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
// cardDeck() - createEmptyCardDeck()
//    Deafult constructor
// Pre: None
// Post: An Empty deck is created.
///////////////////////////////////////////////////////////////////////
cardDeck::cardDeck()
{
  // No need to create a dynamic array since empty
  // card deck will have 52 memory slots allocated to it.

  // Set size to zero to note the deck is "empty"
  size = 0;

  // Allocate 52 spaces for card objects.
  cdeck = new card[52];
}

//////////////////////////////////////////////////////////////////////
// cardDeck(newsize, initvalue=0)
// constructor to create a new dynamic deck with size newsize
// if memory cannot be allocated, exception is thrown
//
// parameter: newsize - size of dynamic array
//////////////////////////////////////////////////////////////////////
cardDeck::cardDeck(int newSize)
{
  size = newSize;
  try {
    //deck = new int[size];
    cdeck = new card[size];
    //cdeck = new card[size]
  } catch (bad_alloc ex) {
    // report error to cerr and rethrow exception
    cerr << "Error with allocation of memory "
    << "deck(newsize)\n";
    throw ex;
  }
}

//////////////////////////////////////////////////////////////////////
// dynarray(orig)
// copy constructor to create copy of a card deck with its own
// memory. if memory cannot be allocated, exception is thrown
// parameter: orig - reference to original deck
//////////////////////////////////////////////////////////////////////
cardDeck::cardDeck(cardDeck &orig)
{

  //   //// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //   /// Need to change this to custom COPY
  //   //// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

//////////////////////////////////////////////////////////////////////
// ~cardDeck()
// destructor for class - frees up
// the dynamically allocated
// memory
//
// parameter: none
//////////////////////////////////////////////////////////////////////

cardDeck::~cardDeck()
{
  delete[] cdeck;
}

//////////////////////////////////////////////////////////////////////
//getNumberOfCards()
//////////////////////////////////////////////////////////////////////


int cardDeck::getNumberOfCards() const
{
  return size;
}

//////////////////////////////////////////////////////////////////////
//initialiseCardDeck(int setNum)
//////////////////////////////////////////////////////////////////////

void cardDeck::initialiseCardDeck(int setNumSets/*,cardDeck deck*/)
{

  /// Should be code here to create setNumsets amount of decks
  // and fill them
  int counter = 0;
  for (int suit = card::Clubs; suit <= card::Diamonds; ++suit)
  {
    for (int rank = card::Ace; rank <= card::King; ++rank)
    {
    if (counter < size)
    {

    card cc((card::Suit) suit, (card::Rank) rank);
    cdeck[counter] = cc;}
    counter = counter + 1;
    }
  }

}

void cardDeck::createInitialisedCardDeck(int s)
{
  int counter = 0;
  for (int suit = card::Clubs; suit <= card::Diamonds; ++suit)
  {
    for (int rank = card::Ace; rank <= card::King; ++rank)
    {
    if (counter < size)
    {

    card cc((card::Suit) suit, (card::Rank) rank);
    cdeck[counter] = cc;}
    counter = counter + 1;
    }
  }

}

//////////////////////////////////////////////////////////////////////
// deleteCard()
//////////////////////////////////////////////////////////////////////

void cardDeck::deleteCard()
{
  // If less that the current size
  // then it is better to just reduce the
  // index total size rather than waste
  // processing copying
  //
  // Simple and effective

  // if (size > 0){size = size-1;}
  try {
        size = size - 1;
        if(size < 0)
        {throw cardDeckException("Size in the negative -- incorrect");}
      }
        catch(cardDeckException ex)
        {cout << ex.getException() << endl; ++size;}
}

//////////////////////////////////////////////////////////////////////
// deleteCard()
//////////////////////////////////////////////////////////////////////

card cardDeck::getACard()
{
  // If less that the current size
  // then it is better to just reduce the
  // index total size rather than waste
  // processing copying
  //
  // Simple and effective

  // if (size > 0){size = size-1;}

  card temp;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // THIS THROWS TO MAIN --- Needs Matching CATCH
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  try {
        int size2 = size - 1;
        if(size2 < 0)
        {throw cardDeckException("Size in the negative -- incorrect");}
      else {temp= cdeck[size];size = size - 1;}
      }
        catch(cardDeckException ex)
        {cout << ex.getException() << endl;}

        return temp;
    }

//////////////////////////////////////////////////////////////////////
// addCard()
//////////////////////////////////////////////////////////////////////

void cardDeck::addCard(card passedCard)
{
  /*
  need to make sure that cards cant be added
  above 52

  Also the delete function just
  make an index unaccessable
  so test to make sure index are
  just not hidden before wasting
  resouces --- Note to Self

  Correct Error handling too
  */
  int i;
  card *newDeck;

  try{
      int newsize = size +1;
      if (newsize > 52)
      {throw cardDeckException("Size is incorrect");}

      newDeck = new card[newsize];
      for (i=0; i<newsize; i++)
        {
        if (i<size) newDeck[i] = cdeck[i];
        else newDeck[i] = passedCard;
        }
        // deallocate old memory
        delete[] cdeck;
        // use newdata as data
        cdeck = newDeck;
        size = newsize;
      }
  catch(cardDeckException ex)
  {cout << ex.getException() << endl;size = size - 1;}
  catch (bad_alloc memex)
  {cerr << "Memory allocation Issue"  << endl;throw memex;}

}

//////////////////////////////////////////////////////////////////////
// lookAtCard(index)
// provides access (both reading and writing) to the top element
// of the card deck.
//
// Does not modify the Deck
//
// parameter: index - index of element to be accessed
//////////////////////////////////////////////////////////////////////

card &cardDeck::lookAtCard(int index) const
{
  if (index > size){throw cardDeckException("Index out of range");}
  else {return cdeck[index];}
  return cdeck[index];
}

///////////////////////////////////////////////////////////
//
// Incomplete Funtions
//////////////////////

//////////////////////////////////////////////////////////////////////
//moveAllCards(destination): Moves all cards
//from the CardDeck source to CardDeck destination.
//
//Pre: source and destination are valid instantiations of the ADT CardDeck.
//Post: All cards have been moved from source (which now is empty)
//to destination (which now contains additionally all cards previously in source)
//////////////////////////////////////////////////////////////////////

int &cardDeck::moveAllCards(int &destination)
{
  return destination;
}

//////////////////////////////////////////////////////////////////////
// shuffleDeck()
//
//
//Uses a starting seed from time and generates a random sequence
//this sequecnce does not end up distributing uniformly
//when attempting to generate a 52 number sequence,
//so an "Mangled" Bubble swap has been used, where one
//side of the swap is a random number(r) in range up to the
//current counter postition counter (i).
//This swaps at random, and so it doesnt matter if the same index
//is swaped at some stage as both index objects
//remain in the Deck regardless.
//The counter decrements
//
//pre:a valid Deck exists
//post:the contents of that deck have been shuffled
//////////////////////////////////////////////////////////////////////

void cardDeck::shuffleDeck()
{
    srand (time(0));
    for (int i = 52-1; i > 0; i--)
    {
      int r = rand() % (i+1);
      card temp = cdeck[i];
      cdeck[i] = cdeck[r];
      cdeck[r] = temp;
    }
}

void cardDeck::deleteCardDeck()
{


}

void cardDeck::fillcards()
{
  int counter = 0;
  for (int suit = card::Clubs; suit <= card::Diamonds; ++suit)
  {
    for (int rank = card::Ace; rank <= card::King; ++rank)
    {
      counter = counter + 1;
      card cc((card::Suit) suit, (card::Rank) rank);
      cdeck[counter] = cc;
    }
  }
}

//////////////////////////////////////////////////////////////////////
//
// Development Testing Funtions
//
//////////////////////////////////////////////////////////////////////

void cardDeck::testListContents()
{
    for (int i=0; i<size+2; ++i)
    {

    }
}

void cardDeck::fill()
{
  int counter = 0;
  for (int suit = card::Clubs; suit <= card::Diamonds; ++suit)
  {
    for (int rank = card::Ace; rank <= card::King; ++rank)
    {
      if (counter < size)
      {
        card cc((card::Suit) suit, (card::Rank) rank);
        cdeck[counter] = cc;}
        counter = counter + 1;
      }
  }
}

card &cardDeck::accessCard(int index)
{
  return cdeck[index];
}
