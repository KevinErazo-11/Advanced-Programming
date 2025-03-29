#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  std::vector<std::string::const_iterator> iterators = find_all(source.begin(), source.end(), ::isspace);
  iterators.insert(iterators.begin(), source.begin());
  iterators.push_back(source.end());

  std::set<Token> tokens;
  std::transform(iterators.begin(), iterators.end() - 1, iterators.begin() + 1, 
                 std::inserter(tokens, tokens.begin()), 
                 [&source](auto it1, auto it2) { return Token(source, it1, it2); });
  
  std::erase_if(tokens, [](const Token& t) { return t.content.empty(); });
  
  return tokens;
}


std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  auto misspelled_tokens = source | std::ranges::views::filter([&](const Token& token) {
    return !dictionary.contains(token.content);
  });

  auto misspellings = misspelled_tokens | std::ranges::views::transform([&](const Token& token) {
    auto suggestions = dictionary | std::ranges::views::filter([&](const std::string& word) {
      return levenshtein(token.content, word) == 1;
    });

    return Mispelling{token, {suggestions.begin(), suggestions.end()}};
  }) | std::ranges::views::filter([](const Mispelling& misp) {
    return !misp.suggestions.empty();
  });

  return {misspellings.begin(), misspellings.end()};
}



/* Helper methods */

#include "utils.cpp"
