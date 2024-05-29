

#include <cassert>
#include <filesystem>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

Parser::Parser(const Ctx& ctx, const std::shared_ptr<SourceFile>& file, const std::vector<Token>& tokens)
    : ctx(ctx), file(file), tokens(tokens) {
  assert(!tokens.empty());
  current = tokens[0]; // we know that there is at least one token
}

namespace {

std::string remove_sub_folders(const std::string& full, const std::string& sub) {
  // Split full path into directories
  std::istringstream fullStream(full);
  std::vector<std::string> fullDirs;
  std::string dir;
  while (std::getline(fullStream, dir, '/')) {
    fullDirs.push_back(dir);
  }  
  // Split subpath into directories
  std::istringstream subStream(sub);
  std::vector<std::string> subDirs;
  while (std::getline(subStream, dir, '/')) {
    subDirs.push_back(dir);
  }
  // Find the position of subpath in full path
  size_t pos = full.find(sub);  
  // If subpath is not found, return the full path
  if (pos == std::string::npos) {
    return full;
  }
  // Find the position of the second occurrence of '/' after the subpath
  size_t secondSlash = full.find('/', pos + sub.length());  
  // If second slash is not found, return the full path
  if (secondSlash == std::string::npos) {
    return full;
  }
  // Extract the part after the second slash
  std::string result = full.substr(secondSlash + 1);
  // Find the position of the next '/' after the second slash
  size_t nextSlash = result.find('/');  
  // If next slash is found, remove everything before it
  if (nextSlash != std::string::npos) {
    result = result.substr(nextSlash + 1);
  }
  // Prepend the directory right before the subpath
  auto result_path = result;
  result_path = result_path.substr(0, result_path.find_first_of('.'));
  return result_path;
}
}

Module Parser::parse() {
  auto root_name = ctx.package_config.value().project.name;
  // Subtract from the path until we find the src dir
  auto src_dir = std::filesystem::path(ctx.package_config.value().project.src);
  auto dir = std::filesystem::path(file->get_path());
  // Find the first instance of the src_dir
  auto new_dir = remove_sub_folders(dir, src_dir);
  auto path = NamespacePath::from_file(root_name + "/" + new_dir);
  bool is_main = (root_name == ctx.root_package_config.value().project.name);
  try {
    return Module(parse_top_level(), path, is_main);
  } catch (const StopParsing&) {
    return Module(ast::TopLevelAst(), path, is_main); // we are gonna error out anyway
  }
}

Token Parser::peek(int offset, bool safe) {
  if (tok_index + offset + 1 >= tokens.size()) {
    if (safe) {
      return Token { 
        .type = Token::Type::Eof, 
        .location = std::make_pair(0, 0)
      };
    }
    sn_assert(false, "Unexpected end of file");
  }
  return tokens[tok_index + 1 + offset];
}

void Parser::next(int offset) {
  if (tok_index + offset >= tokens.size()) {
    tok_index = tokens.size() - 1;
    return;  
  }
  tok_index += offset;
  current = tokens[tok_index];
}

void Parser::prev() {
  if (tok_index == 0) {
    return;
  }
  tok_index--;
  current = tokens[tok_index];
}

bool Parser::is(Token::Type type) {
  return current.type == type;
}

bool Parser::is(Token::Type type, const Token& tok) {
  return tok.type == type;
}

void Parser::err(const std::string& message, const Error::Info& info, Error::Type type, bool fatal) {
  SourceLocation loc(current.location.first, current.location.second, current.get_width(), file);
  add_error(E(message, loc, info, type));
  if (fatal && type != Error::Type::Warn)
    throw StopParsing();
}

const Token& Parser::expect(Token::Type type, const std::string& expectation) {
  return expect(type, expectation, Token::Type::Eof);
}

const Token& Parser::expect(Token::Type type, const std::string& expectation, Token::Type recover) {
  return expect(type, expectation, std::vector<Token::Type> { recover });
}

const Token& Parser::expect(Token::Type type, const std::string& expectation, std::vector<Token::Type> recover) {
  if (is(type)) {
    return current;
  }
  err(fmt::format("Unexpected token '{}' found!", current), Error::Info {
    .highlight = fmt::format("Token '{}' is not expected here", current),
    .help = fmt::format("Expected a token to satisfy '{}'", expectation),
    .note = has_errors() ? "This error might be caused by error recovery activated by another\nerror before this one" : ""
  }, Error::Type::Err, recover.empty() || recover[0] == Token::Type::Eof);
  _recover(recover); // It already skips Eof if it is Eof
  return current;
}

void Parser::_recover(std::vector<Token::Type> tys) {
  if (tys.empty()) {
    return;
  } else if (tys[0] == Token::Type::Eof) {
    sn_assert(tys.size() == 1, "Eof should be the only token in the recovery set");
    return;
  }

  while (!is(Token::Type::Eof)) {
    for (unsigned int i = 0; i < tys.size(); i++) {
      if (tys[i] == Token::Type::Eof) {
        sn_assert(false, "Eof should be the only token in the recovery set")
      }
      if (is(tys[i])) {
        prev();
        return;
      }
    }
    next();
  }
  if (is(Token::Type::Eof)) {
    err("Unexpected end of file while trying to recover from a previous error", Error::Info {
      .highlight = "Unexpected end of file",
      .help = "Found an unexpected end of file while trying to recover from a previous error",
      .note = "This error might be caused by error recovery activated by another\nerror before this one"
    }, Error::Type::Err, true);
  }
}

SourceLocation Parser::loc() const {
  return SourceLocation(current.location.first, current.location.second, current.get_width(), file);
}

}
}
