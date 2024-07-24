use anyhow::Result;

// Reky package manager
// The reky package manager will download and install packages
// from the snowball package repository. It will also manage
// the dependencies of the packages.
//
// Reky will build a module graph of the packages for the
// compiler to use. The module graph will be used to resolve
// dependencies and to build the packages in the correct order.
//
// The module graph will be stored in a file in the project
// directory. The file can be used as a cache to speed up
// the build process.
//
// We separate the term "package" from "module" to avoid
// confusion. A package is a collection of modules that
// can be installed and used in a project and Snowball doesn't
// really care about them. A module is a single file that
// contains code that can be imported and used in a project.
//
// The package manager will also manage the project's
// configuration file. The configuration file will contain
// the project's dependencies and other settings.
//
// Any changes for Module, PackageConfig, and Package should
// be reflected in the C++ API.


// Group: Export to the C++ API

#[cxx::bridge(namespace = "snowball")]
mod ffi {
  #[derive(Clone, Debug)]
  struct Module {
    pub path: String, // Path of the source file  "src/hello/world.sn"
    pub name: String, // Name of the module. e.g. ^- "std::hello::world"
  
    pub cache: bool   // If the module is cached
  }
  
  #[derive(Clone, Debug)]
  struct PackageConfig {
    pub name: String,   // Name of the package
    pub version: String // Version of the package
  }
  
  #[derive(Clone, Debug)]
  struct Package {
    pub config: PackageConfig, // Package configuration
    pub modules: Vec<Module>   // Modules in the package
  }

  extern "Rust" {
    fn lib_reky_entry() -> Result<Vec<Package>>;
  }
}

// Group: Reky library

use crate::ffi::Package;
use crate::ffi::PackageConfig;
use crate::ffi::Module;

impl Package {
  pub fn new(config: PackageConfig) -> Self {
    Package {
      config,
      modules: Vec::new()
    }
  }

  pub fn add_module(&mut self, module: Module) {
    self.modules.push(module);
  }
}

pub struct PackageManager {
  pub packages: Vec<Package> // List of packages
}

impl PackageManager {
  pub fn new() -> Self {
    PackageManager {
      packages: Vec::new()
    }
  }

  pub fn add_package(&mut self, package: Package) {
    self.packages.push(package);
  }

  pub fn entry(&self) -> anyhow::Result<Vec<Package>> {
    println!("Hello from Reky!");
    Ok(self.packages.clone())
  }
}

// Group: Entry point

/// @brief Entry point for the Reky library
/// @note Any failures will be cached with c++ exception
/// @see https://cxx.rs/binding/result.html
pub fn lib_reky_entry() -> anyhow::Result<Vec<Package>> {
  let mut package_manager = PackageManager::new();
  Err(anyhow::anyhow!("Not implemented\nhello"))
}

