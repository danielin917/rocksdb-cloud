
// Copyright (c) 2016-present, Rockset, Inc. All rights reserved.

#ifndef ROCKSDB_LITE
#include <iostream>
#include "cloud/azure/azure_env.h"
#include "cloud/cloud_storage_provider_impl.h"
#include "rocksdb/cloud/cloud_storage_provider.h"
#include "logging/logging.h"
#include "rocksdb/convenience.h"


#ifdef USE_AZURE

namespace ROCKSDB_NAMESPACE {

Status AzureEnv::NewAzureEnv(Env *env, const CloudEnvOptions& env_options,
                            const std::shared_ptr<Logger>& info_log,
                            CloudEnv** cenv) {
  assert(cenv);
  Status status;
  *cenv = nullptr;
  if (!env) {
    env = Env::Default();
  }
  CloudEnvOptions copts = env_options;
  copts.info_log = info_log;
  std::unique_ptr<AzureEnv> aenv(new AzureEnv(env, copts));
  ConfigOptions config_options;
  config_options.env = aenv.get();
  assert(aenv);
  status = aenv->PrepareOptions(config_options);
  if (status.ok()) {
    *cenv = aenv.release();
  }
  return Status::OK();
}

Status AzureEnv::NewAzureEnv(Env *env, std::unique_ptr<CloudEnv>* cenv) {
  assert(cenv);
  cenv->reset(new AzureEnv(env, CloudEnvOptions()));
  return Status::OK();
}

AzureEnv::AzureEnv(Env* _underlying_env, const CloudEnvOptions& _cloud_options) :
  CloudEnvImpl(_cloud_options, _underlying_env) {
}

Status AzureEnv::PrepareOptions(const ConfigOptions& options) {
  if (cloud_env_options.storage_provider == nullptr) {
    Status s = CloudStorageProvider::CreateFromString(
      options, CloudStorageProviderImpl::kAzure(), &cloud_env_options.storage_provider);

    if (!s.ok()) {
      return s;
    }
  }
  return CloudEnvImpl::PrepareOptions(options);
}

} // namespace

#endif // USE_AZURE
#endif // ROCKSDB_LITE
