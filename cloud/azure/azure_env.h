// Copyright (c) 2016-present, Rockset, Inc. All rights reserved.
//

#pragma once

#ifdef USE_AZURE
#include "cloud/cloud_env_impl.h"

namespace ROCKSDB_NAMESPACE {
//
// The Azure environment for rocksdb.

class AzureEnv : public CloudEnvImpl {
 public:
  static Status NewAzureEnv(Env *env, const CloudEnvOptions& env_options,
                            const std::shared_ptr<Logger>& info_log,
                            CloudEnv** cenv);
  static Status NewAzureEnv(Env *env, std::unique_ptr<CloudEnv>* cenv);
  explicit AzureEnv(Env* underlying_env, const CloudEnvOptions& cloud_options);
  static const char *kName() { return kAzure(); }
  const char *Name()  const override { return kAzure(); }
  Status PrepareOptions(const ConfigOptions& options) override;
};

} // namespace

#endif // USE_AZURE
