#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

const std::string keymap_filepath = "keyboards/zsa/moonlander/keymaps/kvs/keymap.c";

const int LINES_PER_LAYOUT = 5;
const int KEYS_PER_TOP_ROW = 14;

const std::string INDENT = "\t\t";

void trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.cbegin(), s.cend(), [](int c) { return !std::isspace(c); }));
    s.erase(std::find_if(s.crbegin(), s.crend(), [](int c) { return !std::isspace(c); }).base(), s.cend());
}

struct LineInfo {
    std::string text;
    int         items;
    int         longest;
};
LineInfo get_line_info(std::string line) {
    int  items    = 0;
    int  longest  = 0;
    int  current  = 0;
    bool in_paren = false;
    for (const char c : line) {
        switch (c) {
            case ' ':
                break;
            case ',':
                if (in_paren) {
                    ++current;
                    break;
                }

                ++items;
                longest = std::max(longest, current);
                current = 0;
                break;
            default:
                ++current;
                if (c == '(') {
                    in_paren = true;
                }
                if (c == ')') {
                    in_paren = false;
                }
        }
    }
    return {line, items, longest};
}

std::string format_line(std::string line, const int items, const int longest) {
    const int   num_spaces          = KEYS_PER_TOP_ROW - items;
    std::string formatted_line      = INDENT;
    int         current_item_length = 0;
    bool        in_paren            = false;
    int         word_count          = 0;
    trim(line);
    for (const char c : line) {
        switch (c) {
            case ' ':
                break;
            case ',':
                if (in_paren) {
                    ++current_item_length;
                    formatted_line += c;
                    break;
                }

                formatted_line += ',';
                formatted_line += std::string(longest + 1 - current_item_length, ' ');
                current_item_length = 0;
                ++word_count;

                if (word_count == (items - num_spaces) / 2) {
                    for (int i = 0; i < num_spaces; ++i) {
                        formatted_line += std::string(longest + 2, ' ');
                    }
                }

                break;
            default:
                ++current_item_length;
                formatted_line += c;
                if (c == '(') {
                    in_paren = true;
                }
                if (c == ')') {
                    in_paren = false;
                }
        }
    }

    return formatted_line;
}

std::string format_thumb_line(std::string line, int longest) {
    const int line_length = KEYS_PER_TOP_ROW * (longest + 2); // +1 for ' ' and +1 for ','

    trim(line);
    std::cout << line << "\n";

    const std::string pad = std::string((line_length - line.size()) / 2, ' ');

    std::string result = INDENT + pad;

    bool in_paren = false;
    for (char c : line) {
        switch (c) {
            case ' ':
                break;
            case ',':
                if (in_paren) {
                    result += c;
                    break;
                }
                result += ", ";
                break;
            default:
                result += c;

                if (c == '(') {
                    in_paren = true;
                }
                if (c == ')') {
                    in_paren = false;
                }
        }
    }

    result += pad;
    return result;
}

int main() {
    std::ifstream in_file(keymap_filepath);
    if (!in_file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::vector<std::string> new_lines;

    std::string line;
    while (std::getline(in_file, line)) {
        if (line.find("LAYOUT(") != std::string::npos) {
            new_lines.push_back(line);

            // first get line info...
            LineInfo lines_info[LINES_PER_LAYOUT];
            int      longest = 0;
            for (int i = 0; i < LINES_PER_LAYOUT; ++i) {
                std::getline(in_file, line);
                lines_info[i] = get_line_info(line);
                longest       = std::max(longest, lines_info[i].longest);
            }

            // ...then update lines
            for (int i = 0; i < LINES_PER_LAYOUT; ++i) {
                new_lines.push_back(format_line(lines_info[i].text, lines_info[i].items, longest));
            }

            // finally update thumb line
            getline(in_file, line);
            new_lines.push_back(format_thumb_line(line, longest));
        } else {
            new_lines.push_back(line);
        };
    }

    in_file.close();

    std::ofstream out_file("keymap.c");
    if (!out_file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    for (const auto line : new_lines) {
        out_file << line << "\n";
    }
}
