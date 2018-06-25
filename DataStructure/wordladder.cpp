#include "stdafx.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

std::unordered_map<std::string, std::string> findChain(std::unordered_map<std::string, std::vector<std::string>> &adjacentWords,
	const std::string &first)
{
	std::unordered_map<std::string, std::string> previousWords;
	std::queue<std::string> qwords;
	qwords.push(first);

	while (!qwords.empty())
	{
		std::string  item = qwords.front();
		qwords.pop();


		for (auto &current : adjacentWords[item])
		{
			if (previousWords.find(current) == previousWords.end())
			{
				previousWords.insert(std::pair<std::string, std::string>(current, item));
				qwords.push(current);
			}
		}
	}

	previousWords[first] = "";
	return previousWords;
}


std::vector<std::string> getChainFromPreviousMap(const std::unordered_map<std::string, std::string> &previousWords,
	const std::string &first, const std::string &second)
{

	std::vector<std::string> result;
	std::string current = second;
	auto &prev = const_cast<std::unordered_map<std::string, std::string>&> (previousWords);

	while (current != "")
	{
		result.push_back(current);
		current = prev[current];
	}
	std::reverse(result.begin(), result.end());
	return result;
}