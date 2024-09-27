#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <regex>
#include <emscripten/emscripten.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

int main() {}

std::string getYoutubeIdFromUrl(const std::string& url) {
    std::regex pattern(R"(.*(?:youtu\.be/|v/|u/\w/|embed/|watch\?v=)([^#&?]*).*)");
    std::smatch matches;
    if (std::regex_match(url, matches, pattern) && matches.size() > 1) {
        return matches[1].str();
    }
    return "";
}

EXTERN EMSCRIPTEN_KEEPALIVE std::string embed(const std::string& video) {
    return "https://www.youtube.com/embed/" + getYoutubeIdFromUrl(video);
}

EXTERN EMSCRIPTEN_KEEPALIVE std::string localize(double num) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(3) << num;
    return out.str();
}

EXTERN EMSCRIPTEN_KEEPALIVE std::string getThumbnailFromId(const std::string& id) {
    return "https://img.youtube.com/vi/" + id + "/mqdefault.jpg";
}

EXTERN EMSCRIPTEN_KEEPALIVE std::vector<int> shuffle(std::vector<int> array) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(array.begin(), array.end(), g);
    return array;
}
