use anyhow::Result;
use cxx::{type_id, ExternType};
use yscl::prelude::*;
use yscl::prelude::ParseError;
use colored::*;

// Clowder package manager
// The Clowder package manager will download and install packages
// from the snowball package repository. It will also manage
// the dependencies of the packages.
//
// Clowder will build a module graph of the packages for the
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

#[cxx::bridge(namespace = "snowball::clowder")]
mod ffi {
  #[derive(Clone, Debug)]
  struct Module {
    pub path: String, // Path of the source file  "src/hello/world.sn"
    pub name: String, // Name of the module. e.g. ^- "std::hello::world"
  
    pub cache: bool   // If the module is cached
  }

  #[derive(Clone, Debug)]
  struct Dependency {
    pub name: String,  // Name of the dependency
    pub version: String // Version of the dependency
  }
  
  #[derive(Clone, Debug)]
  struct PackageConfig {
    pub name: String,                  // Name of the package
    pub version: String,               // Version of the package
    pub dependencies: Vec<Dependency>, // Dependencies of the package
    pub source: String                 // Source of the package
  }

  struct Context {
    home: String,
    workspace: String,
    debug: bool
  }
  
  #[derive(Clone, Debug)]
  struct Package {
    pub config: PackageConfig, // Package configuration
    pub modules: Vec<Module>   // Modules in the package
  }

  extern "Rust" {
    fn lib_clowder_entry(ctx: &Context) -> Result<Vec<Package>>;
  }
}

// Group: clowder library

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

pub struct PackageManager<'a> {
  pub packages: Vec<Package>,// List of packages
      cache_file: String,    // Path to the cache file
      cached: Vec<Package>,  // Cached packages

      ctx: &'a ffi::Context      // C++ context
}

fn parser_error_to_string(err: ParseError) -> String {
  match err {
    ParseError::UnexpectedChar(char, pos) => format!("Unexpected character '{}' at position {}", char, pos),
    ParseError::UnexpectedEoi => "Unexpected end of input".to_string(),
    ParseError::DuplicateKey(key, ..) => format!("Duplicate key '{}'", key)
  }
}

impl<'a> PackageManager<'a> {
  pub fn new(ctx: &'a ffi::Context) -> Self {
    PackageManager {
      packages: Vec::new(),
      cache_file: String::new(),
      cached: Vec::new(),
      ctx: ctx
    }
  }

  fn debug(&self, msg: &str) {
    if self.ctx.debug {
      println!("{}: {}", "debug[clowder]".purple().bold(), msg);
    }
  }

  fn add_package(&mut self, package: Package) {
    self.packages.push(package);
  }

  fn get_config_from(&self, path: &str) -> Result<PackageConfig, std::io::Error> {
    self.debug(&format!("Getting config from {}", path));
    let config_file = format!("{}/sn.conf", path);
    let data = std::fs::read_to_string(config_file)?;
    let parsed_raw = parse_doc(&data);
    if parsed_raw.is_err() {
      return Err(std::io::Error::new(std::io::ErrorKind::InvalidData, format!("Invalid config file. {}", parser_error_to_string(parsed_raw.err().unwrap()))));
    }
    let parsed = parsed_raw.unwrap();
    let name = parsed.get("name");
    let version = parsed.get("version");
    let dependencies = parsed.get("dependencies");
    if name.is_none() || version.is_none() {
      return Err(std::io::Error::new(std::io::ErrorKind::InvalidData, "Invalid config file. Name or version is missing"));
    }
    let package_name = name.unwrap().clone().atom().unwrap().value;
    let mut needs = vec![];
    if dependencies.is_some() {
      let deps = dependencies.unwrap().clone().map();
      if deps.is_none() {
        return Err(std::io::Error::new(std::io::ErrorKind::InvalidData, "Invalid config file. Dependencies is not a map"));
      }
      for entry in deps.unwrap().entries.iter() {
        let key = entry.key.clone().to_string();
        let value = entry.value.clone().atom().unwrap().value;
        let dep_data = ffi::Dependency {
          name: key,
          version: value
        };
        self.debug(&format!(" [{}] needs {:?}", package_name, dep_data));
        needs.push(dep_data);
      }
    }
    let mut source = parsed.get("src");
    let mut sourecStr = "./src".to_string();
    if source.is_none() {
      source = parsed.get("source");
    }
    if source.is_some() {
      sourecStr = source.unwrap().clone().atom().unwrap().value.to_string();
    }
    self.debug(&format!(" [{}] version {}", package_name, version.unwrap().clone().atom().unwrap().value));
    Ok(PackageConfig {
      name: package_name,
      version: version.unwrap().clone().atom().unwrap().value,
      dependencies: needs,
      source: sourecStr
    })
  }

  fn get_module_name(&self, path: &str, parent_path: &str) -> String {
    // remove the parent path from the module name
    let mut name = path.replace(&parent_path, "");
    if name.starts_with("/") {
      name = name[1..].to_string();
    }
    name = name.replace("/", "::");
    name = name.replace(".sn", "");
    name
  }

  fn collect_modules(&self, source: &str, current_dir: &std::path::Path) -> Result<Vec<Module>, std::io::Error> {
    // Recursively iterate all files and add them to the package
    let mut modules = Vec::new();
    for entry in std::fs::read_dir(current_dir)? {
      let entry = entry?;
      let path = entry.path();
      if path.is_dir() {
        let sub_modules = self.collect_modules(source, &path)?;
        modules.extend(sub_modules);
      } else {
        let path_str = path.to_str().unwrap();
        if path_str.ends_with(".sn") {
          let module = Module {
            path: path_str.to_string(),
            name: self.get_module_name(path_str, source),
            cache: false
          };
          self.debug(&format!(" [{}] found module {}", path_str, module.name));
          modules.push(module);
        }
      }
    }
    Ok(modules)
  }

  fn get_full_source_path(&self, current_dir: &std::path::Path, source: &str) -> String {
    let mut source_path = current_dir.to_path_buf();
    source_path.push(source);
    // clean up the path
    source_path = source_path.canonicalize().unwrap();
    source_path.to_str().unwrap().to_string()
  }

  fn create_recursive_package(&mut self, current_dir: &std::path::Path) -> Result<(), std::io::Error> {
    let mut package = Package::new(self.get_config_from(current_dir.to_str().unwrap())?);
    let abs_source = self.get_full_source_path(current_dir, &package.config.source);
    self.debug(&format!(" [{}] found package {}", current_dir.to_str().unwrap(), package.config.name));
    let modules = self.collect_modules(&abs_source, current_dir)?;
    for module in modules {
      package.add_module(module.clone());
    }
    self.add_package(package.clone());
    Ok(())
  }

  pub fn entry(&mut self) -> anyhow::Result<Vec<Package>> {
    let current_dir = std::env::current_dir().unwrap();
    self.create_recursive_package(&current_dir)?;
    Ok(self.packages.clone())
  }
}

// Group: Entry point

/// @brief Entry point for the clowder library
/// @note Any failures will be cached with c++ exception
/// @see https://cxx.rs/binding/result.html
pub fn lib_clowder_entry(ctx: &ffi::Context) -> anyhow::Result<Vec<Package>> {
  let mut package_manager = PackageManager::new(ctx);
  package_manager.entry()
}

