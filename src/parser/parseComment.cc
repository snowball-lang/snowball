
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>
#include <regex>
#include <string>

namespace snowball::parser {
using CommentType = Syntax::Comment;

static const std::regex tagRegex("@(\\w+)\\s*(.*)");

CommentType* Parser::parseDocstring(std::string p_content) {

  auto comment = m_current.getComment();
  bool valid = true;
  bool isMultiLine = false;
  std::map<std::string, std::string> tags;
  std::string content;

  if (utils::startsWith(comment, "///")) {
    comment = comment.substr(3);
  } else if (utils::startsWith(comment, "/**")) {
    comment = comment.substr(3);
    comment = comment.substr(0, comment.size() - 2);
    isMultiLine = true;
  } else {
    valid = false;
  }
  
  if (valid) {
    int paramCount = 0;
    auto lines = utils::split(comment, "\n");
    std::smatch matches;
    for (auto& line : lines) {
      if (std::regex_search(line, matches, tagRegex)) {
        std::string tag = matches[1];
        std::string content = matches[2];

        if (tag == "param") {
          tag = "param$" + std::to_string(paramCount);
        }
        tags[tag] = content;     
      } else {
        auto trim = line;
        utils::replaceAll(trim, " ", "");
        if (utils::startsWith(trim, "*")) {
          auto idx = line.find_first_of("*");
          line = line.substr(idx + 1);
        }
        if (!line.empty()) {
          content += line + "\n";
        }
      }
    } 

    return new CommentType(tags, content, valid);
  }

  return nullptr;
}

} // namespace snowball::parser
