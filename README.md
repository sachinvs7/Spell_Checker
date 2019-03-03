# Spell_Checker

Implementing a spell checker tool in C that determines if a given word is spelled correctly based on a dictionary lookup. When the word is not spelled correctly, it will provide a list of similar-sounding words based on implementation of the Metaphone algorithm, and orders the results based on their edit distance from the string that the user types.

An example would be, if the user types in "Speling", the suggestions would be "Spelling", "Spending", "Spoiling" etc.

The Metaphone is a phonetic algorithm, [details.](https://en.wikipedia.org/wiki/Metaphone)

Update 1 : Succesfully implemented the Metaphone algorithm, refer meta.c file.
