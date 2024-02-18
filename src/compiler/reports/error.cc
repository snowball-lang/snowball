
#include <fmt/format.h>
#include <fmt/color.h>

#include "compiler/reports/dbg.h"
#include "compiler/reports/error.h"
#include "compiler/utils/logger.h"
#include "compiler/globals.h"


namespace snowball {
using namespace utils;

void Error::print() {
  auto contents = globals::read_file(get_location().file);
  auto dbg_info = reports::DebugSourceLocation::from_file(contents, get_location().line);

  Logger::error(highlight_quotes(message));
  fmt::print(fmt::text_style(fmt::emphasis::bold), "  at : [{}:{}:{}{}\n", 
    fmt::styled(get_location().file, fmt::fg(fmt::terminal_color::bright_blue)), 
    fmt::styled(get_location().line, fmt::fg(fmt::terminal_color::white) | fmt::emphasis::bold), 
    fmt::styled(get_location().column, fmt::fg(fmt::terminal_color::white) | fmt::emphasis::bold),
    fmt::styled("]", fmt::emphasis::bold));
  fmt::print(fmt::text_style(fmt::emphasis::bold), "     |\n");
  if (!dbg_info.line_before_before.empty()) {
    fmt::print(fmt::text_style(fmt::emphasis::bold), "{:>4} | {}\n", get_location().line - 2, fmt::styled(dbg_info.line_before_before, fmt::fg(fmt::terminal_color::black)));
  }
  if (!dbg_info.line_before.empty()) {
    fmt::print(fmt::text_style(fmt::emphasis::bold), "{:>4} | {}\n", get_location().line - 1, fmt::styled(dbg_info.line_before, fmt::fg(fmt::terminal_color::black)));
  }
  fmt::print(fmt::text_style(fmt::emphasis::bold), "{:>4} | {}\n", get_location().line, fmt::styled(dbg_info.line, fmt::fg(fmt::terminal_color::black)));
  fmt::print(fmt::text_style(fmt::emphasis::bold), "     | ");
  for (unsigned int i = 0; i < get_location().column; i++) {
    fmt::print(" ");
  }
  for (unsigned int i = 0; i < get_location().length; i++) {
    fmt::print("{}", fmt::styled("^", fmt::fg(fmt::terminal_color::red) | fmt::emphasis::bold));
  } 
  if (!info.highlight.empty()) {
    fmt::print(" {}", fmt::styled(info.highlight, fmt::fg(fmt::terminal_color::red) | fmt::emphasis::bold));
  }
  fmt::print("\n");
  if (!dbg_info.line_after.empty()) {
    fmt::print(fmt::text_style(fmt::emphasis::bold), "{:>4} | {}\n", get_location().line + 1, fmt::styled(dbg_info.line_after, fmt::fg(fmt::terminal_color::black)));
  }
  if (!dbg_info.line_after_after.empty()) {
    fmt::print(fmt::text_style(fmt::emphasis::bold), "{:>4} | {}\n", get_location().line + 2, fmt::styled(dbg_info.line_after_after, fmt::fg(fmt::terminal_color::black)));
  }
  fmt::print(fmt::text_style(fmt::emphasis::bold), "     |\n");
  if (!info.help.empty()) {
    fmt::print(fmt::text_style(fmt::emphasis::bold), " {}: {}\n", fmt::styled("help", fmt::fg(fmt::terminal_color::bright_yellow) | fmt::emphasis::bold), highlight_quotes(info.help));
  }
  if (!info.note.empty()) {
    fmt::print(fmt::text_style(fmt::emphasis::bold), " {}: {}\n", fmt::styled("note", fmt::fg(fmt::terminal_color::bright_blue) | fmt::emphasis::bold), highlight_quotes(info.note));
  }
  if (!info.see.empty()) {
    fmt::print(fmt::text_style(fmt::emphasis::bold), "  {}: {}\n", fmt::styled("see", fmt::fg(fmt::terminal_color::bright_green) | fmt::emphasis::bold), highlight_quotes(info.see));
  }
  fmt::print(fmt::text_style(fmt::emphasis::bold), "     |\n\n");
}
}
