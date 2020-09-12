#include "stats.h"

#include <algorithm>

Stats::Stats()
{
	for (size_t i = 0; i < 5; ++i)
	{
		method_stats[methods.at(i)] = 0;
		uri_stats[uris.at(i)] = 0;
	}
	uri_stats[uris.at(5)] = 0;
}

void Stats::AddMethod(string_view method)
{
	const auto iter = find(methods.begin(), methods.end(), method);

	if (iter == methods.end())
		++method_stats[*(prev(methods.end()))];
	else
	{
		++method_stats[methods.at(iter - methods.begin())];
	}

}

void Stats::AddUri(string_view uri)
{
	const auto iter = find(uris.begin(), uris.end(), uri);

	if (iter == uris.end())
		++uri_stats[*(prev(uris.end()))];
	else
		++uri_stats[uris.at(iter - uris.begin())];
}

const map<string_view, int>& Stats::GetMethodStats() const
{
	return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const
{
	return uri_stats;
}

HttpRequest ParseRequest(string_view line)

{
	auto pos = line.find_first_not_of(' ');
	line.remove_prefix(pos);

	pos = line.find(' ');
	const auto method = string_view(line.data(), pos);
	line.remove_prefix(pos + 1);

	pos = line.find(' ');
	const auto uri = string_view(line.data(), pos);
	line.remove_prefix(pos + 1);

	const auto version = string_view(line.data());

	return { method, uri, version };
}
