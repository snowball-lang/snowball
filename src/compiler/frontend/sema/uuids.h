
#ifndef __SNOWBALL_FRONTEND_SEMA_UUIDS_H__
#define __SNOWBALL_FRONTEND_SEMA_UUIDS_H__

static const std::vector<std::string> core_string = {"std", "string"};

// This is a list of allowed UUIDs that can be used in the type checker
// note: They should ALWAYS follow std's library structure
#define ALLOWED_UUIDS std::vector{\
  NamespacePath(core_string),\
  NamespacePath(""),\
  }

#endif // __SNOWBALL_FRONTEND_SEMA_UUIDS_H__
