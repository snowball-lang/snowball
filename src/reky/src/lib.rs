use anyhow::Result;

#[cxx::bridge(namespace = "snowball")]
mod ffi {
  extern "Rust" {
    fn lib_reky_entry() -> bool;
  }
}

/// @brief Entry point for the Reky library
/// @note We dont return a Result<> here because we
///       it's easier to handle the error in the C++ side
///     We will be following POSIX error handling, where
///     0 is success and 1 is failure
pub fn lib_reky_entry() -> bool {
  false
}

