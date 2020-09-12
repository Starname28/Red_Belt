#pragma once
#include "http_request.h"

//#include <string_view>
#include <array>
#include <map>
#include <algorithm>

using namespace std;

class Stats {
public:
	Stats();

	void AddMethod(string_view method);

	void AddUri(string_view uri);

	const map<string_view, int>& GetMethodStats() const;

	const map<string_view, int>& GetUriStats() const;

private:
	map<string_view, int> method_stats;
	map<string_view, int> uri_stats;

	array<string, 5> methods = { "GET", "POST", "PUT", "DELETE", "UNKNOWN" };
	array<string, 6> uris = { "/", "/order", "/product", "/basket", "/help", "unknown" };
};

HttpRequest ParseRequest(string_view line);