all:
	g++ card.cpp cardDeck.cpp cardDeckContainer.cpp cardDeckException.cpp main.cpp -o cardGameBinary

clean:
	rm -rf *o cardGameBinary
