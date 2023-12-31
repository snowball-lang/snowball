
#include "Manager.h"

namespace fs = std::filesystem;

namespace snowball {
namespace pm {

Manager::Manager(toml::parse_result p_package, bool p_silent, std::string p_cwd, std::string p_configFolder) {
  package = p_package;
  silent = p_silent;
  cwd = p_cwd;
  configFolder = p_configFolder;
}

std::string Manager::getGit() {
  std::string git = "git";
  if (getenv("SNOWBALL_GIT_PATH") != NULL) {
    git = getenv("SNOWBALL_GIT_PATH");
  }
  return git;
}

int Manager::runAsMain() {
  if (!package["dependencies"]) return EXIT_SUCCESS;
  (void)chdir(((fs::path)configFolder/"deps").c_str());

  // example: "owner/repo" = { version = "1.0.0" }
  auto packages = package["dependencies"].as_table();
  
  packages->for_each([&](auto&& key, auto&& value) {
    auto packageStr = (std::string)key.str();

    // split package into owner and repo
    auto parts = utils::list2vec(utils::split(packageStr, "/"));
    if (parts.size() != 2) {
      throw SNError(Error::PM_ERROR, FMT("Invalid package name '%s'.\n\tExpected the following format: '{owner}/{package}'", packageStr.c_str()));
    }

    auto owner = parts[0];
    auto repo = parts[1];

    auto packageData = package["dependencies"][packageStr];

    Package packageInfo;
    packageInfo.owner = owner;
    packageInfo.repo = repo;
    packageInfo.version = packageData["version"].value_or<std::string>("latest");
    packageInfo.provider = packageData["provider"].value_or<std::string>("https://github.com");
  
    auto result = install(packageInfo);
    if (result != EXIT_SUCCESS) {
      throw SNError(Error::PM_ERROR, FMT("Failed to install package %s", packageStr.c_str()));
    }
  });

  (void)chdir(cwd.c_str());

  return EXIT_SUCCESS;
}

bool Manager::isInstalled(Package p_package) {
  // check on folder structure
  auto packageFolder = (fs::path)configFolder / "deps" / p_package.owner / p_package.repo;
  return fs::is_directory(packageFolder);
}

int Manager::install(Package p_package) {
  if (isInstalled(p_package)) return EXIT_SUCCESS;

  std::string git = getGit();
  if (!silent) {
    Logger::message("Downloading", FMT("Package %s/%s%s%s from git repository", p_package.owner.c_str(), BOLD, p_package.repo.c_str(), RESET));
  }

  auto packageFolder = (fs::path)configFolder / "deps" / p_package.owner / p_package.repo;

  if (!fs::is_directory(p_package.owner)) {
    fs::create_directory(p_package.owner);
  }

  auto gitCommand = std::vector<std::string>{};
  gitCommand.push_back(git);
  gitCommand.push_back("clone");
  gitCommand.push_back(FMT("%s/%s/%s", p_package.provider.c_str(), p_package.owner.c_str(), p_package.repo.c_str()));
  gitCommand.push_back(packageFolder);
  gitCommand.push_back("--depth=1");
  gitCommand.push_back("--quiet");
  auto status = os::Driver::run(gitCommand);  

  if (status != EXIT_SUCCESS) {
    throw SNError(Error::PM_ERROR, FMT("Failed to install package %s/%s. See the output above", p_package.owner.c_str(), p_package.repo.c_str()));
  }

  return EXIT_SUCCESS;
}


} // namespace pm
} // namespace snowball
